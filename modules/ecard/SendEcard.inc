<?php
/*
 * $RCSfile: AddComment.inc,v $
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Ecard
 * @subpackage UserInterface
 * @author Nico Kaiser <nico@siriux.net>
 */

/**
 * Required classes
 */
GalleryCoreApi::requireOnce('modules/ecard/classes/EcardHelper.class');
 
/**
 * Send photo as eCard
 * 
 * @package Ecard
 * @subpackage UserInterface
 */
class SendEcardController extends GalleryController {

    var $_subject;
    var $_bcc;
    var $_header;
    var $_footer;

    var $_text;
    var $_from;
    var $_fromName;
    var $_to;
    var $_toName;

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
    	global $gallery;
    	$session =& $gallery->getSession();
	$itemId = GalleryUtilities::getRequestVariables('itemId');	
	$redirect = $status = $error = array();

	list ($ret, $hasPermission) = GalleryCoreApi::hasItemPermission($itemId, 'ecard.send');
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (! $hasPermission) {
	    return null;
	}
	
	if (isset($form['action']['send'])) {
	    if (! class_exists('Mail_mime')) {
		GalleryCoreApi::requireOnce('modules/ecard/lib/pear/mime.php');
	    }
	    
	    list ($ret, $config) = GalleryCoreApi::fetchAllPluginParameters('module', 'ecard');
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Validate form */
	    if (!GalleryUtilities::isValidEmailString($form['to'])) {
		$error[] = 'form[error][to][missing]';
	    }
	    if (!GalleryUtilities::isValidEmailString($form['from'])) {
		$error[] = 'form[error][from][missing]';
	    }
	    if (empty($form['text'])) {
		$error[] = 'form[error][text][missing]';
	    }

	    if (empty($error)) {

		/* Get current item */
		list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
				    
		/* Get item path */
		list($ret, $path) = $item->fetchPath();
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		list ($ret, $resize) = EcardHelper::getSmallestResize($itemId);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		list ($ret, $path) = $resize->fetchPath();
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Get pseudo filename and attach image */
		list ($ret, $filename) = GalleryUtilities::getPseudoFileName($item);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$data = array (
		    'from'     => $form['from'],
		    'fromName' => $form['fromName'],
		    'to'       => $form['to'],
		    'toName'   => $form['toName'],
		    'header'   => EcardHelper::replaceKeywords($config['header'], $form),
		    'footer'   => EcardHelper::replaceKeywords($config['footer'], $form),
		    'text'     => $form['text'],
		    'image'    => $filename,
		);
		$data_plain = $data;
		foreach (array_keys($data_plain) as $key) {
		    GalleryUtilities::unsanitizeInputValues($data_plain[$key], false);
		}

		$data['header'] = nl2br($data['header']);
		$data['footer'] = nl2br($data['footer']);
		$data['text'] = nl2br($data['text']);

		$headers = array (
		    'from'    => empty($config['from']) ? $form['from'] : $config['from'],
		    'to'      => $form['to'],
		    'subject' => EcardHelper::replaceKeywords($config['subject'], $form)
		);
		if (!empty($config['bcc'])) {
		    $headers['bcc'] = $config['bcc'];
		}
		foreach (array_keys($headers) as $key) {
		    GalleryUtilities::unsanitizeInputValues($headers[$key], false);
		}

		$message_html = GalleryPlatform::file_get_contents(
		    dirname(__FILE__).'/templates/Message.html');
		$message_html = EcardHelper::replaceKeywords($message_html, $data);
		
		$message_plain = GalleryPlatform::file_get_contents(
		    dirname(__FILE__).'/templates/Message.txt');
		$message_plain = EcardHelper::replaceKeywords($message_plain, $data_plain);
		
		$mime = new Mail_mime("\n");
		$mime->setTXTBody($message_plain);
		
		/* Either add attachment (plain) or add HTML image (html) */
		if ($config['format'] == 'plain') {
		    $mime->addAttachment($path, $item->getMimeType(), $filename);
		} else {
		    $mime->addHTMLImage($path, $item->getMimeType(), $filename);
		    $mime->setHTMLBody($message_html);
		}
		
		$body = $mime->get(array (
		    'html_charset'  => 'UTF-8',
		    'text_charset'  => 'UTF-8',
		    'text_encoding' => '8bit',
		    'head_charset'  => 'UTF-8'
		));
		$tmp = Array ( 'From' => $headers['from'] );
		if ($headers['bcc']) {
			$tmp['BCC'] = $headers['bcc'];
		}
		$hdrs = '';
		foreach ($mime->headers($tmp) as $key => $value) {
		    $hdrs .= $key . ': '.$value."\n";
		}
		$success = GalleryPlatform::mail(
		    $headers['to'], $headers['subject'], $body, $hdrs);
		if (! $success) {
		    return GalleryCoreApi::error(ERROR_UNKNOWN, __FILE__, __LINE__, 
			'Could not send mail to ' . $headers['to']);
		}
		
		/* Put sender data into session */
		$session->put('ecard.from', $form['from']);
		$session->put('ecard.fromName', $form['fromName']);
		
		/* Send the user to a confirmation page, for now */
		$redirect['view'] = 'ecard.Confirmation';
		$redirect['itemId'] = (int)$itemId;
		$status['sent'] = 1;
	    }
	} else if (isset($form['action']['preview'])) {
	    
	    if (!GalleryUtilities::isValidEmailString($form['to'])) {
		$error[] = 'form[error][to][missing]';
	    }
	    if (!GalleryUtilities::isValidEmailString($form['from'])) {
		$error[] = 'form[error][from][missing]';
	    }
	    if (empty($form['text'])) {
		$error[] = 'form[error][text][missing]';
	    }
	    
	    /* Fall through back to the current view */
	} else if (isset($form['action']['cancel'])) {
	    /* Where to go on a cancel?  Back to viewing the item. */
	    $redirect['view'] = 'core.ShowItem';
	    $redirect['itemId'] = (int)$itemId;
	}
	
	/* Prepare our results */
	if (!empty($redirect)) {
	    //$results['return'] = 1;
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'ecard.SendEcard';
	}
	$results['status'] = $status;
	$results['error'] = $error;
	    
	return array(null, $results);
    }
}

/**
 * This view will show an ecard form
 * 
 * @package Ecard
 * @subpackage UserInterface
 */
class SendEcardView extends GalleryView {
    
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$session =& $gallery->getSession();
	
	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $config) = GalleryCoreApi::fetchAllPluginParameters('module', 'ecard');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'SendEcard') {
	    $form['formName'] = 'SendEcard';
	    $form['to'] = '';
	    $form['toName'] = '';
	    $form['from'] = $session->get('ecard.from');
	    $form['fromName'] = $session->get('ecard.fromName');
	    $form['text'] = '';
	} else {
	    foreach (array('to', 'toName', 'from', 'fromName', 'text') as $key) {
		if (empty($form[$key])) {
		    $form[$key] = '';
		}
	    }
	}
	
	$SendEcard = array();
	$SendEcard['itemId'] = $item->getId();
	$SendEcard['item'] = (array)$item;

	list ($ret, $resize) = EcardHelper::getSmallestResize($item->getId());
	if ($ret) {
	     return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$tmp = (array)$resize;
	$tmp['viewInline'] = 1;
	$SendEcard['resize'] = $tmp;

	$SendEcard['subject'] = EcardHelper::replaceKeywords($config['subject'], $form);
	$SendEcard['header'] = $config['bcc'];
	$SendEcard['header'] = EcardHelper::replaceKeywords($config['header'], $form);
	$SendEcard['footer'] = EcardHelper::replaceKeywords($config['footer'], $form);
	
	$template->setVariable('SendEcard', $SendEcard);
	$template->setVariable('controller', 'ecard.SendEcard');
	
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'ecard');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$template->title($module->translate('Send eCard'));
	
	return array(null, array('body' => 'modules/ecard/templates/SendEcard.tpl'));
    }
    
    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'ecard');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	return array(null, $module->translate('Send eCard'));
    }   
}
?>

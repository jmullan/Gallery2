<?php
/*
 * $RCSfile: module.inc,v $
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Ecard
 * @author Nico Kaiser <nico@siriux.net>
 */
 
 /**
 * This controller will handle the setting of Ecard module options
 *
 * @package Ecard
 * @subpackage UserInterface
 */
class AdminEcardController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;
	
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$results = $error = $status = array();
	
	if (isset($form['action']['save'])) {
	    foreach (array('from', 'subject', 'bcc', 'header', 'footer', 'format') as $key) {
		$ret = GalleryCoreApi::setPluginParameter('module', 'ecard',
			    $key, $form[$key]);
		if ($ret) {
		    return array($ret->wrap(__LINE__, __LINE__), null);
		}
	    }
	    
	    $redirect['subView'] = 'ecard.AdminEcard';
	    $status['saved'] = 1;
	} else if (isset($form['action']['reset'])) {
	    $redirect['view'] = 'core.SiteAdmin';
	    $redirect['subView'] = 'ecard.AdminEcard';
	}
	
	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core.SiteAdmin';
	    $results['delegate']['subView'] = 'ecard.AdminEcard';
	}
	$results['status'] = $status;
	$results['error'] = $error;
	
	return array(null, $results);
    }
}

/**
 * This view will prompt for general Gallery settings
 *
 * @package Ecard
 * @subpackage UserInterface
 */
class AdminEcardView extends GalleryView {
        
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	if ($form['formName'] != 'AdminEcard') {
	    $form['formName'] = 'AdminEcard';
	    foreach (array('from', 'subject', 'bcc', 'header', 'footer', 'format') as $key) {
		list ($ret, $form[$key]) =
		    GalleryCoreApi::getPluginParameter('module', 'ecard', $key);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}
	
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'ecard');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$AdminEcard = array(
	    'formatList' => array(
		'plain' => $module->translate('Plain text only'),
		'html'  => $module->translate('HTML')
	));
	
	$template->setVariable('AdminEcard', $AdminEcard);
	$template->setVariable('controller', 'ecard.AdminEcard');
	
	return array(null, array('body' => 'modules/ecard/templates/AdminEcard.tpl'));
    }
}
?>

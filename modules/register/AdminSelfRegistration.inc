<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package SelfRegistration
 * @author Sebastian Eichner <mailsp@sebastian-eichner.de>
 */

/**
 * @package SelfRegistration
 * @subpackage UserInterface
 */
class AdminSelfRegistrationController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	if (isset($form['action']['save'])) {

	    foreach (array('emailconfirmation', 'subject', 'from', 'reallysend') as $key) {
		if (isset($form[$key])) {
		    $ret = GalleryCoreApi::setPluginParameter(
					   'module', 'register', $key, trim($form[$key]));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'register:AdminSelfRegistration';
	    $status['saved'] = 1;
	} else if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'register:AdminSelfRegistration';
	}

	if (!empty($redirect)) {
	    $results['return'] = 1;
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'register:AdminSelfRegistration';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package SelfRegistration
 * @subpackage UserInterface
 */
class AdminSelfRegistrationView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list($ret, $module) = GalleryCoreApi::loadPlugin('module', 'register');
	if ($ret->isError()) 
	    return array($ret->wrap(__FILE__, __LINE__), null);

	/* Load our default values if we didn't just come from this form. */
	if ($form['formName'] != 'AdminSelfRegistration') {
	    foreach (array('emailconfirmation', 'subject', 'from', 'reallysend') as $key) {
		list ($ret, $form[$key]) =
		    GalleryCoreApi::getPluginParameter('module', 'register', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $form['formName'] = 'AdminSelfRegistration';
	}
	
	$selfregistration = array();
	$selfregistration['emailConfirmationList'] = array(
	    'true' => $module->translate('Use confirmation emails'),
	    'false' => $module->translate('Accept without confirmation') );
	$selfregistration['reallySendList'] = array(
	    'true' => $module->translate('Yes'), 'false' => $module->translate('No') );
	$template->setVariable('SelfRegistration', $selfregistration);
	$template->setVariable('controller', 'register:AdminSelfRegistration');

	return array(GalleryStatus::success(),
		     array('body' => 'modules/register/templates/AdminSelfRegistration.tpl'));
    }
}
?>

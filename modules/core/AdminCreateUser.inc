<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the creation of an user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminCreateUserController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$status = array();
	$redirectParams = array();
	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminUsers view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['create'])) {
	    /*
	     * If all the right fields are in place then go ahead and
	     * create the user.
	     */
	    if (!empty($form['userName']) &&
	        !empty($form['email']) &&
	        !empty($form['password1']) &&
	        $form['password1'] == $form['password2']) {
	    
		list ($ret, $user) = GalleryFactory::newInstance('GalleryEntity', 'GalleryUser');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($user)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}
		
		$ret = $user->create($form['userName']);
		if ($ret->isError()) {
		    if (!($ret->getErrorCode() & ERROR_COLLISION)) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    // Set our error status and fall back to the view.
		    GalleryUtilities::putRequestVariable('form.error.userName.exists', 1);
		} else {
		    $user->setEmail($form['email']);
		    $user->setFullName($form['fullName']);
		    $user->setLanguage($form['language']);
		    $user->changePassword($form['password1']);
		
		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Request a redirect to the confirmation screen */
		    $redirectParams['view'] = 'core:SiteAdmin';
		    $redirectParams['subView'] = 'core:AdminUsers';
		    $status['createdUser'] = $form['userName'];
		}
	    } else {
		foreach (array('userName', 'email', 'password1', 'password2') as $key) {
		    if (empty($form[$key])) {
			GalleryUtilities::putRequestVariable('form.error.' . $key . '.missing', 1);
		    }
		}

		if (!empty($form['password1']) &&
		        !empty($form['password2']) &&
		        $form['password1'] != $form['password2']) {
		    GalleryUtilities::putRequestVariable('form.error.password.mismatch', 1);
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	    $results['status'] = $status;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateUser');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for data to create a new user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCreateUserView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	if ($form['formName'] != 'AdminCreateUser') {
	    /* First time around, set our defaults here. */
	    $form['userName'] = '';
	    $form['email'] = '';
	    $form['fullName'] = '';
	    $form['language'] = '';
	}

	/* Set up our language selection list */
	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$languageList = array();
	$languageList[''] = $module->translate('<none>');
	
	$translator =& $gallery->getTranslator();
	$supportedLanguages = $translator->getSupportedLanguages();
	foreach ($supportedLanguages as $language => $countryList) {
	    foreach ($countryList as $country => $languageData) {
		$languageList[$language . '_' . $country] =
		    $languageData['description'];
	    }
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('languageList', $languageList);
	$template->setVariable('controller', 'core:AdminCreateUser');
	list($ret, $html) = $template->render('AdminCreateUser.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), $html);
	}

	return array(GalleryStatus::success(), $html);
    }
}
?>

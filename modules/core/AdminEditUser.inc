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
 * This controller will handle changes made to an user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminEditUserController extends GalleryController {

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
	$error = array();

	$userId = GalleryUtilities::getRequestVariables('userId');
	list ($ret, $user) = $gallery->loadEntitiesById($userId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * We treat anonymous users differently, so see if we're editing the
	 * anonymous user.
	 */
	list ($ret, $anonymousUserId) =
	    $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$isAnonymous = ($userId == $anonymousUserId);

	if (isset($form['action']['cancel'])) {

	    /* Redirect back to the AdminUsers view */
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminUsers';
	    
	} else if (isset($form['action']['undo'])) {

	    /* Redirect back to the same view to reset the form */
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminEditUser';
	    $redirect['userId'] = $userId;
	    
	} else if (isset($form['action']['save'])) {

	    /*
	     * Validate our data before we continue.
	     */
	    
	    /* full name is optional for everybody */

	    /* language is optional for everybody */

	    if (!$isAnonymous) {
		/* email required for non-anonymous */
		if (empty($form['email'])) {
		    $error[] = 'form.error.email.missing';
		}

		if ($form['password1'] != $form['password2']) {
		    $error[] = 'form.error.password.mismatch';
		}
	    }

	    /*
	     * If all the right fields are in place then go ahead and modify
	     * the user.
	     */
	    if (empty($error)) {
		list ($ret, $lockId) = $gallery->acquireWriteLock($user->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		list ($ret, $user) = $user->refresh();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$user->setFullname($form['fullName']);
		if (!$isAnonymous) {
		    $user->setEmail($form['email']);
		    $user->setLanguage($form['language']);
		    if (!empty($form['password1'])) {
			$user->changePassword($form['password1']);
		    }
		}

		$ret = $user->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $gallery->releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Request a redirect to the confirmation screen */
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminUsers';
		$status['modifiedUser'] = $form['userName'];
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'core:AdminEditUser';
	}
	$results['status'] = $status;
	$results['error'] = $error;
	

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show a form to change user options
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminEditUserView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$userId = GalleryUtilities::getRequestVariables('userId');
	list ($ret, $user) = $gallery->loadEntitiesById($userId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the form with user data the first time around. */
	if ($form['formName'] != 'AdminEditUser') {
	    $form['userName'] = $user->getUserName();
	    $form['fullName'] = $user->getFullName();
	    $form['email'] = $user->getEmail();
	    $form['language'] = $user->getLanguage();
	    $form['formName'] = 'AdminEditUser';
	}

	/* Email is not required for the anonymous user */
	list ($ret, $anonymousUserId) =
	    $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$show['email'] = ($userId != $anonymousUserId);
	$show['language'] = ($userId != $anonymousUserId);
	$show['password'] = ($userId != $anonymousUserId);

	if ($show['language']) {
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
		    $languageList[$language . '_' . $country] = $languageData['description'];
		}
	    }
	}

	$AdminEditUser = array();
	$AdminEditUser['show'] = $show;
	$AdminEditUser['user'] = $user->getMemberData();
	$AdminEditUser['languageList'] = $languageList;

	$template->setVariable('AdminEditUser', $AdminEditUser);
	$template->setVariable('controller', 'core:AdminEditUser');
	return array(GalleryStatus::success(), '', 'modules/core/templates/AdminEditUser.tpl');
    }
}
?>

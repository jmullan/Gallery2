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
	$redirectParams = array();

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
	    $redirectParams['view'] = 'core:SiteAdmin';
	    $redirectParams['subView'] = 'core:AdminUsers';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['undo'])) {

	    /* Redirect back to the same view to reset the form */
	    $redirectParams['view'] = 'core:SiteAdmin';
	    $redirectParams['subView'] = 'core:AdminEditUser';
	    $redirectParams['userId'] = $userId;
	    
	} else if (isset($form['action']['save'])) {

	    /*
	     * Validate our data before we continue.
	     */
	    $error = false;
	    /* full name is always mandatory */
	    if (empty($form['fullName'])) {
		GalleryUtilities::putRequestVariable('form.error.fullName.missing', 1);
		$error = true;
	    }

	    /* language is optional for everybody */

	    if (!$isAnonymous) {
		/* email required for non-anonymous */
		if (empty($form['email'])) {
		    GalleryUtilities::putRequestVariable('form.error.email.missing', 1);
		    $error = true;
		}

		if ($form['password1'] != $form['password2']) {
		    GalleryUtilities::putRequestVariable('form.error.password.mismatch', 1);
		    $error = true;
		}
	    }

	    /*
	     * If all the right fields are in place then go ahead and modify
	     * the user.
	     */
	    if (!$error) {
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
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'core:AdminUsers';
		$redirectParams['form.status.modifiedUser'] = $form['userName'];
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
	    }
	}

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
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
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

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('user', $user->getMemberData());
	$template->setVariable('show', $show);
	if ($show['language']) {
	    $template->setVariable('languageList', $languageList);
	}
	$template->setVariable('controller', 'core:AdminEditUser');
	$html = $template->render('AdminEditUser.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

<?php
/*
 * $RCSfile
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
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();
	$form = GalleryUtilities::getFormVariables('form.');

	list ($ret, $user) = $gallery->loadEntitiesById($form['userid']);
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
	$isAnonymous = ($form['userid'] == $anonymousUserId);

	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminUsers view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['undo'])) {

	    /* Reset our form */
	    GalleryUtilities::putRequestVariable('form.fullname', $user->getFullName());
	    GalleryUtilities::putRequestVariable('form.email', $user->getEmail());
	    GalleryUtilities::putRequestVariable('form.language', $user->getLanguage());
	    
	} else if (isset($form['action']['save'])) {

	    /*
	     * If all the right fields are in place then go ahead and
	     * edit the user.
	     */
	    if ($isAnonymous ||
		(!empty($form['username']) &&
		 !empty($form['email']) &&
		 $form['password1'] == $form['password2'])) {
		
		list ($ret, $lockId) = $gallery->acquireWriteLock($user->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		list ($ret, $user) = $user->refresh();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		$user->setFullname($form['fullname']);
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
		$redirectParams['subView'] = 'core:AdminEditUserConfirmation';
		$redirectParams['username'] = $form['username'];
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
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	list ($userid, $formName) =
	    GalleryUtilities::getRequestVariables('userid', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* The 'userid' variable is set the first time we come to this page */
	if (!empty($userid)) {
	    $form['userid'] = $userid;
	}
	
	list ($ret, $user) = $gallery->loadEntitiesById($form['userid']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Email is not required for the anonymous user */
	list ($ret, $anonymousUserId) =
	    $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$isAnonymous = ($form['userid'] == $anonymousUserId);

	if ($formName == 'AdminEditUser') {
	    /* Complain if any required fields are missing */
	    if (empty($form['email'])) {
		if (!$isAnonymous) {
		    $form['error']['email']['missing'] = 1;
		}
	    }
	    
	    if ((isset($form['password1']) && !isset($form['password2'])) ||
		(isset($form['password2']) && !isset($form['password1']))) {
		$form['error']['password2']['mismatch'] = 1;
	    }
	} else {
	    /* First time around, load the form with user data */
	    $form['username'] = $user->getUserName();
	    $form['fullname'] = $user->getFullName();
	    $form['email'] = $user->getEmail();
	    $form['language'] = $user->getLanguage();
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
	$template->setVariable('isAnonymous', $isAnonymous);
	$template->setVariable('languageList', $languageList);
	$template->setVariable('controller', 'core:AdminEditUser');
	$html = $template->render('AdminEditUser.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

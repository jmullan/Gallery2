<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class AdminEditUserController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();
	$form = GalleryUtilities::getFormVariables('form');

	list ($ret, $user) = GalleryUserHelper::fetchUserByUsername($form['username']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * We treat anonymous users differently, so see if we're editting the
	 * anonymous user.
	 */
	list ($ret, $anonymousUserId) =
	    $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	if ($user->getId() == $anonymousUserId) {
	    $isAnonymous = true;
	} else {
	    $isAnonymous = false;
	}

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

		$user->refresh();
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
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminEditUserView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	return array(GalleryStatus::success(), false);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Specify our translation module */
	$ret = $this->_setTranslationModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$username = GalleryUtilities::getRequestVariables('username');
	$form = GalleryUtilities::getFormVariables('form');

	/* The 'username' variable is set the first time we come to the page */
	$firstTime = false;
	if (!empty($username)) {
	    $form['username'] = $username;
	    $firstTime = true;
	}
	
	/* Get our smarty instance */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->template_dir = dirname(__FILE__) . '/templates';

	list ($ret, $user) = GalleryUserHelper::fetchUserByUsername($form['username']);
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		$smarty->assign('username', $form['username']);
		$html = $smarty->fetch('AdminEditUserMissing.tpl');
	    } else {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    /* Email is not required for the anonymous user */
	    list ($ret, $anonymousUserId) =
		$gallery->getModuleParameter('core', 'id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    if ($user->getId() == $anonymousUserId) {
		$isAnonymous = true;
	    } else {
		$isAnonymous = false;
	    }
	    
	    if ($firstTime) {
		/* First time around, load the form with user data */
		$form['fullname'] = $user->getFullName();
		$form['email'] = $user->getEmail();
		$form['language'] = $user->getLanguage();
	    } else {
		/* After that, complain if any required fields are missing */
		
		if (empty($form['email'])) {
		    if (!$isAnonymous) {
			$form['error']['email']['missing'] = 1;
		    }
		}

		if ((isset($form['password1']) && !isset($form['password2'])) ||
		    (isset($form['password2']) && !isset($form['password1']))) {
		    $form['error']['password2']['mismatch'] = 1;
		}
	    }

	    /* Set up our language selection list */
	    list ($ret, $translator) = $gallery->getTranslator();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $languageList = array();
	    $languageList[''] = '<none>';
	    $supportedLanguages = $translator->getSupportedLanguages();
	    foreach ($supportedLanguages as $language => $countryList) {
		foreach ($countryList as $country => $languageData) {
		    $languageList[$language . '_' . $country] =
			$languageData['description'];
		}
	    }

	    /* Render the HTML body */
	    $smarty->assign('form', $form);
	    $smarty->assign('isAnonymous', $isAnonymous);
	    $smarty->assign('languageList', $languageList);
	    $smarty->assign('controller', 'core:AdminEditUser');
	    $html = $smarty->fetch('AdminEditUser.tpl');
	}

	return array(GalleryStatus::success(), $html);
    }
}
?>

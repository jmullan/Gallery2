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

class AdminCreateUserController extends GalleryController {

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

	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminUsers view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['create'])) {
	    /*
	     * If all the right fields are in place then go ahead and
	     * create the user.
	     */
	    if (!empty($form['username']) &&
	        !empty($form['email']) &&
	        !empty($form['password1']) &&
	        $form['password1'] == $form['password2']) {
	    
		list ($ret, $user) = $gallery->newEntity('GalleryUser');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $user->create($form['username']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_COLLISION) {
			/*
			 * Fall through -- the view will let the user know about
			 * the duplication.
			 */
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    $user->setEmail($form['email']);
		    $user->setFullname($form['fullname']);
		    $user->setLanguage($form['language']);
		    $user->changePassword($form['password1']);
		
		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Request a redirect to the confirmation screen */
		    $redirectParams['view'] = 'core:SiteAdmin';
		    $redirectParams['subView'] = 'core:AdminCreateUserConfirmation';
		    $redirectParams['username'] = $form['username'];
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateUser');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminCreateUserView extends GalleryView {

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

	$form = GalleryUtilities::getFormVariables('form');

	if (empty($form['username']) &&
	        empty($form['fullname']) &&
	        empty($form['email']) &&
	        empty($form['language']) &&
	        empty($form['password1']) &&
	        empty($form['password2'])) {
	    
	    /*
	     * Nothing posted -- set our defaults here.
	     */
	    $form['username'] = '';
	    $form['email'] = '';
	    $form['fullname'] = '';
	    $form['language'] = '';
	} else {
	    /*
	     * The form was posted unsuccessfully, so audit the inputs here
	     */
	    $errors = array();
	    foreach (array('username', 'email', 'password1', 'password2') as $key) {
		if (empty($form[$key])) {
		    $form['error'][$key]['missing'] = 1;
		}
	    }

	    if (!empty($form['username'])) {
		list ($ret, $user) = GalleryUserHelper::fetchUserByUsername($form['username']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			/* We're good -- no use by that name */
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    /* A user exists by that name */
		    $form['error']['username']['exists'] = 1;
		}
	    }
		    
	    if (empty($form['error'])) {
		if ($form['password1'] != $form['password2']) {
		    $form['error']['password2']['mismatch'] = 1;
		}
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
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('form', $form);
	$smarty->assign('languageList', $languageList);
	$smarty->assign('controller', 'core:AdminCreateUser');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminCreateUser.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

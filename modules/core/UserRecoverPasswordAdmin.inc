<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
 * @author Jay Rossiter <cryptographite@users.sf.net>
 */

/**
 * This controller will handle the recovery of passwords that have
 * been lost or forgotten by the user.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
 
class UserRecoverPasswordAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$status = array();
	$results = array();
	$error = array();

	$platform =& $gallery->getPlatform();
	$session =& $gallery->getSession();

	$authFile = dirname(__FILE__) . '/../../login.txt';

	$authFromFile = trim(join('', $platform->file($authFile)));

	if ($session->get('core.UserRecoverPasswordAdminAuthKey') != $authFromFile) {
	    /* Just set a flag so we don't continue.  The actual error is handled in the view */
	    $error[] = 'form[error][authString][incorrect]';
	}

	if (empty($error) && isset($form['action']['recover'])) {
	    if (empty($form['password1']) || empty($form['password2'])) {
		$error[] = 'form[error][password][missing]';
	    } else if ($form['password1'] != $form['password2']) {
		$error[] = 'form[error][password][mismatch]';
	    }

	    if (empty($error)) {
		/* 
		 * TODO - We need to be able to support a renamed administrator account
		 * or, possibly, the recovery of any administrator account.
		 */
		list ($ret, $user) = GalleryCoreApi::fetchUserByUsername('admin');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__, 'Unable to load admin user'), null);
		}

		if ($user && $user->getUserName() == 'admin') {
		    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($user->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $user) = $user->refresh();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    $user->changePassword($form['password1']);

		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = GalleryCoreApi::releaseLocks($lockId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $status['passwordRecovered'] = 1;
		    $session->remove('core.UserRecoverPasswordAdminAuthKey');
		} else {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}
	    }
	} else if (isset($form['action']['cancel'])) {
	    $results['redirect']['view'] = 'core.UserAdmin';
	    $results['redirect']['subView'] = 'core.UserRecoverPasswordAdmin';
	    $results['return'] = 1;
	} 
	
	if (empty($error) && !empty($status)) {
	    $results['redirect']['view'] = 'core.UserAdmin';
	    $results['redirect']['subView'] = 'core.UserLogin';
	    $results['return'] = 0;
	} else if (empty($results['return'])) {
	    $results['delegate']['view'] = 'core.UserAdmin';
	    $results['delegate']['subView'] = 'core.UserRecoverPasswordAdmin';
	}
	
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view prompts for login information
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class UserRecoverPasswordAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$error = array();
	$status = array();

	$platform =& $gallery->getPlatform();

	$authFile = dirname(__FILE__) . '/../../login.txt';
	$authFilePath = $platform->realpath(dirname(__FILE__) . '/../../');

	$session =& $gallery->getSession();

	if ($form['formName'] != 'UserRecoverPasswordAdmin') {
	    $form['formName'] = 'UserRecoverPasswordAdmin';

	    /* Don't display the Authorization Incorrect error on first page load */
	    $status['firstLoad'] = 1;

	    /* Generate the auth string on the first visit to this view */
	    $this->_generateAuthString();
	}

	$authString = $session->get('core.UserRecoverPasswordAdminAuthKey');

	if (!$platform->file_exists($authFile)) {
	    $error['authFile']['missing'] = 1;
	} else if (!$platform->is_readable($authFile)) {
	    $error['authFile']['unreadable'] = 1;
	} else {
	    $authStringFromFile = trim(join('', $platform->file($authFile)));
	    if ($authStringFromFile == $authString) {
		$status['authString']['correct'] = 1;
	    } else {
		$error['authString']['incorrect'] = 1;
	    }
	}

	$UserRecoverPasswordAdmin['authFilePath'] = $authFilePath;
	$UserRecoverPasswordAdmin['authString'] = $authString;
	$UserRecoverPasswordAdmin['error'] = $error;
	$UserRecoverPasswordAdmin['status'] = $status;
	$template->setVariable('UserRecoverPasswordAdmin', $UserRecoverPasswordAdmin);
	$template->setVariable('controller', 'core.UserRecoverPasswordAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/UserRecoverPasswordAdmin.tpl'));
    }

    /**
     * Generate the authorization string used for login.txt
     */
    function _generateAuthString() {
	global $gallery;

	$session =& $gallery->getSession();

        for ($len=64, $rand='';
             strlen($rand) < $len;
             $rand .= chr(!mt_rand(0, 2) ? mt_rand(48, 57) :
                          (!mt_rand(0, 1) ? mt_rand(65, 90) :
                           mt_rand(97, 122))));
        $session->put('core.UserRecoverPasswordAdminAuthKey', md5($rand));
    }
}
?>

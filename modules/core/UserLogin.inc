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
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle an user logging in to Gallery
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class UserLoginController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$results = array();
	$error = array();
	if (isset($form['action']['login'])) {

	    if (!empty($form['password']) && !empty($form['username'])) {
		list ($ret, $user) = GalleryCoreApi::fetchUserByUsername($form['username']);
		if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($user != null && $user->isCorrectPassword($form['password'])) {
		    $gallery->setActiveUser($user);

		    $event = GalleryCoreApi::newEvent('Gallery::Login');
		    $event->setEntity($user);
		    list ($ret, $redirect) = GalleryCoreApi::postEvent($event);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    // Redirect if requested by event listener, otherwise return
		    if (!empty($redirect)) {
			$results['redirect'] = array_shift($redirect);
		    } else {
			$results['return'] = 1;
		    }
		} else {
		    $error[] = 'form[error][invalidPassword]';
		}
	    }

	} else if (isset($form['action']['cancel'])) {
	    $results['return'] = 1;
	}

	if (!empty($error)) {
	    $results['delegate']['view'] = 'core:UserAdmin';
	    $results['delegate']['subView'] = 'core:UserLogin';
	}
	$results['status'] = array();
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
class UserLoginView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	if ($form['formName'] == 'UserLogin') {
	    if (empty($form['username'])) {
		$form['error']['username']['missing'] = 1;
	    }

	    if (empty($form['password'])) {
		$form['error']['password']['missing'] = 1;
	    }
	} else {
	    $form['username'] = '';
	    $form['formName'] = 'UserLogin';
	}

	$template->setVariable('controller', 'core:UserLogin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/UserLogin.tpl'));
    }
}
?>

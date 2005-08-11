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
 * @package SelfRegistration
 * @subpackage UserInterface
 * @author Sebastian Eichner <mailsp@sebastian-eichner.de>
 */

/**
 * This controller will handle the confirmation-link that is sent in the confirmation email
 *
 * @package SelfRegistration
 * @subpackage UserInterface
 *
 */
class ConfirmRegistrationController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	GalleryCoreApi::relativeRequireOnce(
	    'modules/register/classes/GalleryPendingUserHelper.class');
	$results = array('status' => array(), 'error' => array());

	/* turn the pending user into a real user */
	list ($username, $regKey) = GalleryUtilities::getRequestVariables('username', 'key');

	list ($ret, $user) = GalleryPendingUserHelper::fetchPendingUserByUsername($username);
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		$results['error'][] = 'form[error][unknownUser]';
	    } else {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    /* verify registration key: */
	    if ($regKey != $user->getRegistrationKey()) {
		$results['error'][] = 'form[error][unknownUser]';
	    } else {
		$ret = GalleryPendingUserHelper::createGalleryUser($user);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	$results['delegate']['view'] = 'core.UserAdmin';
	$results['delegate']['subView'] = 'register.ConfirmRegistration';

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view shows a confirmation that the users account was activated
 *
 * @package Selfregistration
 * @subpackage UserInterface
 */
class ConfirmRegistrationView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	$template->setVariable('controller', 'register.ConfirmRegistration');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/register/templates/ConfirmRegistration.tpl'));
    }
}
?>

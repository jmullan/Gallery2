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
 * This controller will handle an user logging in to Gallery
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class LoginController extends GalleryController {
    
    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$results = array();
	$return = GalleryUtilities::getFormVariables('return.');

	if (isset($form['action']['login'])) {

	    if (!empty($form['password']) && !empty($form['username'])) {
		list ($ret, $user) = GalleryUserHelper::fetchUserByUsername($form['username']);
		if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($user != null && $user->isCorrectPassword($form['password'])) {
		    $session =& $gallery->getSession();
		    $session->put('core.id.activeUser', $user->getId());
		    $redirectParams = $return;
		} else {
		    GalleryUtilities::putRequestVariable('form.error.invalidPassword', 1);
		}
	    }

	} else if (isset($form['action']['cancel'])) {
	    $redirectParams = $return;
	}
	
	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:Login';
	    }
	}

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
class LoginView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	global $gallery;

	$template = $this->_getTemplate();
	$html = $template->render('LoginHead.tpl');
	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;

	$return = GalleryUtilities::getFormVariables('return.');

	if ($form['formName'] == 'Login') {
	    if (empty($form['username'])) {
		$form['error']['username']['missing'] = 1;
	    }

	    if (empty($form['password'])) {
		$form['error']['password']['missing'] = 1;
	    }
	} else {
	    $form['username'] = '';
	    $form['return'] = $return;
	}

	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$template->setVariable('controller', 'core:Login');
	$html = $template->render('Login.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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
     * UserLoginPlugin instances to use when handling this request.  Only used by
     * test code.
     *
     * @var array (pluginId => object UserLoginPlugin) $_plugins
     * @private
     */
    var $_pluginInstances;

    /**
     * Tests can use this method to hardwire a specific set of plugin instances to use.
     * This avoids situations where some of the option instances will do unpredictable
     * things and derail the tests.
     *
     * @param array (pluginId => UserLoginPlugin, ...)
     */
    function setPluginInstances($pluginInstances) {
	$this->_pluginInstances = $pluginInstances;
    }

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$results = array();
	$error = array();
	if (isset($form['action']['login'])) {
	    if (empty($form['username'])) {
		$error[] = 'form[error][username][missing]';
	    }

	    if (empty($form['password'])) {
		$error[] = 'form[error][password][missing]';
	    }

	    if (empty($error)) {
		if (isset($this->_pluginInstances)) {
		    $pluginInstances = $this->_pluginInstances;
		} else {
		    /* Get all the login plugins */
		    list ($ret, $pluginInstances) =
			GalleryCoreApi::getAllFactoryImplementationIds('UserLoginPlugin');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    foreach (array_keys($pluginInstances) as $pluginId) {
			list ($ret, $pluginInstances[$pluginId]) =
			    GalleryCoreApi::newFactoryInstanceById('UserLoginPlugin', $pluginId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}
		    
		/* Let each plugin do its verification */
		foreach ($pluginInstances as $pluginId => $plugin) {
		    list ($ret, $pluginErrors, $continue) = $plugin->handleRequestBeforeLogin($form);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $error = array_merge($error, $pluginErrors);

		    if (!$continue) {
			break;
		    }
		}
	    }

	    if (empty($error)) {
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

		    $session =& $gallery->getSession();
		    $session->regenerate();

		    /* Redirect if requested by event listener, otherwise return */
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

	$UserLogin = array();

	/* Get all the login plugins */
	list ($ret, $allPluginIds) =
	    GalleryCoreApi::getAllFactoryImplementationIds('UserLoginPlugin');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Let each plugin load its template data */
	$UserLogin['plugins'] = array();
	foreach (array_keys($allPluginIds) as $pluginId) {
	    list ($ret, $plugin) =
		GalleryCoreApi::newFactoryInstanceById('UserLoginPlugin', $pluginId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $data['file'], $data['l10Domain']) = $plugin->loadTemplate($template, $form);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $UserLogin['plugins'][] = $data;
	}

	$template->setVariable('UserLogin', $UserLogin);
	$template->setVariable('controller', 'core:UserLogin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/UserLogin.tpl'));
    }
}

class UserLoginPlugin {
    /**
     * Perform any special actions on the login request before we actually
     * try to log in.
     *
     * @param array the form values
     * @return array object GalleryStatus a status code
     *               boolean true/false should we continue trying to log in?
     *               array of error keys
     */
    function handleRequestBeforeLogin(&$form) {
	return array(GalleryStatus::success(), true);
    }

    /**
     * @param object GalleryTemplate the template instance
     * @param array the form values
     * @return array object GalleryStatus a status code
     *               string the path to a template file to include
     *               string localization domain for the template file
     */
    function loadTemplate(&$template, &$form) {
	return array(GalleryStatus::success(), null);
    }
}
?>

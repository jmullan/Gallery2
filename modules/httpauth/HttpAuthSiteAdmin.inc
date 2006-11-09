<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @package HttpAuth
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$ $Date$
 */
class HttpAuthSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret, null);
	}

	$error = $status = array();
	if (isset($form['action']['save'])) {
	    ob_start();
	    if (preg_match($form['authtypePattern'], '') === false) {
		$error[] = 'form[error][authtype][regex][invalid]';
	    }
	    $status['authtypeRegexMessage'] = ob_get_contents();
	    ob_clean();

	    ob_start();
	    if (preg_match($form['usernamePattern'], '') === false) {
		$error[] = 'form[error][username][regex][invalid]';
	    }
	    $status['usernameRegexMessage'] = ob_get_contents();
	    ob_clean();

	    if (!empty($error)) {
		return array(null, array('delegate' => array('view' => 'core.SiteAdmin',
			'subView' => 'httpauth.HttpAuthSiteAdmin'),
		    'error' => $error,
		    'status' => $status));
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'httpauth');
	    if ($ret) {
		return array($ret, null);
	    }

	    foreach (array('httpAuthPlugin', 'authName', 'serverAuthPlugin', 'regexAuthPlugin',
		    'authtypePattern', 'usernamePattern', 'usernameReplace') as $key) {
		$ret = $module->setParameter($key, $form[$key]);
		if ($ret) {
		    return array($ret, null);
		}
	    }

	    $ret = GalleryCoreApi::unregisterFactoryImplementationsByModuleId('httpauth');
	    if ($ret) {
		return array($ret, null);
	    }

	    $ret = $module->performFactoryRegistrations();
	    if ($ret) {
		return array($ret, null);
	    }

	    $status['saved'] = true;
	}

	return array(null, array('redirect' => array('view' => 'core.SiteAdmin',
		'subView' => 'httpauth.HttpAuthSiteAdmin'),
	    'error' => $error,
	    'status' => $status));
    }
}

class HttpAuthSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret, null);
	}

	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'httpauth');
	if ($ret) {
	    return array($ret, null);
	}

	$HttpAuthSiteAdmin = array();
	if ($params['httpAuthPlugin'] && strstr(php_sapi_name(), 'cgi')) {

	    /* Check Authorization HTTP header rewrite rule is enabled, until RewriteApi is ready */
	    list ($ret, $activeRules) = GalleryCoreApi::getPluginParameter('module', 'rewrite',
		'activeRules');
	    if ($ret) {
		return array($ret, null);
	    }
	    $activeRules = unserialize($activeRules);

	    if (!in_array('httpauth', array_keys($activeRules))) {
		$HttpAuthSiteAdmin['rewriteWarning'] = true;
	    }
	}

	/* Load our default values if we didn't just come from this form */
	if ($form['formName'] != 'HttpAuthSiteAdmin') {
	    $form['formName'] = 'HttpAuthSiteAdmin';
	    foreach (array('httpAuthPlugin', 'authName', 'serverAuthPlugin', 'regexAuthPlugin',
		    'authtypePattern', 'usernamePattern', 'usernameReplace') as $key) {
		if (!empty($params[$key])) {
		    $form[$key] = $params[$key];
		}
	    }
	}

	/* Render HTML body */
	$template->setVariable('HttpAuthSiteAdmin', $HttpAuthSiteAdmin);
	$template->setVariable('controller', 'httpauth.HttpAuthSiteAdmin');
	$template->javascript('lib/javascript/BlockToggle.js');

	return array(null, array('body' => 'modules/httpauth/templates/HttpAuthSiteAdmin.tpl'));
    }
}
?>

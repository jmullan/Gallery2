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
 * This controller will handle the setting of several general Gallery options
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCoreController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	$canSave = false;
	if (isset($form['action']['save'])) {
	    /* Verify cookie domain / path */
	    $urlGenerator =& $gallery->getUrlGenerator();
	    $cookiePathValid = false;
	    if (isset($form['cookie']['path'])) {
		/* It should either be empty or a substring of the request-URI */
		if (!empty($form['cookie']['path'])) {
		    $paths['cookie'] = $form['cookie']['path'];
		    $urlComponents = parse_url($urlGenerator->getCurrentUrlDir(true));
		    $paths['standalone'] = $urlComponents['path'];
		    $urlComponents = parse_url($urlGenerator->getCurrentUrlDir(false));
		    $paths['embedded'] = $urlComponents['path'];
		    foreach ($paths as $key => $value) {
			if ($value{strlen($value)-1} != '/') {
			    $value .= '/';
			}
			if ($value{0} != '/') {
			    $value = '/' . $value;
			}
			$paths[$key] = $value;
		    }
		    if (strpos($paths['standalone'], $paths['cookie']) === 0 &&
			strpos($paths['embedded'], $paths['cookie']) === 0) {
			$cookiePathValid = true;
			$form['cookie']['path'] = $paths['cookie'];
		    } else {
			$error[] = 'form[error][cookie][invalidPath]';
		    }
		} else {
		    $form['cookie']['path']= '';
		    $cookiePathValid = true;
		}
	    }
	    $cookieDomainValid = false;
	    if (isset($form['cookie']['domain'])) {
		/* It should either be empty or a substring of the request-host */
		if (!empty($form['cookie']['domain'])) {
		    $cookieDomain = $form['cookie']['domain'];
		    if ($cookieDomain{0} != '.') {
			$cookieDomain = '.' . $cookieDomain;
		    }
		    $urlComponents = parse_url($urlGenerator->getCurrentUrlDir());
		    $currentHost = '.' . $urlComponents['host'];
		    /*
		     * The cookie domain should be a substring of the host and contain an embedded
		     * dot 
		     */
		    if (strpos($currentHost, $cookieDomain) !== false
			    && strpos($cookieDomain, '.', 1)) {
			$cookieDomainValid = true;
			$form['cookie']['domain'] = $cookieDomain;
		    } else {
			$error[] = 'form[error][cookie][invalidDomain]';
		    }
		} else {
		    $form['cookie']['domain'] = '';
		    $cookieDomainValid = true;
		}
	    }

	    if ($cookieDomainValid && $cookiePathValid) {
		$canSave = true;
	    }
	} else if (isset($form['action']['addUploadLocalServerDir'])) {
	    $path = GalleryUtilities::htmlEntityDecode($form['uploadLocalServer']['newDir']);
	    if (empty($path)) {
		$error[] = 'form[error][uploadLocalServer][newDir][missing]';
	    } else {
		$platform = $gallery->getPlatform();
		$splitPath = $platform->splitPath($path);
		if (!preg_match('{[\\/]}', $splitPath[0]) || in_array('..', $splitPath)) {
		    /* Use realpath value if path is relative or has .. */
		    $path = $platform->realpath($path);
		}

		if ($platform->isRestrictedByOpenBaseDir($path)) {
		    $error[] = 'form[error][uploadLocalServer][newDir][restrictedByOpenBaseDir]';
		} else if (!$platform->is_readable($path)) {
		    $error[] = 'form[error][uploadLocalServer][newDir][notReadable]';
		} else if (!$platform->is_dir($path)) {
		    $error[] = 'form[error][uploadLocalServer][newDir][notADirectory]';
		}
	    }

	    if (empty($error)) {
		for ($i = 1; !empty($param['uploadLocalServer.dir.' . $i])
			  && ($param['uploadLocalServer.dir.' . $i] != $path); $i++) { }

		if (empty($param['uploadLocalServer.dir.' . $i])) {
		    $ret = GalleryCoreApi::setPluginParameter(
			'module', 'core', 'uploadLocalServer.dir.' . $i, $path);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['addedDir'] = 1;
		}
		$canSave = true;
		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminCore';
	    }
	} else if (isset($form['action']['removeUploadLocalServerDir'])) {
	    if (!empty($form['uploadLocalServer']['selectedDir'])) {
		for ($i = $form['uploadLocalServer']['selectedDir'] + 1;
			!empty($param['uploadLocalServer.dir.' . $i]); $i++) {
		    $ret = GalleryCoreApi::setPluginParameter('module', 'core',
			'uploadLocalServer.dir.' . ($i - 1), $param['uploadLocalServer.dir.' . $i]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$ret = GalleryCoreApi::removePluginParameter('module', 'core',
							     'uploadLocalServer.dir.' . ($i - 1));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['removedDir'] = 1;
		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminCore';
	    } else {
		$error[] = 'form[error][uploadLocalServer][selectedDir][missing]';
	    }
	} else if (isset($form['action']['emailTest'])) {
	    if (empty($form['emailTest']['to']) ||
		    !GalleryUtilities::isValidEmailString($form['emailTest']['to'])) {
		$error[] = 'form[error][emailTest][invalidTo]';
	    } else {
		list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$canSave = true;
		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminCore';
	    }
	}

	if ($canSave) {
	    foreach (array('permissions.directory',
			   'permissions.file',
			   'exec.expectedStatus',
			   'default.orderBy',
			   'default.orderDirection',
			   'default.layout',
			   'default.theme',
			   'default.language',
			   'language.selector',
			   'session.lifetime',
			   'session.inactivityTimeout',
			   'misc.markup',
			   'misc.login',
			   'smtp.host',
			   'smtp.from',
			   'smtp.username',
			   'cookie.path',
			   'cookie.domain',
			   'lock.system') as $key) {
		list ($outer, $inner) = explode('.', $key);
		if (isset($form[$outer][$inner])) {
		    $ret = GalleryCoreApi::setPluginParameter(
			'module', 'core', $key, $form[$outer][$inner]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    if (isset($form['smtp']['password'])) {
		$ret = GalleryCoreApi::setPluginParameter('module', 'core', 'smtp.password',
							  base64_encode($form['smtp']['password']));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    
	    $status['saved'] = 1;
	    $redirect['view'] = 'core.SiteAdmin';
	    $redirect['subView'] = 'core.AdminCore';
	}

	if (isset($form['action']['emailTest']) && empty($error)) {
	    $gallery->startRecordingDebugSnippet();
	    ob_start();
	    $ret = GalleryCoreApi::sendTemplatedEmail(
		'modules/core/templates/EmailTest.tpl', array(), null,
		$form['emailTest']['to'], $module->translate('Gallery Email Test'));
	    $output = ob_get_contents();
	    ob_end_clean();
	    $debugSnippet = $gallery->stopRecordingDebugSnippet();

	    if ($ret->isError()) {
		$status['emailTestError'] = $ret->getAsHtml();
		$status['emailTestDebug'] = $output . $debugSnippet;
	    } else {
		$status['emailTestSuccess'] = 1;
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core.SiteAdmin';
	    $results['delegate']['subView'] = 'core.AdminCore';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for general Gallery settings
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCoreView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'AdminCore') {
	    /* Load up our form data */
	    foreach (array('permissions.directory',
			   'permissions.file',
			   'exec.expectedStatus',
			   'default.language',
			   'language.selector',
			   'session.lifetime',
			   'session.inactivityTimeout',
			   'misc.markup',
			   'misc.login',
			   'smtp.host',
			   'smtp.from',
			   'smtp.username',
			   'smtp.password',
			   'cookie.path',
			   'cookie.domain',
			   'lock.system') as $key) {

		list ($ret, $value) =
		    GalleryCoreApi::getPluginParameter('module', 'core', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		list ($outer, $inner) = explode('.', $key);
		$form[$outer][$inner] = $value;
	    }
	    $form['formName'] = 'AdminCore';
	    $form['uploadLocalServer']['newDir'] = '';
	    $form['emailTest']['to'] = '';
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the list of legal local server dirs */
	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$localServerDirList = array();
	for ($i = 1; !empty($param['uploadLocalServer.dir.' . $i]); $i++) {
	    $localServerDirList[$i] = $param['uploadLocalServer.dir.' . $i];
	}

	$platform = $gallery->getPlatform();
	$translator =& $gallery->getTranslator();
	$AdminCore = $can = array();

	if ($translator->canTranslate()) {
	    $can['translate'] = true;

	    /* Set up our language selection list */
	    $AdminCore['languageList'] = array('' => $module->translate('&laquo; None &raquo;'));

	    $supportedLanguages = $translator->getSupportedLanguages();
	    foreach ($supportedLanguages as $language => $countryList) {
		foreach ($countryList as $country => $languageData) {
		    $AdminCore['languageList'][$language . '_' . $country] =
			$languageData['description'];
		}
	    }

	    $AdminCore['languageSelectorList'] = array(
		'none' => $module->translate('None'),
		'guest' => $module->translate('Guest User Only'),
		'all' => $module->translate('Everybody')
	    );
	}

	/* Set up our session time lists */
	$sessionTimeLists = array();
	foreach (array(15, 30, 45) as $minutes) {
	    $sessionTimeList[$minutes * 60] =
		$module->translate(array('one' => '%d minute',
					 'many' => '%d minutes',
					 'count' => $minutes,
					 'arg1' => $minutes));
	}
	foreach (array(1, 6, 12) as $hours) {
	    $sessionTimeList[$hours * 3600] =
		$module->translate(array('one' => '%d hour',
					 'many' => '%d hours',
					 'count' => $hours,
					 'arg1' => $hours));
	}
	foreach (array(1, 2, 3, 4, 5, 6) as $days) {
	    $sessionTimeList[$days * 86400] =
		$module->translate(array('one' => '%d day',
					 'many' => '%d days',
					 'count' => $days,
					 'arg1' => $days));
	}
	foreach (array(1, 2, 3) as $weeks) {
	    $sessionTimeList[$weeks * 7 * 86400] =
		$module->translate(array('one' => '%d week',
					 'many' => '%d weeks',
					 'count' => $weeks,
					 'arg1' => $weeks));
	}
	$sessionTimeList[25 * 365 * 86400] = $module->translate('forever');

	if (GalleryUtilities::isA($platform, 'UnixPlatform')) {
	    $can['setPermissions'] = true;

	    /* Set up our permission selection lists */
	    $AdminCore['permissionsDirectoryList'] =
		array('700', '750', '755', '770', '775', '777');
	    $AdminCore['permissionsFileList'] = array('600', '640', '644', '660', '664', '666');
	}

	/* Miscellaneous lists */
	$loginMethod = array('link' => $module->translate('Link to Login Page'),
			     'form' => $module->translate('Form on Sidebar'),
			     'both' => $module->translate('Both'));

	$embeddedMarkupList = array('none' => $module->translate('No Markup'),
				    'bbcode' => $module->translate('BBCode'),
				    'html' => $module->translate('Raw HTML'));

	$lockSystemList = array('database' => $module->translate('Database'),
				'flock' => $module->translate('File'));

	list ($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$AdminCore['can'] = $can;
	$AdminCore['localServerDirList'] = $localServerDirList;
	$AdminCore['sessionTimeList'] = $sessionTimeList;
	$AdminCore['loginMethod'] = $loginMethod;
	$AdminCore['embeddedMarkupList'] = $embeddedMarkupList;
	$AdminCore['lockSystemList'] = $lockSystemList;

	$template->setVariable('controller', 'core.AdminCore');
	$template->setVariable('AdminCore', $AdminCore);
	$template->javascript('lib/javascript/BlockToggle.js');

	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/AdminCore.tpl'));
    }
}
?>

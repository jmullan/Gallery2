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
if (!file_exists(dirname(__FILE__) . '/config.php') ||
	filesize(dirname(__FILE__) . '/config.php') < 10) {
    header("Location: install/");
    return;
}

require_once(dirname(__FILE__) . '/init.php');
if (!defined('G2_EMBED')) {

    /* Initialize Gallery */
    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	_GalleryMain_errorHandler($ret->wrap(__FILE__, __LINE__), null, false);
	return;
    }

    /* Process the request */
    GalleryMain();
}

function GalleryMain($returnHtml=false) {
    global $gallery;

    /* Process the request */
    list($ret, $g2Data) = _GalleryMain($returnHtml);
    if ($ret->isSuccess()) {
	/* Write out our session data */
	$session =& $gallery->getSession();
	$ret = $session->save();
    }

    /* Complete our transaction */
    if ($ret->isSuccess() && $gallery->isStorageInitialized()) {
	$storage =& $gallery->getStorage();
	$ret = $storage->commitTransaction();
    }

    /* Error handling (or redirect info in debug mode) */
    if ($ret->isError() || isset($g2Data['redirectUrl'])) {
	_GalleryMain_errorHandler($ret->wrap(__FILE__, __LINE__), $g2Data);
	$g2Data['isDone'] = true;

	if ($ret->isError() && $gallery->isStorageInitialized()) {
	    /* Nuke our transaction, too */
	    $storage =& $gallery->getStorage();
	    $storage->rollbackTransaction();
	}
    }

    return $g2Data;
}

/**
 * Process our request
 * @return array object GalleryStatus a status code
 *               array[]
 */
function _GalleryMain($returnHtml=false) {
    global $gallery;

    /* Let our url generator process the query string and redirect if suggested */
    $urlGenerator =& $gallery->getUrlGenerator();
    list ($ret, $redirectUrl) = $urlGenerator->parseCurrentUrl();
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }
    if (!empty($redirectUrl)) {
	return array(GalleryStatus::success(), _GalleryMain_doRedirect($redirectUrl));
    }

    /* Figure out the target view/controller */
    list($viewName, $controllerName) = GalleryUtilities::getRequestVariables('view', 'controller');

    if (!$returnHtml && $gallery->getConfig('mode.embed.only') && $viewName != 'core:DownloadItem') {
	/* Lock out direct access when embed-only is set */
	return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
    }

    /* Try renderShortcut for fastest possible response */
    if (!empty($viewName)) {
	list ($ret, $view) = GalleryView::loadView($viewName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $responseComplete) = $view->renderShortcut();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($responseComplete) {
	    /* We're done */
	    return array(GalleryStatus::success(), array('isDone' => true));
	}
    }

    /* Check if core module needs upgrading */
    list ($ret, $core) = GalleryCoreApi::loadPlugin('module', 'core', true);
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }
    $installedVersions = $core->getInstalledVersions();
    if ($installedVersions['core'] != $core->getVersion()) {
	$redirectUrl = $urlGenerator->generateUrl(array('href' => 'upgrade/'));
	return array(GalleryStatus::success(), _GalleryMain_doRedirect($redirectUrl));
    }

    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }

    /* Load and run the appropriate controller */
    $results = array();
    if (!empty($controllerName)) {
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryController.class');
	list ($ret, $controller) = GalleryController::loadController($controllerName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get our form and return variables */
	$form = GalleryUtilities::getFormVariables('form');

	/* Let the controller handle the input */
	list ($ret, $results) = $controller->handleRequest($form);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Check to make sure we got back everything we want */
	if (!isset($results['status']) ||
	    !isset($results['error']) ||
	    (!isset($results['redirect']) && !isset($results['delegate']) && !isset($results['return']))) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					      'Controller results are missing status, ' .
					      'error or (redirect,delegate,return)'),
			 null);
	}

	/* Try to return if the controller instructs it */
	if (!empty($results['return'])) {
	    list ($ret, $navigationLinks) = $urlGenerator->getNavigationLinks(1);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (count($navigationLinks) > 0) {
		/* Go back to the previous navigation point in our history */
		$redirectUrl = $navigationLinks[0]['url'];
	    } else {
		$redirectUrl = GalleryUtilities::getRequestVariables('return');
	    }
	}

	/* Failing that, redirect if so instructed */
	if (empty($redirectUrl) && !empty($results['redirect'])) {
	    /*
	     * If we have a status, store its data in the session and attach it
	     * to the URL.
	     */
	    if (!empty($results['status'])) {
		$session =& $gallery->getSession();
		$results['redirect']['statusId'] = $session->putStatus($results['status']);
	    }

	    $urlToGenerate = $results['redirect'];
	    /* Keep our navId in the URL */
	    $navId = $urlGenerator->getNavigationId();
	    if (!empty($navId)) {
		$urlToGenerate['navId'] = $navId;
	    }
	    $redirectUrl = $urlGenerator->generateUrl($urlToGenerate);
	}

	/* If we have a redirect url.. use it */
	if (!empty($redirectUrl)) {
	    return array(GalleryStatus::success(), _GalleryMain_doRedirect($redirectUrl));
	}

	/* Let the controller specify the next view */
	if (!empty($results['delegate'])) {

	    /* Load any errors into the request */
	    if (!empty($results['error'])) {
		foreach ($results['error'] as $error) {
		    GalleryUtilities::putRequestVariable($error, 1);
		}
	    }

	    /* Save the view name, put the rest into the request so the view can get it */
	    foreach ($results['delegate'] as $key => $value) {
		switch($key) {
		case 'view':
		    $viewName = $value;
		    break;

		default:
		    GalleryUtilities::putRequestVariable($key, $value);
		    break;
		}
	    }
	}
    }

    /* Load and run the appropriate view */
    if (empty($viewName)) {
	$viewName = 'core:ShowItem';
    }

    if (!isset($view)) {
	list ($ret, $view) = GalleryView::loadView($viewName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
    }

    /* Initialize our container for template data */
    $main = array();
    $gallery->setCurrentView($viewName);

    /*
     * If this is an immediate view, it will send its own output directly.  This is
     * used in the situation where we want to send a binary file to the browser.
     */
    if ($view->isImmediate()) {
	$status = isset($results['status']) ? $results['status'] : array();
	$error = isset($results['error']) ? $results['error'] : array();
	$ret = $view->renderImmediate($status, $error);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), array('isDone' => true));
    } else {
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(__FILE__));
	list ($ret, $results) = $view->doLoadTemplate($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($results['redirect'])) {
	    $redirectUrl = $urlGenerator->generateUrl($results['redirect']);
	    return array(GalleryStatus::success(), _GalleryMain_doRedirect($redirectUrl, $template));
	} else {
	    if (isset($results['html'])) {
		$main['html'] = $results['html'];
	    } else if (empty($results['body'])) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
						  'View results are missing body file'), null);
	    } else {
		$main['viewBodyFile'] = $results['body'];
	    }
	    $main['viewL10Domain'] = $view->getL10Domain();
	}
    }

    $ret = _GalleryMain_setupMain($main, $urlGenerator, $installedVersions['gallery']);
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }
    $template->setVariable('main', $main);
    $template->setVariable('l10Domain', 'modules_core');

    if (isset($main['html']) || !$returnHtml) {
	$templatePath = isset($main['html']) ? 'gallery:templates/standalone.tpl'
					     : 'gallery:templates/global.tpl';
	/* Write directly for speed */
	$ret = $template->display($templatePath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), array('isDone' => true));
    } else {
	/* Gather content to return to embedding application */
	list ($ret, $headHtml) = $template->fetch('gallery:templates/embedHead.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $bodyHtml) = $template->fetch('gallery:templates/embedBody.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$data = array('isDone' => false, 'headHtml' => $headHtml, 'bodyHtml' => $bodyHtml);

	if ($template->hasVariable('layout')) {
	    $layout =& $template->getVariableByReference('layout');
	    $data['layoutData'] = $layout;
	    if (isset($layout['show']['sidebar']) && $layout['show']['sidebar'] === false) {
		/*
		 * Render sidebar and return as separate block of content if
		 * embedding app requested no sidebar in G2 content..
		 */
		$layout['show']['sidebar'] = true;
		list ($ret, $data['sidebarHtml']) = $template->fetch('gallery:templates/sidebar.tpl');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}
	return array(GalleryStatus::success(), $data);
    }

    return array(GalleryStatus::success(), array('isDone' => true));
}

function _GalleryMain_setupMain(&$main, $urlGenerator=null, $version=null) {
    global $gallery;
    if (!isset($urlGenerator)) {
	$urlGenerator =& $gallery->getUrlGenerator();
    }

    if ($gallery->getDebug() == 'buffered') {
	$main['debug'] = $gallery->getDebugBuffer();
    }
    if ($gallery->isProfiling('sql')) {
	$storage =& $gallery->getStorage();
	$main['profile'] = $storage->getProfilingHtml();
    }

    list ($ret, $markup) = GalleryCoreApi::getPluginParameter('module', 'core', 'misc.markup');
    if ($ret->isError()) {
	$error = $ret->wrap(__FILE__, __LINE__);
	$markupType = 'none';
    }
    $main['markupType'] = $markup;

    /* Calculate a URI that we can use for the validation link */
    $main['validationUri'] = $urlGenerator->getCurrentUrl();
    $session =& $gallery->getSession();
    if ($session->isUsingCookies()) {
	$main['validationUri'] = $urlGenerator->appendParamsToUrl($main['validationUri'],
						array($session->getKey() => $session->getId()));
    }
    $main['validationUri'] = urlencode($main['validationUri']);

    $translator =& $gallery->getTranslator();
    $main['isRightToLeft'] = $translator->isRightToLeft();

    if (!isset($version)) {
	GalleryCoreApi::relativeRequireOnce('modules/core/module.inc');
	$installedVersions = CoreModule::getInstalledVersions();
	$version = $installedVersions['gallery'];
    }
    $main['gallery']['version'] = $version;

    return isset($error) ? $error : GalleryStatus::success();
}

function _GalleryMain_doRedirect($redirectUrl, $template=null) {
    global $gallery;
    if ($gallery->getDebug() == false || $gallery->getDebug() == 'logged') {
	/*
	 * The URL generator makes HTML 4.01 compliant URLs using
	 * &amp; but we don't want those in our Location: header.
	 */
	$redirectUrl = str_replace('&amp;', '&', $redirectUrl);

	header("Location: $redirectUrl");
	return array('isDone' => true);
    } else {
	return array('isDone' => true, 'redirectUrl' => $redirectUrl, 'template' => $template);
    }
}

function _GalleryMain_errorHandler($error, $g2Data=null, $initOk=true) {
    global $gallery;
    if (!$initOk) {
	/* May not have session or translator.. just dump error to browser. */
	print '<h2>Error</h2>' . $error->getAsHtml(false);
	if ($gallery->getDebug() == 'buffered') {
	    print '<h3>Debug Output</h3><pre>' . $gallery->getDebugBuffer() . '</pre>';
	}
	return;
    }

    if (isset($g2Data['template'])) {
	/* Main processing created a template before error occurred.. */
	$template = $g2Data['template'];
    } else {
	/* Create a template with default theme.. */
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(__FILE__));

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTheme.class');
	list ($ret, $theme) = GalleryTheme::loadTheme();
	if ($ret->isSuccess()) {
	    $templateAdapter =& $gallery->getTemplateAdapter();
	    $templateAdapter->setTheme($theme);
	}
    }

    list ($ret, $isAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
    $isAdmin = $ret->isSuccess() && $isAdmin;
    $template->head('templates/errorHead.tpl', 'modules_core');
    $main = array('isAdmin' => $isAdmin,
		  'error' => array('stackTrace' => $error->getAsHtml($isAdmin)),
		  'viewBodyFile' => 'templates/errorBody.tpl',
		  'viewL10Domain' => 'modules_core');
    _GalleryMain_setupMain($main);

    if (isset($g2Data['redirectUrl'])) {
	/* Redirect in debug mode.. */
	$templatePath = 'gallery:templates/redirect.tpl';
	$main['redirectUrl'] = $g2Data['redirectUrl'];
    } else {
	/* Landing page for errors.. */
	$templatePath = 'gallery:templates/global.tpl';
	$errorCode = $error->getErrorCode();

	if ($errorCode & ERROR_OBSOLETE_DATA) {
	    $main['error']['obsoleteData'] = true;
	}
	if ($errorCode & (ERROR_PERMISSION_DENIED | ERROR_BAD_PARAMETER)) {
	    $main['error']['securityViolation'] = true;
	}
	if ($errorCode & ERROR_STORAGE_FAILURE) {
	    $main['error']['storageFailure'] = true;
	}

	if ($isAdmin) {
	    $main['error']['phpversion'] = phpversion();
	    $main['error']['php_uname'] = php_uname();
	    $main['error']['php_sapi_name'] = php_sapi_name();
	    $main['error']['webserver'] = isset($_SERVER['SERVER_SOFTWARE']) ? $_SERVER['SERVER_SOFTWARE'] : '';
	    $main['error']['browser'] = isset($_SERVER['HTTP_USER_AGENT']) ? $_SERVER['HTTP_USER_AGENT'] : '';
	    if ($gallery->isStorageInitialized()) {
		$storage =& $gallery->getStorage();
		$main['error']['dbType'] = $storage->_impl->getAdoDbType();
		$main['error']['dbVersion'] = @$storage->_impl->getVersion();

		list ($ret, $list) = GalleryCoreApi::getToolkitOperationMimeTypes('thumbnail');
		if ($ret->isSuccess()) {
		    $toolkitList = array();
		    foreach ($list as $tmp) {
			$toolkitList = array_merge($toolkitList, $tmp);
		    }
		    $main['error']['toolkits'] = implode(', ', array_unique($toolkitList));
		}
	    }
	}
    }

    $template->setVariable('main', $main);
    $template->setVariable('l10Domain', 'modules_core');
    GalleryUtilities::putRequestVariable('view', 'error');

    $ret = $template->display($templatePath);
    if ($ret->isError()) {
	/* Smarty failure.. all we can do now is dump the error out to the browser. */
	print '<h2>Error</h2>' . $error->getAsHtml($isAdmin)
	    . '<h3>Smarty Error</h3>' . $ret->getAsHtml($isAdmin);
	if (isset($main['debug'])) {
	    print '<h3>Debug Output</h3><pre>' . $main['debug'] . '</pre>';
	}
    }
}
?>

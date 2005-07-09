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
include(dirname(__FILE__) . '/bootstrap.inc');

/*
 * If they don't have a setup password, we assume that the config.php is
 * empty and this is an initial install.
 */
if (!@$gallery->getConfig('setup.password')) {
    /* May be invalid if a multisite install lost its config.php; galleryBaseUrl unknown */
    header('Location: install/');
    return;
}

if (!GalleryUtilities::isEmbedded()) {
    /* If this is a request for a public data file, give it to the user immediately */
    list ($view, $itemId) = GalleryUtilities::getRequestVariables('view', 'itemId');
    if ($view == 'core.DownloadItem' && !empty($itemId)) {
	/*
	 * Our urls are immutable because they have the serial numbers embedded.
	 * So if the browser presents us with an If-Modified-Since then it has
	 * the latest version of the file already.
	 */
	if (function_exists('getallheaders')) {
	    $headers = GetAllHeaders();
	    if (isset($headers['If-Modified-Since']) || isset($headers['If-modified-since'])) {
		header('HTTP/1.x 304 Not Modified');
		return;
	    }
	}

	/*
	 * Fast download depends on having data.gallery.cache set, so set it now.  If for some
	 * reason we fail, we'll reset it in init.inc (but that's ok).
	 */
	$gallery->setConfig(
	    'data.gallery.cache', $gallery->getConfig('data.gallery.base') . '/cache/');

	$path = GalleryDataCache::getCachePath(
	    array('type' => 'fast-download', 'itemId' => $itemId));
	/* We don't have a platform yet so we have to use the raw file_exists */
	if (file_exists($path)) {
	    include($path);
	    if (GalleryFastDownload()) {
		return;
	    }
	}
    }

    /* Otherwise, proceed with our regular process */
    require_once(dirname(__FILE__) . '/init.inc');
    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	_GalleryMain_errorHandler($ret->wrap(__FILE__, __LINE__), null, false);
	return;
    }

    /* Process the request */
    GalleryMain();
} else {
    require_once(dirname(__FILE__) . '/init.inc');
}

function GalleryMain($embedded=false) {
    global $gallery;

    /* Process the request */
    list($ret, $g2Data) = _GalleryMain($embedded);
    if ($ret->isSuccess()) {
	$gallery->performShutdownActions();

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
    if ($ret->isError()) {
	_GalleryMain_errorHandler($ret->wrap(__FILE__, __LINE__), $g2Data);
	$g2Data['isDone'] = true;

	if ($ret->isError() && $gallery->isStorageInitialized()) {
	    /* Nuke our transaction, too */
	    $storage =& $gallery->getStorage();
	    $storage->rollbackTransaction();
	}
    } else if (isset($g2Data['redirectUrl'])) {
	/* If we're in debug mode, show a redirect page */
	print '<H1> Debug Redirect </H1>';
	print 'Not automatically redirecting you to the next page because we\'re in debug mode<br/>';
	printf('<a href="%s">Continue to the next page</a>', $g2Data['redirectUrl']);
	print '<hr/>';
	print $gallery->getDebugBuffer();
    }

    return $g2Data;
}

/**
 * Process our request
 * @return array object GalleryStatus a status code
 *               array[]
 */
function _GalleryMain($embedded=false) {
    global $gallery;

    $main = array();
    $urlGenerator =& $gallery->getUrlGenerator();
    $urlGenerator->initNavigation();

    /* Figure out the target view/controller */
    list($viewName, $controllerName) = GalleryUtilities::getRequestVariables('view', 'controller');

    if (!$embedded && $gallery->getConfig('mode.embed.only') && $viewName != 'core.DownloadItem') {
	/* Lock out direct access when embed-only is set */
	return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
    }

    /* Check if core module needs upgrading */
    list ($ret, $core) = GalleryCoreApi::loadPlugin('module', 'core', true);
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }
    $installedVersions = $core->getInstalledVersions();
    if ($installedVersions['core'] != $core->getVersion()) {
	$redirectUrl = $urlGenerator->getCurrentUrlDir(true) . 'upgrade/index.php';
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
	    (!isset($results['redirect']) &&
	     !isset($results['delegate']) &&
	     !isset($results['return']))) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					      'Controller results are missing status, ' .
					      'error, (redirect, delegate, return)'),
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
		if (empty($redirectUrl)) {
		    $redirectUrl = GalleryUtilities::getRequestVariables('formUrl');
		}
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
	$viewName = 'core.ShowItem';
    }

    list ($ret, $view) = GalleryView::loadView($viewName);
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }

    /* Initialize our container for template data */
    $gallery->setCurrentView($viewName);

    /*
     * If this is an immediate view, it will send its own output directly.  This is
     * used in the situation where we want to send back data that's not controlled by the
     * layout.  That's usually something that's not user-visible like a binary file.
     */
    $data = array();
    if ($view->isImmediate()) {
	$status = isset($results['status']) ? $results['status'] : array();
	$error = isset($results['error']) ? $results['error'] : array();
	$ret = $view->renderImmediate($status, $error);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$data['isDone'] = true;
    } else {
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(__FILE__));
	list ($ret, $results, $theme) = $view->doLoadTemplate($template, $embedded);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($results['redirect'])) {
	    $redirectUrl = $urlGenerator->generateUrl($results['redirect']);
	    return array(GalleryStatus::success(),
			 _GalleryMain_doRedirect($redirectUrl, $template));
	}

	if (empty($results['body'])) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					      'View results are missing body file'), null);
	}

	$templatePath = $results['body'];
	$template->setVariable('l10Domain', $view->getL10Domain());

	if ($embedded) {
	    list ($ret, $html) = $template->fetch($templatePath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $data = $theme->splitHtml($html);
	    $data['isDone'] = false;
	} else {
	    $ret = $template->display($templatePath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $data['isDone'] = true;
	}
    }

    return array(GalleryStatus::success(), $data);
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

/* TODO: move this out of main.php so that we don't have load it on every page view */
function _GalleryMain_errorHandler($error, $g2Data=null, $initOk=true) {
    global $gallery;
    $failsafe = false;
    if (!$initOk) {
	$failsafe = true;
    }

    if (!$failsafe) {
	list ($ret, $themeId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'default.theme');
	if ($ret->isError()) {
	    $failsafe = true;
	}
    }

    if (!$failsafe) {
	list ($ret, $theme) = GalleryCoreApi::loadPlugin('theme', $themeId);
	if ($ret->isError()) {
	    $failsafe = true;
	}
	$templateAdapter =& $gallery->getTemplateAdapter();
	$templateAdapter->setTheme($theme);
    }

    if (!$failsafe) {
	list ($ret, $view) = GalleryView::loadView('core.ErrorPage');
	if ($ret->isError()) {
	    $failsafe = true;
	}
    }

    if (!$failsafe) {
	$dummyForm = array();
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(__FILE__));
	$view->setError($error);
	list ($ret, $results) = $view->loadTemplate($template, $dummyForm);
	if ($ret->isError()) {
	    $failsafe = true;
	}

	$t =& $template->getVariableByReference('theme');
	$t['errorTemplate'] = $results['body'];
    }

    if (!$failsafe) {
	$template->setVariable('l10Domain', 'modules_core');
	list ($ret, $templatePath) = $theme->showErrorPage($template);
	if ($ret->isError()) {
	    $failsafe = true;
	}
    }

    if (!$failsafe) {
	$template->setVariable('l10Domain', 'themes_' . $themeId);
	$ret = $template->display("themes/$themeId/templates/$templatePath");
	if ($ret->isError()) {
	    $failsafe = true;
	}
    }

    if ($failsafe) {
	/* Some kind of catastrophic failure.  Just dump the error out to the browser. */
	print '<h2>Error</h2>' . $error->getAsHtml(false);
	if ($gallery->getDebug() == 'buffered') {
	    print '<h3>Debug Output</h3><pre>' . $gallery->getDebugBuffer() . '</pre>';
	}
	return;
    }
}
?>

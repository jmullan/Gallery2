<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
	$ret = $ret->wrap(__FILE__, __LINE__);
	print $ret->getAsHtml();
	return;
    }

    /* Process the request */
    GalleryMain();
}

function GalleryMain($returnHtml=false) {
    global $gallery;

    /* Go! */
    list($ret, $g2Data) = _GalleryMain($returnHtml);

    /* Save our session */
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

    /*
     * If we get an error at this level, we can't rely on smarty so all we can do is
     * dump the error out to the browser.
     */
    if ($ret->isError()) {
	$ret = $ret->wrap(__FILE__, __LINE__);
	print $ret->getAsHtml();

	if ($gallery->getDebug() == 'buffered') {
	    print '<pre>';
	    print $gallery->getDebugBuffer();
	    print '</pre>';
	}
	$g2Data['isDone'] = true;

	/* Nuke our transaction, too */
	$storage =& $gallery->getStorage();
	if (isset($storage)) {
	    $storage->rollbackTransaction();
	}
    }

    return $g2Data;
}

function _GalleryMain($returnHtml=false) {
    global $gallery;
    
    /* Let our url generator process the query string */
    $urlGenerator =& $gallery->getUrlGenerator();
    list ($ret, $redirectUrl) = $urlGenerator->parseCurrentUrl();
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }

    list ($ret, $core) = GalleryCoreApi::loadPlugin('module', 'core', true);
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }

    $installedVersions = $core->getInstalledVersions();
    if ($installedVersions['core'] != $core->getVersion()) {
	header(sprintf("Location: %s",
		       $urlGenerator->generateUrl(array('href' => 'upgrade/'))));
	return array(GalleryStatus::success(), array('isDone' => true));
    }
    
    /* Figure out the target module/controller */
    list($viewName, $controllerName) = GalleryUtilities::getRequestVariables('view', 'controller');

    if (!$returnHtml && $gallery->getConfig('mode.embed.only') && $viewName != 'core:DownloadItem') {
	return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
    }

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
	    // We're done
	    return array(GalleryStatus::success(), array('isDone' => true));
	}
    }

    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return array($ret->wrap(__FILE__, __LINE__), null);
    }
    
    /* Initialize our container for template data */
    $main = array();
    
    /* If the URL generator suggested that we redirect, then do so */
    if (!empty($redirectUrl)) {
	if ($gallery->getDebug() == false) {
	    /*
	     * The URL generator makes HTML 4.01 compliant URLs using
	     * &amp; but we don't want those in our Location: header.
	     */
	    $redirectUrl = str_replace('&amp;', '&', $redirectUrl);
	    
	    header("Location: $redirectUrl");
	    return array(GalleryStatus::success(), array('isDone' => true));
	} else {
	    $main['redirectUrl'] = $redirectUrl;
	}
    }

    /* Load and run the appropriate controller */
    $results = array();
    if (empty($redirectUrl) && !empty($controllerName)) {
	require_once(dirname(__FILE__) . '/modules/core/classes/GalleryController.class');
	list ($ret, $controller) = GalleryController::loadController($controllerName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get our form and return variables */
	$form = GalleryUtilities::getFormVariables('form');

	/* Let the controller handle the input */
	list ($ret, $results) = $controller->handleRequest($form);
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_OBSOLETE_DATA) {
		/*
		 * Treat this as if they redirected to the ObsoleteDataError view.  Store the error code in
		 * our status, so that it will persist across the redirect.  Errors won't persist.
		 */
		$results['status'] = array('retAsHtml' => $ret->getAsHtml());
		$results['error'] = array();
		$results['delegate'] = array('view' => 'core:ObsoleteDataError');
	    } else {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Check to make sure we got back everything we want */
	if (!isset($results['status']) ||
	    !isset($results['error']) ||
	    (!isset($results['redirect']) && !isset($results['delegate']) && !isset($results['return']))) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					      'Controller results are missing status, ' .
					      'error or (redirect,delegate)'),
			 null);
	}

	/* Try to return if the controller instructs it */
	$redirectUrl = null;
	if (!empty($results['return'])) {
	    list ($ret, $navigationLinks) = $urlGenerator->getNavigationLinks(1);
	    if (count($navigationLinks) > 0) {
		/* Go back to the previous navigation point in our history */
		$redirectUrl = $navigationLinks[0]['url'];
	    } else {
		$redirectUrl = GalleryUtilities::getRequestVariables('return');
	    }
	}

	/* Failing that, redirect if so instructed */
	if (empty($redirectUrl) && !empty($results['redirect'])) {
	    $urlGenerator =& $gallery->getUrlGenerator();

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
	
	/* If we have a redirect url .. use it */ 
	if (!empty($redirectUrl)) {
	    if ($gallery->getDebug() == false || $gallery->getDebug() == 'logged') {
		/*
		 * The URL generator makes HTML 4.01 compliant URLs using
		 * &amp; but we don't want those in our Location: header.
		 */
		$redirectUrl = str_replace('&amp;', '&', $redirectUrl);
		
		header("Location: $redirectUrl");
		return array(GalleryStatus::success(), array('isDone' => true));
	    } else {
		$main['redirectUrl'] = $redirectUrl;
	    }
	}
	
	/* Let the controller specify the next view */
	if (!empty($results['delegate'])) {

	    /* Load any errors into the request */
	    if (!empty($results['error'])) {
		for ($i = 0; $i < sizeof($results['error']); $i++) {
		    GalleryUtilities::putRequestVariable($results['error'][$i], 1);
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

    $showGlobal = true;
    if (empty($redirectUrl)) {

	/* Load and run the appropriate view */
	if (empty($viewName)) {
	    $viewName = 'core:ShowItem';
	}
    
	list ($ret, $view) = GalleryView::loadView($viewName);
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_BAD_PARAMETER) {
		list ($ret, $view) = GalleryView::loadView('core:SecurityViolation');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    } else {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

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
		require_once(dirname(__FILE__) . '/modules/core/classes/GalleryTemplate.class');
		$template = new GalleryTemplate(dirname(__FILE__));
		
		$main['error'] = $ret->getAsHtml();
	    } else {
		$showGlobal = false;
	    }
	} else {
            GalleryCoreApi::requireOnce(dirname(__FILE__) .
					'/modules/core/classes/GalleryTemplate.class');
	    $template = new GalleryTemplate(dirname(__FILE__));
	    list ($ret, $results) = $view->doLoadTemplate($template);
	    if ($ret->isError()) {
		$main['error'] = $ret->getAsHtml();
	    } else {
		if (isset($results['redirect'])) {
		    $redirectUrl = $urlGenerator->generateUrl($results['redirect']);
		    if ($gallery->getDebug() == false) {
			/*
			 * The URL generator makes HTML 4.01 compliant URLs using
			 * &amp; but we don't want those in our Location: header.
			 */
			$redirectUrl = str_replace('&amp;', '&', $redirectUrl);
			
			header("Location: $redirectUrl");
			return array(GalleryStatus::success(), array('isDone' => true));
		    } else {
			$main['redirectUrl'] = $redirectUrl;
		    }
		} else {
		    if (isset($results['html'])) {
			$main['html'] = $results['html'];
		    }

		    if (isset($results['head'])) {
			$main['viewHeadFile'] = $results['head'];
		    } else {
			$main['viewHeadFile'] = '';
		    }

		    if (isset($results['body'])) {
			$main['viewBodyFile'] = $results['body'];
		    } else {
			$main['viewBodyFile'] = '';
		    }
		    $main['viewL10Domain'] = $view->getL10Domain();
		}
	    }
	}
	
    } else {
	/* Set the default theme for the redirect page */
	require_once(dirname(__FILE__) . '/modules/core/classes/GalleryTheme.class');
	list ($ret, $theme) = GalleryTheme::loadTheme();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	require_once(dirname(__FILE__) . '/modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(__FILE__));

	/* Pass the theme to the template adapter */
	$templateAdapter =& $gallery->getTemplateAdapter();
	$templateAdapter->setTheme($theme);
    }

    if ($showGlobal) {
	/* If we're debugging, gather up our debug info also */
	if ($gallery->getDebug()) {
	    if ($gallery->getDebug() == 'buffered') {
		$main['debug'] = $gallery->getDebugBuffer();
	    }
	}

	if ($gallery->isProfiling('sql')) {
	    $storage =& $gallery->getStorage();
	    $main['profile'] = $storage->getProfilingHtml();
	}

	list ($ret, $markup) = GalleryCoreApi::getPluginParameter('module', 'core', 'misc.markup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$main['markupType'] = $markup;

	/* Calculate a URI that we can use for the validation link */
	$main['validationUri'] = $urlGenerator->getCurrentUrl();
	$session =& $gallery->getSession();
	if ($session->isUsingCookies()) {
	    $main['validationUri'] =
		$urlGenerator->appendParamsToUrl($main['validationUri'],
						 array($session->getKey() => $session->getId()));
	}
	$main['validationUri'] = urlencode($main['validationUri']);

	$main['gallery']['version'] = $installedVersions['gallery'];
	$template->setVariable('main', $main);
	$template->setVariable('l10Domain', 'modules_core');

	if (isset($main['redirectUrl'])) {
	    $templatePath = 'gallery:templates/redirect.tpl';
	} else if (isset($main['error'])) {
	    $templatePath = 'gallery:templates/error.tpl';
	} else if (isset($main['html'])) {
	    $templatePath = 'gallery:templates/standalone.tpl';
	}

	if (isset($templatePath) || !$returnHtml) {
	    if (!isset($templatePath)) {
		$templatePath = 'gallery:templates/global.tpl';
	    }
	    /* Write directly for speed */
	    $ret = $template->display($templatePath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    return array(GalleryStatus::success(), array('isDone' => true));
	} else {
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
		$data['layout'] = $layout;
		if (isset($layout['show']['sidebar']) && $layout['show']['sidebar'] === false) {
		    // Render sidebar and return as separate block of content if
		    // embedding app requested no sidebar in G2 content..
		    $layout['show']['sidebar'] = true;
		    list ($ret, $data['sidebarHtml']) =
			$template->fetch('gallery:templates/sidebar.tpl');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    return array(GalleryStatus::success(), $data);
	}
    }

    return array(GalleryStatus::success(), array('isDone' => true));
}
?>

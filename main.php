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

/* Go! */
$ret = GalleryMain(microtime());

/* Save our session */
if ($ret->isSuccess()) {
    /* Write out our session data */
    $session =& $gallery->getSession();
    $ret = $session->save();
}

/* Complete our transaction */
if ($ret->isSuccess()) {
    $ret = $gallery->commitTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
}

/*
 * If we get an at this level, we can't rely on smarty so all we can do is dump
 * the error out to the browser.
 */
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();

    if ($gallery->getDebug() == 'buffered') {
	print '<pre>';
	print $gallery->getDebugBuffer();
	print '</pre>';
    }

    /* Nuke our transaction, too */
    $gallery->rollbackTransaction();
    return;
}

function GalleryMain($startTime) {

    /* Initialize Gallery */
    require_once(dirname(__FILE__) . '/init.php');
    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Get the global gallery object.  We can't just declare "global $gallery"
     * at the top of this function because the variable isn't defined until we
     * call GalleryInitFirstPass()
     */

    /**
     * The all mighty global Gallery object
     *
     * @global Gallery $gallery
     */
    $gallery =& $GLOBALS['gallery'];
    GalleryProfiler::start('main.GalleryMain', $startTime);
    GalleryProfiler::start('init.GalleryInitFirstPass', $startTime);
    GalleryProfiler::stop('init.GalleryInitFirstPass');

    /* Init our storage */
    $ret = GalleryInitStorage();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Start our transaction */
    $ret = $gallery->beginTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Do the second pass of initialization */
    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    
    /*
     * Specify the base URL to the Gallery.  In standalone mode this will be the
     * empty string (since everything is relative to main.php).  But when we're
     * embedded, we need to put in the relative path from the outer app to the
     * Gallery directory (eg for PostNuke it might be 'modules/gallery')
     */
    $gallery->setConfig('url.gallery.base', '');

    /* Configure out url Generator for standalone mode. */
    $urlGenerator = new GalleryUrlGenerator($gallery->getConfig('url.gallery.base'),
					    'main.php');
    $gallery->setUrlGenerator($urlGenerator);

    /* Figure out the target module/controller */
    list($viewName, $controllerName) = GalleryUtilities::getRequestVariables('view', 'controller');

    /* Load and run the appropriate controller */
    $main = array();
    if (!empty($controllerName)) {
	list ($ret, $controller) = GalleryController::loadController($controllerName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Get our form and return variables */
	$form = GalleryUtilities::getFormVariables('form.');

	/* Let the controller handle the input */
	list ($ret, $results) = $controller->handleRequest($form);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Check to make sure we got back everything we want */
	if (!isset($results['status']) ||
	    !isset($results['error']) ||
	    (!isset($results['redirect']) && !isset($results['delegate']))) {
	    $gallery->debug("Controller results are missing status, error or (redirect,delegate)");
	    $gallery->debug_r($results);
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
	}

	/* Try to return if the controller instructs it */
	$redirectUrl = null;
	if (!empty($results['return'])) {
	    $redirectUrl = GalleryUtilities::getRequestVariables('return');
	}

	/* Failing that, redirect if so instructed */
	if (empty($redirectUrl) && !empty($results['redirect'])) {
	    $urlGenerator = $gallery->getUrlGenerator();

	    /*
	     * If we have a status, store its data in the session and attach it
	     * to the URL.
	     */
	    if (!empty($results['status'])) {
		$session =& $gallery->getSession();
		$results['redirect']['statusId'] = $session->putStatus($results['status']);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	    
	    $redirectUrl = $urlGenerator->generateUrl($results['redirect']);
	}
	
	/* If we have a redirect url .. use it */ 
	if (!empty($redirectUrl)) {
	    if ($gallery->getDebug() == false) {
		/*
		 * The URL generator makes HTML 4.01 compliant URLs using
		 * &amp; but we don't want those in our Location: header.
		 */
		$redirectUrl = str_replace('&amp;', '&', $redirectUrl);
		
		header("Location: $redirectUrl");
		return GalleryStatus::success();
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

    $template = new GalleryTemplate($gallery->getConfig('code.gallery.base') . 'templates/');
    
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
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    } else {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	/*
	 * If this is an immediate view, it will send its own output directly.  This is
	 * used in the situation where we want to send a binary file to the browser.
	 */
	if ($view->isImmediate()) {
	    $ret = $view->renderImmediate();
	    if ($ret->isError()) {
		$main['error'] = $ret->getAsHtml();
	    } else {
		$showGlobal = false;
	    }
	} else {
	    list($ret, $main['viewHeadFile'], $main['viewBodyFile']) = $view->doLoadTemplate($template);
	    if ($ret->isError()) {
		$main['error'] = $ret->getAsHtml();
	    }
	    $main['viewL10Domain'] = $view->getL10Domain();
	}
    } else {
	/* Set the default theme for the redirect page */
	list ($ret, $theme) = GalleryTheme::loadTheme();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

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

	if ($gallery->isProfiling()) {
	    GalleryProfiler::stop('main.GalleryMain');
	    $main['profile'] = GalleryProfiler::getProfile();
	}

	$main['gallery']['version'] = '2';
	$template->setVariable('main', $main);
	$template->setVariable('l10Domain', 'modules_core');

	if (isset($main['redirectUrl'])) {
	    list($ret, $html) = $template->render('redirect.tpl');
	} else if (isset($main['error'])) {
	    list($ret, $html) = $template->render('error.tpl');
	} else {
	    list($ret, $html) = $template->render('global.tpl');
	}
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	print $html;
    }

    return GalleryStatus::success();
}
?>

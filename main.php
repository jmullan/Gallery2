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

if (!file_exists(dirname(__FILE__) . '/config.php')) {
    header("Location: install/");
    return;
}

/* Go! */
$ret = GalleryMain();

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

function GalleryMain() {

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
     *
     * @global Gallery $gallery
     */
    $gallery =& $GLOBALS['gallery'];

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

    /* Configure our url Generator for standalone mode. */
    $urlGenerator = new GalleryUrlGenerator('main.php');
    $gallery->setUrlGenerator($urlGenerator);

    /* Do the second pass of initialization */
    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Initialize our container for template data */
    $main = array();
    
    /* Let our url generator process the query string */
    list ($ret, $redirectUrl) = $urlGenerator->parseCurrentUrl();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* If the URL generator suggested that we redirect, then do so */
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

    /* Figure out the target module/controller */
    list($viewName, $controllerName) = GalleryUtilities::getRequestVariables('view', 'controller');

    /* Load and run the appropriate controller */
    $results = array();
    if (empty($redirectUrl) && !empty($controllerName)) {
	require_once(dirname(__FILE__) . '/modules/core/classes/GalleryController.class');
	list ($ret, $controller) = GalleryController::loadController($controllerName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Get our form and return variables */
	$form = GalleryUtilities::getFormVariables('form');

	/* Let the controller handle the input */
	list ($ret, $results) = $controller->handleRequest($form);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Check to make sure we got back everything we want */
	if (!isset($results['status']) ||
	    !isset($results['error']) ||
	    (!isset($results['redirect']) && !isset($results['delegate']))) {
	    $gallery->debug_r($results);
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					"Controller results are missing status, error or (redirect,delegate)");
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
	    if ($gallery->getDebug() == false || $gallery->getDebug() == 'logged') {
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
	    require_once(dirname(__FILE__) . '/modules/core/classes/GalleryTemplate.class');
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
			return GalleryStatus::success();
		    } else {
			$main['redirectUrl'] = $redirectUrl;
		    }
		} else {
		    if (isset($results['main'])) {
			$main['viewMainFile'] = $results['main'];
		    }
		    if (isset($results['onLoad'])) {
			$main['onLoad'] = $results['onLoad'];
		    }
		    if (isset($results['onUnload'])) {
			$main['onUnload'] = $results['onUnload'];
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
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
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


	list ($ret, $markup) = GalleryCoreApi::getPluginParameter('module', 'core', 'misc.markup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$main['markupType'] = $markup;

	/* Calculate a URI that we can use for the validation link */
	$main['validationUri'] = $urlGenerator->getCurrentUrl();
	$session =& $gallery->getSession();
	$sessionDescriptor = $session->getSessionDescriptor();
	$main['validationUri'] =
	    urlencode($urlGenerator->appendParamsToUrl($urlGenerator->getCurrentUrl(),
						       array($sessionDescriptor[0] => $sessionDescriptor[1])));

	$main['gallery']['version'] = '2';
	$template->setVariable('main', $main);
	$template->setVariable('l10Domain', 'modules_core');

	/* TODO: consider switching to using $template->display() for speed */
	if (isset($main['redirectUrl'])) {
	    list ($ret, $html) = $template->fetch('gallery:templates/redirect.tpl');
	} else if (isset($main['error'])) {
	    list ($ret, $html) = $template->fetch('gallery:templates/error.tpl');
	} else {
	    list ($ret, $html) = $template->fetch('gallery:templates/global.tpl');
	}
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	print $html;
    }

    return GalleryStatus::success();
}
?>

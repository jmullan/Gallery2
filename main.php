<?php
/*
 * $RCSfile
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

$ret = GalleryMain(microtime());
if ($ret->isError()) {

    /*
     * If we get an error back up at this level, we can't rely on smarty so all
     * we can do is dump the error out to the browser.
     */
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();

    if ($gallery->getDebug() == 'buffered') {
	print "<pre>";
	print $gallery->getDebugBuffer();
	print "</pre>";
    }
    return;
}

function GalleryMain($startTime) {

    /* Initialize Gallery */
    require_once(dirname(__FILE__) . '/init.php');
    $ret = GalleryInit();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Get the global gallery object.  We can't just declare "global $gallery"
     * at the top of this function because the variable isn't defined until we
     * call GalleryInit()
     */
    $gallery =& $GLOBALS['gallery'];
    GalleryProfiler::start('GalleryMain', $startTime);
    GalleryProfiler::start('GalleryInit', $startTime);
    GalleryProfiler::stop('GalleryInit');
    
    /*
     * Specify the base URL to the Gallery.  In standalone mode this will be the
     * empty string (since everything is relative to main.php).  But when we're
     * embedded, we need to put in the relative path from the outer app to the
     * Gallery directory (eg for PostNuke it might be 'modules/gallery')
     */
    $gallery->setConfig('url.gallery.base', '');

    /*
     * Create, configure and register our template adapter.
     */
    $templateAdapter = new GalleryTemplateAdapter();
    $templateAdapter->setBaseUrl($gallery->getConfig('url.gallery.base') .
				 'main.php');
    $gallery->setTemplateAdapter($templateAdapter);

    /* Figure out the target module/controller */
    list($viewName, $controllerName) =
	GalleryUtilities::getRequestVariables('view', 'controller');

    /* Load and run the appropriate controller */
    if (!empty($controllerName)) {
	list ($ret, $controller) = GalleryController::loadController($controllerName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Let the controller handle the input */
	list ($ret, $results) = $controller->handleRequest();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	/* Redirect, if so instructed */
	if (!empty($results['redirect'])) {
	    header("Location: $results[redirect]");
	    print "DEBUG! Redirect to: <a href=\"$results[redirect]\">$results[redirect]</a>";
	    return GalleryStatus::success();
	}
	
	/* Let the controller specify the next view */
	if (!empty($results['view'])) {
	    $viewName = $results['view'];
	}
    }

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
     * Otherwise, we're rendering in buffered mode and are expecting to receive 
     * HTML head and HTML body content.
     */
    $showGlobal = true;
    if ($view->isImmediate()) {
	$ret = $view->renderImmediate();
	if ($ret->isError()) {
	    $master['view']['head'] = '';
	    $master['view']['body'] = $ret->getAsHtml();
	} else {
	    $showGlobal = false;
	}
    } else {
	GalleryProfiler::start('GalleryView::renderHeadAndBody');

	list ($ret, $master['view']) = $view->renderHeadAndBody();
	if ($ret->isError()) {
	    $master['error'] = $ret->getAsHtml();
	}
	GalleryProfiler::stop('GalleryView::renderHeadAndBody');
    }

    if ($showGlobal) {

	/* If we're debugging, gather up our debug info also */
	if ($gallery->getDebug()) {
	    if ($gallery->getDebug() == 'buffered') {
		$master['debug'] = $gallery->getDebugBuffer();
	    }
	} 

	$template = new GalleryTemplate('modules', 'core',
            $gallery->getConfig('code.gallery.base') . 'templates/');

	if ($gallery->isProfiling()) {
	    GalleryProfiler::stop('GalleryMain');
	    $master['profile'] = GalleryProfiler::getProfile();
	}

	$galleryData['version'] = '2';

	$template->setVariable('master', $master);
	$template->setVariable('gallery', $galleryData);
	print $template->render('global.tpl');
    }

    return GalleryStatus::success();
}
?>

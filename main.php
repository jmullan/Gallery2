<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

$ret = GalleryMain();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

function GalleryMain() {
    /* Prepare a spot to hold all our data for the global template */
    $master = array();
    list($master['profile']['start_usecs'],
	 $master['profile']['start_secs']) = explode(" ", microtime());

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

    /* Figure out the target module/controller */
    list($viewName, $controllerName) =
	GalleryUtilities::getRequestVariables('view', 'controller');

    /* Load and run the appropriate controller */
    if (!empty($controllerName)) {
	ereg('^([[:alnum:]]+):([[:alnum:]]+)$', $controllerName, $regs);
	if (sizeof($regs) == 3) {
	    $module = $regs[1];
	    $class = $regs[2];

	    require_once($gallery->getConfig('code.gallery.modules') .
			 $module . '/' . $class . '.inc');
	    $controllerClassName = $class . 'Controller';
	    $controller = new $controllerClassName;
    
	    /* Let the controller handle the input */
	    $ret = $controller->handleRequest();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	} else {
	    $viewName = 'core:SecurityViolation';
	}
    }

    /* Load and run the appropriate view */
    if (empty($viewName)) {
	$module = 'core';
	$class = 'ShowItem';
    } else {
	ereg('^([[:alnum:]]+):([[:alnum:]]+)$', $viewName, $regs);
	if (sizeof($regs) != 3) {
	    $module = 'core';
	    $class = 'SecurityViolation';
	} else {
	    $module = $regs[1];
	    $class = $regs[2];
	}
    }

    /*
     * Specify the base URL to the Gallery.  In standalone mode this will be the
     * empty string (since everything is relative to main.php).  But when we're
     * embedded, we need to put in the relative path from the outer app to the
     * Gallery directory (eg for PostNuke it might be 'modules/gallery')
     */
    $gallery->setConfig('url.gallery.base', '');

    require_once($gallery->getConfig('code.gallery.modules') .
		 $module . '/' . $class . '.inc');
    $viewClassName = $class . 'View';
    $view = new $viewClassName();
    
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
	list ($ret, $master['view']) = $view->fetchHeadAndBody();
	if ($ret->isError()) {
	    $master['error'] = $ret->getAsHtml();
	}
    }

    if ($showGlobal) {
	/* If we're debugging, gather up our debug and profiling info */
	if ($gallery->getDebug()) {
	    list($master['profile']['stop_usecs'],
		 $master['profile']['stop_secs']) = explode(" ", microtime());
    
	    $master['profile']['elapsed'] =
		($master['profile']['stop_secs'] - $master['profile']['start_secs']) +
		($master['profile']['stop_usecs'] - $master['profile']['start_usecs']);

	    if ($gallery->getDebug() == 'buffered') {
		$master['debug'] = $gallery->getDebugBuffer();
	    }
	}

	/* Display the global output */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$smarty->assign('master', $master);
	$smarty->display('global.tpl');
    }

    return GalleryStatus::success();
}

/*
 * Define our URL generator hook
 */
function galleryUrlGenerator($params, &$smarty) {
    foreach ($params as $key => $value) {
	$args[] = GALLERY_ARGUMENT_PREFIX . "$key=$value";
    }
    print 'main.php?' . join('&amp;', $args);
}

/*
 * Define our form open generator
 */
function galleryFormOpenGenerator($params, &$smarty) {
    if (empty($params['method'])) {
	$method = 'POST';
    } else {
	$method = $params['method'];
	unset($params['method']);
    }

    $url = $params['url'];
    unset($params['url']);
    
    print '<form method="' . $method . '" action="' . $url . '">';
    foreach ($params as $key => $value) {
	print '<input type="hidden" ' .
	    'name="' . $key . '"' .
	    'value="' . $value . '">';
    }
}

/*
 * Define our form close generator
 */
function galleryFormCloseGenerator($params, &$smarty) {
    print '</form>';
}

/*
 * Define our translator hook
 */
function galleryTranslator($params, &$smarty) {
    global $gallery;
    print $gallery->translate($params);
}
?>

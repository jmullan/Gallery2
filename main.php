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

/* Initialize Gallery */
require(dirname(__FILE__) . '/init.php');

/* Figure out the target module/controller */
list($viewName, $controllerName) =
    GalleryUtilities::getRequestVariables('gView', 'gController');

/* Load and run the appropriate controller */
if (!empty($controllerName)) {
    ereg('^([[:alnum:]]+):([[:alnum:]]+)$', $controllerName, $regs);
    if (sizeof($regs) == 3) {
	$module = $regs[1];
	$class = $regs[2];
	require_once($gallery->getConfig('core.directory.modules') .
		     $module . '/' . $class . '.inc');
	$controllerClassName = $class . 'Controller';
	$controller = new $controllerClassName;
    
	/* Let the controller handle the input */
	$ret = $controller->handleRequest();
    
	/*
	 * XXX: Handle errors in an unclean fashion for now
	 * eventually push this out into its own view
	 */
	if ($ret->isError()) {
	    print $ret->getAsHtml();
	    return;
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

require_once($gallery->getConfig('core.directory.modules') .
	     $module . '/' . $class . '.inc');
$viewClassName = $class . 'View';
$view = new $viewClassName;
    
/* Render the view */
$ret = $view->render();
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}
?>

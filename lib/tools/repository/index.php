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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 */

 /**
 * @package RepositoryTools
 */
include('../../support/security.inc');
include('../../../bootstrap.inc');
require_once('../../../init.inc');

function RepositoryToolsMain() {
    $ret = GalleryInitFirstPass();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryInitSecondPass();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    global $gallery;

    GalleryCoreApi::requireOnce(
	'lib/tools/repository/classes/RepositoryControllerAndView.class');

    /* Set repository configuration data. */
    $repositoryPath = $gallery->getConfig('data.gallery.base') . '/repository/';
    $gallery->setConfig('repository.path', $repositoryPath);
    $gallery->setConfig('repository.templates', 'lib/tools/repository/templates/');

    /* Verify our repository structure exists */
    $platform =& $gallery->getPlatform();
    foreach (array($repositoryPath,
		   $repositoryPath . '/modules',
		   $repositoryPath . '/themes') as $path) {
	if (!$platform->file_exists($path)) {
	    if (!$platform->mkdir($path)) {
		return GalleryCoreApi::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					    "Unable to create directory: $path");
	    }
	}
    }

    /* Configure our url Generator for repository mode. */
    $urlGenerator = new GalleryUrlGenerator();
    $ret = $urlGenerator->init('lib/tools/repository');
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    $gallery->setUrlGenerator($urlGenerator);

    /* Load controller. */
    $controllerName = GalleryUtilities::getRequestVariables('controller');
    $methodName = GalleryUtilities::getRequestVariables('action');
    $controllerPath = sprintf('%s/%s.inc', dirname(__FILE__), $controllerName);

    $platform =& $gallery->getPlatform();
    if (!$platform->file_exists($controllerPath)) {
	/* Set default controller. */
	$controllerName = 'MainPage';
	$controllerPath = sprintf('%s/%s.inc', dirname(__FILE__), $controllerName);
	$methodName = 'showAvailableActions';
    }

    $controllerClassName = $controllerName . 'ControllerAndView';
    require_once($controllerPath);
    $controller = new $controllerClassName();
    $controller->init();

    /* Call a controller method. */
    if (!method_exists($controller, $methodName)) {
	return GalleryCoreApi::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
				    "Method [$methodName] does not exist in $controllerClassName");
    }

    $ret = $controller->$methodName();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return null;
}

$ret = RepositoryToolsMain();
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    print $gallery->getDebugBuffer();
    return;
}

list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}
?>

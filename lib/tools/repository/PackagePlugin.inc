<?php
/*
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
 *
 * $Id$
 */

GalleryCoreApi::relativeRequireOnce('lib/tools/repository/classes/RepositoryObject.class');
GalleryCoreApi::relativeRequireOnce('lib/tools/repository/classes/RepositoryDescriptor.class');
GalleryCoreApi::relativeRequireOnce('lib/tools/repository/classes/RepositoryPackage.class');

/**
 * Controller for the plugin packaging page.
 *
 * @author Jozef Selesi <selesi at gmail dot com>
 *
 * @version $Id$
 * @package RepositoryTools
 * @subpackage Controllers
 * @module PackagePluginController
 */
class PackagePluginControllerAndView extends RepositoryControllerAndView {

    /**
     * Displays the available plugins that can be packaged.
     *
     * @return object GalleryStatus a status code
     */
    function showAvailablePlugins() {
	list ($ret, $plugins) = $this->getAvailablePluginList(array(
	    'package' => array('controller' => 'PackagePlugin', 'action' => 'packagePlugin')));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->showView('PackagePlugin', array('plugins' => $plugins));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Creates all packages for the selected plugin and displays a summary page when completed.
     *
     * @return object GalleryStatus a status code
     */
    function packagePlugin() {
	list ($pluginId, $pluginType) =
	    GalleryUtilities::getRequestVariables('pluginId', 'pluginType');

	if (empty($pluginId) || empty($pluginType)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
	    				sprintf('pluginId [%s] and/or pluginType [%s] not set.',
	    					$pluginId, $pluginType));
	}

	list ($ret, $pluginInfo) = $this->doPackagePlugin($pluginType, $pluginId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->showView('PackageResults', array('results' => array($pluginInfo)));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Creates packages for all plugins that match the 'filter' request variable.
     *
     * @return object GalleryStatus a status code
     */
    function packagePlugins() {
	$pluginsPackaged = 0;

	/* Set default filter if none is provided. */
	$filter = GalleryUtilities::getRequestVariables('filter');
	if (strlen($filter) < 3) { /* Is there a check to see if a regexp is valid? */
	    $filter = '/.*/';
	}

	list ($ret, $plugins) = $this->getAvailablePluginList(array());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	foreach ($plugins as $pluginId => $plugin) {
	    if (preg_match($filter, $pluginId)) {
		list ($ret, $pluginInfo) = $this->doPackagePlugin($plugin['type'], $pluginId);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		$packagedPluginList[] = $pluginInfo;
	    }
	}
	$this->showView('PackageResults', array('results' => $packagedPluginList));
	return GalleryStatus::success();
    }

    /**
     * Creates all packages for the specified plugin.
     *
     * @return object GalleryStatus a status code
     */
    function doPackagePlugin($pluginType, $pluginId) {
	global $gallery;
	$outputDir = $gallery->getConfig('repository.path');

	list ($ret, $plugin) = GalleryCoreApi::loadPlugin($pluginType, $pluginId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$outputDir .= sprintf('%ss', $pluginType);

	$descriptor = new RepositoryDescriptor();
	$ret = $descriptor->init($outputDir);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $descriptor->generate($plugin);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $descriptor->writeToDisk();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$package = new RepositoryPackage();
	$ret = $package->init($descriptor, $descriptor->getOutputDir());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $packagesWritten) = $package->writeAllPackagesToDisk();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$pluginInfo = array('pluginId' => $descriptor->getPluginId(),
			    'outputDir' => $descriptor->getOutputDir(),
			    'packageInfo' => $packagesWritten);

	return array(GalleryStatus::success(), $pluginInfo);
    }

    /**
     * Creates a list of all existing plugins with optional action links.
     *
     * @param array 'action' => array(UrlGeneratorParameters)
     * @return array object GalleryStatus a status code
     *		     array plugin list
     */
    function getAvailablePluginList($links) {
	global $gallery;
	$urlGenerator = $gallery->getUrlGenerator();
	$data = array();
	$pluginTypes = array('module', 'theme');

	foreach ($pluginTypes as $pluginType) {
	    list ($ret, $plugins) = GalleryCoreApi::fetchPluginStatus($pluginType, true);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($plugins as $pluginId => $plugin) {
		$data[$pluginId]['type'] = $pluginType;
		$data[$pluginId]['active'] = isset($plugin['active']) ? 'active' : 'inactive';
		$data[$pluginId]['available'] = isset($plugin['available']) ? 'available'
									    : 'unavailable';

		$pluginUrlParameters = array('pluginId' => $pluginId, 'pluginType' => $pluginType);
		foreach ($links as $link => $extraUrlParameters) {
		    $data[$pluginId]['links'][$link] =
			$urlGenerator->generateUrl($extraUrlParameters + $pluginUrlParameters);
		}
	    }
	}

	return array(GalleryStatus::success(), $data);
    }
}
?>
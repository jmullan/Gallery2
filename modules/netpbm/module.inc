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
/**
 * @version $Revision$ $Date$
 * @package NetPbm
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * NetPBM Graphics Module
 *
 * This module provides the NetPBM graphics toolkit for Gallery
 *
 * @package NetPbm
 */
class NetPbmModule extends GalleryModule {

    function NetPbmModule() {
	global $gallery;

	$this->setId('netpbm');
	$this->setName('NetPBM');
	$this->setDescription($gallery->i18n('NetPBM Graphics Toolkit'));
	$this->setVersion('0.8.3');
	$this->setGroup('toolkits', $this->translate('Graphics Toolkits'));
	$this->setCallbacks('performFactoryRegistrations|getSiteAdminViews');
	$this->setRequiredCoreApi(array(1, 0));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our graphics class with the factory */
	GalleryCoreApi::registerFactoryImplementation('GalleryToolkit',
						      'NetPbmToolkit',
						      'NetPBM',
						      $classDir . 'NetPbmToolkit.class');
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    /* Initial install */
	    foreach (array('path' => '',
			   'jpegQuality' => '75',
			   'pnmtojpeg' => 'pnmtojpeg')
		     as $key => $value) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	global $gallery;

	list ($ret, $needsConfiguration) = $this->needsConfiguration();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), false);
	}

	if (!$needsConfiguration) {
	    return array(GalleryStatus::success(), true);
	}

	/* Try a bunch of likely seeming paths to see if any of them work. */
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();

	/*
	 * Start with system paths.  Tack on a trailing slash if necessary,
	 * then tack on other likely paths, based on our OS
	 */
	$paths = array();
	if (GalleryUtilities::isA($platform, 'WinNtPlatform')) {
	    foreach (explode(';', getenv('PATH')) as $path) {
		$path = trim($path);
		if ($path{strlen($path)-1} != $slash) {
		    $path .= $slash;
		}
		$paths[] = $path;
	    }

            /*
	     * Double-quoting the paths removes any ambiguity about the
	     * double-slashes being escaped or not
	     */
	    $paths[] = "C:\\Program Files\\netpbm\\";
	    $paths[] = "C:\\apps\\netpbm\\";
	    $paths[] = "C:\\apps\\jhead\\";
	    $paths[] = "C:\\netpbm\\";
	    $paths[] = "C:\\jhead\\";
	} else if (GalleryUtilities::isA($platform, 'UnixPlatform')){
	    foreach (explode(':', getenv('PATH')) as $path) {
		$path = trim($path);
		if ($path{strlen($path)-1} != $slash) {
		    $path .= $slash;
		}
		$paths[] = $path;
	    }

	    $paths[] = '/usr/bin/';
	    $paths[] = '/usr/local/bin/';
	    $paths[] = '/usr/local/netpbm/bin/';
	    $paths[] = '/bin/';
	    $paths[] = '/sw/bin/';
	} else {
	    return array(GalleryStatus::success(), false);
	}

	/* Load any classes we require */
	require_once(dirname(__FILE__) . '/classes/NetPbmToolkitHelper.class');

	/* Now try each path in turn to see which ones work */
	$lowestFailCount = 999;
	$success = false;
	foreach ($paths as $path) {
	    foreach (array('ppmtojpeg', 'pnmtojpeg') as $pnmtojpeg) {
		if (!$platform->isRestrictedByOpenBasedir($path) && !$platform->file_exists($path)) {
		    continue;
		}

		list ($ret, $testResults) =
		    NetPbmToolkitHelper::testBinaries($path, array('pnmtojpeg' => $pnmtojpeg));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/*
		 * In order for us to consider this a success, we need to wind
		 * up with at least support for JPEGs so track the path with
		 * the lowest failure count and working jpegtopnm/p?mtojpeg
		 */
		$failCount = 0;
		$jpegWorking = 0;
		foreach ($testResults as $testResult) {
		    /* All tests should work, else this path is not a valid one */
		    if ($testResult['success']) {
			if (preg_match('/jpegtopnm|p?mtojpeg/', $testResult['name'])) {
			    $jpegWorking++;
			}
		    } else {
			$failCount++;
		    }

		}

		if ($jpegWorking == 2) {
		    if ($failCount <= $lowestFailCount) {
			/* We have a winner */
			$ret = GalleryCoreApi::setPluginParameter('module', 'netpbm', 'path', $path);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), false);
			}

			$ret = GalleryCoreApi::setPluginParameter('module', 'netpbm', 'pnmtojpeg', $pnmtojpeg);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), false);
			}

			$lowestFailCount = $failCount;
			$success = true;
		    }
		}

		if ($lowestFailCount == 0) {
		    /* We're done */
		    break 2;
		}
	    }

	}
	/* Now try each path in turn to see which ones work for jhead */
	foreach ($paths as $path) {
	    if ($platform->file_exists($path)) {
		list ($ret, $testResults) = NetPbmToolkitHelper::testJhead($path);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
		foreach ($testResults as $testResult) {
		    if ($testResult['success'] && ($testResult['name'] == 'jhead')) {
			$ret = GalleryCoreApi::setPluginParameter('module', 'netpbm', 'jheadPath', $path);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), false);
			}

			break 2;
		    }
		}
	    }
	}

	return array(GalleryStatus::success(), $success);
    }

    /**
     * @see GalleryModule::activate()
     */
    function activate() {
	/* Load any classes we require */
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/NetPbmToolkitHelper.class');

	/* Find out what operations and properties we have available to us */
	list ($ret, $results) =
	    NetPbmToolkitHelper::getOperationsAndProperties();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $priority) = GalleryCoreApi::getMaximumManagedToolkitPriority();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$priority++;

	foreach ($results['operations'] as $operation => $info) {
	    $outputMimeType = isset($info['outputMimeType']) ? $info['outputMimeType'] : '';
	    $ret = GalleryCoreApi::registerToolkitOperation('NetPBM',
							   $info['mimeTypes'],
							   $operation,
							   $info['params'],
							   $info['description'],
							   $outputMimeType, $priority);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	foreach ($results['properties'] as $property => $info) {
	    $ret = GalleryCoreApi::registerToolkitProperty('NetPBM',
							  $info['mimeTypes'],
							  $property,
							  $info['type'],
							  $info['description']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $redirect) = parent::activate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * @see GalleryModule::deactivate()
     */
    function deactivate() {
	/*
	 * Unregister all of our properties and operations.  Do this before the parent deactivates so that any
	 * event handlers triggered by the deactivation will see the world as it will be after the
	 * deactivation is done.
	 */
	$ret = GalleryCoreApi::unregisterToolkit('NetPBM');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $redirect) = parent::deactivate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * @see GalleryModule::needsConfiguration()
     */
    function needsConfiguration() {
	/*
	 * This module requires all fields to be filled out before it can be
	 * activated.
	 */
	foreach (array('path', 'jpegQuality', 'pnmtojpeg') as $key) {
	    list ($ret, $value) = $this->getParameter($key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($value)) {
		return array(GalleryStatus::success(), true);
	    }
	}

	return array(GalleryStatus::success(), false);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('NetPBM'),
				 'view' => 'netpbm:AdminNetPbm')));
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	return 'netpbm:AdminNetPbm';
    }
}
?>

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
/**
 * @version $Revision$ $Date$
 * @package SquareThumb
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Square thumbnails
 *
 * This module creates thumbnails with a 1x1 aspect ratio; it relies on some other toolkit
 * being active to perform the actual image manipulation (dimensions, crop, scale)
 *
 * @package SquareThumb
 */
class SquareThumbModule extends GalleryModule /* and GalleryEventListener */ {

    function SquareThumbModule() {
	global $gallery;

	$this->setId('squarethumb');
	$this->setName($gallery->i18n('Square Thumbnails'));
	$this->setDescription($gallery->i18n('Crop all thumbnails so they are square'));
	$this->setVersion('0.9.1');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('registerEventListeners');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryToolkit', 'SquareThumbToolkit', 'SquareThumb',
	    'modules/squarethumb/classes/SquareThumbToolkit.class', 'squarethumb', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::registerEventListeners();
     */
    function registerEventListeners() {
	GalleryCoreApi::registerEventListener('Gallery::DeactivatePlugin',
					      new SquareThumbModule());
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::activate()
     */
    function activate() {
	global $gallery;

	list ($ret, $mimeTypes) = $this->_getSupportedMimeTypes();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Register toolkit operation using high priority */
	if (!empty($mimeTypes)) {
	    $ret = GalleryCoreApi::registerToolkitOperation('SquareThumb', $mimeTypes, 'thumbnail',
		array(array('type' => 'int', 'description' => $gallery->i18n('target size')),
		      array('type' => 'int', 'description' => $gallery->i18n('(optional)'))),
		$gallery->i18n('Create square thumbnail'), '', 10);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    /* Can't activate unless there's a toolkit to leech off of */
	    return array(GalleryStatus::success(),
			 array('view' => 'core:SiteAdmin',
			       'subView' => 'squarethumb:CantActivate'));
	}

	list ($ret, $redirect) = parent::activate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * Find out what mime-types currently have toolkit support for:
     *    scale, crop, dimensions
     *
     * @return array object GalleryStatus a status code
     *               array mime types
     */
    function _getSupportedMimeTypes() {
	list ($ret, $scale) = GalleryCoreApi::getToolkitOperationMimeTypes('scale');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $crop) = GalleryCoreApi::getToolkitOperationMimeTypes('crop');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$mimeTypes = array();
	foreach (array_keys(array_merge($scale, $crop)) as $mimeType) {
	    list ($ret, $properties) = GalleryCoreApi::getToolkitProperties($mimeType);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($properties as $tmp) {
		if ($tmp['name'] == 'dimensions') {
		    $mimeTypes[] = $mimeType;
		    break;
		}
	    }
	}

	return array(GalleryStatus::success(), $mimeTypes);
    }

    /**
     * @see GalleryModule::deactivate()
     */
    function deactivate() {
	global $gallery;

	list ($ret, $redirect) = parent::deactivate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Unregister all of our properties and operations */
	$ret = GalleryCoreApi::unregisterToolkit('SquareThumb');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * Handler for Gallery::DeactivatePlugin event.
     *
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	/*
	 * We're going to deactivate this plugin which will generate another
	 * Gallery::DeactivatePlugin event, so make sure that we don't handle
	 * *that* event and get into an infinite loop!
	 */
	$data = $event->getData();
	if ($event->getEventName() == 'Gallery::DeactivatePlugin' &&
	    $data['pluginId'] != 'squarethumb' &&
	    $data['pluginType'] == 'module') {

	    list ($ret, $isActive) = $this->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($isActive) {
		list ($ret, $redirect) = $this->deactivate();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		list ($ret, $mimeTypes) = $this->_getSupportedMimeTypes();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!empty($mimeTypes)) {
		    list ($ret, $redirect) = $this->activate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Redirect should be empty since we verified the mime types exist */
		}
	    }
	}
	return array(GalleryStatus::success(), null);
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	return 'squarethumb:CantActivate';
    }
}
?>

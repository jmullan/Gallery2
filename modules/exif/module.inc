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
/**
 * @package Exif
 * @version $Revision$ $Date$
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Exif Module
 *
 * This module provides support for adding exifs to items
 *
 * @package Exif
 */
class ExifModule extends GalleryModule {

    function ExifModule() {
	global $gallery;
	
	$this->setId('exif');
	$this->setName('Exif Parser');
	$this->setDescription($gallery->i18n('Extract EXIF data from JPEG photos'));
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init()
     */
    function init() {
	global $gallery;

	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	require_once(dirname(__FILE__) . '/classes/ExifHelper.class');
	require_once(dirname(__FILE__) . '/classes/ExifPropertiesMap.class');
	
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), false);
	}

	$installed = false;
	if ($version != $this->getVersion()) {
	    /* The store requires configuration. */
	    $storage = $gallery->getStorage();
	    $ret = $storage->configureStore('exif');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	    
	    if (empty($version)) {
		$ret = ExifHelper::setDefaultProperties(EXIF_SUMMARY);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
		
		$ret = ExifHelper::setDefaultProperties(EXIF_DETAILED);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$installed = true;
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	}
	
	return array(GalleryStatus::success(), $installed);
    }
	
    /**
     * @see GalleryModule::loadItemDetails()
     */
    function loadItemDetails(&$template, $item) {
	global $gallery;

	/* We only work on data items */
	if (!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    return array(GalleryStatus::success(), '');
	}

	/* And those data items have to be JPEGs */
	if ($item->getMimeType() != 'image/jpeg') {
	    return array(GalleryStatus::success(), '');
	}
	    
	/* Feed the file to exifer */
	list($ret, $path) = $item->fetchPath();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out which version we're looking at */
	$session =& $gallery->getSession();
	if (empty($mode)) {
	    $mode = $session->get('exif.module.loadItemDetails.mode');
	    if (empty($mode)) {
		$mode = 'summary';
	    }
	}

	if ($mode == 'detailed') {
	    $filter = EXIF_DETAILED;
	} else {
	    $filter = EXIF_SUMMARY;
	}

	list ($ret, $exifData) = ExifHelper::getExifData($path, $filter);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ExifItemDetails = array();
	$ExifItemDetails['exifData'] = $exifData;
	$ExifItemDetails['mode'] = $mode;
	$template->setVariable('ExifItemDetails', $ExifItemDetails);

	return array(GalleryStatus::success(), 'modules/exif/templates/ExifItemDetails.tpl');
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Exif Parser'),
				 'view' => 'exif:AdminExif')));
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	global $gallery;
	return array(GalleryStatus::success(), 'exif:AdminExif');
    }

}
?>
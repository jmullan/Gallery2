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
	
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/*
		 * This is an initial install. Make sure that we have some
		 * reasonable defaults.
		 */
		foreach (array(
			       'IFD0.DateTime' => EXIF_SIMPLE,
			       'IFD0.ImageType' => EXIF_ADVANCED,
			       'IFD0.Make' => EXIF_SIMPLE,
			       'IFD0.Model' => EXIF_SIMPLE,
			       'IFD0.Orientation' => EXIF_ADVANCED,
			       'IFD0.PhotoshopSettings' => EXIF_ADVANCED,
			       'IFD0.ResolutionUnit' => EXIF_ADVANCED,
			       'IFD0.xResolution' => EXIF_ADVANCED,
			       'IFD0.yResolution' => EXIF_ADVANCED,
			       'IFD1.Compression' => EXIF_ADVANCED,
			       'SubIFD.ApertureValue' => EXIF_SIMPLE,
			       'SubIFD.BrightnessValue' => EXIF_ADVANCED,
			       'SubIFD.ColorSpace' => EXIF_SIMPLE,
			       'SubIFD.Contrast' => EXIF_ADVANCED,
			       'SubIFD.ExposureBiasValue' => EXIF_SIMPLE,
			       'SubIFD.ExposureMode' => EXIF_ADVANCED,
			       'SubIFD.ExposureProgram' => EXIF_SIMPLE,
			       'SubIFD.ExposureTime' => EXIF_SIMPLE,
			       'SubIFD.FNumber' => EXIF_SIMPLE,
			       'SubIFD.Flash' => EXIF_SIMPLE,
			       'SubIFD.FlashEnergy' => EXIF_ADVANCED,
			       'SubIFD.FocalLength' => EXIF_SIMPLE,
			       'SubIFD.ISOSpeedRatings' => EXIF_SIMPLE,
			       'SubIFD.MeteringMode' => EXIF_SIMPLE,
			       'SubIFD.Saturation' => EXIF_ADVANCED,
			       'SubIFD.SceneType' => EXIF_ADVANCED,
			       'SubIFD.Sharpness' => EXIF_ADVANCED,
			       'SubIFD.ShutterSpeedValue' => EXIF_SIMPLE,
			       'SubIFD.SubjectDistance' => EXIF_ADVANCED,
			       )
			 as $key => $value) {
		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	
	return GalleryStatus::success();
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
		$mode = 'simple';
	    }
	}

	if ($mode == 'advanced') {
	    $filter = EXIF_ADVANCED;
	} else {
	    $filter = EXIF_SIMPLE;
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
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
	$this->setVersion('0.9.1');
	$this->setGroup('data', $this->translate('Extra Data'));
	$this->setCallbacks('loadItemDetails|getSiteAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    /* Initial install */
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ExifHelper.class');
	    $ret = ExifHelper::setDefaultProperties(EXIF_SUMMARY);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = ExifHelper::setDefaultProperties(EXIF_DETAILED);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $this->setParameter('addOption', '0');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	} else {
	    switch ($currentVersion) {
	    case '0.8.2':
	    case '0.8.3':
		$ret = $this->setParameter('addOption', '0');
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

	    case '0.8.4':
	    case '0.8.5':
	    case '0.8.6':
	    case '0.8.7':
	    case '0.8.8':
	    case '0.8.9':
	    case '0.9.1':
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ExifInterface_1_0', 'ExifExtractor', 'Exif',
	    'modules/exif/classes/ExifExtractor.class', 'exif', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryToolkit', 'ExifToolkit', 'Exif',
	    'modules/exif/classes/ExifToolkit.class', 'exif', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation('ItemAddOption',
	    'ExifDescriptionOption', 'ExifDescriptionOption',
	    'modules/exif/ExifDescriptionOption.inc', 'exif', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::activate
     */
    function activate() {
	global $gallery;
	$ret = GalleryCoreApi::registerToolkitProperty('Exif',
							array('image/jpeg'),
							'originationTimestamp',
							'int',
							$gallery->i18n('Get the origination timestamp'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $redirect) = parent::activate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
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
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::loadItemDetails()
     */
    function loadItemDetails(&$template, $item) {
	global $gallery;

	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ExifHelper.class');

	/* We only work on data items */
	if (!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    return array(GalleryStatus::success(), '');
	}

	/* And those data items have to be JPEGs */
	if ($item->getMimeType() != 'image/jpeg' && $item->getMimeType() != 'image/pjpeg') {
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
	if (empty($exifData) && $filter == EXIF_SUMMARY) {
	    list ($ret, $exifData) = ExifHelper::getExifData($path, EXIF_DETAILED);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $mode = null;
	}
	if (empty($exifData)) {
	    return array(GalleryStatus::success(), null);
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
		     array(array('name' => $this->translate('EXIF Parser'),
				 'view' => 'exif:AdminExif')));
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	return 'exif:AdminExif';
    }
}
?>

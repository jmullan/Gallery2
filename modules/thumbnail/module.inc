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
 * @package Thumbnail
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Thumbnail defaults
 *
 * This module provides default thumbnails for non-image mime types.
 *
 * @package Thumbnail
 */
class ThumbnailModule extends GalleryModule {

    function ThumbnailModule() {
	global $gallery;

	$this->setId('thumbnail');
	$this->setName($gallery->i18n('Thumbnail Manager'));
	$this->setDescription($gallery->i18n('Set default thumbnails for non-image items'));
	$this->setVersion('0.9.1');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('getSiteAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	switch ($currentVersion) {
	case '0.8.1':
	case '0.8.2':
	    /*
	     * Assign parent to existing ThumbnailImage entities
	     */
	    list ($ret, $rootId) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $storage =& $gallery->getStorage();
	    $query = 'INSERT INTO [GalleryChildEntity] SELECT [ThumbnailImage::id], '
		   . $rootId . ' FROM [ThumbnailImage]';
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.8.3':
	case '0.8.4':
	case '0.8.5':
	case '0.8.6':
	case '0.8.7':
	case '0.8.8':
	    break;

	default:
	    return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					sprintf('Unknown module version %s', $currentVersion));
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryEntity', 'ThumbnailImage', 'ThumbnailImage',
	    'modules/thumbnail/classes/ThumbnailImage.class', 'thumbnail', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryToolkit', 'ThumbnailToolkit', 'Thumbnail',
	    'modules/thumbnail/classes/ThumbnailToolkit.class', 'thumbnail', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemEditOption', 'CustomThumbnailOption', 'CustomThumbnailOption',
	    'modules/thumbnail/CustomThumbnailOption.inc', 'thumbnail', array('ItemEditItem'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
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
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::activate()
     */
    function activate() {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ThumbnailHelper.class');
	global $gallery;

	/* Register toolkit operation for any mime type settings already in the database */
	list ($ret, $mimeTypeMap) = ThumbnailHelper::fetchMimeTypeMap();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($mimeTypeMap)) {
	    $ret = GalleryCoreApi::registerToolkitOperation('Thumbnail',
				   array_keys($mimeTypeMap), 'convert-to-image/jpeg', array(),
				   $gallery->i18n('Convert to a JPEG'), 'image/jpeg', 50);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Set some defaults if not already supported */
	list ($ret, $toolkitMime) = ThumbnailHelper::fetchToolkitSupport();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$itemId = array();
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ThumbnailImage.class');
	foreach (array(
	    'G2audio.jpg' => array('audio/mpeg', 'audio/x-wav', 'audio/x-aiff', 'audio/midi', 'audio/basic', 'audio/x-ms-wma'),
	    'G2video.jpg' => array('video/mpeg', 'video/quicktime', 'video/x-msvideo', 'video/x-ms-asf', 'video/x-ms-wmv')
	    ) as $mimeImage => $mimeList) {
	    foreach ($mimeList as $mime) {
		if (!isset($toolkitMime[$mime])) {
		    if (!isset($itemId[$mimeImage])) {
			list ($ret, $itemId[$mimeImage]) = ThumbnailHelper::addItem($mime, null,
			    $mimeImage, dirname(__FILE__) . '/images/' . $mimeImage, 'image/jpeg',
			    array('width' => 400, 'height' => 352),
			    new ThumbnailImage());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			$ret = ThumbnailHelper::updateItem($itemId[$mimeImage], $mime);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}
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
	global $gallery;

	list ($ret, $redirect) = parent::deactivate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Unregister all of our properties and operations */
	$ret = GalleryCoreApi::unregisterToolkit('Thumbnail');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Thumbnails'),
				 'view' => 'thumbnail:ThumbnailSiteAdmin')));
    }
}
?>

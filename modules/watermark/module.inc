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
 * @package Watermark
 * @version $Revision$ $Date$
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Watermark Module
 *
 * This module provides support for adding watermarks to images
 *
 * @package Watermark
 */
class WatermarkModule extends GalleryModule /* and GalleryEventListener */ {

    function WatermarkModule() {
	global $gallery;

	$this->setId('watermark');
	$this->setName('Watermark');
	$this->setDescription($gallery->i18n('Watermark your images'));
	$this->setVersion('0.9.1');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('registerEventListeners|getSiteAdminViews|getUserAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryEntity', 'WatermarkImage', 'WatermarkImage',
	    'modules/watermark/classes/WatermarkImage.class', 'watermark', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemEditPlugin', 'ItemEditWatermark', 'ItemEditWatermark',
	    'modules/watermark/ItemEditWatermark.inc', 'watermark', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemAddOption', 'WatermarkOption', 'WatermarkOption',
	    'modules/watermark/WatermarkOption.inc', 'watermark', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::registerEventListeners();
     */
    function registerEventListeners() {
	GalleryCoreApi::registerEventListener('GalleryEntity::delete', new WatermarkModule());
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
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Watermarks'),
				 'view' => 'watermark:WatermarkSiteAdmin')));
    }

    /**
     * @see GalleryModule::getUserAdminViews();
     */
    function getUserAdminViews($user) {
	global $gallery;

	list ($ret, $anonymousUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$views = array();
	if ($user->getId() != $anonymousUserId) {
	    $views[] = array('name' => $this->translate('Watermarks'),
			     'view' => 'watermark:UserWatermarks');
	}

	return array(GalleryStatus::success(), $views);
    }

    /**
     * Handler for GalleryEntity::delete event.  Get rid of any watermarks
     * for users that are deleted.
     *
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	if ($event->getEventName() == 'GalleryEntity::delete') {
	    $entity = $event->getEntity();
	    if (GalleryUtilities::isA($entity, 'GalleryUser')) {
		GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/WatermarkHelper.class');
		list ($ret, $watermarkIds) =
		    WatermarkHelper::fetchWatermarkIdsByOwnerId($entity->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		foreach ($watermarkIds as $id) {
		    list ($ret) = WatermarkHelper::deleteWatermarkImageById($id, true);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	}
	return array(GalleryStatus::success(), null);
    }
}
?>

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
 * @package Migrate
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Migrate Module
 *
 * This module provides support for Migrating the Gallery
 *
 * @package Migrate
 */
class MigrateModule extends GalleryModule /* and GalleryEventListener */ {
    function MigrateModule() {
	global $gallery;

	$this->setId('migrate');
	$this->setName('Migration');
	$this->setDescription($gallery->i18n('Migrate your Gallery 1 albums to Gallery 2'));
	$this->setVersion('0.8.3');
	$this->setGroup('import', $this->translate('Import'));
	$this->setCallbacks('registerEventListeners|getSiteAdminViews');
	$this->setRequiredCoreApi(array(1, 0));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	GalleryCoreApi::registerEventListener('GalleryEntity::delete', new MigrateModule(), true);
    }

    /**
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	$item = $event->getEntity();
	if (GalleryUtilities::isA($item, 'GalleryItem')) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/G1MigrateMap.class');
	    $ret = G1MigrateMap::removeMapEntry(array('itemId' => $item->_id));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	return array(GalleryStatus::success(), null);
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
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	global $gallery;
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Gallery 1'),
				 'view' => 'migrate:SelectGallery')));
    }
}
?>

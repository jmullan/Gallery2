<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

/*
 * Bootstrap code: We have to load a few classes just so that the GalleryModule
 * parent class exists. This is only because we are the core module; other
 * modules should not have to do stuff like this.
 */
$classDir = dirname(__FILE__) . '/classes/';
require_once($classDir . 'GalleryModule.class');

class CoreModule extends GalleryModule {

    var $_gallery;

    function CoreModule() {
	$this->setName('core');
	$this->setDescription('Core Gallery functionality');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init();
     */
    function init() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Load all the core Gallery classes */
	require_once($classDir . 'GalleryUtilities.class');
	require_once($classDir . 'GalleryStatus.class');
	require_once($classDir . 'GalleryPersistent.class');
	require_once($classDir . 'GalleryEntity.class');
	require_once($classDir . 'GalleryChildEntity.class');
	require_once($classDir . 'GalleryFileSystemEntity.class');
	require_once($classDir . 'GalleryItem.class');
	require_once($classDir . 'GalleryAlbumItem.class');
	require_once($classDir . 'GalleryDerivative.class');
	require_once($classDir . 'GalleryDataItem.class');
	require_once($classDir . 'GalleryGraphics.class');
	require_once($classDir . 'GalleryGraphicsFactory.class');
	require_once($classDir . 'GalleryItemFactory.class');
	require_once($classDir . 'Gallery.class');
	require_once($classDir . 'GalleryLock.class');
	require_once($classDir . 'GalleryStorage.class');
	require_once($classDir . 'GalleryStorageFactory.class');
	require_once($classDir . 'GalleryUser.class');
	require_once($classDir . 'GalleryGroup.class');
	require_once($classDir . 'GalleryDerivativeImage.class');
	require_once($classDir . 'GalleryMovieItem.class');
	require_once($classDir . 'GalleryPhotoItem.class');
	require_once($classDir . 'GalleryUnknownItem.class');
	require_once($classDir . 'GalleryPlatform.class');
	require_once($classDir . 'GalleryPlatformFactory.class');
	require_once($classDir . 'GallerySearchResult.class');
	require_once($classDir . 'GalleryItemPropertiesMap.class');
	require_once($classDir . 'GalleryUserGroupMap.class');
	require_once($classDir . 'GalleryPermissionMap.class');
	require_once($classDir . 'GalleryViewCountMap.class');
	require_once($classDir . 'GalleryModuleMap.class');
	require_once($classDir . 'GalleryModuleParameterMap.class');

	/*
	 * Set up our Gallery global.  It's important to use a reference here because
	 * the constructor registers a shutdown function and ties it to the instance in
	 * the constructor.  This global should be the only one that Gallery requires.
	 * Everything else should be inside it so that we do not pollute the namespace
	 * (especially important when we're embedded inside another application).
	 */
	$gallery =& new Gallery();
	$gallery->setModule('core', $this);

	/* Configure the Platform */
	if (substr(PHP_OS, 0, 3) == 'WIN') {
	    $gallery->setConfig('platform.type', 'windows');
	} else {
	    $gallery->setConfig('platform.type', 'unix');
	}

	/* Register all core permissions */
	$gallery->addRegistry('GalleryPermissionMap',
			      array('id' => 'core.all', 'description' => 'Full'),
			      array('id' => 'core.view', 'description' => 'View'),
			      array('id' => 'core.viewResizes', 'description' => 'View Resizes'),
			      array('id' => 'core.viewSource', 'description' => 'View Original'),
			      array('id' => 'core.insert', 'description' => 'Insert'),
			      array('id' => 'core.change', 'description' => 'Change'),
			      array('id' => 'core.move', 'description' => 'Move'),
			      array('id' => 'core.changeText', 'description' => 'Change Text'),
			      array('id' => 'core.delete', 'description' => 'Delete'));

	$this->_gallery =& $gallery;
			      
	return parent::init();
    }

    /**
     * Return the core Gallery instance that we initialized in the init() method
     *
     * @return object Gallery the core Gallery instance
     */
    function &getGallery() {
	return $this->_gallery;
    }

    /**
     * @see GalleryModule::getAdminView();
     */
    function getAdminView() {
	return array(GalleryStatus::success(), 'core::Admin.inc');
    }
}
?>

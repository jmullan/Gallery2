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
	require_once($classDir . 'Gallery.class');
	require_once($classDir . 'GalleryController.class');
	require_once($classDir . 'GalleryDerivativeHelper.class');
	require_once($classDir . 'GalleryItemPropertiesMap.class');
	require_once($classDir . 'GalleryLayout.class');
	require_once($classDir . 'GalleryLock.class');
	require_once($classDir . 'GalleryModuleMap.class');
	require_once($classDir . 'GalleryModuleParameterMap.class');
	require_once($classDir . 'GalleryPermissionMap.class');
	require_once($classDir . 'GalleryProfiler.class');
	require_once($classDir . 'GalleryStatus.class');
	require_once($classDir . 'GalleryTemplateAdapter.class');
	require_once($classDir . 'GalleryTheme.class');
	require_once($classDir . 'GalleryUserGroupMap.class');
	require_once($classDir . 'GalleryUserHelper.class');
	require_once($classDir . 'GalleryGroupHelper.class');
	require_once($classDir . 'GalleryUtilities.class');
	require_once($classDir . 'GalleryView.class');
	require_once($classDir . 'GalleryViewCountMap.class');

	/*
	 * Set up our Gallery global.  It's important to use a reference here because
	 * the constructor registers a shutdown function and ties it to the instance in
	 * the constructor.  This global should be the only one that Gallery requires.
	 * Everything else should be inside it so that we do not pollute the namespace
	 * (especially important when we're embedded inside another application).
	 */
	$gallery =& new Gallery();
	$GLOBALS['gallery'] =& $gallery;
	$gallery->setCoreModule($this);

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

	/* Register our entity implementations */
	$gallery->addRegistry('GalleryEntity.GalleryAlbumItem',
			      $classDir . 'GalleryAlbumItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryUser',
			      $classDir . 'GalleryUser.class');
	$gallery->addRegistry('GalleryEntity.GalleryGroup',
			      $classDir . 'GalleryGroup.class');
	$gallery->addRegistry('GalleryEntity.GalleryDerivative',
			      $classDir . 'GalleryDerivative.class');
	$gallery->addRegistry('GalleryEntity.GalleryDerivativeImage',
			      $classDir . 'GalleryDerivativeImage.class');
	$gallery->addRegistry('GalleryEntity.GalleryMovieItem',
			      $classDir . 'GalleryMovieItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryPhotoItem',
			      $classDir . 'GalleryPhotoItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryUnknownItem',
			      $classDir . 'GalleryUnknownItem.class');
			      
	return parent::init();
    }

    /**
     * @see GalleryModule::getSiteAdminViews();
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('General'),
				 'view' => 'core:AdminCore'),
			   array('name' => $this->translate('Users'),
				 'view' => 'core:AdminUsers'),
			   array('name' => $this->translate('Groups'),
				 'view' => 'core:AdminGroups'),
			   array('name' => $this->translate('Modules'),
				 'view' => 'core:AdminModules')));
    }
}
?>

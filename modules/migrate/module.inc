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
class MigrateModule extends GalleryModule {
    function MigrateModule() {
	global $gallery;
	
	$this->setId('migrate');
	$this->setName('Migration');
	$this->setDescription($gallery->i18n('Migrate your Gallery 1 albums to Gallery 2'));
	$this->setVersion('1.0');
    }
    
    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;
	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$classDir = dirname(__FILE__) . '/classes/';
	require_once($classDir . 'Gallery1DataParser.class');
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
	global $gallery;
		
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), false);
	}

	$installed = false;
	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/* Initial install */
		$installed = true;

		/* Set any module defaults here */
	    }
	    
	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	    /* XXX: Register permissions here */
	}
	return array(GalleryStatus::success(), $installed);
    }

    /**
     * @see GalleryModule::canBeAutoInstalled
     */
    function canBeAutoInstalled() {
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
		     array(array('name' => $this->translate('Migrate Albums'),
				 'view' => 'migrate:SelectGallery'
				 )
			   )
		     );
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	global $gallery;
	return array(GalleryStatus::success(), 'migrate:SelectGallery');
    }
}
?>

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

/**
 * NetPBM Graphics Module
 *
 * This module provides the NetPBM graphics toolkit for Gallery
 *
 * @version $Id$
 * @package NetPBM
 * @author Bharat Mediratta <bharat@menalto.com>
 */
class NetPbmModule extends GalleryModule {

    function NetPbmModule() {
	$this->setName('netpbm');
	$this->setDescription('NetPBM Graphics Toolkit');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;
	
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our graphics class with the factory */
	$gallery->addRegistry('GalleryGraphicsFactory',
			      array('id' => 'netpbm',
				    'classFile' => $classDir . 'NetPbmGraphics.class',
				    'className' => 'NetPbmGraphics'));

	return parent::init();
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $gallery->translate('NetPBM'),
				 'view' => 'netpbm:AdminNetPbm')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	global $gallery;

	return array(GalleryStatus::success(), 'netpbm:AdminNetPbm');
    }
}
?>
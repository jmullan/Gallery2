<?php
/*
 * $RCSfile
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
 * ImageMagick Graphics Module
 *
 * This module provides the ImageMagick graphics toolkit for Gallery
 *
 * @version $Revision$ $Date$
 * @package ImageMagick
 * @author Vallimar <vallimar@sexorcisto.com>
 * @author Bharat Mediratta <bharat@menalto.com>
 */
class ImageMagickModule extends GalleryModule {

    function ImageMagickModule() {
	$this->setName('imagemagick');
	$this->setDescription('ImageMagick Graphics Toolkit');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;
	
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our graphics class with the factory */
	GalleryFactory::registerImplementation('GalleryGraphics',
					       'ImageMagickGraphics',
					       'ImageMagick',
					       $classDir . 'ImageMagickGraphics.class');

	return parent::init();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
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
		foreach (array('path' => '',
			       'jpegQuality' => '75')
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
     * @see GalleryModule::activate
     */
    function activate() {
	global $gallery;

	$ret = parent::activate();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	/*
	 * If our graphics type is not Imagemagick, set it now.
	 */
	list($ret, $graphicsType) = $gallery->getModuleParameter('core', 'graphics.type');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($graphicsType != 'imagemagickgraphics') {
	    $ret = $gallery->setModuleParameter('core', 'graphics.type', 'ImageMagickGraphics');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	return GalleryStatus::success();
    }
	
    /**
     * @see GalleryModule::needsConfiguration
     */
    function needsConfiguration() {
	global $gallery;

	/*
	 * This module requires all fields to be filled out before it can be
	 * activated. 
	 */
	foreach (array('path', 'jpegQuality') as $key) {
	    list ($ret, $value) = $this->getModuleParameter($key);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    if (empty($value)) {
		return array(GalleryStatus::success(), true);
	    }
	}

	return array(GalleryStatus::success(), false);
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('ImageMagick'),
				 'view' => 'imagemagick:AdminImageMagick')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	return array(GalleryStatus::success(), 'imagemagick:AdminImageMagick');
    }
}
?>
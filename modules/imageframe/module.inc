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
 * @package ImageFrame
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * The implementation of the Image Frame module
 *
 * @package ImageFrame
 */
class ImageFrameModule extends GalleryModule {

    function ImageFrameModule() {
	global $gallery;
	$this->setId('imageframe');
	$this->setName('ImageFrame');
	$this->setDescription($gallery->i18n('Render frames around images'));
	$this->setVersion('0.8.2');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('performFactoryRegistrations');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';
	GalleryCoreApi::registerFactoryImplementation(
	    'ImageFrameInterface_1_0', 'ImageFrameImpl', 'ImageFrame',
	    dirname(__FILE__) . '/classes/ImageFrameImpl.class');
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }
}
?>

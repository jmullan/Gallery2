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
 * @package Slideshow
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * The implementation of the Slideshow module
 *
 * @package Slideshow
 */
class SlideshowModule extends GalleryModule {

    function SlideshowModule() {
	global $gallery;
	$this->setId('slideshow');
	$this->setName($gallery->i18n('Slideshow'));
	$this->setDescription($gallery->i18n('Slideshow'));
	$this->setVersion('0.9.1');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('getItemLinks');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'SlideshowInterface_1_0', 'SlideshowImpl', 'Slideshow',
	    'modules/slideshow/classes/SlideshowImpl.class', 'slideshow', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
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

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	global $gallery;
	$links = array();
	foreach ($items as $item) {
	    $links[$item->getId()][] =
		array('text' => $this->translate('view slideshow'),
		      'params' => array(
			'view' => 'slideshow:Slideshow',
			'itemId' => $item->getId()));
	}
	return array(GalleryStatus::success(), $links);
    }
}
?>

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
	$this->setName('Slideshow');
	$this->setDescription($gallery->i18n('Slideshow'));
	$this->setVersion('0.8');
    }

    /**
     * @see GalleryModule::init()
     */
    function init() {
	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	GalleryCoreApi::registerFactoryImplementation(
	    'SlideshowInterface_1_0', 'SlideshowImpl', 'Slideshow',
	    dirname(__FILE__) . '/classes/SlideshowImpl.class');

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;

	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__,__LINE__), false);
	}

	$installed = false;
	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/* Initial install */
		$installed = true;
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	}

	return array(GalleryStatus::success(), $installed);
    }

    /**
     * @see GalleryModule::canBeAutoInstalled()
     */
    function canBeAutoInstalled() {
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

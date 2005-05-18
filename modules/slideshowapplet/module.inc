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
 * @package uploadapplet
 * @author Pierre-Luc Paour <paour@users.sourceforge.net>
 */

class SlideshowAppletModule extends GalleryModule {

    function SlideshowAppletModule() {
	global $gallery;
	$this->setId('slideshowapplet');
	$this->setName($gallery->i18n('Slideshow Applet'));
	$this->setDescription($gallery->i18n('Fullscreen slideshow using a Java applet'));
	$this->setVersion('0.9.3');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('getItemLinks|getItemAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'SlideshowInterface_1_0', 'SlideshowApplet', 'SlideshowApplet',
	    'modules/slideshowapplet/SlideshowApplet.inc', 'slideshowapplet', null);
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
		array('text' => $this->translate('view slideshow (fullscreen)'),
		      'params' => array(
			  'view' => 'core:ItemAdmin',
			  'subView' => 'slideshowapplet:SlideshowApplet',
			  'itemId' => $item->getId()));
	}
	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getItemAdminViews()
     */
    function getItemAdminViews($item) {
	global $gallery;

	$view = array('name' => $this->translate('View Slideshow (fullscreen)'),
		      'view' => 'slideshowapplet:SlideshowApplet');

	return array(GalleryStatus::success(), array($view));
    }
}
?>

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
 * @package uploadapplet
 * @author Pierre-Luc Paour <paour@users.sourceforge.net>
 */

class UploadAppletModule extends GalleryModule {

    function UploadAppletModule() {
	global $gallery;
	$this->setId('uploadapplet');
	$this->setName('Upload Applet');
	$this->setDescription($gallery->i18n('Easy to use upload applet for media'));
	$this->setVersion('0.8.2');
	$this->setGroup('import', $gallery->i18n('Import'));
	$this->setCallbacks('performFactoryRegistrations');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our item add plugins */
	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddUploadApplet',
						      'ItemAddUploadApplet',
						      dirname(__FILE__) . '/ItemAddUploadApplet.inc');
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

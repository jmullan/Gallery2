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
 * Module to allow publishing from XP directly to Gallery.
 *
 * This module allows the user to register Gallery with Windows XP as a web service
 * allowing photos to be directly uploaded from XP.  To use the service, the user
 * has to download a registry file and install it.  Once installed, the user can use
 * the Publish option.
 *
 * @version $Id$
 * @package PublishXp
 * @author Timothy Webb <tiwebb@cisco.com>
 */
class PublishXpModule extends GalleryModule {
    /**
     * Constructs the PublishXpModule that is registered with Gallery.
     */
    function PublishXpModule() {
	global $gallery;
	$this->setId('publishxp');
	$this->setName($gallery->i18n('Publish XP'));
	$this->setDescription($gallery->i18n('Implementation for direct publishing from XP'));
	$this->setVersion('0.9.3');
	$this->setGroup('import', $this->translate('Import'));
	$this->setCallbacks('');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredModuleApi(array(0, 12));
    }

    /**
     * Registers the item add operation with Gallery.
     *
     * @return GalleryStatus the status indicating if the registrations was done.
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	/* Register our item add plugins */
	GalleryCoreApi::registerFactoryImplementation(
	    'ItemAddPlugin',
	    'ItemAddPublishXp',
	    'ItemAddPublishXp',
	    'modules/publishxp/ItemAddPublishXp.inc',
	    'publishxp',
	    null);
	return GalleryStatus::success();
    }

    /**
     * Returns true that this is recommended during installation.
     *
     * @return GalleryStatus the status indicating recommended during installation.
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * Configures the module for use.
     *
     * There is no configuration needed for this module.
     *
     * @return array the status indicating that this was configured.
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }
}
?>

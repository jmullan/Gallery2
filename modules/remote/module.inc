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
 * @package remote
 * @author Pierre-Luc Paour <paour@users.sourceforge.net>
 */

class RemoteModule extends GalleryModule {

    function RemoteModule() {
	global $gallery;
	$this->setId('remote');
	$this->setName('Remote');
	$this->setDescription($gallery->i18n('Implementation for the remote control protocol'));
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

	/* Register our item add plugins */
	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddGalleryRemote',
						      'ItemAddGalleryRemote',
						      dirname(__FILE__) . '/ItemAddGalleryRemote.inc');

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
}
?>

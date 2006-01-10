<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
/**
 * @version $Revision$ $Date$
 * @package Fotokasten
 * @author Ioana Ciocanescu <service@fotokasten.de>
 */

/**
 * Print photos on fotokasten.de
 *
 * @package Fotokasten
 */
class FotokastenModule extends GalleryModule {

    function FotokastenModule() {
	global $gallery;

	$this->setId('fotokasten');
	$this->setName($gallery->i18n('Fotokasten'));
	$this->setDescription($gallery->i18n('Fotokasten Photo Printing Module'));
	$this->setVersion('1.0.1');
	$this->setGroup('commerce', $this->translate('Commerce'));
	$this->setCallbacks('getItemLinks');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredModuleApi(array(3, 0));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    list ($ret, $coreParams) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* Register our permission */
	    $ret = GalleryCoreApi::registerPermission($this->getId(), 'fotokasten.print',
						      $gallery->i18n('[fotokasten] Print'));
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    /* Give everybody print permission by default */
	    $ret = GalleryCoreApi::addGroupPermission(
		$coreParams['id.rootAlbum'], $coreParams['id.everybodyGroup'],
		'fotokasten.print', true);
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	return null;
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'CartPluginInterface_1_0', 'FotokastenCartPlugin', 'fotokasten',
	    'modules/fotokasten/classes/FotokastenCartPlugin.class', 'fotokasten', null);
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return null;
    }

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items, $wantsDetailedLinks, $permissions) {
	$links = array();

	foreach ($items as $item) {
	    $itemId = $item->getId();
	    if (isset($wantsDetailedLinks[$itemId]) &&
		    isset($permissions[$itemId]['fotokasten.print']) &&
		    GalleryUtilities::isA($item, 'GalleryPhotoItem')) {
		$links[$itemId][] =
		    array('text' => $this->translate('Print on Fotokasten.de'),
			  'params' => array('controller' => 'fotokasten.PrintPhotos',
					    'itemId' => $itemId, 'return' => 1));
	    }
	}

	return array(null, $links);
    }
}
?>

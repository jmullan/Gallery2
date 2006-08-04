<?php
/*
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
 * @package Digibug
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Photo printing at digibug.com
 *
 * @package Digibug
 */
class DigibugModule extends GalleryModule {

    function DigibugModule() {
	global $gallery;

	$this->setId('digibug');
	$this->setName($gallery->i18n('Digibug'));
	$this->setDescription($gallery->i18n('Digibug Photo Printing Module'));
	$this->setVersion('0.3.5'); /* Update upgrade() too */
	$this->setGroup('commerce', $gallery->i18n('Commerce'));
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
	    $currentVersion = '0';
	} else if (version_compare($currentVersion, '1.0.0', '<')) {
	    /* Instead of enumerating all previous versions... */
	    $currentVersion = '1.0.0';
	}
	list ($ret, $coreParams) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	switch ($currentVersion) {
	case '0':
	    /* Register our permission */
	    $ret = GalleryCoreApi::registerPermission($this->getId(), 'digibug.print',
						      $gallery->i18n('[digibug] Print'));
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    /* Give everybody print permission by default */
	    $ret = GalleryCoreApi::addGroupPermission(
		$coreParams['id.rootAlbum'], $coreParams['id.everybodyGroup'],
		'digibug.print', true);
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    break;

	case '1.0.0':
	    $ret = GalleryCoreApi::registerPermission($this->getId(), 'digibug.print',
						      $gallery->i18n('[digibug] Print'));
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $ret = GalleryCoreApi::addGroupPermission(
		$coreParams['id.rootAlbum'], $coreParams['id.everybodyGroup'],
		'digibug.print', true);
	    if ($ret) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '1.0.1':
	case '1.0.2':
	case '1.0.3':

	case 'end of upgrade path':
	    break;

	default:
	    return GalleryCoreApi::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					sprintf('Unknown module version %s', $currentVersion));
	}

	return null;
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'CartPluginInterface_1_0', 'DigibugCartPlugin', 'digibug',
	    'modules/digibug/classes/DigibugCartPlugin.class', 'digibug', null);
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
		    isset($permissions[$itemId]['digibug.print']) &&
		    GalleryUtilities::isA($item, 'GalleryPhotoItem')) {
		$links[$itemId][] =
		    array('text' => $this->translate('Print on Digibug.com'),
			  'params' => array('view' => 'digibug.PrintPhotos',
					    'itemId' => $itemId, 'return' => 1));
	    }
	}

	return array(null, $links);
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	global $gallery;
	list ($ret, $needsConfiguration) = $this->needsConfiguration();
	if ($ret) {
	   return array($ret->wrap(__FILE__, __LINE__), false);
	} else {
	   return array(null, true);
	}
    }

    function needsConfiguration(){
	/* This module requires all fields to be filled out before it can be activated. */
	foreach (array('digibugCustomerId', 'digibugPricelistId') as $key) {
	    list ($ret, $value) = $this->getParameter($key);
	    if ($ret) {
	       return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (empty($value)) {
		return array(null, true);
	    }
	}
	return array(null, false);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(null,
	array(array('name' => $this->translate('digibug'), 'view' => 'digibug.AdminDigibug')));
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	return 'digibug.AdminDigibug';
    }
}
?>

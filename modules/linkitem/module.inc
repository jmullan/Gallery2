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
 * @package LinkItem
 * @author Alan Harder <alan.harder@sun.com>
 */
class LinkItemModule extends GalleryModule {

    function LinkItemModule() {
	global $gallery;
	$this->setId('linkitem');
	$this->setName('Link Items');
	$this->setDescription($gallery->i18n('Create links to other albums or external urls'));
	$this->setVersion('1.0.0');
	$this->setGroup('display', $gallery->i18n('Display'));
	$this->setCallbacks('');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredModuleApi(array(3, 0));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;
	$platform =& $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();

	$imageDir = $gallery->getConfig('data.gallery.plugins_data') . "modules${slash}linkitem";
	list ($success) = GalleryUtilities::guaranteeDirExists($imageDir);
	if (!$success) {
	    return GalleryCoreApi::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					"Unable to create directory: $imageDir");
	}

	$imageFile = "$imageDir${slash}arrow.png";
	if (!$platform->is_file($imageFile) &&
	    !$platform->copy(dirname(__FILE__) . "${slash}images${slash}arrow.png", $imageFile)) {
	    return GalleryCoreApi::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					"Unable to copy arrow.png to $imageDir");
	}

	return null;
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryEntity', 'GalleryLinkItem', 'GalleryLinkItem',
	    'modules/linkitem/classes/GalleryLinkItem.class', 'linkitem', null);
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemAddPlugin', 'ItemAddLinkItem', 'ItemAddLinkItem',
	    'modules/linkitem/ItemAddLinkItem.inc', 'linkitem', null);
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemEditOption', 'LinkItemOption', 'LinkItemOption',
	    'modules/linkitem/LinkItemOption.inc', 'linkitem', array('ItemEditItem'));
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return null;
    }

    /**
     * @see GalleryModule::getModuleEntityTypes()
     */
    function getModuleEntityTypes() {
	return array('GalleryLinkItem');
    }
}
?>

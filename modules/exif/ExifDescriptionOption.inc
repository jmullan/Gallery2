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
 * @package Exif
 * @subpackage UserInterface
 * @author Elliot Shepherd <elliot@jarofworms.com>
 */

/**
 * This ItemAddOption uses the EXIF description value for the
 * gallery item summary/description when the image is uploaded.
 *
 * @package Exif
 * @subpackage UserInterface
 */
class ExifDescriptionOption extends ItemAddOption {

    /**
     * @see ItemAddOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(GalleryStatus::success(), 'modules/exif/templates/Empty.tpl', 'modules_exif');
    }

    /**
     * @see ItemAddOption::isAppropriate
     */
    function isAppropriate() {
	list ($ret, $addOption) = GalleryCoreApi::getPluginParameter('module', 'exif', 'addOption');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $addOption > 0);
    }

    /**
     * @see ItemAddOption::handleRequestAfterAdd
     */
    function handleRequestAfterAdd($form, &$item) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ExifExtractor.class');
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ExifHelper.class');
	$itemId = $item->getId();

	list ($ret, $exifData) =
	    ExifExtractor::getMetaData(array($itemId), array('ImageDescription'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($exifData[$itemId]['ImageDescription']['value'])) {
	    $exifDescription = $exifData[$itemId]['ImageDescription']['value'];

	    list ($ret, $addOption) =
		GalleryCoreApi::getPluginParameter('module', 'exif', 'addOption');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($addOption & EXIF_ITEM_SUMMARY) {
		$item->setSummary($exifDescription);
	    }
	    if ($addOption & EXIF_ITEM_DESCRIPTION) {
		$item->setDescription($exifDescription);
	    }

	    $ret = $item->save();
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = GalleryCoreApi::releaseLocks($lockId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	return array(GalleryStatus::success(), array(), array());
    }
}
?>

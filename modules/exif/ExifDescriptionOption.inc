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
 * @package Exif
 * @subpackage UserInterface
 * @author Elliot Shepherd <elliot@jarofworms.com>
 * @author Georg Rehfeld <rehfeld@georg-rehfeld.de>
 */

/**
 * This ItemAddOption uses the EXIF description value for the
 * gallery item summary/description and the IPTC keywords for the
 * gallery item keywords when the image is uploaded.
 *
 * @package Exif
 * @subpackage UserInterface
 */
class ExifDescriptionOption extends ItemAddOption {

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
    function handleRequestAfterAdd($form, $items) {
	$errors = array();
	$warnings = array();
	GalleryCoreApi::relativeRequireOnce('modules/exif/classes/ExifExtractor.class');
	GalleryCoreApi::relativeRequireOnce('modules/exif/classes/ExifHelper.class');
	$itemIds = array();
	foreach ($items as $item) {
	    $itemIds[] = $item->getId();
	}
	
	list ($ret, $addOption) =
	    GalleryCoreApi::getPluginParameter('module', 'exif', 'addOption');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($itemIds);
	if ($ret->isError()) {
	    GalleryCoreApi::releaseLocks($lockId);
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	for ($i = 0; $i < count($items); $i++) {
	    $warnings[$i] = array();
	    $itemId = $items[$i]->getId();

	    list ($ret, $exifData) =
		ExifExtractor::getMetaData(
		    array($itemId),
		    array('IPTC/Caption', 
			  'ImageDescription',
			  'UserComment', 
			  'IPTC/Keywords', 
			 )
		);
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $mustSave = false;

	    /* TODO(xlerb) reconsider, if ExifHelper should be changed to do the preferences. */
	    $itemDescription = '';
	    if (!empty($exifData[$itemId]['IPTC/Caption']['value'])) {
		$itemDescription = $exifData[$itemId]['IPTC/Caption']['value'];
	    }
	    elseif (!empty($exifData[$itemId]['ImageDescription']['value'])) {
		$itemDescription = $exifData[$itemId]['ImageDescription']['value'];
	    }
	    elseif (!empty($exifData[$itemId]['UserComment']['value'])) {
		$itemDescription = $exifData[$itemId]['UserComment']['value'];
	    }

	    if (!empty($itemDescription)) {
		if ($addOption & EXIF_ITEM_SUMMARY) {
		    $items[$i]->setSummary($itemDescription);
		    $mustSave = true;
		}
		if ($addOption & EXIF_ITEM_DESCRIPTION) {
		    $items[$i]->setDescription($itemDescription);
		    $mustSave = true;
		}
	    }

	    if (!empty($exifData[$itemId]['IPTC/Keywords']['value'])) {
		$iptcKeywords = $exifData[$itemId]['IPTC/Keywords']['value'];
		if ($addOption & IPTC_ITEM_KEYWORDS) {
		    $items[$i]->setKeywords($iptcKeywords);
		    $mustSave = true;
		}
	    }

	    if ($mustSave) {
		$ret = $items[$i]->save();
		if ($ret->isError()) {
		    GalleryCoreApi::releaseLocks($lockId);
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
	    }
	}
	$ret = GalleryCoreApi::releaseLocks($lockId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	return array(GalleryStatus::success(), $errors, $warnings);
    }
}
?>

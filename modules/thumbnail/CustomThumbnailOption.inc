<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU DataItem Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * DataItem Public License for more details.
 *
 * You should have received a copy of the GNU DataItem Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Thumbnail
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * ItemEditOption for uploading a custom thumbnail for an item
 *
 * @package Thumbnail
 * @subpackage UserInterface
 *
 */
class CustomThumbnailOption extends ItemEditOption {

    /**
     * @see ItemEditOption::isAppropriate
     */
    function isAppropriate($item, $thumbnail) {
	return array(GalleryStatus::success(),
		     (GalleryUtilities::isA($item, 'GalleryItem') && $item->getParentId() > 0));
    }

    /**
     * @see ItemEditOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ThumbnailHelper.class');

	// is this item already using a custom thumbnail..
	list ($ret, $thumbnailImage) = ThumbnailHelper::fetchThumbnail($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	if (isset($thumbnailImage)) {
	    $thumbnailImage = $thumbnailImage->getMemberData();
	} else {
	    /* Set the form's encoding type since we're uploading binary files */
	    if ($template->hasVariable('ItemAdmin')) {
		$ItemAdmin =& $template->getVariableByReference('ItemAdmin');
		$ItemAdmin['enctype'] = 'multipart/form-data';
	    } else {
		$ItemAdmin = array('enctype' => 'multipart/form-data');
		$template->setVariable('ItemAdmin', $ItemAdmin);
	    }
	}
	$template->setVariable('CustomThumbnailOption', array('thumbnail' => $thumbnailImage));

	return array(GalleryStatus::success(),
		    'modules/thumbnail/templates/CustomThumbnail.tpl',
		    'modules_thumbnail');
    }

    /**
     * @see ItemEditOption::handleRequestAfterEdit
     */
    function handleRequestAfterEdit($form, &$item, &$preferred) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ThumbnailHelper.class');

	$error = array();
	if (!empty($form['tmp_name'][1])) {
	    list ($ret, $lockId) = GalleryCoreApi::acquireReadLock(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $thumbnailId) = ThumbnailHelper::addItem(
		null, $item->getId(), $form['name'][1], $form['tmp_name'][1], $form['type'][1]);
	    if ($ret->isError() && ($ret->getErrorCode() & ERROR_UNSUPPORTED_FILE_TYPE)) {
		$error[] = 'form[CustomThumbnailOption][error][imageMime]';
	    } else if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($error)) {
		$ret = ThumbnailHelper::applyThumbnail($item, $thumbnailId);
		if ($ret->isError()) {
		    GalleryCoreApi::releaseLocks($lockId);
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    $ret = GalleryCoreApi::releaseLocks($lockId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else if (isset($form['CustomThumbnailOption']['delete'])) {
	    list ($ret, $thumbnailImage) = ThumbnailHelper::fetchThumbnail($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!isset($thumbnailImage)) {
		return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	    }
	    $ret = ThumbnailHelper::restoreThumbnail($item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ret = GalleryCoreApi::deleteEntityById($thumbnailImage->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	return array(GalleryStatus::success(), $error);
    }
}
?>

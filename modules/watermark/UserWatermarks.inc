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
 * @package Watermark
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class UserWatermarksController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$status = array();
	$error = array();
	if (isset($form['action']['add']) && !empty($form['tmp_name'][1])) {

	    /* Get the mime type from the upload info. */
	    $mimeType = $form['type'][1];

	    /*
	     * If we don't get useful data from that or its a type we don't
	     * recognize, take a swing at it using the file name.
	     */
	    if ($mimeType == 'application/octet-stream' ||
		    $mimeType == 'application/unknown' ||
		    GalleryCoreApi::convertMimeToExtension($mimeType) == null) {
		$extension = GalleryUtilities::getFileExtension($form['name'][1]);
		$mimeType = GalleryCoreApi::convertExtensionToMime($extension);
	    }

	    list ($ret, $item) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'WatermarkImage');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!isset($item)) {
		return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	    }

	    $ret = $item->create($form['tmp_name'][1], $mimeType, $form['name'][1]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = $item->save();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Give appropriate permissions */
	    list ($ret, $id) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
		
	    $ret = GalleryCoreApi::addGroupPermission($item->getId(), $id, 'core.all');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = GalleryCoreApi::addUserPermission($item->getId(), $gallery->getActiveUserId(),
						     'core.all');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $results['redirect']['view'] = 'core:UserAdmin';
	    $results['redirect']['subView'] = 'watermark:UserWatermarkEdit';
	    $results['redirect']['itemId'] = $item->getId();
	} else if (isset($form['action']['add'])) {
	    $error[] = 'form[error][missingFile]';
	    $results['delegate']['view'] = 'core:UserAdmin';
	    $results['delegate']['subView'] = 'watermark:UserWatermarks';
	} else if (isset($form['action']['delete']) &&
		   isset($form['delete']['itemId'])) {

	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($form['delete']['itemId']);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		    // Remap it as permission denied so that we avoid object id fishing
		    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
		} else {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    if (!GalleryUtilities::isA($item, 'WatermarkImage') ||
		    $item->getOwnerId() != $gallery->getActiveUserId()) {
		return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
	    }
	    
	    $ret = GalleryCoreApi::deleteEntityById($form['delete']['itemId']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    $status['delete'] = 1;
	    $results['redirect']['view'] = 'core:UserAdmin';
	    $results['redirect']['subView'] = 'watermark:UserWatermarks';
	}

	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class UserWatermarksView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/WatermarkHelper.class');

	list ($ret, $anonymousUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($gallery->getActiveUserId() == $anonymousUserId) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
	}

	list ($ret, $watermarks) = WatermarkHelper::fetchWatermarks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($watermarks as $id => $watermark) {
	    /* Exclude site-wide watermarks (and, in the case of admins -- other people's) */
	    if ($watermark->getOwnerId() != $gallery->getActiveUserId()) {
		unset($watermarks[$id]);
		continue;
	    }
	    
	    $watermarks[$id] = $watermark->getMemberData();
	}

	if ($form['formName'] != 'UserWatermarks') {
	    $form['formName'] = 'UserWatermarks';
	    if (!empty($watermarks)) {
		$form['watermarkId'] = array_shift(array_keys($watermarks));
	    }
	}
	
	/* Set the form's encoding type since we're uploading binary files */
	if ($template->hasVariable('UserAdmin')) {
	    $UserAdmin =& $template->getVariableByReference('UserAdmin');
	    $UserAdmin['enctype'] = 'multipart/form-data';
	} else {
	    $UserAdmin['enctype'] = 'multipart/form-data';
	    $template->setVariable('UserAdmin', $UserAdmin);
	}

	$UserWatermarks = array();
	$UserWatermarks['watermarks'] = $watermarks;

	$template->setVariable('UserWatermarks', $UserWatermarks);
	$template->setVariable('controller', 'watermark:UserWatermarks');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/watermark/templates/UserWatermarks.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	list ($ret, $core) = GalleryCoreApi::loadPlugin('module', 'watermark');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	return array(GalleryStatus::success(), $core->translate('user watermarks'));
    }
}
?>

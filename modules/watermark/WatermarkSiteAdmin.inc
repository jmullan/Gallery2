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
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class WatermarkSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
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

	    list ($ret, $adminGroupId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ret = GalleryCoreApi::addGroupPermission($item->getId(), $adminGroupId, 'core.viewSource');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $status['add'] = 1;
	} else if (isset($form['action']['add'])) {
	    $status['add_error'] = 1;
	} else if (isset($form['action']['delete']) &&
		   isset($form['delete']['itemId'])) {

	    $ret = GalleryCoreApi::deleteEntityById($form['delete']['itemId']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status['delete'] = 1;
	}

	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'watermark:WatermarkSiteAdmin';
	$results['status'] = $status;
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class WatermarkSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	require_once(dirname(__FILE__) . '/classes/WatermarkHelper.class');

	if ($form['formName'] != 'WatermarkSiteAdmin') {
	    $form['formName'] = 'WatermarkSiteAdmin';
	}
	list ($ret, $list) = WatermarkHelper::fetchWatermarks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$form['list'] = array();
	foreach ($list as $id => $fileName) {
	    $form['list'][] = array('id' => $id, 'name' => $fileName);
	}

	/* Set the form's encoding type since we're uploading binary files */
	if ($template->hasVariable('SiteAdmin')) {
	    $SiteAdmin =& $template->getVariableByReference('SiteAdmin');
	    $SiteAdmin['enctype'] = 'multipart/form-data';
	} else {
	    $SiteAdmin['enctype'] = 'multipart/form-data';
	    $template->setVariable('SiteAdmin', $SiteAdmin);
	}

	$template->setVariable('controller', 'watermark:WatermarkSiteAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/watermark/templates/SiteAdmin.tpl'));
    }
}
?>

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
 * @package Thumbnail
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package Thumbnail
 * @subpackage UserInterface
 */
class ThumbnailSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	require_once(dirname(__FILE__) . '/classes/ThumbnailHelper.class');

	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = '';
	if (isset($form['action']['add'])) {
	    if (empty($form['mimeType'])) {
		return array(GalleryStatus::success(), $this->_exitStatus('mime_error'));
	    }
	    list ($ret, $tList) = GalleryCoreApi::getToolkitOperationMimeTypes('thumbnail');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $cList) = GalleryCoreApi::getToolkitOperationMimeTypes('convert-to-image/jpeg');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $mimeMap = array_merge_recursive($tList, $cList);
	    if (isset($mimeMap[$form['mimeType']])) {
		return array(GalleryStatus::success(), $this->_exitStatus('mime_duplicate'));
	    }
	}

	if (isset($form['action']['add']) && $form['image']=='new') {
	    if (empty($form['tmp_name'][1])) {
		return array(GalleryStatus::success(), $this->_exitStatus('file_error'));
	    }
	    $this->_addItem($form['mimeType'], $form['name'][1], $form['tmp_name'][1], $form['type'][1]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status = 'add';
	} else if (isset($form['action']['add'])) { /* $form['image']=='old' */
	    $ret = $this->_updateItem($form['oldimage'], $form['mimeType'], true);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status = 'addMime';
	} else if (isset($form['action']['delete']) && isset($form['delete']['itemId'])) {
	    if (isset($form['delete']['mimeType'])) {
		$ret = $this->_updateItem($form['delete']['itemId'], $form['delete']['mimeType'], false);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status = 'deleteMime';
	    } else {
		list ($ret, $item) = GalleryCoreApi::loadEntitiesById($form['delete']['itemId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$itemMimeTypesList = $item->getItemMimeTypesList();
		$ret = GalleryCoreApi::deleteEntityById($form['delete']['itemId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$ret = GalleryCoreApi::unregisterToolkitOperation('Thumbnail',
				       'convert-to-image/jpeg', $itemMimeTypesList);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status = 'delete';
	    }
	}

	return array(GalleryStatus::success(), $this->_exitStatus($status));
    }

    function _exitStatus($status) {
	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'thumbnail:ThumbnailSiteAdmin';
	$results['status'] = array($status => 1);
	$results['error'] = array();
	return $results;
   }

    function _addItem($mimeType, $filename, $tmpfile, $fileMimeType) {
	global $gallery;
	/*
	 * If we don't get useful data from the form or its a type we don't
	 * recognize, take a swing at it using the file name.
	 */
	if ($fileMimeType == 'application/octet-stream' ||
	        $fileMimeType == 'application/unknown' ||
	        GalleryUtilities::convertMimeToExtension($fileMimeType) == null) {
	    $extension = GalleryUtilities::getFileExtension($filename);
	    $fileMimeType = GalleryUtilities::convertExtensionToMime($extension);
	}

	list ($ret, $item) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'ThumbnailImage');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!isset($item)) {
	    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	}

	$ret = $item->create($tmpfile, $fileMimeType, $filename);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$item->setitemMimeTypes($mimeType);
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

	$ret = GalleryCoreApi::registerToolkitOperation('Thumbnail',
				array($mimeType), 'convert-to-image/jpeg', array(),
				$gallery->i18n('Convert to a JPEG'), 'image/jpeg');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return GalleryStatus::success();
    }

    function _updateItem($itemId, $mimeType, $isAdd=true) {
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$mimeTypes = $item->getItemMimeTypesList();
	if ($isAdd) {
	    $mimeTypes[] = $mimeType;
	    $item->setItemMimeTypesList($mimeTypes);
	} else {
	    $newList = array();
	    foreach ($mimeTypes as $mime) {
		if ($mime != $mimeType) {
		    $newList[] = $mime;
		}
	    }
	    $item->setItemMimeTypesList($newList);
	}
	$ret = $item->save();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$ret = GalleryCoreApi::releaseLocks($lockId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($isAdd) {
	    global $gallery;
	    $ret = GalleryCoreApi::registerToolkitOperation('Thumbnail',
				   array($mimeType), 'convert-to-image/jpeg', array(),
				   $gallery->i18n('Convert to a JPEG'), 'image/jpeg');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $ret = GalleryCoreApi::unregisterToolkitOperation('Thumbnail',
				   'convert-to-image/jpeg', array($mimeType));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	return GalleryStatus::success();
    }
}

/**
 * @package Thumbnail
 * @subpackage UserInterface
 */
class ThumbnailSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	require_once(dirname(__FILE__) . '/classes/ThumbnailHelper.class');

	if ($form['formName'] != 'ThumbnailSiteAdmin') {
	    $form['formName'] = 'ThumbnailSiteAdmin';
	}

	$form['mimeMap'] = GalleryUtilities::getMimeTypeMap();
	ksort($form['mimeMap']);

	list ($ret, $list) = ThumbnailHelper::fetchThumbnails();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$form['list'] = array();
	if (!empty($list)) {
	    list ($ret, $thumbs) = GalleryCoreApi::loadEntitiesById(array_keys($list));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($thumbs as $thumb) {
		$data = $thumb->getMemberData();
		$data['itemMimeTypesList'] = array();
		foreach ($thumb->getItemMimeTypesList() as $mime) {
		    if (isset($form['mimeMap'][$mime])) {
			$data['itemMimeTypesList'][] = array($mime,
			    $mime . ' (' . implode(' ', $form['mimeMap'][$mime]) . ')');
		    } else {
			$data['itemMimeTypesList'][] = array($mime, $mime);
		    }
		}
		$form['list'][] = $data;
	    }
	}

	$form['badMime'] = array();
	list ($ret, $tList) = GalleryCoreApi::getToolkitOperationMimeTypes('thumbnail');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $cList) = GalleryCoreApi::getToolkitOperationMimeTypes('convert-to-image/jpeg');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach (array_merge_recursive($tList, $cList) as $mime => $toolkits) {
	    foreach ($toolkits as $id) {
		if (!isset($op[$id]) || !in_array($mime, $op[$id])) {
		    $op[$id][] = $mime;
		}
	    }
	    if (in_array('Thumbnail', $toolkits) && count($toolkits) > 1) {
		$form['badMime'][] = $mime;
	    }
	}
	unset($op['Thumbnail']);
	$form['operationSupport'] = $op;

	/* Set the form's encoding type since we're uploading binary files */
	if ($template->hasVariable('SiteAdmin')) {
	    $SiteAdmin =& $template->getVariableByReference('SiteAdmin');
	    $SiteAdmin['enctype'] = 'multipart/form-data';
	} else {
	    $SiteAdmin['enctype'] = 'multipart/form-data';
	    $template->setVariable('SiteAdmin', $SiteAdmin);
	}

	$template->setVariable('controller', 'thumbnail:ThumbnailSiteAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/thumbnail/templates/SiteAdmin.tpl'));
    }
}
?>

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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the deletion of an item
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemDeleteController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* 
	 * Get the parent id -- it's the destination item after we delete this
	 * one
	 */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$parentId = $item->getParentId();

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($item->getId() == $rootId) {
	    if ($gallery->getDebug()) {
		$gallery->debug("Can't delete the root album");
	    }
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	if (isset($form['action']['delete'])) {

	    $ret = $gallery->deleteEntityById($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Figure out where to redirect upon success */
	    $redirect['view'] = 'core:ItemAdmin';
	    $redirect['itemId'] = $parentId;
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemDelete';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for confirmation on the deletion of an item
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemDeleteView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	if ($item->getId() == $rootId) {
	    if ($gallery->getDebug()) {
		$gallery->debug("Can't delete the root album");
	    }
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null, null);
	}
	
	/* Count its children */
	$childCount = 0;
	if ($item->getCanContainChildren()) {
	    list ($ret, $childCountTable) = GalleryItemHelper::getChildCounts(array($item->getId()));
	    if (isset($childCountTable[$item->getId()])) {
		$childCount = $childCountTable[$item->getId()];
	    }
	}
	
	/* Get the type of the item */
	if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
	    $itemType = 'album';
	} else {
	    $itemType = 'item';
	}

	$ItemDelete = array();
	$ItemDelete['itemType'] = $itemType;
	$ItemDelete['childCount'] = $childCount;

	$template->setVariable('controller', 'core:ItemDelete');
	$template->setVariable('ItemDelete', $ItemDelete);

	return array(GalleryStatus::success(), '', 'modules/core/templates/ItemDelete.tpl');
    }
}
?>

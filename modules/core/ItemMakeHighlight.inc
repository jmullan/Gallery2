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
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will make an item the highlight for its parent
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemMakeHighlightController extends GalleryController {

    /**
     * 
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$parentId = $item->getParentId();

	/* Make sure we have permission to edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($parentId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	if (isset($form['action']['makeHighlight'])) {
	    $ret = GalleryItemHelper::setThumbnailFromItem($parentId, $itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    /* Figure out where to redirect upon success */
	    $redirect['view'] = 'core:ItemAdmin';
	    $redirect['itemId'] = $item->getId();
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
 * This view will prompt for files to add as children to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemMakeHighlightView extends GalleryView {

    /**
     * 
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$parentId = $item->getParentId();

	/* Make sure we have permission do edit the parent of this item */
	$ret = GalleryUserHelper::assertHasItemPermission($parentId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($form['formName'] != 'ItemMakeHighlight') {
	    $form['formName'] = 'ItemMakeHighlight';
	}

	$ItemMakeHighlight = array();

	/* Render the HTML body */
	$template->setVariable('ItemMakeHighlight', $ItemMakeHighlight);
	$template->setVariable('controller', 'core:ItemMakeHighlight');

	return array(GalleryStatus::success(), '', 'modules/core/templates/ItemMakeHighlight.tpl');
    }
}
?>

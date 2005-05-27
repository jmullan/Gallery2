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
 * @package Cart
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Required classes
 */
GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/CartHelper.class');

/**
 * This controller will handle the addition of a comment to an item
 *
 * @package Cart
 * @subpackage UserInterface
 */
class AddToCartController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out what ids we care about */
	if ($item->getCanContainChildren()) {
	    list ($ret, $ids) = GalleryCoreApi::fetchChildDataItemIds($item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $ids = array($item->getId());
	}

	$ret = CartHelper::addItemsToCart($ids);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Prepare our results */
	$results['redirect']['view'] = 'cart.ViewCart';
	$results['status'] = array();
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}
?>

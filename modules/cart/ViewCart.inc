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
 * @package Comment
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

require_once(dirname(__FILE__) . '/classes/CartHelper.class');

/**
 * This view will show the comments stored for an item
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class ViewCartView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($ret, $cartItemIds) = CartHelper::fetchCartItemCounts();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ViewCart') {
	    /* First time around, initialize the cart counts */
	    foreach ($cartItemIds as $itemId => $count) {
		$form['counts'][$itemId] = $count;
	    }
	    $form['formName'] = 'ViewCart';
	}

	$items = array();
	$thumbnails = array();
	if (!empty($cartItemIds)) {
	    /* Fetch items */
	    list ($ret, $itemList) = GalleryCoreApi::loadEntitiesById(array_keys($cartItemIds));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($itemList as $item) {
		$items[$item->getId()] = $item->getMemberData();
	    }
		
	    /* Fetch thumbnails */
	    list ($ret, $thumbnailList) =
		GalleryCoreApi::fetchThumbnailsByItemIds(array_keys($cartItemIds));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($thumbnailList as $thumbnail) {
		$thumbnails[$thumbnail->getParentId()] = $thumbnail->getMemberData();
	    }
	}

	$ViewCart = array();
	$ViewCart['items'] = $items;
	$ViewCart['thumbnails'] = $thumbnails;
	$ViewCart['controller'] = 'cart:ModifyCart';

	$template->setVariable('ViewCart', $ViewCart);
	return array(GalleryStatus::success(),
		     array('head' => 'modules/cart/templates/ViewCartHead.tpl',
			   'body' => 'modules/cart/templates/ViewCart.tpl'));
    }
}
?>

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

require_once(dirname(__FILE__) . '/classes/CartHelper.class');

/**
 * @version $Revision$ $Date$
 * @package Cart
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the addition of a comment to an item
 *
 * @package Cart
 * @subpackage UserInterface
 *
 */
class ModifyCartController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
	global $gallery;

	list ($ret, $cartItemIds) = CartHelper::fetchCartItemCounts();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	if (!isset($form['action']) || isset($form['action']['update'])) {
	    /* Update counts */
	    if (isset($form['counts'])) {
		foreach ($form['counts'] as $itemId => $count) {
		    if ($count <= 0) {
			unset($cartItemIds[$itemId]);
		    } else {
			$cartItemIds[$itemId] = (int)$count;
		    }
		}
	    }
	    
	    /* Delete whatever needs deleting */
	    if (isset($form['delete'])) {
		foreach ($form['delete'] as $itemId => $junk) {
		    unset($cartItemIds[$itemId]);
		}
	    }

	    /* Update the cart values */
	    $ret = CartHelper::setCartItemCounts($cartItemIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status['cartModified'] = 1;
	} else if (isset($form['action']['empty'])) {
	    /* Empty the cart */
	    $ret = CartHelper::setCartItemCounts(array());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status['cartModified'] = 1;
	}

	/* Prepare our results */
	$results['redirect']['view'] = 'cart:ViewCart';
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}
?>

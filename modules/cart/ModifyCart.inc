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
 * This controller will handle the changing of item quantities in a cart
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
	list ($ret, $cartItemIds) = CartHelper::fetchCartItemCounts();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	$results = array();
	if (!isset($form['action']) || isset($form['action']['modify'])) {
	    switch ($form['pluginId']) {
	    case 'updateCart':
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
		break;

	    case 'emptyCart':
		/* Empty the cart */
		$ret = CartHelper::setCartItemCounts(array());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['cartModified'] = 1;
		break;

	    default:
		/* Expect it to be one of our plugins */
		require_once(dirname(__FILE__) . '/classes/CartPluginInterface_1_0.class');
		list ($ret, $cartPlugin) =
		    GalleryCoreApi::newFactoryInstanceById('CartPluginInterface_1_0',
							   $form['pluginId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($cartPlugin)) {
		    break;
		}

		/* Pass in only the types the plugin supports */
		list ($ret, $itemList) = GalleryCoreApi::loadEntitiesById(array_keys($cartItemIds));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$fulfillmentCart = array();
		$supportedTypes = $cartPlugin->getSupportedItemTypes();
		foreach ($itemList as $item) {
		    foreach ($supportedTypes as $type) {
			if ($type == '*' || GalleryUtilities::isA($item, $type)) {
			    $fulfillmentCart[$item->getId()] = $cartItemIds[$item->getId()];
			    break;
			}
		    }
		}

		list ($ret, $redirect) = $cartPlugin->fulfillCart($fulfillmentCart);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Remove the fulfilled items */
		foreach (array_keys($fulfillmentCart) as $id) {
		    unset($cartItemIds[$id]);
		}

		/* Save the modified cart */
		$ret = CartHelper::setCartItemCounts($cartItemIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($redirect['href'])) {
		    /* If we're redirecting offsite, don't include the status */
		    $status['cartModified'] = 1;
		}

		/* Redirect according to the wishes of the cart plugin */
		$results['redirect'] = $redirect;
		break;
	    }
	}

	/* Prepare our results */
	if (!isset($results['redirect'])) {
	    $results['redirect']['view'] = 'cart:ViewCart';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}
?>

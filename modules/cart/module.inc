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
 * @package Cart
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * The implementation of the core-module
 *
 * @package Cart
 */
class CartModule extends GalleryModule {

    function CartModule() {
	global $gallery;

	$this->setId('cart');
	$this->setName('Cart');
	$this->setDescription($gallery->i18n('Shopping Cart Module'));
	$this->setVersion('0.8.4');
	$this->setGroup('commerce', $this->translate('Commerce'));
	$this->setCallbacks('getItemLinks|loadSystemContent|registerEventListeners');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	GalleryCoreApi::registerEventListener('GalleryEntity::delete', new CartModule());
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	global $gallery;

	$links = array();
	foreach ($items as $item) {
	    $itemTypeNames = $item->itemTypeName();
	    $links[$item->getId()][] =
		array('text' => $this->translate(array('text' => 'add %s to cart',
						       'arg1' => $itemTypeNames[1])),
		      'params' => array('controller' => 'cart:AddToCart',
					'itemId' => $item->getId(),
					'return' => true));
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	global $gallery;
	$content = array();

	$view = GalleryUtilities::getRequestVariables('view');
	if ($view == 'cart:ViewCart') {
	    return array(GalleryStatus::success(), array());
	}

	/* The "View Cart" link */
	$links = array();
	$links[] = array('text' => $this->translate('View Cart'),
			 'params' => array('view' => 'cart:ViewCart',
					   'return' => true));
	$CartSystemContent['links'] = $links;

	/* The cart content's count */
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/CartHelper.class');
	list ($ret, $cartItemIds) = CartHelper::fetchCartItemCounts();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$CartSystemContent['count'] = 0;
	foreach ($cartItemIds as $itemId => $count) {
	    $CartSystemContent['count'] += $count;
	}

	$template->setVariable('CartSystemContent', $CartSystemContent);

	$content = array();
	$content['cart'] = 'modules/cart/templates/CartSystemContent.tpl';

	return array(GalleryStatus::success(), $content);
    }

    /**
     * Event handler for GalleryEntity::delete event.
     * Remove deleted item from all carts.
     *
     * @param object GalleryEvent the event
     * @return object GalleryStatus a status code
     */
    function handleEvent($event) {
	$entity = $event->getEntity();
	if (GalleryUtilities::isA($entity, 'GalleryDataItem')) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/CartHelper.class');
	    $ret = CartHelper::removeIdFromAllCarts($entity->getId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	return GalleryStatus::success();
    }
}
?>

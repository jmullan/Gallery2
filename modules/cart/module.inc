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
	$this->setVersion('0.8.1');
	$this->setGroup('commerce', $gallery->i18n('Commerce'));
	$this->setCallbacks('getItemLinks|getSystemLinks');
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
					'itemId' => $item->getId()));
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks() {
	$links[] = array('text' => $this->translate('View Cart'),
			 'params' => array('view' => 'cart:ViewCart'));
	return array(GalleryStatus::success(), $links);
    }
}
?>

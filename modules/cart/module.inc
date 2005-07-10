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
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * The implementation of the cart module
 *
 * @package Cart
 */
class CartModule extends GalleryModule {

    function CartModule() {
	global $gallery;

	$this->setId('cart');
	$this->setName($gallery->i18n('Cart'));
	$this->setDescription($gallery->i18n('Shopping Cart Module'));
	$this->setVersion('0.9.6'); /* Update upgrade() function below too */
	$this->setGroup('commerce', $this->translate('Commerce'));
	$this->setCallbacks('getItemLinks');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredModuleApi(array(2, 0));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!empty($currentVersion)) {
	    switch ($currentVersion) {
	    case '0.8':
	    case '0.8.1':
	    case '0.8.2':
	    case '0.8.3':
	    case '0.8.4':
	    case '0.8.5':
	    case '0.8.6':
	    case '0.8.7':
	    case '0.8.8':
		$storage =& $gallery->getStorage();
		$query = '
		  DROP TABLE [CartMap]
		';
		$ret = $storage->execute($query);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		$query = '
		  DELETE FROM [Schema]
		  WHERE [Schema::name] = \'CartMap\'
		';
		$ret = $storage->execute($query);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

	    case '0.8.9':
	    case '0.8.10':
	    case '0.9.1':
	    case '0.9.2':
	    case '0.9.3':
	    case '0.9.4':
	    case '0.9.5':

	    case 'end of upgrade path':
		break;

	    default:
		return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					    sprintf('Unknown module version %s', $currentVersion));
	    }
	}

	return GalleryStatus::success();
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
    function getItemLinks($items, $wantsDetailedLinks, $permissions) {
	$links = array();
	foreach ($items as $item) {
	    $itemTypeNames = $item->itemTypeName();
	    $links[$item->getId()][] =
		array('text' => $this->translate(array('text' => 'add %s to cart',
						       'arg1' => $itemTypeNames[1])),
		      'params' => array('controller' => 'cart.AddToCart',
					'itemId' => $item->getId(),
					'return' => true));
	}

	return array(GalleryStatus::success(), $links);
    }
}
?>

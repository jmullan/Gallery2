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
 * @package Rearrange
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * The implementation of the Rearrange module
 *
 * @package Rearrange
 */
class RearrangeModule extends GalleryModule {

    function RearrangeModule() {
	global $gallery;
	$this->setId('rearrange');
	$this->setName('Rearrange');
	$this->setDescription($gallery->i18n('Rearrange the order of album items all at once'));
	$this->setVersion('0.7.0');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('getItemLinks|getItemAdminViews');
	$this->setRequiredCoreApi(array(3, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	$links = array();

	$itemIds = array();
	foreach ($items as $item) {
	    if ($item->getCanContainChildren()) {
		$itemIds[] = $item->getId();
	    }
	}
	if (empty($itemIds)) {
	    return array(GalleryStatus::success(), $links);
	}

	list ($ret, $childCounts) = GalleryCoreApi::fetchChildCounts($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach ($itemIds as $itemId) {
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['core.edit']) &&
		    !empty($childCounts[$itemId]) && $childCounts[$itemId] > 1) {
		$links[$itemId][] =
		    array('text' => $this->translate('rearrange items'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'rearrange:RearrangeItems',
					    'itemId' => $itemId, 'return' => 1));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	$views = array();
	if (!$item->getCanContainChildren()) {
	    return array(GalleryStatus::success(), $views);
	}

	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $childCounts) = GalleryCoreApi::fetchChildCounts(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$childCount = empty($childCounts[$item->getId()]) ? 0 : $childCounts[$item->getId()];

	if (isset($permissions['core.edit']) && $childCount > 1) {
	    $views[] = array('name' => $this->translate('Rearrange Items'),
			     'view' => 'rearrange:RearrangeItems');
	}

	return array(GalleryStatus::success(), $views);
    }
}
?>

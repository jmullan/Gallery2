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
 * @package Gallery
 * @author Alan Harder <alan.harder@sun.com>
 */

/** 
 * This implements gallery layout combining thumb-view, image-view
 * and slideshow into a single dynamic page.
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class HybridLayout extends GalleryLayout {

    /**
     * @see GalleryLayout::init()
     */
    function init() {
	global $gallery;

	$this->setId('hybrid');
	$this->setName('Hybrid');
	$this->setDescription($gallery->i18n('Combined album/image/slideshow dynamic view'));
	$this->setVersion('0.1');
	$this->setL10Domain('layouts_hybrid');
	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    function loadTemplate(&$template, $item) {
	global $gallery;

	$layout = array();
	$layout['title'] = $item->getTitle();
	if (empty($layout['title'])) {
	    $layout['title'] = $item->getPathComponent();
	}
	$layout['item'] = $item->getMemberData();

	if (!$item->getCanContainChildren()) {
	    /* Get item details */
	    list ($ret, $moduleItemDetailFiles) = $this->_loadModuleItemDetails($template, $item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout['moduleItemDetailFiles'] = $moduleItemDetailFiles;
	    $template->setVariable('layout', $layout);
	    return array(GalleryStatus::success(),
	                 array('main' => 'layouts/hybrid/templates/detail.tpl'));
	}

	list ($ret, $itemList, $imageWidths, $imageHeights) =
	    $this->_buildItemList($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout['itemList'] = $itemList;
	$layout['count'] = count($itemList);
	$layout['imageWidths'] = implode(',',$imageWidths);
	$layout['imageHeights'] = implode(',',$imageHeights);

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system content */
	list ($ret, $moduleSystemContentFiles) = $this->_loadModuleSystemContent($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item links and flatten out the modules */
	$moduleItemLinks = array();
	list ($ret, $tmp) = $this->_getModuleItemLinks($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($tmp as $tmpId => $moduleLinks) {
	    foreach ($moduleLinks as $module => $links) {
		$moduleItemLinks = array_merge($moduleItemLinks, $links);
	    }
	}
	usort($moduleItemLinks, array($this, '_sortItemLinks'));

	/* Load the parents */
	list ($ret, $parents) = GalleryCoreApi::fetchParents($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	for ($i = 0; $i < sizeof($parents); $i++) {
	    $parents[$i] = $parents[$i]->getMemberData();
	}

	/* Get the active user */
	list ($ret, $user) = $gallery->getActiveUser();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout['user'] = $user->getMemberData();
	$layout['moduleSystemLinks'] = $moduleSystemLinks;
	$layout['moduleSystemContentFiles'] = $moduleSystemContentFiles;
	$layout['moduleItemLinks'] = $moduleItemLinks;
//	$layout['totalChildCount'] = $totalChildCount;
//	$layout['totalDescendentCount'] = $totalDescendentCount;
	$layout['layoutUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));
	$layout['parents'] = $parents;
//	if (!empty($parents)) {
//	    $layout['parent'] = $parents[sizeof($parents)-1];
//	} else {
//	    $layout['parent'] = null;
//	}

	$template->setVariable('layout', $layout);
	return array(GalleryStatus::success(),
//	             array('main' => 'layouts/hybrid/templates/hybrid.tpl'));
array('body' => 'layouts/hybrid/templates/hybrid.tpl',
      'head' => 'layouts/hybrid/templates/header.tpl',
      'onLoad' => 'app_onload()', 'onUnload' => 'app_setcookie()'));
    }

    function _buildItemList(&$item) {
	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$itemList = array();
	$imageWidths = array();
	$imageHeights = array();
	$childItems = array();
	if (!empty($childIds)) {
	    $ret = GalleryCoreApi::studyPermissions($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $childItems) = GalleryCoreApi::loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $preferredFullImages) =
		GalleryCoreApi::fetchPreferredsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
//	    list ($ret, $resizedImages) =
//		GalleryCoreApi::fetchResizesByItemIds($childIds);
//	    if ($ret->isError()) {
//		return array($ret->wrap(__FILE__, __LINE__), null);
//	    }
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    // If an Exif extractor is available try to get capture dates..
//	    $exif = array();
//	    if (isset($this->exifExtractor)) {
//		list ($ret, $exif) =
//		    $this->exifExtractor->getMetaData($childIds);
//		if ($ret->isError()) {
//		    return array($ret->wrap(__FILE__, __LINE__), null);
//		}
//	    }
	}
	foreach ($childItems as $child) {
	    $childId = $child->getId();
	    $newItem = array('id' => $childId,
			     'data' => $child->getMemberData(),
			     'isContainer' => $child->getCanContainChildren());
	    if (isset($thumbnails[$childId])) {
		$newItem['thumb'] = $thumbnails[$childId]->getMemberData();
	    }

	    /* Get item links and flatten out the modules */
	    $moduleItemLinks = array();
	    list ($ret, $tmp) = $this->_getModuleItemLinks($child);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($tmp as $tmpId => $moduleLinks) {
		foreach ($moduleLinks as $module => $links) {
		    $moduleItemLinks = array_merge($moduleItemLinks, $links);
		}
	    }
	    if (!empty($moduleItemLinks)) {
		usort($moduleItemLinks, array($this, '_sortItemLinks'));
		$newItem['moduleItemLinks'] = $moduleItemLinks;
	    }

	    if (is_a($child, 'GalleryDataItem') && $child->canBeViewedInline()) {
		list ($ret, $permissions) =
		    GalleryCoreApi::getPermissions($childId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$images = array();
		if (isset($permissions['core.viewSource'])) {
		    // Full size; check for preferred copy
		    if (isset($preferredFullImages[$childId])) {
			$images[] = $preferredFullImages[$childId];
		    } else {
			$images[] = $child;
		    }
		}
//		if (isset($permissions['core.viewResizes']) &&
//			isset($resizedImages[$childId])) {
//		    foreach ($resizedImages[$childId] as $resize) {
//			$images[] = $resize;
//		    }
//		}
		if (isset($thumbnails[$childId])) {
		    $images[] = $thumbnails[$childId];
		}

		if (!empty($images)) {
		    $image = $images[0];

		    // Rebuild derivative if needed so width/height known..
		    if (is_a($image, 'GalleryDerivativeImage')) {
			list ($ret, $image) =
			    GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent(
				    $image->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		    $image = $image->getMemberData();
		    if ($image['width'] > 0 && $image['height'] > 0) {
			$newItem['image'] = $image;
			$newItem['imageIndex'] = count($imageWidths);
			$imageWidths[] = $image['width'];
			$imageHeights[] = $image['height'];
		    }
		}
	    }

	    $itemList[] = $newItem;
	}
	return array(GalleryStatus::success(), $itemList,
	             $imageWidths, $imageHeights);
    }

    function _sortItemLinks($a, $b) {
	return strcmp($a['text'], $b['text']);
    }
}


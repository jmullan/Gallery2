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
 * This implements a gallery layout with a scrollable view of all image thumbnails
 * and slideshow support in a single dynamic page.  Displays inline items ONLY; subalbums
 * or other items types are NOT shown.
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class SliderLayout extends GalleryLayout {

    /**
     * Constructor
     */
    function SliderLayout() {
	global $gallery;

	$this->setId('slider');
	$this->setName('Slider');
	$this->setDescription($gallery->i18n('Image viewer/slideshow; subalbums/other items not shown'));
	$this->setVersion('0.8');
	$this->setL10Domain('layouts_slider');

	return GalleryStatus::success();
    }

    function loadTemplate(&$template, $item) {
	global $gallery;
	$renderId = GalleryUtilities::getRequestVariables('renderId');

	if (!$item->getCanContainChildren() && !empty($renderId)) {
	    /* Render this item */
	    list ($ret, $image) = GalleryCoreApi::loadEntitiesById($renderId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout = array('item' => $item->getMemberData(),
			    'image' => $image->getMemberData());
	    $template->setVariable('layout', $layout);
	    return array(GalleryStatus::success(),
			 array('html' => 'layouts/slider/templates/render.tpl'));
	}

	if (!$item->getCanContainChildren()) {
	    /* Load parent with initial view of this item  */
	    $viewItemId = $item->getId();
	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$layout = array();
	$layout['title'] = $item->getTitle();
	if (empty($layout['title'])) {
	    $layout['title'] = $item->getPathComponent();
	}
	$layout['item'] = $item->getMemberData();

	list ($ret, $itemList, $imageWidths, $imageHeights, $maxTW, $maxTH) =
	    $this->_buildItemList($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout['itemList'] = $itemList;
	$layout['count'] = count($itemList);
	$layout['imageWidths'] = implode(',',$imageWidths);
	$layout['imageHeights'] = implode(',',$imageHeights);
	$layout['maxThumbWidth'] = $maxTW;
	$layout['maxThumbHeight'] = $maxTH;
	$layout['imageCount'] = count($imageWidths);
	$layout['layoutUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));

	$urlGenerator = $gallery->getUrlGenerator();
	$cookiePath = preg_replace('|^[^/]*//[^/]*/|', '/', $urlGenerator->getCurrentUrlDir());
	$layout['cookiePath'] = $cookiePath;

	/* Init view with specific image */
	if (isset($viewItemId)) {
	    foreach ($itemList as $tmp) {
		if ($tmp['id'] == $viewItemId) {
		    if (isset($tmp['imageIndex'])) {
			$layout['viewIndex'] = $tmp['imageIndex'];
			/* Set cookie to popup image just once */
			$cook = 'G2_slider_' . $item->getId();
			setcookie($cook, '-2' .
			    (isset($_COOKIE[$cook]) ? strstr($_COOKIE[$cook], ';') : ';'),
			    0, $cookiePath);
		    }
		    break;
		}
	    }
	}

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
	$user = $gallery->getActiveUser();

	$layout['moduleSystemLinks'] = $moduleSystemLinks;
	$layout['moduleSystemContentFiles'] = $moduleSystemContentFiles;
	$layout['moduleItemLinks'] = $moduleItemLinks;
	$layout['parents'] = $parents;
	$layout['user'] = $user->getMemberData();

	$template->setVariable('layout', $layout);
	return array(GalleryStatus::success(),
		array('body' => 'layouts/slider/templates/slider.tpl',
		      'head' => 'layouts/slider/templates/header.tpl'));
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
	$maxTW = $maxTH = 0;
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
	    list ($ret, $resizedImages) =
		GalleryCoreApi::fetchResizesByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	foreach ($childItems as $child) {
	    $childId = $child->getId();
	    $newItem = array('id' => $childId,
			     'data' => $child->getMemberData(),
			     'isContainer' => $child->getCanContainChildren());
	    if (isset($thumbnails[$childId])) {
		// Rebuild derivative if needed so width/height known..
		$thumb = $thumbnails[$childId];
		if (!($thumb->getWidth() && $thumb->getHeight())) {
		    list ($ret, $thumb) = GalleryCoreApi::rebuildDerivativeCache($thumb->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$newItem['thumb'] = $thumb = $thumb->getMemberData();
		if ($thumb['width'] > $maxTW) {
		    $maxTW = $thumb['width'];
		}
		if ($thumb['height'] > $maxTH) {
		    $maxTH = $thumb['height'];
		}
	    }

	    if (GalleryUtilities::isA($child, 'GalleryDataItem') && $child->canBeViewedInline()) {
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
		if (isset($permissions['core.viewResizes']) &&
			isset($resizedImages[$childId])) {
		    foreach ($resizedImages[$childId] as $resize) {
			$images[] = $resize;
		    }
		}
		if (isset($thumbnails[$childId])) {
		    $images[] = $thumbnails[$childId];
		}

		if (!empty($images)) {
		    $image = $images[0];

		    // Rebuild derivative if needed so width/height known..
		    if (GalleryUtilities::isA($image, 'GalleryDerivativeImage')) {
			list ($ret, $image) =
			    GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent(
				    $image->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		    $image = $image->getMemberData();
		    $newItem['image'] = $image;
		    $newItem['imageIndex'] = count($imageWidths);
		    if (GalleryUtilities::isExactlyA($child, 'GalleryPhotoItem') &&
			    $image['width'] > 0 && $image['height'] > 0) {
			// Display in <img>
			$imageWidths[] = $image['width'];
			$imageHeights[] = $image['height'];
		    } else {
			// Item must render itself
			$newItem['renderItem'] = 1;
			$imageWidths[] = $imageHeights[] = -1;
		    }
		}
	    }

	    $itemList[] = $newItem;
	}
	return array(GalleryStatus::success(), $itemList,
	             $imageWidths, $imageHeights, $maxTW, $maxTH);
    }

    function _sortItemLinks($a, $b) {
	return strcmp($a['text'], $b['text']);
    }
}

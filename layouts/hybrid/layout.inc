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
     * Constructor
     */
    function HybridLayout() {
	global $gallery;

	$this->setId('hybrid');
	$this->setName('Hybrid');
	$this->setDescription($gallery->i18n('Combined album/image/slideshow dynamic view'));
	$this->setVersion('0.8');
	$this->setL10Domain('layouts_hybrid');

	return GalleryStatus::success();
    }

    function loadTemplate(&$template, $item) {
	global $gallery;
	$detail = GalleryUtilities::getRequestVariables('detail');
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
	                 array('immediate' => 'layouts/hybrid/templates/render.tpl'));
	}

	if (!$item->getCanContainChildren() && !$detail) {
	    /* Load parent with initial view of this item  */
	    $viewItemId = $item->getId();
	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $params) = $this->fetchParameters($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout = array();
	$layout['title'] = $item->getTitle();
	if (empty($layout['title'])) {
	    $layout['title'] = $item->getPathComponent();
	}
	$layout['item'] = $item->getMemberData();

	if (!$item->getCanContainChildren() && $detail) {
	    /* Get item details */
	    list ($ret, $moduleItemDetailFiles) = $this->_loadModuleItemDetails($template, $item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout['moduleItemDetailFiles'] = $moduleItemDetailFiles;
	    /* Get thumbnail */
	    list ($ret, $thumbnail) =
		GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!empty($thumbnail)) {
		$layout['thumb'] = $thumbnail[$item->getId()]->getMemberData();
	    }
	    /* Get view count */
	    list ($ret, $viewCount) = GalleryCoreApi::fetchItemViewCounts(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!empty($viewCount)) {
		$layout['viewCount'] = $viewCount[$item->getId()];
	    }
	    /* Get owner */
	    list ($ret, $tmp) = GalleryCoreApi::loadEntitiesById($item->getOwnerId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout['owner'] = $tmp->getMemberData();
	    $template->setVariable('layout', $layout);
	    return array(GalleryStatus::success(),
	                 array('html' => 'layouts/hybrid/templates/detail.tpl'));
	}

	list ($ret, $itemList, $imageWidths, $imageHeights) = $this->_buildItemList($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout['itemList'] = $itemList;
	$layout['count'] = count($itemList);
	$layout['imageWidths'] = implode(',',$imageWidths);
	$layout['imageHeights'] = implode(',',$imageHeights);
	$layout['imageCount'] = count($imageWidths);

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
			$cook = 'G2_hybrid_' . $item->getId();
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

	/* Get all the owners */
	$tmpId = array($item->getOwnerId());
	foreach ($itemList as $tmp) {
	    $tmpId[] = $tmp['data']['ownerId'];
	}
	list ($ret, $tmp) = GalleryCoreApi::loadEntitiesById($tmpId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$owners = array();
	foreach ($tmp as $owner) {
	    $owners[$owner->getId()] = $owner->getMemberData();
	}

	/* Get the view counts */
	$tmpId = array($item->getId());
	foreach ($itemList as $tmp) {
	    $tmpId[] = $tmp['id'];
	}
	list ($ret, $viewCounts) = GalleryCoreApi::fetchItemViewCounts($tmpId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Prepare image frames, if available */
	list ($ret, $imageframe) =
	    GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_0');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$list = array();
	foreach (array('albumFrame', 'imageFrame') as $key) {
	    if (!empty($params[$key])) {
		$list[] = $params[$key];
	    }
	}
	if (!empty($list) && isset($imageframe)) {
	    $frame = array();
	    list ($ret, $frame['template'], $frame['style'], $frame['data']) =
		$imageframe->getImageFrameData($list);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout['frame'] = $frame;
	}

	$layout['user'] = $user->getMemberData();
	$layout['moduleSystemLinks'] = $moduleSystemLinks;
	$layout['moduleSystemContentFiles'] = $moduleSystemContentFiles;
	$layout['moduleItemLinks'] = $moduleItemLinks;
	$layout['owner'] = $owners[$item->getOwnerId()];
	$layout['owners'] = $owners;
	$layout['viewCounts'] = $viewCounts;
//	$layout['totalChildCount'] = $totalChildCount;
//	$layout['totalDescendentCount'] = $totalDescendentCount;
	$layout['layoutUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));
	$layout['parents'] = $parents;
	$layout['params'] = $params;

	$template->setVariable('layout', $layout);
	return array(GalleryStatus::success(),
		array('body' => 'layouts/hybrid/templates/hybrid.tpl',
		      'head' => 'layouts/hybrid/templates/header.tpl'));
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
		list ($ret, $thumbnails[$childId]) =
		    GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($thumbnails[$childId]->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
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
			if (!($image->getWidth() && $image->getHeight())) {
			    list ($ret, $image) = GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($image->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
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
	             $imageWidths, $imageHeights);
    }

    function _sortItemLinks($a, $b) {
	return strcmp($a['text'], $b['text']);
    }

    /**
     * @see GalleryLayout::getSettings()
     */
    function getSettings($itemId=null) {
	global $gallery;
	$settings = array();

	list ($ret, $params) = $this->fetchParameters($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$params = array_merge(array('albumFrame' => '', 'imageFrame' => ''), $params);

	/* Image frame settings, if available */
	list ($ret, $imageframe) =
	    GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_0');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($imageframe)) {
	    list ($ret, $list) = $imageframe->getImageFrameList();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $sampleUrl) = $imageframe->getSampleUrl($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $sample = ' (<a href="' . $sampleUrl . '">' .  $gallery->i18n('View Samples') . '</a>)';

	    $settings[] = array('key' => 'albumFrame',
				'name' => $gallery->i18n('Album Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['albumFrame']);
	    $settings[] = array('key' => 'imageFrame',
				'name' => $gallery->i18n('Image Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['imageFrame']);
	}

	return array(GalleryStatus::success(), $settings);
    }
}


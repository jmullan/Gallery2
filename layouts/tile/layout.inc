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
 * This implements a gallery layout with a tiled background image and image thumbnails
 * on top of it; Displays inline items ONLY; subalbums or other item types are NOT shown.
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class TileLayout extends GalleryLayout {

    /**
     * Constructor
     */
    function init() {
	global $gallery;

	$this->setId('tile');
	$this->setName('Tile');
	$this->setDescription($gallery->i18n('Tile view of background image and image thumbnails; subalbums/other items not shown'));
	$this->setVersion('0.3');
	$this->setL10Domain('layouts_tile');

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
			 array('html' => 'layouts/tile/templates/render.tpl'));
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

	list ($ret, $params) = $this->fetchParameters($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($params['backgroundId'])) {
	    list ($ret, $bgImage) = GalleryCoreApi::loadEntitiesById($params['backgroundId']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $params['bgSerialNumber'] = $bgImage->getSerialNumber();
	}
	foreach (array('backgroundId', 'rows', 'cols', 'cellWidth', 'cellHeight') as $key) {
	    if (!isset($params[$key])) {
		$params[$key] = '0';
	    }
	}
	$map = array();
	for ($i = 0; $i < $params['rows']; $i++) {
	    for ($j = 0; $j < $params['cols']; $j++) {
		$map[$i][$j] = 0;
	    }
	}
	if (isset($params['map'])) {
	    foreach (explode(';', $params['map']) as $key) {
		$value = explode(',', $key);
		if (count($value) == 3) {
		    $map[$value[0]][$value[1]] = $value[2];
		    $params['row_'.$value[2]] = $value[0]+1;
		    $params['col_'.$value[2]] = $value[1]+1;
		}
	    }
	}
	$layout['params'] = $params;
	$layout['map'] = $map;

	list ($ret, $itemList, $imageWidths, $imageHeights) = $this->_buildItemList($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($itemList as $it) {
	    $itemMap[$it['id']] = $it;
	}

	$layout['itemList'] = $itemList;
	$layout['count'] = count($itemList);
	$layout['itemMap'] = $itemMap;
	$layout['imageWidths'] = implode(',', $imageWidths);
	$layout['imageHeights'] = implode(',', $imageHeights);
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
			$cook = 'G2_tile_' . $item->getId();
			setcookie($cook, 'I', 0, $cookiePath);
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
		array('head' => 'layouts/tile/templates/header.tpl',
		      'body' => 'layouts/tile/templates/tile.tpl'));
    }

    function _buildItemList(&$item) {
	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$itemList = array();
	$childItems = array();
	$imageWidths = array();
	$imageHeights = array();
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
		$newItem['thumb'] = $thumbnails[$childId]->getMemberData();
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
		    $thumbnail = $thumbnails[$childId];
		    if (!$thumbnail->getWidth()) {
			list ($ret, $thumbnail) = GalleryCoreApi::rebuildDerivativeCache($thumbnail->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		    $images[] = $thumbnail;
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
		    if (GalleryUtilities::isA($child, 'GalleryPhotoItem') && $image['width'] > 0 && $image['height'] > 0) {
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
	return array(GalleryStatus::success(), $itemList, $imageWidths, $imageHeights);
    }

    /**
     * @see GalleryLayout::isAdvancedSettings
     */
    function isAdvancedSettings() {
	return true;
    }

    /**
     * @see GalleryLayout::loadSettingsTemplate
     */
    function loadSettingsTemplate(&$template, &$form, $itemId=null) {
	if (!isset($itemId)) {
	    // Site admin settings..
	    return array(GalleryStatus::success(), null);
	}
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $tmp) = $this->loadTemplate($template, $item);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return array(GalleryStatus::success(), 'layouts/tile/templates/edit.tpl');
    }

    /**
     * @see GalleryLayout::handleSettingsRequest
     */
    function handleSettingsRequest($form, $itemId=null) {
	if (!isset($itemId)) {
	    // Site admin settings..
	    return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null, null);
	}
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$status = null;
	$error = array();
	if (isset($form['action']['undo'])) {
	    /* Take no action and we'll be redirected back to the same page which will reset the form */
	} else if (isset($form['action']['save'])) {
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    foreach (array('backgroundId', 'rows', 'cols', 'cellWidth', 'cellHeight') as $key) {
		if (isset($form[$key])) {
		    $ret = GalleryCoreApi::setPluginParameter('layout', 'tile', $key, $form[$key], $item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    $map = array();
	    foreach ($form as $key => $value) {
		if (!strncmp($key, 'row_', 4)) {
		    $id = substr($key, 4);
		    $k2 = 'col_' . $id;
		    if (isset($form[$k2]) && $value > 0 && $form[$k2] > 0) {
			$map[] = ($value-1) . ',' . ($form[$k2]-1) . ',' . $id;
		    }
		}
	    }
	    $ret = GalleryCoreApi::setPluginParameter('layout', 'tile', 'map', implode(';', $map), $item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status = $module->translate('Successfully saved layout settings');
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    function _sortItemLinks($a, $b) {
	return strcmp($a['text'], $b['text']);
    }
}

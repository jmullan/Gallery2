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
    function TileLayout() {
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

	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $this->loadLayoutTemplate($template, $item,
	    array('parents', 'systemLinks', 'systemContent', 'itemLinks'),
	    $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$layout =& $template->getVariableByReference('layout');

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

	list ($ret, $imageWidths, $imageHeights) =
	    $this->_buildItemList($childIds, $layout['children']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$itemMap = array();
	foreach ($layout['children'] as $child) {
	    $itemMap[$child['id']] = $child;
	}

	$layout['show']['parents'] = true;
	$layout['show']['systemLinks'] = true;
	$layout['itemMap'] = $itemMap;
	$layout['imageWidths'] = implode(',', $imageWidths);
	$layout['imageHeights'] = implode(',', $imageHeights);
	$layout['imageCount'] = count($imageWidths);

	$urlGenerator = $gallery->getUrlGenerator();
	$cookiePath = preg_replace('|^[^/]*//[^/]*/|', '/', $urlGenerator->getCurrentUrlDir());
	$layout['cookiePath'] = $cookiePath;
	$layout['layoutUrl'] = $urlGenerator->generateUrl(array('href' => 'layouts/tile'), false);

	/* Init view with specific image */
	if (isset($viewItemId)) {
	    foreach ($layout['children'] as $tmp) {
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

	$template->head('layouts/tile/templates/header.tpl');
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/tile/templates/tile.tpl'));
    }

    function _buildItemList($childIds, &$children) {
	$imageWidths = $imageHeights = $childItems = array();
	if (!empty($childIds)) {
	    $ret = GalleryCoreApi::studyPermissions($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $childItems) = GalleryCoreApi::loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $preferredFullImages) =
		GalleryCoreApi::fetchPreferredsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $resizedImages) =
		GalleryCoreApi::fetchResizesByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	}
	$i = 0;
	foreach ($childItems as $child) {
	    $childId = $child->getId();
	    if (isset($thumbnails[$childId])) {
		if (!($thumbnails[$childId]->getWidth() && $thumbnails[$childId]->getHeight())) {
		    list ($ret, $thumbnails[$childId]) =
			GalleryCoreApi::rebuildDerivativeCache($thumbnails[$childId]->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
		$children[$i]['thumbnail'] = $thumbnails[$childId]->getMemberData();
	    }

	    if (!(GalleryUtilities::isA($child, 'GalleryDataItem') && $child->canBeViewedInline())) {
		continue;
	    }

	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($childId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
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
	    if (isset($permissions['core.viewResizes']) && isset($resizedImages[$childId])) {
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
		if (GalleryUtilities::isA($image, 'GalleryDerivativeImage')
			&& !($image->getWidth() && $image->getHeight())) {
		    list ($ret, $image) = GalleryCoreApi::rebuildDerivativeCache($image->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
		$image = $image->getMemberData();
		$children[$i]['image'] = $image;
		$children[$i]['imageIndex'] = count($imageWidths);
		if (GalleryUtilities::isExactlyA($child, 'GalleryPhotoItem')
			&& $image['width'] > 0 && $image['height'] > 0) {
		    // Display in <img>
		    $imageWidths[] = $image['width'];
		    $imageHeights[] = $image['height'];
		} else {
		    // Item must render itself
		    $children[$i]['renderItem'] = 1;
		    $imageWidths[] = $imageHeights[] = -1;
		}
	    }
	    $i++;
	}
	return array(GalleryStatus::success(), $imageWidths, $imageHeights);
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
}

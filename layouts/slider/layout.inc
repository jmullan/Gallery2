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
	$this->setDescription(
	    $gallery->i18n('Image viewer/slideshow; subalbums/other items not shown'));
	$this->setVersion('0.10.0');
	$this->setL10Domain('layouts_slider');
	$this->setRequiredLayoutApi(array(0, 8));
	$this->setRequiredCoreApi(array(5, 0));
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
	    $template->title('');
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

	list ($ret, $imageWidths, $imageHeights) =
	    $this->_buildItemList($childIds, $layout['children']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout['show']['parents'] = true;
	$layout['show']['systemLinks'] = true;
	$layout['imageWidths'] = implode(',', $imageWidths);
	$layout['imageHeights'] = implode(',', $imageHeights);
	$layout['imageCount'] = count($imageWidths);
	$layout['show']['sidebarActions'] = false;

	$urlGenerator =& $gallery->getUrlGenerator();
	$cookiePath = preg_replace('|^[^/]*//[^/]*/|', '/', $urlGenerator->getCurrentUrlDir());
	$layout['cookiePath'] = $cookiePath;
	$layout['layoutUrl'] = $urlGenerator->generateUrl(array('href' => 'layouts/slider'), false);
	$layout['hybridUrl'] = $urlGenerator->generateUrl(array('href' => 'layouts/hybrid'), false);

	/* Init view with specific image */
	if (isset($viewItemId)) {
	    foreach ($layout['children'] as $tmp) {
		if ($tmp['id'] == $viewItemId) {
		    if (isset($tmp['imageIndex'])) {
			$layout['viewIndex'] = $tmp['imageIndex'];
		    }
		    break;
		}
	    }
	}

	$template->head('layouts/slider/templates/header.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/slider/templates/slider.css');
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/slider/templates/slider.tpl'));
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

	    if (!GalleryUtilities::isA($child, 'GalleryDataItem') || !$child->canBeViewedInline()) {
		continue;
	    }

	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($childId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $images = array();
	    if (isset($permissions['core.viewSource'])) {
		/* Full size; check for preferred copy */
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

		/* Rebuild derivative if needed so width/height known */
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
		if (GalleryUtilities::isExactlyA($child, 'GalleryPhotoItem') &&
			    $image['width'] > 0 && $image['height'] > 0) {
		    /* Display in <img> */
		    $imageWidths[] = $image['width'];
		    $imageHeights[] = $image['height'];
		} else {
		    /* Item must render itself */
		    $children[$i]['renderItem'] = 1;
		    $imageWidths[] = $imageHeights[] = -1;
		}
	    }
	    $i++;
	}
	return array(GalleryStatus::success(), $imageWidths, $imageHeights);
    }
}
?>

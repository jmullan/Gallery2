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
	$this->setName($gallery->i18n('Hybrid'));
	$this->setDescription($gallery->i18n('Combined album/image/slideshow dynamic view'));
	$this->setVersion('0.10.1');
	$this->setL10Domain('layouts_hybrid');
	$this->setRequiredLayoutApi(array(0, 10));
	$this->setRequiredCoreApi(array(5, 0));
	$this->setStandardSettings(array('albumFrame' => '', 'itemFrame' => ''));
    }

    /**
     * @see GalleryLayout::loadAlbumTemplate
     */
    function loadAlbumTemplate(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData($template, $item, $params,
	    array('owner', 'viewCount', 'parents', 'systemLinks', 'systemContent', 'itemLinks'),
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

	$template->head('layouts/hybrid/templates/header.tpl');
	$template->style('layouts/hybrid/layout.css');
	return array(GalleryStatus::success(), 'layouts/hybrid/templates/hybrid.tpl');
    }

    /**
     * @see GalleryLayout::loadItemTemplate
     */
    function loadItemTemplate(&$template, $item, $params) {
	list ($detail, $renderId) = GalleryUtilities::getRequestVariables('detail', 'renderId');

	if (!empty($renderId)) {
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
			 array('html' => 'layouts/hybrid/templates/render.tpl'));
	}

	if (!empty($detail)) {
	    $ret = $this->loadCommonTemplateData($template, $item, $params,
						 array('owner', 'viewCount', 'itemDetailFiles'));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $layout =& $template->getVariableByReference('layout');
	    list ($ret, $thumbnail) =
		GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!empty($thumbnail)) {
		$layout['thumbnail'] = $thumbnail[$item->getId()]->getMemberData();
	    }
	    return array(GalleryStatus::success(),
			 array('html' => 'layouts/hybrid/templates/detail.tpl'));
	}

	/* Load parent with initial view of this item  */
	list ($ret, $parent) = GalleryCoreApi::loadEntitiesById($item->getParentId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($parent);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $tplFile) = $this->loadAlbumTemplate($template, $parent, $params, $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Init view with specific image */
	$layout =& $template->getVariableByReference('layout');
	foreach ($layout['children'] as $child) {
	    if ($child['id'] == $item->getId()) {
		if (isset($child['imageIndex'])) {
		    $layout['viewIndex'] = $child['imageIndex'];
		    /* Set cookie to popup image just once */
		    setcookie('G2_hybrid_view', '1');
		}
		break;
	    }
	}

	return array(GalleryStatus::success(), $tplFile);
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
	$i = -1;
	foreach ($childItems as $child) {
	    $i++;
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

	    if (!(GalleryUtilities::isA($child, 'GalleryDataItem')
		    && $child->canBeViewedInline())) {
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

		/* Rebuild derivative if needed so width/height known.. */
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
	}
	return array(GalleryStatus::success(), $imageWidths, $imageHeights);
    }
}
?>

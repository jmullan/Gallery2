<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
 * @package Slideshow
 * @author Alan Harder <alan.harder@sun.com>
 */

class SlideshowView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate()
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$startId = null;
	if (!$item->getCanContainChildren()) {
	    // Photo: do slideshow of parent album, start at this photo
	    $startId = $item->getId();
	    list ($ret, $item) =
		$gallery->loadEntitiesById($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $itemList, $start) =
	    $this->buildSlideshow($item, $startId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$SlideShow = array();
	$SlideShow['item'] = $item->getMemberData();
	$SlideShow['itemList'] = $itemList;
	$SlideShow['count'] = count($itemList);
	$SlideShow['start'] = $start;
	$template->setVariable('SlideShow', $SlideShow);
	return array(GalleryStatus::success(),
	       array('head' => 'modules/slideshow/templates/Header.tpl',
	             'body' => 'modules/slideshow/templates/Slideshow.tpl'));
    }

    /**
     * Build data set to be used by template to render slideshow
     */
    function buildSlideshow($item, $startId = null) {
	global $gallery;
	list ($ret, $childIds) = $item->fetchChildIds();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$itemList = array();
	$childItems = array();
	if (!empty($childIds)) {
	    $ret = GalleryItemHelper::studyPermissions($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $childItems) = $gallery->loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $preferredFullImages) =
		GalleryDerivativeHelper::fetchPreferredsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $resizedImages) =
		GalleryDerivativeHelper::fetchResizesByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    // If an Exif extractor is available try to get capture dates..
	    list ($ret, $exifExtractor) =
		GalleryFactory::newInstance('ExifInterface_1_0');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $exif = array();
	    if (isset($exifExtractor)) {
		list ($ret, $exif) = $exifExtractor->getMetaData($childIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}
	if (!isset($startId)) {
	    $start = 0;
	}
	foreach ($childItems as $child) {

	    $childId = $child->getId();
	    if (!isset($start) && $childId == $startId) {
		$start = count($itemList);
	    }

	    if (!$child->getCanContainChildren()) {

		list ($ret, $permissions) =
		    GalleryItemHelper::getPermissions($childId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$image = null;
		if (isset($permissions['core.viewResizes']) &&
			isset($resizedImages[$childId])) {
		    // Just get the first resized size
		    $image = current($resizedImages[$childId]);
		    //XXX cache refresh?
		} else if (isset($permissions['core.viewSource'])) {
		    // Full size; check for preferred copy
		    if (isset($preferredFullImages[$childId])) {
			$image = $preferredFullImages[$childId];
		    } else if ($child->canBeViewedInline()) {
			$image = $child;
		    }
		} else {
		    // Thumbnail as fallback
		    list ($ret, $thumb) =
			GalleryDerivativeHelper::fetchThumbnailsByItemIds(
						 array($childId));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    if (!empty($thumb)) {
			$image = $thumb[$childId];
		    }
		}

		if (isset($image)) {
		    $itemList[] = array(
			'id' => $childId,
			'data' => $child->getMemberData(),
			'source' => $image->getMemberData(),
			'exif' => isset($exif[$childId])
				  ? $exif[$childId] : array());
		}
	    }
	}
	return array(GalleryStatus::success(),
		     $itemList, isset($start) ? $start : 0);
    }
}
?>

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
	    list ($ret, $thumbnails) =
		GalleryDerivativeHelper::fetchThumbnailsByItemIds($childIds);
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
	// Classify each derivative in a size class..
	$sizeClasses = array(array(320,240),   // 0: < 320x240
	    array(640,480),  array(800,600),   // 1: --640x480  2: --800x600
	    array(1024,768), array(1280,1024)  // 3: --1024x768 4: --1280x1024
	);                                     // 5: > 1280x1024
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

		$images = array();
		if (isset($permissions['core.viewSource'])) {
		    // Full size; check for preferred copy
		    if (isset($preferredFullImages[$childId])) {
			$images[] = $preferredFullImages[$childId];
		    } else if ($child->canBeViewedInline()) {
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

		// build table of {sizeClass}=>{sources_index}
		$sizeClassMap = array_fill(0, count($sizeClasses) + 1, -1);
		$sizeClassArea = array_fill(0, count($sizeClasses) + 1, -1);
		foreach ($images as $i => $image) {
		    // Rebuild derivatives if needed so width/height known..
		    if (is_a($image, 'GalleryDerivativeImage')) {
			list ($ret, $image) =
			    GalleryDerivativeHelper::rebuildCacheIfNotCurrent(
				    $image->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		    $image = $images[$i] = $image->getMemberData();
		    if (!isset($image['width']) || !isset($image['height'])) {
			continue; // Should not happen
		    }
		    $area = $image['width'] * $image['height'];
		    for ($j = count($sizeClasses); $j >= 0; $j--) {
			if ($j < count($sizeClasses) &&
				($image['width'] > $sizeClasses[$j][0] ||
				 $image['height'] > $sizeClasses[$j][1])) {
			    break;
			}
			if ($area > $sizeClassArea[$j]) {
			    $sizeClassMap[$j] = $i;
			    $sizeClassArea[$j] = $area;
			}
		    }
		}
		for ($j = 0, $i = count($sizeClasses); $i >= 0; $i--) {
		    if ($sizeClassMap[$i] < 0) {
			$sizeClassMap[$i] = $j;
		    } else {
			$j = $sizeClassMap[$i];
		    }
		}

		if (!empty($images)) {
		    $itemList[] = array(
			'id' => $childId,
			'data' => $child->getMemberData(),
			'sources' => $images,
			'sizeClassMap' => $sizeClassMap,
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

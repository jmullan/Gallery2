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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Provides downloading of binary items
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class DownloadItemView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate() {
	global $gallery;

	/* Figure out which item we're talking about */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER,
					__FILE__, __LINE__);
	}

	/* Load the item */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Figure out what permission we need to view this item */
	if (GalleryUtilities::isA($item, 'GalleryDerivative')) {
	    switch($item->getDerivativeType()) {
	    case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
		$requiredPermission = 'core.view';
		break;
		
	    case DERIVATIVE_TYPE_IMAGE_RESIZE:
		$requiredPermission = 'core.viewResizes';
		break;

	    case DERIVATIVE_TYPE_IMAGE_PREFERRED:
		$requiredPermission = 'core.viewSource';
		break;
	    }
	    $itemForPermission = $item->getParentId();
	} else {
	    $requiredPermission = 'core.viewSource';
	    $itemForPermission = $item->getId();
	}

	/* Make sure we have it */
	$ret = GalleryUserHelper::assertHasItemPermission($itemForPermission,
							  $requiredPermission);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Get the path to the file */
	list ($ret, $path) = $item->fetchPath();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Rebuild derivative cache, if necessary */
	if (GalleryUtilities::isA($item, 'GalleryDerivative')) {
	    list ($ret, $item) = GalleryDerivativeHelper::rebuildCacheIfNotCurrent($item->getId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $mimeType = $item->getDerivativeMimeType();
	    $size = $item->getDerivativeSize();
	} else {
	    $size = $item->getSize();
	    $mimeType = $item->getMimeType();
	}

	if ($size > 0) {
	    header('Content-length: ' . $size);
	}
	header('Content-type: ' . $mimeType);
	readfile($path);

	return GalleryStatus::success();
    }

    /**
     * @see GalleryView::rewriteQueryString
     */
    function rewriteQueryString($params) {
	global $gallery;
	
	/* We know who we are */
	unset($params['view']);

	$itemId = $params['itemId'];
	unset($params['itemId']);
	
	$buf = '/' . $itemId;

	list ($ret, $entity) = $gallery->loadEntitiesById($itemId);
	if ($ret->isSuccess()) {
	    $buf .= '-' . $entity->getSerialNumber();

	    if (GalleryUtilities::isA($entity, 'GalleryDataItem')) {
		$mimeType = $entity->getMimeType();
	    } else {
		$mimeType = $entity->getDerivativeMimeType();
	    }

	    $extension = GalleryUtilities::convertMimeToExtension($mimeType);
	    if (!empty($extension)) {
		$buf .= '.' . $extension;
	    }
	}

	/* Add in anything else as a standard query element */
	if (!empty($params)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $buf .= $urlGenerator->buildQueryString($params);
	}

	return $buf;
    }

    /**
     * @see GalleryView::parseQueryString()
     */
    function parseQueryString($queryString) {

	/*
	 * Expect the path to be in the format /<itemid>-<serial>.<extension>
	 * We only care about the item id
	 */
	$queryString = preg_match('|/(\d+)-|', $queryString, $regs);
	GalleryUtilities::putRequestVariable('itemId', $regs[1]);
	return GalleryStatus::success();
    }
}
?>

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
     * @see GalleryView::renderShortcut
     */
    function renderShortcut() {
	/*
	 * If the browser passes us a request with an 'If-Modified-Since' header, then its already
	 * got a cached copy of this file.  And since our links always include a serial number,
	 * and any change triggers a serial number change, this means that its cache is always up
	 * to date.  We don't even need to check the modification date.
	 */
	if (function_exists('getallheaders')) {
	    $headers = GetAllHeaders();
	    if (isset($headers['If-Modified-Since'])) {
		header('HTTP/1.x 304 Not Modified');
		return array(GalleryStatus::success(), true);
	    }
	}

	/* Figure out which item we're talking about */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    return array(GalleryStatus::success(), false);
	}

	/* Try to load our shortcut data file */
	global $gallery;
	$platform = $gallery->getPlatform();
	$data = GalleryDataCache::getFromDisk(array('type' => 'derivative-meta',
						    'itemId' => $itemId));
	if (isset($data) && $platform->file_exists($data['derivativePath'])) {

	    $ret = $this->_sendFile($data);
	    if ($ret->isError()) {
		return array(GalleryStatus::success(), false);
	    }
	    return array(GalleryStatus::success(), true);
	}

	return array(GalleryStatus::success(), false);
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	/* Figure out which item we're talking about */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
	}

	/* Load the item */
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Figure out the filename */
	list ($ret, $pseudoFileName) = GalleryUtilities::getPseudoFileName($item);
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
	    list ($ret, $item) = GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($item->getId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $itemForPermission = $item->getParentId();
	    $derivativeType = $item->getDerivativeType();
	} else {
	    $itemForPermission = $item->getId();
	    $derivativeType = null;
	}

	$ret = $this->_sendFile(array('derivativePath' => $path,
				      'derivativeType' => $derivativeType,
				      'mimeType' => $item->getMimeType(),
				      'pseudoFileName' => $pseudoFileName,
				      'parentId' => $itemForPermission));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    function _sendFile($data) {
	global $gallery;
	$platform = $gallery->getPlatform();

	/* Make sure we have permission */
	$permission = 'core.viewSource';
	switch($data['derivativeType']) {
	    case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
		$permission = 'core.view';
		break;

	    case DERIVATIVE_TYPE_IMAGE_RESIZE:
		$permission = 'core.viewResizes';
		break;

	    /* DERIVATIVE_TYPE_IMAGE_PREFERRED uses core.viewSource */
	}
	$ret = GalleryCoreApi::assertHasItemPermission($data['parentId'], $permission);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	header('Content-type: ' . $data['mimeType']);
	header('Content-Disposition: inline; filename="' . $data['pseudoFileName'] . '"');
	$stats = $platform->stat($data['derivativePath']);
	if ($stats[7] > 0) {
	    header('Content-length: ' . $stats[7]);
	}
	header('Last-Modified: ' . GalleryUtilities::getHttpDate($stats[9]));

	/*
	 * Don't use readfile() because it buffers the entire file in memory
	 * Profiling shows that this approach is as efficient as fpassthru()
	 * but we get to call guaranteeTimeLimit which prevents it from failing on
	 * very large files.
	 */
	if ($fd = $platform->fopen($data['derivativePath'], 'rb')) {
	    while (true) {
		$bits = $platform->fread($fd, 65535);
		if (strlen($bits) == 0) {
		    break;
		}
		print $bits;
		$gallery->guaranteeTimeLimit(30);
	    }
	    $platform->fclose($fd);
	}

	flush();
	// Hopefully at this point the file has been sent to the browser; now we can connect
	// to the database for administrative tasks without slowing down the request.

	/* Increment the view count */
	if ($data['derivativeType'] != DERIVATIVE_TYPE_IMAGE_THUMBNAIL) {
	    $ret = GalleryCoreApi::incrementItemViewCount($data['parentId']);
	    if ($ret->isError()) {
		/* We've sent the file so ignore this error.. */
		if ($gallery->getDebug()) {
		    $gallery->debug('Error incrementing view count for ' . $data['parentId'] . "\n"
				   . $ret->getAsText());
		}
	    }
	}

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

	list ($ret, $entity) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return null;
	}

	$buf .= '-' . $entity->getSerialNumber();
	unset($params['serialNumber']);

	list ($ret, $pseudoFileName) = GalleryUtilities::getPseudoFileName($entity);
	if ($ret->isError()) {
	    return null;
	}
	$buf .= '/' . $pseudoFileName;

	if (strpos($pseudoFileName, '.') === false) {
	    $extension = GalleryCoreApi::convertMimeToExtension($entity->getMimeType());
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
	return array(GalleryStatus::success(), null);
    }
}
?>

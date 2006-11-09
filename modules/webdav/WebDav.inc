<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

GalleryCoreApi::requireOnce('modules/core/ItemAdd.inc');
GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * @package WebDav
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$ $Date$
 */
class WebDavController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	/*
	 * GalleryCoreApi::addItemToAlbum normalizes path components but
	 * GalleryCoreApi::fetchItemIdByPath does not.  This is a problem for WebDAV because GET
	 * following a successful PUT at the same URL should succeed.
	 *
	 * An alternative is to consistantly normalize all requests.  While this shouldn't break any
	 * clients, PROPFIND following a successful PUT should strictly include the URL of the PUT.
	 *
	 * Consequently we reject an illegal path component.
	 *
	 * This condition may be relaxed in future if it's a problem.
	 */
	$path = GalleryUtilities::getRequestVariables('path');
	$pathComponent = basename($path);
	if (!$platform->isLegalPathComponent($pathComponent)) {
	    /* Special case to suppress Mac '._' files.  Ignore request but return success. */
	    if (!strncmp($pathComponent, '._', 2)) {
		WebDavServer::setResponseStatus('200 OK');
		return array(GalleryCoreApi::error(ERROR_BAD_PATH), null);
	    }

	    WebDavServer::setResponseStatus('403 Forbidden');
	    return array(GalleryCoreApi::error(ERROR_BAD_PATH), null);
	}

	$requestMethod = strtolower(GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if ($requestMethod == 'get' || $requestMethod == 'head') {
	    if (empty($path)) {
		list ($ret, $itemId) = GalleryCoreApi::getDefaultAlbumId();
		if ($ret) {
		    return array($ret, null);
		}
	    } else {
		list ($ret, $itemId) = GalleryCoreApi::fetchItemIdByPath($path);
		if ($ret) {
		    return array($ret, null);
		}
	    }

	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	    if ($ret) {
		return array($ret, null);
	    }

	    /* Until there's a better way to delegate to Show/DownloadItem */
	    GalleryUtilities::putRequestVariable('itemId', $itemId);
	    if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
		return array(null, array('delegate' => array('view' => 'core.ShowItem'),
					 'status' => array(),
					 'error' => array()));
	    }

	    return array(null, array('delegate' => array('view' => 'core.DownloadItem'),
				     'status' => array(),
				     'error' => array()));
	} else if ($requestMethod == 'put') {
	    $parentPath = dirname($path);

	    /* dirname('foo') is '.' */
	    if ($parentPath == '.') {
		list ($ret, $parentId) = GalleryCoreApi::getDefaultAlbumId();
		if ($ret) {
		    return array($ret, null);
		}
	    } else {
		list ($ret, $parentId) = GalleryCoreApi::fetchItemIdByPath($parentPath);
		if ($ret) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			/*
			 * A PUT that would result in the creation of a resource without an
			 * appropriately scoped parent collection MUST fail with a 409
			 * (Conflict).
			 */
			WebDavServer::setResponseStatus('409 Conflict');
		    }

		    return array($ret, null);
		}

		/* Until there's a better way to delegate to ItemAdd */
		GalleryUtilities::putRequestVariable('itemId', $parentId);
		GalleryUtilities::putRequestVariable('addPlugin', 'ItemAddWebDav');
		list ($ret, $data) = ItemAddController::handleRequest($form);
		if ($ret) {
		    return array($ret, null);
		}

		return array(null, $data);
	    }
	}

	return array(null, array('delegate' => array('view' => 'webdav.WebDav'),
				 'status' => array(),
				 'error' => array()));
    }
}

class WebDavView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	$requestMethod = strtolower(GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if (!in_array($requestMethod, array('options', 'propfind', 'proppatch', 'mkcol', 'delete',
		'move', 'lock', 'unlock'))) {
	    return GalleryCoreApi::error(ERROR_UNIMPLEMENTED);
	}

	$ret = WebDavHelper::$requestMethod();
	if ($ret) {
	    return $ret;
	}

	return null;
    }
}
?>

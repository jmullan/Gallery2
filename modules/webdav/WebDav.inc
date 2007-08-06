<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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

GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * Handle WebDAV requests.
 * @package WebDav
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$
 */
class WebDavController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	/*
	 * Suppress generating HTML error pages for WebDAV clients.  Exploit the fact that event
	 * listeners aren't currently stored in the database, so this event listener is only
	 * registered for this request.  Since this is the WebDAV controller, we know it is a WebDAV
	 * request.
	 */
	$isAppropriate =& WebDavModule::_isAppropriate();
	$isAppropriate['Gallery::Error'] = true;

	/*
	 * Windows Web Folders doesn't respect HTTP auth in PUT responses, so the user is not
	 * prompted to login.  To work around this, request HTTP auth in all responses to anonymous
	 * Windows Web Folders requests.  Consequently anonymous users can't connect with Windows
	 * Web Folders.
	 */
	$userAgent = GalleryUtilities::getServerVar('HTTP_USER_AGENT');
	if (strpos($userAgent, 'Microsoft Data Access Internet Publishing Provider DAV') !== false
		|| strpos($userAgent, 'Microsoft-WebDAV-MiniRedir') !== false) {
	    list ($ret, $isAnonymous) = GalleryCoreApi::isAnonymousUser();
	    if ($ret) {
		return array($ret, null);
	    }
	    if ($isAnonymous) {
		return array(GalleryCoreApi::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__,
		    'WebDAV: Anonymous request with Windows Web Folders.'
		    . '  Workaround: Request HTTP auth in all responses.'), null);
	    }
	}

	$path = WebDavHelper::getRequestVariable('path', true, false);
	$pathComponent = urldecode(basename($path));

	/* Special case to suppress Mac '._' files.  Ignore request but return success. */
	if (!strncmp($pathComponent, '._', 2)) {
	    WebDavServer::setResponseStatus('200 OK');
	    return array(GalleryCoreApi::error(ERROR_BAD_PATH), null);
	}

	/* Special case to suppress Mac '.DS_Store' files.  Return 403 Forbidden. */
	if ($pathComponent == '.DS_Store') {
	    WebDavServer::setResponseStatus('403 Forbidden');
	    return array(GalleryCoreApi::error(ERROR_BAD_PATH), null);
	}

	$requestMethod = GalleryUtilities::strToLower(
	    GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if ($requestMethod == 'get' || $requestMethod == 'head') {
	    list ($ret, $itemId) = WebDavHelper::fetchItemIdByPath($path);
	    if ($ret) {
		return array($ret, null);
	    }

	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId, 'GalleryItem');
	    if ($ret) {
		return array($ret, null);
	    }

	    /* Until there's a better way to delegate to ShowItem / DownloadItem */
	    GalleryUtilities::putRequestVariable('itemId', $itemId);
	    if ($item->getCanContainChildren()) {
		return array(null, array('delegate' => array('view' => 'core.ShowItem'),
					 'status' => array(),
					 'error' => array()));
	    }

	    return array(null, array('delegate' => array('view' => 'core.DownloadItem'),
				     'status' => array(),
				     'error' => array()));
	} else if ($requestMethod == 'put') {
	    list ($ret, $itemId) = WebDavHelper::fetchItemIdByPath($path);
	    if ($ret) {
		if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		    /* Item doesn't already exist at this path.  Create it. */
		    $parentPath = WebDavHelper::getParentPath($path);
		    list ($ret, $parentId) = WebDavHelper::fetchItemIdByPath($parentPath);
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

		    GalleryUtilities::putRequestVariable('itemId', $parentId);
		    GalleryUtilities::putRequestVariable('addPlugin', 'ItemAddWebDav');

		    list ($ret, $controller) = GalleryController::loadController('core.ItemAdd');
		    if ($ret) {
			return array($ret, null);
		    }

		    list ($ret, $results) = $controller->handleRequest($form);
		    if ($ret) {
			return array($ret, null);
		    }

		    return array(null, $results);
		}

		return array($ret, null);
	    }

	    /* Item already exists at this path.  Replace it. */
	    GalleryUtilities::putRequestVariable('itemId', $itemId);
	    GalleryUtilities::putRequestVariable('editPlugin', 'ItemEditWebDav');

	    list ($ret, $controller) = GalleryController::loadController('core.ItemEdit');
	    if ($ret) {
		return array($ret, null);
	    }

	    list ($ret, $results) = $controller->handleRequest($form);
	    if ($ret) {
		return array($ret, null);
	    }

	    return array(null, $results);
	}

	return array(null, array('delegate' => array('view' => 'webdav.WebDav'),
				 'status' => array(),
				 'error' => array()));
    }

    /**
     * @see GalleryController::omitAuthTokenCheck
     */
    function omitAuthTokenCheck() {
	return true;
    }
}

/**
 * Generate WebDAV responses.
 */
class WebDavView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::isControllerLike
     */
    function isControllerLike() {
	/* Although this view is controller-like, we return false since we can't add authTokens */
	return false;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	$requestMethod = GalleryUtilities::strToLower(
	    GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if (!in_array($requestMethod, array('options', 'propfind', 'proppatch', 'mkcol', 'delete',
					    'move', 'lock', 'unlock'))) {
	    WebDavServer::setResponseStatus('405 Method Not Allowed');
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

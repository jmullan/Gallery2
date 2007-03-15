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

GalleryCoreApi::requireOnce('modules/core/ItemAdd.inc');
GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * Add items with WebDAV.  Handle WebDAV PUT requests and show instructions to mount Gallery with
 * WebDAV.
 * @package WebDav
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$
 */
class ItemAddWebDav extends ItemAddPlugin {

    /**
     * @see ItemAddPlugin::handleRequest
     */
    function handleRequest($form, &$album) {
	$requestMethod = GalleryUtilities::strToLower(
	    GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if ($requestMethod != 'put') {
	    return array(GalleryCoreApi::error(ERROR_REQUEST_FORGED), null, null);
	}

	$path = WebDavHelper::getRequestVariable('path', true, false);
	$pathComponent = urldecode(basename($path));

	/* Check resource is not locked */
	$ret = WebDavHelper::checkLocks($path);
	if ($ret) {
	    return array($ret, null, null);
	}

	/* Prepare data-structure from PUT request */
	list ($ret, $webDavOptions, $stream, $mimeType) = WebDavHelper::putRequestHelper();
	if ($ret) {
	    return array($ret, null, null);
	}

	list ($ret, $itemId) = WebDavHelper::fetchItemIdByPath($path);
	if ($ret) {
	    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		/* Item doesn't already exist at this path.  Create it. */
		list ($ret, $error, $status) = $this->_addItem(
		    $webDavOptions, $stream, $pathComponent, $mimeType, $album->getId());
		if ($ret) {
		    return array($ret, null, null);
		}

		return array(null, $error, $status);
	    }

	    return array($ret, null, null);
	}

	list ($ret, $error, $status) = $this->_replaceItem(
	    $webDavOptions, $stream, $pathComponent, $mimeType, $itemId);
	if ($ret) {
	    return array($ret, null, null);
	}

	return array(null, $error, $status);
    }

    /**
     * Add new item.
     * @param array $webDavOptions WebDAV library options
     * @param resource $stream request body file handle
     * @param string $pathComponent the path component
     * @param string $mimeType request content type
     * @param int $albumId the id of the target album
     * @access private
     */
    function _addItem($webDavOptions, $stream, $pathComponent, $mimeType, $albumId) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	/* Following pattern from ItemAddWebCam */
	$tmpDir = $gallery->getConfig('data.gallery.tmp');
	$tmpFile = $platform->tempnam($tmpDir, 'webdav');

	$handle = $platform->fopen($tmpFile, 'wb');
	if (!$handle) {
	    return array(GalleryCoreApi::error(ERROR_PLATFORM_FAILURE), null, null);
	}

	while (!$platform->feof($stream)) {
	    $buf = $platform->fread($stream, 4096);
	    if ($platform->fwrite($handle, $buf) != 4096) {
		break;
	    }
	}

	$platform->fclose($handle);

	list ($ret, $mimeExtensions) = GalleryCoreApi::convertMimeToExtensions($mimeType);
	if ($mimeType == 'application/octet-stream'
		|| $mimeType == 'application/unknown'
		|| empty($mimeExtensions)) {
	    $extension = GalleryUtilities::getFileExtension($pathComponent);
	    list ($ret, $mimeType) = GalleryCoreApi::convertExtensionToMime($extension);
	    if ($ret) {
		$mimeType = 'application/unknown';
	    }
	}

	list ($ret, $item) = GalleryCoreApi::addItemToAlbum(
	    $tmpFile, $pathComponent, $pathComponent, '', '', $mimeType, $albumId);
	@$platform->unlink($tmpFile);
	if ($ret) {
	    return array($ret, null, null);
	}

	/* Set WebDAV path component */
	if ($item->getPathComponent() != $pathComponent) {
	    $ret = GalleryCoreApi::addMapEntry('WebDavPathComponentMap',
		array('itemId' => $item->getId(), 'pathComponent' => $pathComponent));
	    if ($ret) {
		return array($ret, null, null);
	    }
	}

	WebDavServer::setResponseStatus('201 Created');
	return array(null, array(), array('addedFiles' => array(array(
	    'fileName' => $pathComponent, 'id' => $item->getId()))));
    }

    /**
     * Replace existing item.
     * @param array $webDavOptions WebDAV library options
     * @param resource $stream request body file handle
     * @param string $pathComponent the path component
     * @param string $mimeType request content type
     * @param int $itemId the id of the target item
     * @access private
     */
    function _replaceItem($webDavOptions, $stream, $pathComponent, $mimeType, $itemId) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret) {
	    return array($ret, null, null);
	}

	list ($ret, $filePath) = $item->fetchPath();
	if ($ret) {
	    return array($ret, null, null);
	}

	/*
	 * The parent must be read locked at this point to make sure that it's not going to be moved
	 * around while we're copying a file to its directory
	 */
	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLockParents($itemId);
	if ($ret) {
	    return array($ret, null, null);
	}

	list ($ret, $lockIds[]) = GalleryCoreApi::acquireWriteLock($itemId);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null);
	}

	$handle = $platform->fopen($filePath, 'wb');

	/* Format PUT response */
	$ret = WebDavHelper::putResponseHelper($webDavOptions, $handle);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null);
	}

	$ret = $item->rescan();
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null);
	}

	$item->setMimeType($mimeType);

	if ($item->isModified()) {
	    $ret = $item->save();
	    if ($ret) {
		GalleryCoreApi::releaseLocks($lockIds);
		return array($ret, null, null);
	    }
	}

	$ret = GalleryCoreApi::releaseLocks($lockIds);
	if ($ret) {
	    return array($ret, null, null);
	}

	$ret = GalleryCoreApi::expireDerivativeTreeBySourceIds($itemId);
	if ($ret) {
	    return array($ret, null, null);
	}

	/* TODO: A GalleryCoreApi method for replacing file contents would be nice here */

	return array(null, array(), array('addedFiles' => array(array(
	    'fileName' => $pathComponent, 'id' => $itemId))));
    }

    /**
     * @see ItemAddPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(null, 'modules/webdav/templates/ItemAddWebDav.tpl', null);
    }

    /**
     * @see ItemAddPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'webdav');
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, $module->translate('WebDAV'));
    }
}
?>

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

GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * @package WebDav
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$ $Date$
 */
class ItemAddWebDav extends ItemAddPlugin {

    /**
     * @see ItemAddPlugin::handleRequest
     */
    function handleRequest($form, &$item) {
	$path = GalleryUtilities::getRequestVariables('path');

	/* Check resource is not locked */
	$ret = WebDavHelper::checkLocks($path);
	if ($ret) {
	    return $ret;
	}

	/* Prepare data-structure from PUT request */
	list ($ret, $webDavOptions, $stream, $mimeType) = WebDavHelper::putRequestHelper();
	if ($ret) {
	    return array($ret, null, null);
	}

	list ($ret, $itemId) = GalleryCoreApi::fetchItemIdByPath($path);
	if ($ret) {
	    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		/* Item doesn't already exist at this path.  Create it. */
		list ($ret, $error, $status) = $this->_addItem(
		    $item, $webDavOptions, $stream, $mimeType, $path);
		if ($ret) {
		    return array($ret, null, null);
		}

		return array(null, $error, $status);
	    }

	    return array($ret, null, null);
	}

	list ($ret, $error, $status) = $this->_replaceItem(
	    $item, $webDavOptions, $stream, $mimeType, $path, $itemId);
	if ($ret) {
	    return array($ret, null, null);
	}

	return array(null, $error, $status);
    }

    /**
     * Add new item.
     * @param object GalleryItem $item
     * @param array $webDavOptions WebDAV library options
     * @param resource $stream request body file handle
     * @param string $mimeType request content type
     * @param string $path the path to the destination in the Gallery hierarchy
     * @access private
     */
    function _addItem(&$item, $webDavOptions, $stream, $mimeType, $path) {
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
	    $extension = GalleryUtilities::getFileExtension(basename($path));
	    list ($ret, $mimeType) = GalleryCoreApi::convertExtensionToMime($extension);
	    if ($ret) {
		$mimeType = 'application/unknown';
	    }
	}

	list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum($tmpFile, basename($path),
	    basename($path), '', '', $mimeType, $item->getId());
	@$platform->unlink($tmpFile);
	if ($ret) {
	    return array($ret, null, null);
	}

	WebDavServer::setResponseStatus('201 Created');
	return array(null, array(), array('addedFiles' => array(array(
	    'fileName' => basename($path), 'id' => $newItem->getId()))));
    }

    /**
     * Replace existing item.
     * @param object GalleryItem $item
     * @param array $webDavOptions WebDAV library options
     * @param resource $stream request body file handle
     * @param string $mimeType request content type
     * @param string $path the path to the destination in the Gallery hierarchy
     * @param int $itemId
     * @access private
     */
    function _replaceItem(&$item, $webDavOptions, $stream, $mimeType, $path, $itemId) {
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

	/* TODO: a GalleryCoreApi method for replacing file contents would be nice here. */

	return array(
	    null, array(),
	    array('addedFiles' => array(array('fileName' => basename($path), 'id' => $itemId))));
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

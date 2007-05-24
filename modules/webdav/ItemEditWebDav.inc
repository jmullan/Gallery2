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

GalleryCoreApi::requireOnce('modules/core/ItemEdit.inc');
GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * Replace items with WebDAV.  Handle WebDAV PUT requests and show instructions to mount Gallery
 * with WebDAV.
 * @package WebDav
 * @subpackage UserInterface
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision: 16164 $
 */
class ItemEditWebDav extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	/* Accept only the PUT request method.  Others can be easily forged with HTML. */
	$requestMethod = GalleryUtilities::strToLower(
	    GalleryUtilities::getServerVar('REQUEST_METHOD'));
	if ($requestMethod != 'put') {
	    return array(GalleryCoreApi::error(ERROR_REQUEST_FORGED), null, null, null);
	}

	/* Only data items can have file content */
	if (!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    WebDavServer::setResponseStatus('403 Forbidden');
	    return array(GalleryCoreApi::error(ERROR_BAD_DATA_TYPE), null, null, null);
	}

	$path = WebDavHelper::getRequestVariable('path', true, false);
	$pathComponent = urldecode(basename($path));

	/* Check resource is not locked */
	$ret = WebDavHelper::checkLocks($path);
	if ($ret) {
	    return array($ret, null, null, null);
	}

	/* Prepare data-structure from PUT request */
	list ($ret, $webDavOptions, $stream, $mimeType) = WebDavHelper::putRequestHelper();
	if ($ret) {
	    return array($ret, null, null, null);
	}

	/* If the mime type is unknown try to get a mime type from the file name */
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

	/*
	 * The parent must be read locked at this point to make sure that it's not going to be moved
	 * around while we're copying a file to its directory
	 */
	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLockParents($item->getId());
	if ($ret) {
	    return array($ret, null, null, null);
	}

	/* Write lock the item we're replacing */
	list ($ret, $lockIds[]) = GalleryCoreApi::acquireWriteLock($item->getId());
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	/* Refresh the item in case it changed before it was locked */
	list ($ret, $item) = $item->refresh();
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	/* Replace the file content */
	list ($ret, $filePath) = $item->fetchPath();
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	if (($handle = $platform->fopen($filePath, 'wb')) === false) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array(GalleryCoreApi::error(ERROR_PLATFORM_FAILURE), null, null, null);
	}

	/* Format PUT response */
	$ret = WebDavHelper::putResponseHelper($webDavOptions, $handle);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	$item->setMimeType($mimeType);

	/* Get a new item by mime type */
	list ($ret, $newItem) = GalleryCoreApi::newItemByMimeType($mimeType);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}
	if (!isset($newItem)) {
	    $gallery->debug(
		'Error in ItemEditWebDav::handleRequest: Failed to get new item by mime type: '
		. $mimeType);
	    $newItem = $item;
	}

	/* Make the new item as close a copy of the original item as possible */
	list ($ret, $newItem) = WebDavHelper::mirrorEntity($item, $newItem);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	/* Check if the class has changed */
	if ($newItem->getClassName() != $item->getClassName()) {
	    /* Fall back on the original item if the new class doesn't support the file content */
	    $ret = $newItem->rescan();
	    if ($ret) {
		if (!($ret->getErrorCode() & ERROR_BAD_DATA_TYPE)) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array($ret, null, null, null);
		}

		$newItem = $item;
	    }
	}

	/* Check if the class hasn't changed or the new class doesn't support the file content */
	if ($newItem->getClassName() == $item->getClassName()) {
	    $ret = $newItem->rescan();
	    if ($ret) {
		if (!($ret->getErrorCode() & ERROR_BAD_DATA_TYPE)) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array($ret, null, null, null);
		}

		/*
		 * Fall back on an unknown item if the original class doesn't support the file
		 * content
		 */
		list ($ret, $newItem) = GalleryCoreApi::newFactoryInstanceById('GalleryEntity',
		    'GalleryUnknownItem');
		if ($ret) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array($ret, null, null, null);
		}
		if (!isset($newItem)) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array(GalleryCoreApi::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__,
			'Failed to get GalleryUnknownItem instance'), null, null, null);
		}

		/* Make the new item as close a copy of the original item as possible */
		list ($ret, $newItem) = WebDavHelper::mirrorEntity($item, $newItem);
		if ($ret) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array($ret, null, null, null);
		}

		$ret = $newItem->rescan();
		if ($ret) {
		    GalleryCoreApi::releaseLocks($lockIds);
		    return array($ret, null, null, null);
		}
	    }
	}

	/* Follow pattern from ItemAddWebCam */
	$tmpDir = $gallery->getConfig('data.gallery.tmp');
	$tmpFile = $platform->tempnam($tmpDir, 'webdav');

	/* Backup the file content */
	if (!$platform->copy($filePath, $tmpFile)) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array(GalleryCoreApi::error(ERROR_PLATFORM_FAILURE), null, null, null);
	}

	$ret = $item->delete();
	if ($ret) {
	    @$platform->unlink($tmpFile);
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	/*
	 * Restore the file content.  If this fails, we rollback the database transaction but the
	 * file content is missing.
	 */
	if (!$platform->copy($tmpFile, $filePath)) {
	    @$platform->unlink($tmpFile);
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array(GalleryCoreApi::error(ERROR_PLATFORM_FAILURE), null, null, null);
	}
	@$platform->unlink($tmpFile);

	$newItem->setPersistentFlag(STORAGE_FLAG_NEWLY_CREATED);
	$ret = $newItem->save();
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	$ret = GalleryCoreApi::addExistingItemToAlbum($newItem, $item->getParentId(), true);
	if ($ret) {
	    GalleryCoreApi::releaseLocks($lockIds);
	    return array($ret, null, null, null);
	}

	$ret = GalleryCoreApi::releaseLocks($lockIds);
	if ($ret) {
	    return array($ret, null, null, null);
	}

	return array(null, array(), array(), false);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	return array(null, 'modules/webdav/templates/WebDavMount.tpl', null);
    }

    /**
     * @see ItemEditPlugin::getTitle
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

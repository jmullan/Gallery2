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
    function handleRequest($form, &$parentItem) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	/* Accept only the PUT request method.  Others can be easily forged with HTML. */
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

	/* Follow pattern from ItemAddWebCam */
	$tmpDir = $gallery->getConfig('data.gallery.tmp');
	$tmpFile = $platform->tempnam($tmpDir, 'webdav');

	if (($handle = $platform->fopen($tmpFile, 'wb')) === false) {
	    return array(GalleryCoreApi::error(ERROR_PLATFORM_FAILURE), null, null);
	}

	while (!$platform->feof($stream)) {
	    $buf = $platform->fread($stream, 4096);
	    if ($platform->fwrite($handle, $buf) != 4096) {
		break;
	    }
	}

	$platform->fclose($handle);

	list ($ret, $item) = GalleryCoreApi::addItemToAlbum(
	    $tmpFile, $pathComponent, $pathComponent, '', '', $mimeType, $parentItem->getId());
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
     * @see ItemAddPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(null, 'modules/webdav/templates/WebDavMount.tpl', null);
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

<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package WebCam
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package WebCam
 * @subpackage UserInterface
 */
class ItemAddLiveImage extends ItemAddPlugin {

    /**
     * @see ItemAddPlugin::handleRequest
     */
    function handleRequest($form, &$item) {
	global $gallery;

	$status = array();
	$error = array();
	if (isset($form['action']['checkUrl'])) {
	    /* Delegate back to the same view */
	} else if (isset($form['action']['addLiveImage'])) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryLiveImageHelper.class');

	    // fetch url, create item, set type to GalleryLiveImage, save params
	    $platform = $gallery->getPlatform();
	    $tmpDir = $gallery->getConfig('data.gallery.tmp');
	    $tmpFile = $platform->tempnam($tmpDir, 'webcam');
	    $url = GalleryUtilities::htmlEntityDecode($form['imageUrl']);

	    list ($successfullyCopied, $response, $headers) =
		GalleryCoreApi::fetchWebFile($url, $tmpFile);
	    if (!$successfullyCopied || strpos($response, '404 Not Found') !== false) {
		$error[] = 'form[error][imageUrl][unavailable]';
	    }

	    if (!empty($headers['Content-Type'])) {
		$mimeType = $headers['Content-Type'];
	    } else {
		list ($base, $extension) = GalleryUtilities::getFileNameComponents(basename($url));
		$mimeType = GalleryCoreApi::convertExtensionToMime($extension);
	    }

	    if (empty($error)) {
		list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum(
		    $tmpFile, basename($url), basename($url), '', '', $mimeType, $item->getId());
		@$platform->unlink($tmpFile);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		if (GalleryUtilities::isExactlyA($newItem, 'GalleryPhotoItem')) {

		    $ret = GalleryLiveImageHelper::assignEntityType($newItem, $url);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $status['addedFiles'][] = array('fileName' => basename($form['imageUrl']),
						    'id' => $newItem->getId());
		} else {
		    $ret = GalleryCoreApi::deleteEntityById($newItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $error[] = 'form[error][imageUrl][notImage]';
		}
	    } else {
		@$platform->unlink($tmpFile);
	    }
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemAdd:loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	global $gallery;

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'webcam');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($form['formName'] != 'ItemAddLiveImage') {
	    $form['formName'] = 'ItemAddLiveImage';
	    $form['imageUrl'] = '';
	}

	if (isset($form['action']['checkUrl'])) {
	    if (empty($form['imageUrl'])) {
		$form['error']['imageUrl']['missing'] = 1;
	    } else {
		$baseUrlComponents = parse_url($form['imageUrl']);
		if (empty($baseUrlComponents['scheme']) || $baseUrlComponents['scheme'] != 'http') {
		    $form['error']['imageUrl']['invalid'] = 1;
		}
	    }
	}

	return array(GalleryStatus::success(),
		     'modules/webcam/templates/ItemAddLiveImage.tpl', 'modules_webcam');
    }

    /**
     * @see ItemAddPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'webcam');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('WebCam/Live Image'));
    }
}
?>

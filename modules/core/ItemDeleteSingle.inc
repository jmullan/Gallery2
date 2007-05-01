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

/**
 * This controller-like view will handle the deletion of a single item
 * Note (Dec. 2006): this functionality has been rewritten using AJAX
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 * @version $Revision$
 */
class ItemDeleteSingleView extends GalleryView {

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
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	list ($ret, $result) = $this->handleCallback();
	if ($ret) {
	    $ret->putInSession();
	    $result['status'] = 'error';
	}
	
	GalleryCoreApi::requireOnce('lib/JSON/JSON.php');
	$json = new Services_JSON();
	print $json->encode($result);
	return null;
    }
    
    /**
     * Delete the specified item
     *
     * @return array object GalleryStatus a status code
     *               array  interface object for AJAX call
     */
    function handleCallback() {
	global $gallery;
	list ($itemId, $pageItemId) = GalleryUtilities::getRequestVariables('itemId', 'pageId');

	/* The view shouldn't let us get this far if we don't have delete permission */
	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.delete');
	if ($ret) {
	    return array($ret, null);
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId, 'GalleryItem');
	if ($ret) {
	    return array($ret, null);
	}
	$urlGenerator =& $gallery->getUrlGenerator();
	
	/* Get the parent *before* we delete the item */	
	$parentId = $item->getParentId();
	
	/* Get the root album id, so we don't try to delete it */
	list ($ret, $rootId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret) {
	    return array($ret, null);
	}

	/* The view shouldn't let us try to delete the root album, either */
	if ($itemId == $rootId) {
	    return array(GalleryCoreApi::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					 "Can't delete the root album"), null);
	}

	$ret = GalleryCoreApi::deleteEntityById($itemId, 'GalleryItem');
	if ($ret) {
	    return array($ret, null);
	}
	
	list ($ret, $unused) = GalleryCoreApi::guaranteeAlbumHasThumbnail($parentId);
	if ($ret) {
	    return array($ret, null);
	}

	$result['redirect'] = $urlGenerator->generateUrl(
	    array('view' => 'core.ShowItem', 
		  'itemId' => ($itemId == $pageItemId ? $parentId : $pageItemId), 'return' => 1),
	    array('forceServerRelativeUrl' => true));
	$result['status'] = 'success';
	return array(null, $result);
    }
}
?>

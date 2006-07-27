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

/**
 * @version $Revision$ $Date$
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

class ShowItemController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	/*
	 * Note that this always changes user preview mode; if we add management of other variables
	 * to this controller then we should guard this properly.  (Maybe delete this comment after
	 * writing the unit test that verifies it)
	 */
	$guestPreviewMode = GalleryUtilities::getRequestVariables('guestPreviewMode');
	if ($guestPreviewMode != null) {
	    $session =& $gallery->getSession();
	    $session->put('theme.guestPreviewMode', $guestPreviewMode ? 1 : 0);
	}

	return array(null, array('return' => 1, 'status' => array(), 'error' => array()));
    }
}

/**
 * This controller will handle the rendering of an album or item
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ShowItemView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	list ($ret, $item) = $this->_getItem();
	if ($ret) {
	    return array($ret, null);
	}

	/* Make sure we have permission to view this item */
	$ret = GalleryCoreApi::assertHasItemPermission($item->getId(), 'core.view');
	if ($ret) {
	    if ($ret->getErrorCode() & ERROR_PERMISSION_DENIED) {
		list ($ret2, $isAnonymous) = GalleryCoreApi::isAnonymousUser();
		if ($ret2) {
		    return array($ret, null);
		}
		if ($isAnonymous) {
		    /* Redirect to login view */
		    return array(null, array('redirect' => $gallery->getConfig('loginRedirect')));
		}
		/* Try to redirect to default album */
		list ($ret2, $rootId) = GalleryCoreApi::getDefaultAlbumId();
		if ($ret2) {
		    return array($ret, null);
		}
		if ($item->getId() == $rootId) {
		    /* No permission on root album; redirect to login view */
		    return array(null, array('redirect' => $gallery->getConfig('loginRedirect')));
		}
		return array(null, array('redirect' =>
		    array('view' => 'core.ShowItem', 'itemId' => $rootId)));
	    }
	    return array($ret, null);
	}

	/* Increment the view count */
	$ret = GalleryCoreApi::incrementItemViewCount($item->getId());
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, array());
    }

    /**
     * @see GalleryView::_getItem
     */
    function _getItem() {
	list ($ret, $item, $wasSpecified) = parent::_getItem();
	if ($ret) {
	    return array($ret, null, null);
	}
	if (!$wasSpecified) {
	    GalleryUtilities::putRequestVariable('itemId', $item->getId());
	}
	/* Always return wasSpecified==true so w/o itemId we still use root album theme/params */
	return array(null, $item, true);
    }

    /**
     * @see GalleryView::getViewDescription
     */
    function getViewDescription() {
	list ($ret, $item) = $this->_getItem();
	if ($ret) {
	    return array($ret, null);
	}

	$typeName = $item->itemTypeName(true);
	return array(null, $typeName[1]);
    }

    /**
     * @see GalleryView::getViewType
     */
    function getViewType() {
	return VIEW_TYPE_SHOW_ITEM;
    }
}
?>

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
 * @package Shutterfly
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This view creates a form to send data to shutterfly.com
 *
 * @package Shutterfly
 * @subpackage UserInterface
 */
class PrintPhotosView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::loadTemplate()
     */
    function renderImmediate($status, $error) {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();

	list ($itemId, $returnUrl) = GalleryUtilities::getRequestVariables('itemId', 'return');
	if (!empty($itemId)) {
	    $cartItemIds = array($itemId => 1);
	} else {
	    $session =& $gallery->getSession();
	    $cartItemIds = $session->get('shutterfly.cart');
	    $session->remove('shutterfly.cart');
	}
	if (empty($cartItemIds) || empty($returnUrl)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}

	/* Load the necessary item data */
	$itemIds = array_keys($cartItemIds);
	list ($ret, $items) = GalleryCoreApi::loadEntitiesById($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $thumbnails) = GalleryCoreApi::fetchThumbnailsByItemIds($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $resizes) = GalleryCoreApi::fetchResizesByItemIds($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $preferreds) = GalleryCoreApi::fetchPreferredsByItemIds($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = GalleryCoreApi::studyPermissions($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Assemble all our data */
	$i = 1;
	$entries = array();
	foreach ($items as $item) {
	    $itemId = $item->getId();
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['core.viewSource'])) {
		$source = isset($preferreds[$itemId]) ? $preferreds[$itemId] : $item;
	    } else if (isset($permissions['core.viewResizes']) && !empty($resizes[$itemId])) {
		$maxSize = null;
		foreach ($resizes[$itemId] as $resize) {
		    $size = $resize->getDerivativeSize();
		    if (!isset($maxSize) || $size > $maxSize) {
			$source = $resize;
			$maxSize = $size;
		    }
		}
	    } else if (isset($thumbnails[$itemId])) {
		$source = $thumbnails[$itemId];
	    } else {
		continue;
	    }

	    $entry = array('item' => $item->getMemberData());
	    $entry['imageUrl'] = $urlGenerator->generateUrl(
		array('view' => 'core.DownloadItem', 'itemId' => $source->getId()),
		true);

	    if (isset($thumbnails[$itemId])) {
		$entry['thumbUrl'] = $urlGenerator->generateUrl(
		    array('view' => 'core.DownloadItem', 'itemId' => $thumbnails[$itemId]->getId()),
		    true);
		$entry['thumbWidth'] = $thumbnails[$itemId]->getWidth();
		$entry['thumbHeight'] = $thumbnails[$itemId]->getHeight();
	    }
	    $entry['imageWidth'] = $source->getWidth();
	    $entry['imageHeight'] = $source->getHeight();

	    /*
	     * Ugh, the Shutterfly api doesn't have a parameter for quantity.
	     * Repeat the same entry multiple times to get desired quantity!
	     */
	    for ($j = 0; $j < $cartItemIds[$itemId]; $j++) {
		$entries[$i++] = $entry;
	    }
	}

	/*
	 * Ugh, the Shutterfly api can only track its session data via some cookies
	 * (redirecting to a url with embedded session id won't work) so we must
	 * render a form and submit it.. here we set our own cookie that will be
	 * checked to ensure we submit our form only once.
	 */
	setcookie('G2_shutterfly', '1');

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryTemplate.class');
	$template = new GalleryTemplate(dirname(dirname(dirname(__FILE__))));
	$template->setVariable('l10Domain', 'modules_shutterfly');
	$template->setVariable('PrintPhotos', array('returnUrl' => $returnUrl,
						    'count' => count($entries),
						    'entries' => $entries));
	$template->display('gallery:modules/shutterfly/templates/PrintPhotos.tpl');

	return GalleryStatus::success();
    }
}
?>

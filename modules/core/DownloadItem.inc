<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class DownloadItemView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate() {
	global $gallery;

	/* Figure out which item we're talking about */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER,
					__FILE__, __LINE__);
	}

	$gallery->debug("XXX Missing security checks to see if we can " .
			"view this item or resize");

	/* Load the item */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Get the path to the file */
	list ($ret, $path) = $item->fetchPath();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Rebuild derivative cache, if necessary */
	if (is_subclass_of($item, 'GalleryDerivative')) {
	    list ($ret, $current) = $item->isCacheCurrent();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    if (!$current) {
		$ret = $item->rebuildCache();
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	    $mimeType = $item->getDerivativeMimeType();
	    $size = $item->getDerivativeSize();
	} else {
	    $size = $item->getSize();
	    $mimeType = $item->getMimeType();
	}

	if ($size > 0) {
	    header('Content-length: ' . $size);
	}
	header('Content-type: ' . $mimeType);
	readfile($path);

	return GalleryStatus::success();
    }
}
?>

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

class ShowItemView extends GalleryView {

    /**
     * @see GalleryView::fetchHead
     */
    function fetchHead() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out what style sheet to use and calculate its relative URL */
	$style = $item->getStyle();
	if (empty($style)) {
	    list ($ret, $style) =
		$gallery->getModuleParameter('core', 'default.style');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	$style = $gallery->getConfig('code.gallery.styles') . $style . '/style.css';
	$style = GalleryUtilities::convertPathToRelativeUrl($style);

	/* Render the HTML head */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('item', $item->getMemberData());
	$smarty->assign('style', $style);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('head.tpl');

	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::fetchBody
     */
    function fetchBody() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Update the view count */
	$ret = $item->incrementViewCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Find the right layout for this item  */
	$layout = $item->getLayout();
	if (empty($layout)) {
	    list ($ret, $layout) =
		$gallery->getModuleParameter('core', 'default.layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load the correct layout */
	require_once($gallery->getConfig('code.gallery.layouts') .
		     $layout . '/layout.inc');
	$layoutClassName = $layout . 'Layout';
	if (!class_exists($layoutClassName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__), null);
	}
	$layout = new $layoutClassName();

	/* Render and retrieve the body */
	list ($ret, $html) = $layout->render($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	return array(GalleryStatus::success(), $html);
    }

    function _getItem() {
	global $gallery;
	
	/* If we don't have an item id, default to the root */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    list ($ret, $itemId) =
		$gallery->getModuleParameter('core', 'id.rootAlbum');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load the item */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $item);
    }
}
?>

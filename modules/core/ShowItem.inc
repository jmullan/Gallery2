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
     * @see GalleryView::renderHead
     */
    function renderHead() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out what theme to use and calculate its relative URL */
	$themeName = $item->getTheme();

	list ($ret, $themeName) = $item->getTheme();
	if (empty($themeName)) {
	    list ($ret, $themeName) =
		$gallery->getModuleParameter('core', 'default.theme');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $theme) = $this->_loadTheme($themeName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	list ($ret, $style) = $theme->getStyleUrl();
	if ($ret->isError()) {
	    return $ret;
	}

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
     * @see GalleryView::renderBody
     */
    function renderBody() {
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
	$layoutName = $item->getLayout();
	if (empty($layoutName)) {
	    list ($ret, $layoutName) =
		$gallery->getModuleParameter('core', 'default.layouts');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load the correct layout */
	list ($ret, $layout) = $this->_loadLayout($layoutName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

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

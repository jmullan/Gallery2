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

class ShowItemView /* extends GalleryView */ {

    function isImmediate() {
	return false;
    }

    function renderBuffered() {
	global $gallery;

	/* If we don't have an item id, default to the root */
	$itemId = GalleryUtilities::getRequestVariables('itemId');
	if (empty($itemId)) {
	    $itemId = $gallery->getConfig('core.id.rootAlbum');
	}

	/* Load the item */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
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
	    $layout = $gallery->getConfig('core.default.layout');
	}

	/* Load the correct layout */
	require_once($gallery->getConfig('core.directory.layouts') .
		     $layout . '/layout.inc');
	$layoutClassName = $layout . 'Layout';
	if (!class_exists($layoutClassName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__), null);
	}
	$layout = new $layoutClassName();

	/* Render and retrieve the body */
	list ($ret, $body) = $layout->render($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out what style sheet to use and calculate its relative URL */
	$style = $item->getStyle();
	if (empty($style)) {
	    $style = $gallery->getConfig('core.default.style');
	}
	$style = $gallery->getConfig('core.directory.styles') . $style . '.css';
	$dirbase = $gallery->getConfig('core.directory.base');
	$style = str_replace($dirbase, '', $style);
	$urlbase = $gallery->getConfig('core.url.base');
	if (!empty($urlbase)) {
	    $style = $urlbase . '/' . $style;
	}

	/* Render the HTML head */
	$smarty = $gallery->getSmarty();
	$smarty->assign('item', $item->getMemberData());
	$smarty->assign('style', $style);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$head = $smarty->fetch('head.tpl');

	return array(GalleryStatus::success(),
		     array('head' => $head,
			   'body' => $body));
    }
}
?>

<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the rendering of an album or item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ShowItemView extends GalleryView {

    /**
     * @see GalleryView::getThemeName
     */
    function getThemeName() {
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $item->getTheme());
    }

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$template = $this->_getTemplate();
	$template->setVariable('item', $item->getMemberData());
	$html = $template->render('ShowItemHead.tpl');
	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($item->getId(), 'core.view');
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
		$gallery->getModuleParameter('core', 'default.layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load the correct layout */
	$platform = $gallery->getPlatform();

	if (empty($layoutName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__), null);
	}

	require_once($gallery->getConfig('code.gallery.layouts') .
		     $layoutName . '/layout.inc');
	$layoutClassName = $layoutName . 'Layout';
	if (!class_exists($layoutClassName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__), null);
	}
	$layout = new $layoutClassName();
	$ret = $layout->init($layoutName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render and retrieve the body */
	$urlParams['view'] = 'core:ShowItem';
	$urlParams['itemId'] = $item->getId();
	list ($ret, $html) = $layout->render($item, $urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

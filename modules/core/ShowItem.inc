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
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($item->getId(), 'core.view');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Update the view count */
	$ret = GalleryItemAttributesMap::incrementViewCount($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Find the right layout for this item */
	if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
	    $layoutName = $item->getLayout();
	} else {
	    list ($ret, $parent) = $gallery->loadEntitiesById($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $layoutName = $parent->getLayout();
	}
	if (empty($layoutName)) {
	    list ($ret, $layoutName) =
		$gallery->getModuleParameter('core', 'default.layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	}

	/* Load the correct layout */
	if (empty($layoutName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null, null);
	}

	require_once($gallery->getConfig('code.gallery.layouts') .
		     $layoutName . '/layout.inc');
	$layoutClassName = $layoutName . 'Layout';
	if (!class_exists($layoutClassName)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null, null);
	}
	$layout = new $layoutClassName();
	$layout->init($layoutName);

	$ShowItem = array();
	$ShowItem['item'] = $item->getMemberData();
	$ShowItem['layoutL10Domain'] = $layout->getL10Domain();
	
	/* Let the layout load the template and get its body file */
	list ($ret, $ShowItem['layoutBodyFile']) = $layout->loadTemplate($template, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$template->setVariable('ShowItem', $ShowItem);

	return array(GalleryStatus::success(),
		     'modules/core/templates/ShowItemHead.tpl',
		     'modules/core/templates/ShowItem.tpl');
    }

    /**
     * @see GalleryView::rewriteQueryString
     */
    function rewriteQueryString($params) {
	global $gallery;
	
	/* We know who we are */
	unset($params['view']);

	/* Transform the id into a path */
	$buf = '';
	list ($ret, $entity) = $gallery->loadEntitiesById($params['itemId']);
	if ($ret->isSuccess()) {
	    list ($ret, $path) = $entity->fetchLogicalPath();
	    if ($ret->isSuccess()) {
		$buf .= $path;
		unset($params['itemId']);
	    }
	}

	/* Add in anything else as a standard query element */
	if (!empty($params)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $buf .= $urlGenerator->buildQueryString($params);
	}

	return $buf;
    }

    /**
     * @see GalleryView::parseQueryString()
     */
    function parseQueryString($queryString) {

	/* Treat the input as a path and get the right item id out */
	list ($ret, $itemId) = GalleryFileSystemEntityHelper::fetchItemIdByPath($queryString);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	GalleryUtilities::putRequestVariable('itemId', $itemId);
	return GalleryStatus::success();
    }
    
}
?>

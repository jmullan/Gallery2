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
	global $gallery;
	
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * In the near term, we don't allow data items to have their own theme, even though there's room for
	 * it.  Instead, draw them theme from the parent album.
	 */
	$theme = null;
	if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
	    $theme = $item->getTheme();
	} else {
	    $parentId = $item->getParentId();
	    list ($ret, $parent) = $gallery->loadEntitiesById($parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $theme = $parent->gettheme();
	}

	return array(GalleryStatus::success(), $theme);
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

	list ($ret, $layout) = GalleryLayout::loadLayout($layoutName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

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
	$itemId = null;
	$origQueryString = $queryString;
	while ($itemId == null && !empty($queryString)) {
	    list ($ret, $itemId) = GalleryFileSystemEntityHelper::fetchItemIdByPath(urldecode($queryString));
	    if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($ret->isSuccess()) {
		break;
	    } else {
		/* Object is missing -- try trimming the query string */
		$queryString = preg_replace('|/[^/]*$|', '', $queryString);
	    }
	}

	GalleryUtilities::putRequestVariable('itemId', $itemId);
	if ($origQueryString == $queryString) {
	    return array(GalleryStatus::success(), null);
	} else {
	    return array(GalleryStatus::success(), $queryString);
	}
    }
    
}
?>

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
	 * In the near term, we don't allow data items to have their own theme, even though
	 * there's room for it.  Instead, draw them theme from the parent album.
	 */
	$theme = null;
	if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
	    $theme = $item->getTheme();
	} else {
	    $parentId = $item->getParentId();
	    list ($ret, $parent) = GalleryCoreApi::loadEntitiesById($parentId);
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
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Make sure we have permission to view this item */
	$ret = GalleryCoreApi::assertHasItemPermission($item->getId(), 'core.view');
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_PERMISSION_DENIED) {
		list ($ret2, $anonymousId) = GalleryCoreApi::getPluginParameter(
		    'module', 'core', 'id.anonymousUser');
		if ($ret2->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		if ($gallery->getActiveUserId() == $anonymousId) {
		    /* Redirect to login view */
		    return array(GalleryStatus::success(),
				 array('redirect' => GalleryCapabilities::get('loginRedirect')));
		}
		/* Try to redirect to root */
		list ($ret2, $rootId) = GalleryCoreApi::getPluginParameter(
		    'module', 'core', 'id.rootAlbum');
		if ($ret2->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		if ($item->getId() == $rootId) {
		    /* No permission on root album; redirect to login view */
		    return array(GalleryStatus::success(),
				 array('redirect' => GalleryCapabilities::get('loginRedirect')));
		}
		return array(GalleryStatus::success(), array('redirect' =>
		    array('view' => 'core:ShowItem', 'itemId' => $rootId)));
	    }
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Update the view count for non-data items, like Albums */
	if (GalleryUtilities::isA($item, 'GalleryItem') &&
		!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    $ret = GalleryCoreApi::incrementItemViewCount($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $layoutId) = GalleryCoreApi::fetchLayoutId($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$validLayout = false;
	list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	if ($ret->isError() && !($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($layout)) {
	    list ($ret, $validLayout) = $layout->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if ($validLayout) {
	    /* Let the layout load the template and get its body file */
	    list ($ret, $results) = $layout->loadTemplate($template, $item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($results['redirect'])) {
		return array(GalleryStatus::success(), $results);
	    } else if (isset($results['html'])) {
		return array(GalleryStatus::success(), $results);
	    } else {
		$ShowItem = array();
		$ShowItem['item'] = $item->getMemberData();
		$ShowItem['layoutL10Domain'] = $layout->getL10Domain();
		if (isset($results['body'])) {
		    $ShowItem['layoutBodyFile'] = $results['body'];
		}
		$template->setVariable('ShowItem', $ShowItem);

		/* Provide a title if the layout doesn't */
		$head = $template->getVariable('head');
		if (empty($head['tpl']) && empty($head['title'])) {
		    $template->head('modules/core/templates/ShowItemHead.tpl');
		}

		return array(GalleryStatus::success(),
			     array('body' => 'modules/core/templates/ShowItem.tpl'));
	    }
	} else {
	    return array(GalleryStatus::success(),
			 array('redirect' => array('view' => 'core:ShowItemError',
						   'problem' => 'missingLayout',
						   'itemId' => $item->getId())));
	}
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$typeName = $item->itemTypeName(true);
	return array(GalleryStatus::success(), $typeName[1]);
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
	if (isset($params['itemId'])) {
	    list ($ret, $entity) = GalleryCoreApi::loadEntitiesById($params['itemId']);
	    if ($ret->isSuccess()) {
		list ($ret, $path) = $entity->fetchLogicalPath();
		if ($ret->isSuccess()) {
		    $buf .= $path;
		    unset($params['itemId']);
		}
	    }

	    if (!GalleryUtilities::isA($entity, 'GalleryAlbumItem')) {
		$buf .= '.html';
	    }
	}

	/* Add in anything else as a standard query element */
	if (!empty($params)) {
	    $buf .= GalleryUrlGenerator::buildQueryString($params);
	}

	return $buf;
    }

    /**
     * @see GalleryView::parseQueryString()
     */
    function parseQueryString($queryString) {

	/* Treat the input as a path and get the right item id out */
	$itemId = null;
	if (substr($queryString, -5, 5) == '.html') {
	    $queryString = substr($queryString, 0, strlen($queryString) - 5);
	    $queryString .= '/';
	}
	$origQueryString = $queryString;
	while ($itemId == null && !empty($queryString)) {
	    list ($ret, $itemId) = GalleryCoreApi::fetchItemIdByPath(urldecode($queryString));
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

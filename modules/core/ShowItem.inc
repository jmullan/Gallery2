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
     * @see GalleryView::useDefaultStyle
     */
    function useDefaultStyle() {
	return false;
    }

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$path = GalleryUtilities::getRequestVariables('path');
	if ($path) {
	    if (substr($path, -5) == '.html') {
		$path = substr($path, 0, -5);
	    }

	    list ($ret, $itemId) = GalleryCoreApi::fetchItemIdByPath(urldecode($path));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    GalleryUtilities::putRequestVariable('itemId', $itemId);
	}

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

	if (!$validLayout) {
	    return array(GalleryStatus::success(),
			 array('redirect' => array('view' => 'core:ShowItemError',
						   'problem' => 'missingLayout',
						   'itemId' => $item->getId())));
	}

	/* Let the layout load the template and get its body file */
	list ($ret, $results) = $layout->loadTemplate($template, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($results['redirect'])) {
	    return array(GalleryStatus::success(), $results);
	}

	if (isset($results['html'])) {
	    return array(GalleryStatus::success(), $results);
	}

	$ShowItem = array('item' => $item->getMemberData(),
			  'layoutL10Domain' => $layout->getL10Domain());
	if (isset($results['body'])) {
	    $ShowItem['layoutBodyFile'] = $results['body'];
	}
	$template->setVariable('ShowItem', $ShowItem);

	/* Provide a title if the layout doesn't */
	$head = $template->getVariable('head');
	if (empty($head['tpl']) && empty($head['title'])) {
	    $template->head('modules/core/templates/ShowItemHead.tpl');
	}

	/* Increment the view count */
	$ret = GalleryCoreApi::incrementItemViewCount($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ShowItem.tpl'));
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
}
?>

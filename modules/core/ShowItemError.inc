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
class ShowItemErrorView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$problem = GalleryUtilities::getRequestVariables('problem');

	switch ($problem) {
	case 'missingLayout':
	    $layoutId = $item->getLayout();
	    if (empty($layoutId)) {
		list ($ret, $layoutId) =
		    GalleryCoreApi::getPluginParameter('module', 'core', 'default.layout');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    $template->setVariable('ShowItemError',
				   array('itemId' => $item->getId(),
					 'layoutId' => $layoutId));
	    return array(GalleryStatus::success(),
			 array('body' => 'modules/core/templates/ShowItemError.tpl'));

	default:
	    /*
	     * We know of no other problems!   Returning an results will
	     * throw up a security violation page.
	     */
	    return array(GalleryStatus::success(), array());
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

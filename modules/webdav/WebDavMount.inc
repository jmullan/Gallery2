<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

GalleryCoreApi::requireOnce('modules/webdav/classes/WebDavHelper.class');

/**
 * Show instructions to mount Gallery with WebDAV.
 * @package WebDav
 * @subpackage UserInterface
 * @author Andy Staudacher <ast@gmx.ch>
 * @version $Revision$
 */
class WebDavMountView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	$templateAdapter =& $gallery->getTemplateAdapter();
	$urlGenerator =& $gallery->getUrlGenerator();

	/* Load the requested item */
	$itemId = WebDavHelper::getRequestVariable('itemId');

	$path = WebDavHelper::getRequestVariable('path', true, false);
	$pathComponents = preg_split('/\//', $path, -1, PREG_SPLIT_NO_EMPTY);

	if (!empty($path)) {
	    list ($ret, $itemId) = WebDavHelper::fetchItemIdByPathComponents($pathComponents);
	    if ($ret) {
		return array($ret, null);
	    }
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId, 'GalleryItem');
	if ($ret) {
	    return array($ret, null);
	}

	/* Load item links */
	$ret = $templateAdapter->_theme->loadCommonTemplateData(
	    $template, $item, null, array('itemLinks'));
	if ($ret) {
	    return array($ret, null);
	}

	/* Get navigation links for returning to where we came from */
	list ($ret, $navigationLinks) = $urlGenerator->getNavigationLinks();
	if ($ret) {
	    return array($ret, null);
	}

	/* Render HTML body */
	$template->setVariable('navigationLinks', $navigationLinks);

	return array(null, array('body' => 'modules/webdav/templates/WebDavMount.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription
     */
    function getViewDescription() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'webdav');
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, $module->translate('Mount with WebDAV'));
    }
}
?>

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
 * @package Migrate
 * @subpackage Redirect
 * @author Joseph Elwell <jelwell@yahoo.com>
 */

/**
 * This controller handles rewriting URLs from Gallery1 to the new style Gallery2 locations
 *
 * @package Migrate
 * @subpackage Redirect
 */
class RedirectController extends GalleryController {

    /**
    * @see GalleryController::handleRequest()
    */
    function handleRequest($form) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/G1MigrateHelper.class');
	global $gallery;

	list($file, $full, $page) = GalleryUtilities::getRequestVariables('file', 'full', 'page');
	$path = preg_split('|/|', $file, -1, PREG_SPLIT_NO_EMPTY);
	$view = 'core:ShowItem';

	if (count($path) > 1) {
	    // Check for direct link to image file (name.type, name.thumb.type, name.sized.type)
	    $file = explode('.', $path[1]);
	    switch (count($file)) {
	    case 3:
		if ($file[1] == 'sized') {
		    $derivative = DERIVATIVE_TYPE_IMAGE_RESIZE;
		} else if ($file[1] == 'thumb') {
		    $derivative = DERIVATIVE_TYPE_IMAGE_THUMBNAIL;
		}
	    case 2:
		$view = 'core:DownloadItem';
		$path[1] = $file[0];
		if (!isset($derivative)) {
		    $derivative = DERIVATIVE_TYPE_IMAGE_PREFERRED;
		}
	    }

	    list ($ret, $id) = G1MigrateHelper::fetchMapping($path[0], $path[1]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($id) && isset($derivative)) {
		switch ($derivative) {
		case DERIVATIVE_TYPE_IMAGE_PREFERRED:
		    list ($ret, $data) = GalleryCoreApi::fetchPreferredsByItemIds(array($id));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    break;
		case DERIVATIVE_TYPE_IMAGE_RESIZE:
		    list ($ret, $data) = GalleryCoreApi::fetchResizesByItemIds(array($id));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    break;
		case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
		    list ($ret, $data) = GalleryCoreApi::fetchThumbnailsByItemIds(array($id));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    break;
		}
		if (!empty($data)) {
		    $item = $data[$id];
		    if (is_array($item)) {
			$item = array_shift($item);
		    }
		    $id = $item->getId();
		}
	    }
	} else {
	    list ($ret, $id) = G1MigrateHelper::fetchMapping($path[0]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Redirect browser */
	$results = array('redirect' => array());
	$results['redirect']['href'] = $_SERVER['SCRIPT_NAME'];
	$results['redirect']['view'] = $view;

	if (isset($id)) {
	    $results['redirect']['itemId'] = $id;
	    if (!empty($full)) {
		$results['redirect']['imageViewsIndex'] = 1;
	    }
	    if (!empty($page)) {
		$results['redirect']['page'] = $page;
	    }
	}

	$results['status'] = array();
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * View returns .htaccess file
 */
class RedirectView extends GalleryView {
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	header('Content-type: text/plain');
	$template->setVariable('uriBase', $_SERVER['SCRIPT_NAME']);
	return array(GalleryStatus::success(),
		     array('html' => 'modules/migrate/templates/Htaccess.tpl'));
    }
}
?>

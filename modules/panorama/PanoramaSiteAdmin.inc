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
 * @package Panorama
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package Panorama
 * @subpackage UserInterface
 */
class PanoramaSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	if (isset($form['action']['save'])) {
	    if (!isset($form['width']) || ((int)$form['width']) < 100) {
		$error[] = 'form[error][width]';
	    } else {
		foreach (array('itemType', 'itemLink') as $key) {
		    $ret = GalleryCoreApi::setPluginParameter(
			'module', 'panorama', $key,
			(isset($form[$key]) && $form[$key]) ? 1 : 0);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$ret = GalleryCoreApi::setPluginParameter(
		    'module', 'panorama', 'width', (int)$form['width']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['saved'] = 1;
	    }
	} else if(isset($form['action']['reset'])) {
	    require_once(dirname(__FILE__) . '/classes/PanoramaHelper.class');
	    $ret = PanoramaHelper::resetPanoramaItems();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status['reset'] = 1;
	}

	/* Figure out where to redirect upon success */
	$method = empty($error) ? 'redirect' : 'delegate';
	$results[$method]['view'] = 'core.SiteAdmin';
	$results[$method]['subView'] = 'panorama.PanoramaSiteAdmin';
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Panorama
 * @subpackage UserInterface
 */
class PanoramaSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	require_once(dirname(__FILE__) . '/classes/PanoramaHelper.class');
	foreach (array('itemType', 'itemLink') as $key) {
	    if (!isset($form[$key])) {
		$form[$key] = false;
	    }
	}
	if ($form['formName'] != 'PanoramaSiteAdmin') {
	    $form['formName'] = 'PanoramaSiteAdmin';
	    list ($ret, $param) =
		GalleryCoreApi::fetchAllPluginParameters('module', 'panorama');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($param as $key => $value) {
		$form[$key] = $value;
	    }
	}
	list ($ret, $form['count']) = PanoramaHelper::fetchItemCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$template->setVariable('controller', 'panorama.PanoramaSiteAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/panorama/templates/PanoramaSiteAdmin.tpl'));
    }
}
?>

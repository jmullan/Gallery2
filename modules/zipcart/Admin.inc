<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package ZipCart
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package ZipCart
 * @subpackage UserInterface
 */
class AdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	if (isset($form['action']['save']) || isset($form['action']['test'])) {
	    $form['path'] = trim($form['path']);
	    if (empty($form['path'])) {
		$error[] = 'form[error][path][missing]';
	    } else {
		$platform = $gallery->getPlatform();
		if (!$platform->is_executable($form['path'])) {
		    $error[] = 'form[error][path][badPath]';
		}
	    }
	}

	if (isset($form['action']['save']) && empty($error)) {
	    $ret = GalleryCoreApi::setPluginParameter('module', 'zipcart', 'path', $form['path']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'zipcart:Admin';
	    $status['saved'] = 1;
	} else if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'zipcart:Admin';
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'zipcart:Admin';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package ZipCart
 * @subpackage UserInterface
 */
class AdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	if ($form['formName'] != 'AdminZipCart') {
	    $form['formName'] = 'AdminZipCart';
	    list ($ret, $form['path']) =
		    GalleryCoreApi::getPluginParameter('module', 'zipcart', 'path');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (isset($form['action']['test'])) {
	    $form['test'] = empty($form['error']);
	}

	$template->setVariable('controller', 'zipcart:Admin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/zipcart/templates/Admin.tpl'));
    }
}
?>

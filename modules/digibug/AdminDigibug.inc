<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
/**
 * Digibug4CPG - a plugin for gallery to create photo prints, and print product gift items
 * derived from code written by Bharat Mediratta
 * Copyright (C) 2006 Digibug Express, Inc.
 *
 * @package Digibug
 * @author James Andrews <jandrews@digibug.com>
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * @package Digibug
 * @subpackage UserInterface
 */
class AdminDigibugController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest(&$form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	if (isset($form['action']['save'])) {
	    if (empty($form['digibugCustomerId']) || empty($form['digibugPricelistId'])) {
		if(empty($form['digibugCustomerId'])){
		    $error[] = 'form[error][digibugCustomerId][missing]';
		}
		if(empty($form['digibugPricelistId'])){
		    $error[] = 'form[error][digibugPricelistId][missing]';
		}
	    } else {
		if (empty($error)) {

		    $ret = GalleryCoreApi::setPluginParameter('module','digibug', 'digibugCustomerId', $form['digibugCustomerId']);
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = GalleryCoreApi::setPluginParameter('module', 'digibug', 'digibugPricelistId', $form['digibugPricelistId']);
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'digibug');
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $isActive) = $module->isActive();
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $redirect['view'] = 'core.SiteAdmin';
		    $redirect['subView'] = 'core.AdminModules';
		    $status['configured'] = 'digibug';
		}
	    }
	} else if (isset($form['action']['reset'])) {
	    $redirect['view'] = 'core.SiteAdmin';
	    $redirect['subView'] = 'digibug.AdminDigibug';
	} else if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core.SiteAdmin';
	    $redirect['subView'] = 'core.AdminModules';
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core.SiteAdmin';
	    $results['delegate']['subView'] = 'digibug.AdminDigibug';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(null, $results);
    }
}

/**
 * @package Digibug
 * @subpackage UserInterface
 */
class AdminDigibugView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Load our default values if we didn't just come from this form. */
	if ($form['formName'] != 'AdminDigibug') {
	    foreach (array('digibugCustomerId','digibugPricelistId') as $key) {
		list ($ret, $form[$key]) = GalleryCoreApi::getPluginParameter('module', 'digibug', $key);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $form['formName'] = 'AdminDigibug';
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'digibug');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $isActive) = $module->isActive();
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$AdminDigibug = array();
	$AdminDigibug['isConfigure'] = !$isActive;

	$template->setVariable('AdminDigibug', $AdminDigibug);
	$template->setVariable('controller', 'digibug.AdminDigibug');
	return array(null, array('body' => 'modules/digibug/templates/AdminDigibug.tpl'));
    }
}
?>

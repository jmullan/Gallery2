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
 * This controller will handle the addition of an album
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemAddAlbumController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addAlbumItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $lockIds[]) = $gallery->acquireReadLock($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	if (isset($form['action']['create'])) {
	    /*
	     * Validate the input data.
	     */
	    $platform = $gallery->getPlatform();

	    if (empty($form['pathComponent'])) {
		$error[] = 'form.error.pathComponent.missing';
	    } else if (!$platform->isLegalPathComponent($form['pathComponent'])) {
		$error[] = 'form.error.pathComponent.invalid';
	    }

	    if (empty($error)) {
		list ($ret, $instance) =
		    GalleryFactory::newInstance('GalleryEntity', 'GalleryAlbumItem');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($instance)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}  

		$ret = $instance->create($itemId, $form['pathComponent']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_COLLISION) {
			$error[] = 'form.error.pathComponent.collision';
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    if (empty($error)) {
		$instance->setTitle($form['title']);
		$instance->setSummary($form['summary']);
		$instance->setKeywords($form['keywords']);
		$instance->setDescription($form['description']);
		$ret = $instance->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Figure out where to redirect upon success */
		$redirect['view'] = 'core:ItemAdmin';
		$redirect['subView'] = 'core:ItemEditAlbum';
		$redirect['itemId'] = $instance->getId();
		$status['createdAlbum'] = 1;
	    }
	}

	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemAddAlbum';
	}
	$results['status'] = $status;
	$results['error'] = $error;
	

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for the data for a new album to be created
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddAlbumView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addAlbumItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] == 'ItemAddAlbum') {

	    /* Complain if we have any invalid data */

	} else {
	    /* First time around, load the form with item data */
	    $form['pathComponent'] = '';
	    $form['title'] = '';
	    $form['summary'] = '';
	    $form['keywords'] = '';
	    $form['description'] = '';
	    $form['formName'] = 'ItemAddAlbum';
	}

	$ItemAddAlbum = array();

	/* Render the HTML body */
	$template->setVariable('ItemAddAlbum', $ItemAddAlbum);
	$template->setVariable('controller', 'core:ItemAddAlbum');

	return array(GalleryStatus::success(), '', 'modules/core/templates/ItemAddAlbum.tpl');
    }
}
?>

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
	
	if (isset($form['action']['create'])) {
	    $error = false;

	    /*
	     * Validate the input data.
	     */
	    $platform = $gallery->getPlatform();

	    if (empty($form['pathComponent'])) {
		GalleryUtilities::putRequestVariable('form.error.pathComponent.missing', 1);
		$error = true;
	    } else if (!$platform->isLegalPathComponent($form['pathComponent'])) {
		GalleryUtilities::putRequestVariable('form.error.pathComponent.invalid', 1);
		$error = true;
	    }

	    if (!$error) {
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
			GalleryUtilities::putRequestVariable('form.error.pathComponent.collision', 1);
			$error = true;
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    if (!$error) {
		$instance->setTitle($form['title']);
		$instance->setSummary($form['summary']);
		$instance->setKeywords($form['keywords']);
		$instance->setDescription($form['description']);
		$ret = $instance->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Figure out where to redirect upon success */
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemAddAlbum';
		$redirectParams['itemId'] = $itemId;
	    }
	}

	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemAddAlbum');
	    }
	}

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
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
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
	    $form = array();
	    $form['pathComponent'] = '';
	    $form['title'] = '';
	    $form['summary'] = '';
	    $form['keywords'] = '';
	    $form['description'] = '';
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	/* Including myself */
	$parents[] = $item->getMemberData();
	
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('parents', $parents);
	$template->setVariable('controller', 'core:ItemAddAlbum');
	list($ret, $html) = $template->render('ItemAddAlbum.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), $html);
	}

	return array(GalleryStatus::success(), $html);
    }
}
?>

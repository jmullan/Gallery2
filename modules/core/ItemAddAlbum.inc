<?php
/*
 * $RCSfile
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

class ItemAddAlbumController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.addAlbum'));
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
	    
	    if (!$platform->isLegalPathComponent($form['pathComponent'])) {
		GalleryUtilities::putRequestVariable('form.error.pathComponent.invalid', 1);
		$error = true;
	    }

	    list ($ret, $instance) =
		GalleryFactory::newInstance('GalleryEntity', 'GalleryAlbumItem');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = $instance->create($itemId,
				     $form['pathComponent'],
				     $gallery->getActiveUserId());
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_COLLISION) {
		    GalleryUtilities::putRequestVariable('form.error.pathComponent.collision', 1);
		    $error = true;
		} else {
		    return array($ret->wrap(__FILE__, __LINE__), null);
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
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemAddAlbum');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class ItemAddAlbumView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list ($itemId, $formName) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.addAlbum'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemAddAlbum') {

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
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$this->_setTemplateVariable('parents', $parents);
	$this->_setTemplateVariable('controller', 'core:ItemAddAlbum');
	$html = $this->_renderTemplate('core', 'ItemAddAlbum.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * This controller will handle the changes users make to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditLayoutController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	
	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	$status = array();
	$error = array();
	$errorMessage = array();

	if (isset($form['action']['save'])) {
	    list ($ret, $layout) = GalleryItemHelper::fetchLayout($item);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    /* Get all the possible settings */
	    list ($ret, $settings) = $layout->getSettings($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Validate the settings */
	    $validationErrors = $layout->validateSettings($form['key']);
	    if (empty($validationErrors)) {
		/* Save any settings that have changed */
		foreach ($settings as $setting) {
		    if ($setting['key'] != $form['key'][$setting['key']]) {
			$ret = $layout->setParameter($setting['key'], $form['key'][$setting['key']], $itemId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}

		/* Redirect upon success */
		$redirect['view'] = 'core:ItemAdmin';
		$redirect['subView'] = 'core:ItemEditLayout';
		$redirect['itemId'] = $itemId;
		$status['saved'] = 1;
	    } else {
		foreach ($validationErrors as $validationKey => $validationMessage) {
		    $error[] = sprintf('form.error.key.%s.invalid', $validationKey);
		    $errorMessage[$validationKey] = $validationMessage;
		}
		GalleryUtilities::putRequestVariable('form.errorMessage', $errorMessage);
	    }
	} else if (isset($form['action']['undo'])) {
	    /* Redirect upon success */
	    $redirect['view'] = 'core:ItemAdmin';
	    $redirect['subView'] = 'core:ItemEditLayout';
	    $redirect['itemId'] = $itemId;
	    $status['restored'] = 1;
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemEditLayout';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for settings of an album
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditLayoutView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $layout) = GalleryItemHelper::fetchLayout($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $settings) = $layout->getSettings($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($form['formName'] != 'ItemEditLayout') {
	    $form['formName'] = 'ItemEditLayout';
	    foreach ($settings as $setting) {
		$form['key'][$setting['key']] = $setting['values'][0];
	    }
	}

	$ItemEditLayout = array();
	$ItemEditLayout['settings'] = $settings;
	$ItemEditLayout['layout']['name'] = $layout->getName();
	$ItemEditLayout['layout']['l10Domain'] = $layout->getL10Domain();
	
	$template->setVariable('ItemEditLayout', $ItemEditLayout);
	$template->setVariable('controller', 'core:ItemEditLayout');
	return array(GalleryStatus::success(), '', 'modules/core/templates/ItemEditLayout.tpl');
    }
}
?>

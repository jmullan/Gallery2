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
	    
	    /* Validate the settings */
	    $validationErrors = $layout->validateSettings($form['key']);
	    if (empty($validationErrors)) {
		/* Get the item settings */
		list ($ret, $settings) = $layout->getSettings($itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/*
		 * Any settings that are marked as "use global" should be removed from this item.  Others
		 * should be updated in the database.  Note that we set the parameter even if it is the same
		 * as the original setting value, since we want to make sure that the value is stored per
		 * item, and the original setting value could have been from the global space.
		 */
		foreach ($settings as $setting) {
		    $key = $setting['key'];
		    if (!empty($form['useGlobal'][$key])) {
			$ret = $layout->removeItemParameter($key, $itemId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			$ret = $layout->setParameter($key, $form['key'][$key], $itemId);
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
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $layout) = GalleryItemHelper::fetchLayout($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the per-item settings (global + item) */
	list ($ret, $settings) = $layout->getSettings($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Fetch the global-only params */
	list ($ret, $globalParams) =
	    GalleryPluginParameterMap::fetchAllParameters('layout', $layout->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Fetch the item-only params */
	list ($ret, $itemParams) =
	    GalleryPluginParameterMap::fetchAllParameters('layout', $layout->getId(), $itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ItemEditLayout') {
	    $form['formName'] = 'ItemEditLayout';
	    foreach ($settings as $setting) {
		$key = $setting['key'];
		$form['key'][$key] = $setting['value'];

		/* If the key doesn't exist in the item params then it's a global setting */
		$form['useGlobal'][$key] = isset($itemParams[$key]) ? 0 : 1;
	    }
	} else {
	    /* Make sure all checkbox values are defined */
	    foreach ($settings as $setting) {
		$key = $setting['key'];
		if (!isset($form['useGlobal'][$key])) {
		    $form['useGlobal'][$key] = 0;
		}
	    }
	}

	$ItemEditLayout = array();
	$ItemEditLayout['settings'] = $settings;
	$ItemEditLayout['globalParams'] = $globalParams;
	$ItemEditLayout['itemParams'] = $itemParams;
	$ItemEditLayout['layout']['name'] = $layout->getName();
	$ItemEditLayout['layout']['l10Domain'] = $layout->getL10Domain();
	
	$template->setVariable('ItemEditLayout', $ItemEditLayout);
	$template->setVariable('controller', 'core:ItemEditLayout');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemEditLayout.tpl'));
    }
}
?>

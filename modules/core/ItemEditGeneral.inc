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

class ItemEditGeneralController extends GalleryController {

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
							  array('core.all', 'core.changeText'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['save'])) {

	    /*
	     * Validate the input data.
	     */
	    $platform = $gallery->getPlatform();
	    
	    if (!$platform->isLegalPathComponent($form['pathComponent'])) {
		GalleryUtilities::putRequestVariable('form.error.pathComponent.invalid', 1);
	    } else {
		list ($ret, $lockId) = $gallery->acquireWriteLock($itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    
		list ($ret, $item) = $gallery->loadEntitiesById($itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/*
		 * It's possible to get a collision when we rename, so try that
		 * first.  If there's no collision then make the rest of the changes.
		 */
		$ret = $item->rename($form['pathComponent']);
		if ($ret->isError() && !($ret->getErrorCode() & ERROR_COLLISION)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($ret->isError() && $ret->getErrorCode() & ERROR_COLLISION) {
		    GalleryUtilities::putRequestVariable('form.error.pathComponent.collision', 1);
		} else {
		    $item->setTitle($form['title']);
		    $item->setSummary($form['summary']);
		    $item->setKeywords($form['keywords']);
		    $item->setDescription($form['description']);

		    $ret = $item->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Figure out where to redirect upon success */
		    $redirectParams['view'] = 'core:ItemAdmin';
		    $redirectParams['subView'] = 'core:ItemEditGeneral';
		    $redirectParams['itemId'] = $itemId;
		}

		$ret = $gallery->releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditGeneral');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class ItemEditGeneralView extends GalleryView {

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
							  array('core.all', 'core.changeText'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemEditGeneral' && empty($form['action']['undo'])) {
	    /* Complain if we have any invalid data */
	    $platform = $gallery->getPlatform();

	    if (!$platform->isLegalPathComponent($form['pathComponent'])) {
		$form['error']['pathComponent']['invalid'] = 1;
	    }
	} else {
	    /* First time around, load the form with item data */
	    $form['title'] = $item->getTitle();
	    $form['summary'] = $item->getSummary();
	    $form['keywords'] = $item->getKeywords();
	    $form['description'] = $item->getDescription();
	    $form['pathComponent'] = $item->getPathComponent();
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('parents', $parents);
	$template->setVariable('controller', 'core:ItemEditGeneral');
	$html = $template->render('ItemEditGeneral.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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

/**
 * @version $Revision$ $Date$
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the deletion of an item
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemDeleteController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* 
	 * Get the parent id -- it's the destination item after we delete this
	 * one
	 */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$parentId = $item->getParentId();

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($item->getId() == $rootId) {
	    $gallery->debug("Can't delete the root album");
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__),
			 null);
	}
	
	if (isset($form['action']['delete'])) {

	    $ret = $gallery->deleteEntityById($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['itemId'] = $parentId;
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemDelete');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for confirmation on the deletion of an item
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemDeleteView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list ($itemId, $formName) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($item->getId() == $rootId) {
	    $gallery->debug("Can't delete the root album");
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
					      __FILE__, __LINE__),
			 null);
	}
	
	/* Count its children */
	$childCount = 0;
	if ($item->canContainChildren()) {
	    list ($ret, $childCountTable) = 
		GalleryItemHelper::getChildCounts(array($item->getId()),
						  $gallery->getActiveUserId());
	    if (isset($childCountTable[$item->getId()])) {
		$childCount = $childCountTable[$item->getId()];
	    }
	}
	
	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('childCount', $childCount);
	$template->setVariable('controller', 'core:ItemDelete');
	$html = $template->render('ItemDelete.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * @package Debug
 * @subpackage UserInterface
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will show a tree of elements starting with the current
 * item
 *
 * @package Debug
 * @subpackage UserInterface
 */
class ShowTreeView extends GalleryView {

    /**
     * 
     */
    function renderHead() {
	/* Render the HTML head */
	$template = $this->_getTemplate();
	$html = $template->render('DebugHead.tpl');

	return array(GalleryStatus::success(), $html);
    }

    /**
     * 
     */
    function renderBody($form) {
	global $gallery;

	$return = GalleryUtilities::getFormVariables('return.');
	list ($entityId, $itemId) = GalleryUtilities::getRequestVariables('entityId', 'itemId');

	/* Make sure we have permission */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Try the entity id.  Fall back to the item id, then the root album id */
	if (empty($entityId)) {
	    if (empty($itemId)) {
		$entityId = $itemId;
	    } else {
		list ($ret, $entityId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Get the parent ids leading up to this entity */
	list ($ret, $parentIds) = GalleryChildEntityHelper::fetchParentIds($entityId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get all of this entity's children */
	list ($ret, $childIds) = GalleryChildEntityHelper::fetchChildIds($entityId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load everything at once */
	list ($ret, $entityObjects) =
	    $gallery->loadEntitiesById(array_merge($parentIds, $childIds, array($entityId)));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach ($entityObjects as $entity) {
	    $entityTable[$entity->getId()] = $entity->getMemberData();
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('view', 'debug:ShowTree');
	$template->setVariable('parentIds', $parentIds);
	$template->setVariable('childIds', $childIds);
	$template->setVariable('entityId', $entityId);
	$template->setVariable('entityTable', $entityTable);
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$html = $template->render('ShowTree.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

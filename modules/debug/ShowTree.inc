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
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	list ($entityId, $itemId) = GalleryUtilities::getRequestVariables('entityId', 'itemId');

	/* Make sure we have permission */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Try the entity id.  Fall back to the item id, then the root album id */
	if (empty($entityId)) {
	    if (!empty($itemId)) {
		$entityId = $itemId;
	    } else {
		list ($ret, $entityId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Get the parent ids leading up to this entity */
	list ($ret, $parentIds) = GalleryCoreApi::fetchParentSequence($entityId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load everything at once */
	list ($ret, $entity) = GalleryCoreApi::loadEntitiesById($entityId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get all of this entity's children */
	if ($entity->getCanContainChildren()) {
	    list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($entity);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $childIds = array();
	}

	if (!empty($parentIds) || !empty($childIds)) {
	    /* Load everything at once */
	    list ($ret, $entityObjects) =
		GalleryCoreApi::loadEntitiesById(array_merge($parentIds, $childIds));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	$entityObjects[] = $entity;

	foreach ($entityObjects as $entity) {
	    $isItem[$entity->getId()] = GalleryUtilities::isA($entity, 'GalleryItem');
	    $entityTable[$entity->getId()] = $entity->getMemberData();
	}

	/* Render the HTML body */
	$ShowTree = array();
	$ShowTree['parentIds'] = $parentIds;
	$ShowTree['childIds'] = $childIds;
	$ShowTree['entityId'] = $entityId;
	$ShowTree['entityTable'] = $entityTable;
	$ShowTree['isItem'] = $isItem;
	$ShowTree['form'] = $form;
	$template->setVariable('ShowTree', $ShowTree);

	return array(GalleryStatus::success(),
		     array('head' => 'modules/debug/templates/DebugHead.tpl',
			   'body' => 'modules/debug/templates/ShowTree.tpl'));
    }
}
?>

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
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will handle moving one or more items from one album to
 * another.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemMoveController extends GalleryController {

    /**
     * Move the selected items into the destination album, if all the
     * permissions are set correctly.
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	$status = array();
	$error = array();
	if (isset($form['action']['move'])) {

	    /* First check if everything would be okay with the change */
	    $canAddItem = false;
	    $canAddAlbum = false;
	    if (!empty($form['destination'])) {
		/* Check if we can add albums or items here */
		$newParentId = $form['destination'];
		list ($ret, $permissions) = GalleryItemHelper::getPermissions($newParentId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$canAddItem = isset($permissions['core.addDataItem']);
		$canAddAlbum = isset($permissions['core.addAlbumItem']);
		if (!$canAddAlbum && !$canAddItem) {
		    $error[] = 'form[error][destination][permission]';
		}

		/* Load the destination item */
		list($ret, $newParent) = $gallery->loadEntitiesById($newParentId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Load its parents: we don't want recursive moves */
		list($ret, $newParentAncestors) = $newParent->fetchParents();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$newParentAncestorIds = array();
		foreach ($newParentAncestors as $thisItem) {
		    $newParentAncestorIds[] = $thisItem['id'];
		}
		$newParentAncestorIds[] = $newParentId;
	    } else {
		$error[] = 'form[error][destination][empty]';
	    }
	    
	    if (empty($error) && !empty($form['selectedIds'])) {
		$selectedIds = array_keys($form['selectedIds']);
		
		/* Load the source items */
		list ($ret, $selectedItems) = $gallery->loadEntitiesById($selectedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$ret = GalleryItemHelper::studyPermissions($selectedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$oldParentIds = array();
		foreach ($selectedItems as $selectedItem) {
		    $selectedId = $selectedItem->getId();

		    /* Can't move into a tree that is included in the source */

		    foreach ($newParentAncestorIds as $newParentAncestorId) {
			if ($selectedId == $newParentAncestorId) {
			    $error[] = 'form[error][source][' . $selectedId . '][selfMove]';
			    continue 2; // Skip out of the foreach($selectedItem) also
			}
		    }
		    
		    $oldParentIds[] = $selectedItem->getParentId();
		    list ($ret, $permissions) = GalleryItemHelper::getPermissions($selectedId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Can we delete this item from here? */
		    if (! isset($permissions['core.delete'])) {
			$error[] = 'form[error][source][' . $selectedId . '][permission][delete]';
		    }
		    
		    /* Check if the destination allows this source to be added */
		    if ($selectedItem->getCanContainChildren() && ! $canAddAlbum) {
			$error[] = 'form[error][source][' . $selectedId . '][permission][addAlbumItem]';
		    } elseif (! $selectedItem->getCanContainChildren() && ! $canAddItem) {
			$error[] = 'form[error][source][' . $selectedId . '][permission][addDataItem]';
		    }
		}
		$oldParentIds = array_values(array_unique($oldParentIds));
	    }
	    
	    if (empty($error) && !empty($selectedIds) && !empty($newParentId)) {

		/* Read lock myself, my parent id and the new parent id */
		$lockIds = array();
		list ($ret, $lockIds[]) =
		    $gallery->acquireReadLock(array($newParentId, $itemId));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Write lock all the items we're moving */
		list ($ret, $lockIds[]) = $gallery->acquireWriteLock($selectedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/* If we have no problems, do the moves */
		$status['moved']['count'] = 0;
		foreach ($selectedItems as $selectedItem) {
		    $ret = $selectedItem->move($newParentId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['moved']['count']++;

		    $ret = $selectedItem->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$ret = $gallery->releaseLocks($lockIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Figure out where to redirect upon success */
		$redirect['view'] = 'core:ItemAdmin';
		$redirect['subView'] = 'core:ItemMove';
		$redirect['itemId'] = $itemId;
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemMove';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for which files to move/copy and which is the
 * destination.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemMoveView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* itemId is the album where we want to move items from */
	list ($itemId, $selectedId) = GalleryUtilities::getRequestVariables('itemId', 'selectedId');

        if ($form['formName'] != 'ItemMove') {
            /* First time around, load the form with item data */
            if ($selectedId) {
                $form['selectedIds'][$selectedId] = true;
            }
            $form['destination'] = '';
	    $form['formName'] = 'ItemMove';
        }

        list ($ret, $item) = $gallery->loadEntitiesById($itemId);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	/* Get all peers that we can delete */
        list ($ret, $peerIds) =
            GalleryItemHelper::fetchChildItemIdsWithPermission($itemId, 'core.delete');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	$albumIds = array();
	$peers = array();
	$peerTypes = array();
	$albumTree = array();
	if (!empty($peerIds)) {
	    /* Load all the peers */
	    list ($ret, $peerItems) = $gallery->loadEntitiesById($peerIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Build our peers table */
	    $peers = array();
	    foreach ($peerItems as $peerItem) {
		$peers[$peerItem->getId()] = $peerItem->getMemberData();
		if (GalleryUtilities::isA($peerItem, 'GalleryAlbumItem')) {
		    $peerTypes['album'][$peerItem->getId()] = 1;
		} else {
		    $peerTypes['data'][$peerItem->getId()] = 1;
		}
		$peers[$peerItem->getId()]['selected'] = isset($form['selectedIds'][$peerItem->getId()]);
	    }

	    /* Get all possible destinations (where user has write permission) */
	    list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get ids of all all albums where we can add new data items */
	    list ($ret, $albumIds['addDataItem']) =
		GalleryItemHelper::fetchAllItemIds('GalleryAlbumItem', 'core.addDataItem');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get ids of all all albums where we can add new album items */
	    list ($ret, $albumIds['addAlbumItem']) =
		GalleryItemHelper::fetchAllItemIds('GalleryAlbumItem', 'core.addAlbumItem');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Merge them together to get the master list of ids */
	    $albumIds['allIds'] = array_unique(array_merge($albumIds['addDataItem'],
							   $albumIds['addAlbumItem']));

	    /* Load all the album entities */
	    list ($ret, $albums) = $gallery->loadEntitiesById($albumIds['allIds']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $albumTree = $this->_createAlbumTree($albums);
	}

	$ItemMove = array();

	$ItemMove['albumIds'] = $albumIds;
        $ItemMove['peers'] = $peers;
        $ItemMove['peerTypes'] = $peerTypes;
        $ItemMove['albumTree'] = $albumTree;
        $template->setVariable('ItemMove', $ItemMove);
        $template->setVariable('controller', 'core:ItemMove');

        return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemMove.tpl'));
    }

    /**
     * Turn a set of albums into a depth tree suitable for display in a
     * hierarchical format.
     *
     * @access private
     */
    function _createAlbumTree($albums) {
	/* Index the albums by id */
	$map = array();
	foreach ($albums as $album) {
	    $albumId = $album->getId();
	    $parentId = $album->getParentId();
	    $map[$albumId]['instance'] = $album;
	    if (!empty($parentId)) {
		$map[$albumId]['parent'] = $parentId;
		$map[$parentId]['children'][] = $albumId;
	    }
	}

	/*
	 * Prune parents that don't exist.  This can occur if we have multiple
	 * roots (unusual) or an album in the middle of the hierarchy that is
	 * not viewable.
	 */
	foreach ($map as $id => $info) {
	    if (isset($info['parent']) && !isset($map[$info['parent']]['instance'])) {
		unset($map[$info['parent']]);
	    }
	}

	/* Find root albums */
	foreach ($map as $id => $info) {
	    if (!isset($info['parent']) || !isset($map[$info['parent']])) {
		$roots[] = $id;
	    }
	}

	/* Walk the root albums */
	$tree = array();
	foreach ($roots as $id) {
	    $tree = array_merge($tree, $this->_createDepthTree($map, $id));
	}

	return $tree;
    }

    /**
     * Recursively walk a parent/child map and build the depth tree.
     *
     * @access private
     */
    function _createDepthTree(&$map, $id, $depth=0) {
	$data = array();
	$data[] = array('depth' => $depth, 'data' => $map[$id]['instance']->getMemberData());
	if (isset($map[$id]['children'])) {
	    foreach ($map[$id]['children'] as $childId) {
		$data = array_merge($data, $this->_createDepthTree($map, $childId, $depth+1));
	    }
	}

	return $data;
    }
}
?>

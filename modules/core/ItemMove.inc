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

	if (isset($form['action']['move'])) {

	    /* First check if everything would be okay with the change */
	    $problem = false;
	    $canAddItem = false;
	    $canAddAlbum = false;
	    if (!empty($form['destination'])) {
		/* Check if we can add albums or items here */
		$newParentId = $form['destination'];
		GalleryUtilities::putRequestVariable('form.destination', $newParentId);
		list ($ret, $permissions) = GalleryItemHelper::getPermissions($newParentId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$canAddItem = isset($permissions['core.addDataItem']);
		$canAddAlbum = isset($permissions['core.addAlbumItem']);
		if (!$canAddAlbum && !$canAddItem) {
		    $problem = true;
		    GalleryUtilities::putRequestVariable('form.error.destination.permission', 1);
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
		$problem = true;
		GalleryUtilities::putRequestVariable('form.error.destination.empty', 1);
	    }
	    
	    if (!$problem && !empty($form['selectedIds'])) {
		$selectedIds = array_keys($form['selectedIds']);
		GalleryUtilities::putRequestVariable('form.selectedIds', $selectedIds);
		
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
			    $problem = true;
			    GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId .
								 '.selfMove', 1);
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
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId .
							     '.permission.delete', 1);
		    }
		    
		    /* Check if the destination allows this source to be added */
		    if ($selectedItem->getCanContainChildren() && ! $canAddAlbum) {
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId .
							     '.permission.addAlbumItem', 1);
		    } elseif (! $selectedItem->getCanContainChildren() && ! $canAddItem) {
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId .
							     '.permission.addDataItem', 1);
		    }
		}
		$oldParentIds = array_values(array_unique($oldParentIds));
	    }
	    
	    if (!$problem && !empty($selectedIds) && !empty($newParentId)) {

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
		foreach ($selectedItems as $selectedItem) {
		    $ret = $selectedItem->move($newParentId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

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
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['itemId'] = $itemId;
	    }
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemMove');
	    }
	}

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
     * 
     */
    function renderBody($form) {
	global $gallery;

	/* itemId is the album where we want to move items from */
	list ($itemId, $selectedId) = GalleryUtilities::getRequestVariables('itemId', 'selectedId');

        if ($form['formName'] == 'ItemMove') {
	    /* No validation at the moment */
        } else {
            /* First time around, load the form with item data */
            $form = array();
            if ($selectedId) {
                $form['selectedIds'][$selectedId] = true;
            }
            $form['destination'] = '';
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

        /* Render the HTML body */
        $template = $this->_getTemplate();
	$template->setVariable('albumIds', $albumIds);
        $template->setVariable('item', $item->getMemberData());
        $template->setVariable('form', $form);
        $template->setVariable('peers', $peers);
        $template->setVariable('peerTypes', $peerTypes);
        $template->setVariable('albumTree', $albumTree);
        $template->setVariable('controller', 'core:ItemMove');
        $html = $template->render('ItemMove.tpl');

        return array(GalleryStatus::success(), $html);
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

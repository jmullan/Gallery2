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
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will handle moving one or more items from one album to
 * another
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemMoveController extends GalleryController {

    /**
     * 
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	if (isset($form['action']['move'])) {

	    /* First check if everything would be okey with the change */
	    $problem = false;
	    $canAddItem = false;
	    $canAddAlbum = false;
	    if ($form['destination']) {
		/* Check if we can add albums or items here */
		$newParentId = $form['destination'];
		GalleryUtilities::putRequestVariable('form.destination', $newParentId);
		list ($ret, $permissions) = GalleryItemHelper::getPermissions($newParentId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (isset($permissions['core.addItem'])) {
		    $canAddItem = true;
		}
		if (isset($permissions['core.addAlbum'])) {
		    $canAddAlbum = true;
		}
		if (! $canAddAlbum && ! $canAddItem) {
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
	    if ($form['selectedIds']) {
		$selectedIds = array_keys($form['selectedIds']);
		GalleryUtilities::putRequestVariable('form.selectedIds', $selectedIds);
		/* Load the source items */
		list ($ret, $selectedItems) = $gallery->loadEntitiesById($selectedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$ret = GalleryItemHelper::studyPermissions($selectedIds, $gallery->getActiveUserId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		foreach ($selectedItems as $selectedItem) {
		    $selectedId = $selectedItem->getId();
		    /* Can't move into a tree that is included in the source */
		    $recursiveError = false;
		    foreach ($newParentAncestorIds as $newParentAncestorId) {
			if ($selectedId == $newParentAncestorId) {
			    $problem = true;
			    GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId . '.selfMove', 1);
			    continue;
			}
		    }
		    if ($recursiveError) {
			continue;
		    }
		    $oldParentIds[] = $selectedItem->getParentId();
		    list ($ret, $permissions) = GalleryItemHelper::getPermissions($selectedId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    /* Can we delete this item from here? */
		    if (! isset($permissions['core.delete'])) {
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId . '.permission.deleteSource', 1);
		    }
		    /* Check if the destination allows this source to be added */
		    if ($selectedItem->getCanContainChildren() && ! $canAddAlbum) {
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId . '.permission.addAlbum', 1);
		    } elseif (! $selectedItem->getCanContainChildren() && ! $canAddItem) {
			$problem = true;
			GalleryUtilities::putRequestVariable('form.error.source.' . $selectedId . '.permission.addItem', 1);
		    }
		}
		$oldParentIds = array_values(array_unique($oldParentIds));
	    }
	    if (! $problem && !empty($selectedIds) && !empty($newParentId)) {

		/* Read lock myself and the new parent id */
		$lockIds = array();
		list ($ret, $lockIds[]) = $gallery->acquireReadLock($newParentId, $itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Write locok all the items we're moving */
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
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
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
    function renderBody() {
	global $gallery;

	/* itemId is the album where we want to move items from */
	list ($itemId, $formName, $selectedId) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName', 'selectedId');
	$form = GalleryUtilities::getFormVariables('form.');

        if ($formName == 'ItemMove') {
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

        /* Get all data we have from our peers */
        list ($ret, $peerIds) =
            GalleryItemHelper::fetchChildItemIdsWithPermission($itemId, 'core.delete');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        list ($ret, $peerItems) = $gallery->loadEntitiesById($peerIds);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

        /* Find out which ones we can move away from here */
        $ret = GalleryItemHelper::studyPermissions($peerIds, $gallery->getActiveUserId());
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

        $peers = array();
        $onlyItems = true;
        $onlyAlbums = true;
        foreach ($peerItems as $peerItem) {
            list ($ret, $permissions) = GalleryItemHelper::getPermissions($peerItem->getId());
            if (! isset($permissions['core.delete'])) {
                continue;
            }
            $peers[$peerItem->getId()] = $peerItem->getMemberData();
            $peers[$peerItem->getId()]['selected'] = isset($form['selectedIds'][$peerItem->getId()]) ? true : false;
            if (GalleryUtilities::isA($peerItem, 'GalleryAlbumItem')) {
                $onlyItems = false;
                $peers[$peerItem->getId()]['type'] = 'album';
            } else {
                $onlyAlbums = false;
                $peers[$peerItem->getId()]['type'] = 'item';
            }
        }

        /* Get all possible destinations (where user has write permission in) */
        list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        list ($ret, $root) = $gallery->loadEntitiesById($rootId);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        list ($ret, $entityTree) = $root->getDescendantsList();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

        $destinations = array();
        foreach ($entityTree as $treeItem) {
            if (! GalleryUtilities::isA($treeItem['entity'], 'GalleryItem')) {
                continue;
            }
            if (! $treeItem['entity']->getCanContainChildren()) {
                continue;
            }
            if ($treeItem['entity']->getId() == $itemId) {
                continue;
            }
            /* Check for write permission in the destination album */
            list ($ret, $permissions) = GalleryItemHelper::getPermissions($treeItem['entity']->getId());
            if ($ret->isError()) {
                return array($ret->wrap(__FILE__, __LINE__), null);
            }

            if ($onlyAlbums && ! isset($permissions['core.addAlbum'])) {
                continue;
            }
            if ($onlyItems && ! isset($permissions['core.addItem'])) {
                continue;
            }
            if (!$onlyAlbums && !$onlyItems
                && ! isset($permissions['core.addItem'])
                && ! isset($permissions['core.addAlbum'])) {
                /* Check for the specific permission in the controller, we 
                 * don't know which items/albums we will have to move yet
                 */
                continue;
            }
            $destinations[] = array_merge(
                                array('level' => $treeItem['level']),
                                $treeItem['entity']->getMemberData()
                              );
        }

        /* Render the HTML body */
        $template = $this->_getTemplate();
        $template->setVariable('itemId', $itemId);
        $template->setVariable('form', $form);
        $template->setVariable('peers', $peers);
        $template->setVariable('destinations', $destinations);
        $template->setVariable('controller', 'core:ItemMove');
        $html = $template->render('ItemMove.tpl');

        return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * This controller will handle linking one or more items from one album to
 * another.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemCreateLinkController extends GalleryController {

    /**
     * Link the selected items into the destination album, if all the
     * permissions are set correctly.
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	$status = array();
	$error = array();
	if (isset($form['action']['link'])) {
	    if (empty($form['destination'])) {
		$error[] = 'form[error][destination][empty]';
	    }

	    if (empty($error)) {
		$destinationId = $form['destination'];
		$selectedIds = array_keys($form['selectedIds']);

		/* Make sure we can write to the destination */
		list ($ret, $permissions) = GalleryItemHelper::getPermissions($destinationId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		if (!isset($permissions['core.addDataItem'])) {
		    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__),
				 null);
		}

		/* Load the selected items */
		list ($ret, $selectedItems) = $gallery->loadEntitiesById($selectedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/* Look out for monkey business */
		foreach ($selectedItems as $selectedItem) {
		    if ($selectedItem->getParentId() != $itemId) {
			return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__),
				     null);
		    }
		    
		    if (!$selectedItem->isLinkable()) {
			return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__),
				     null);
		    }
		}
		
		/*
		 * Ok we've got linkable items and a legal destination album.
		 * Lock everything up and start linkin'.  We need to read lock
		 * the source ids, source hierarchy and destination hierarchy.
		 */
		$ids = array_merge($selectedIds, array($itemId, $destinationId));
		list ($ret, $locks[]) = $gallery->acquireReadLock($ids);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		list ($ret, $locks[]) = $gallery->acquireReadLockParents($itemId);
		if ($ret->isError()) {
		    $gallery->releaseLocks($locks);
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		list ($ret, $locks[]) = $gallery->acquireReadLockParents($destinationId);
		if ($ret->isError()) {
		    $gallery->releaseLocks($locks);
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    
		/* Create all our links */
		$status['linked']['count'] = 0;
		foreach ($selectedItems as $selectedItem) {

		    $classType = get_class($selectedItem);
		    $linkedItem = new $classType;

		    /* If we're linking to an item that's already a link, then link to its source instead */
		    if ($selectedItem->isLinked()) {
			$linkedEntity = $selectedItem->getLinkedEntity();
			$ret = $linkedItem->createLink($linkedEntity, $destinationId);
		    } else {
			$ret = $linkedItem->createLink($selectedItem, $destinationId);
		    }
		    if ($ret->isError()) {
			$gallery->releaseLocks($locks);
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $linkedItem->save();
		    if ($ret->isError()) {
			$gallery->releaseLocks($locks);
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = GalleryItemHelper::addExistingItemToAlbum($linkedItem, $destinationId);
		    if ($ret->isError()) {
			$gallery->releaseLocks($locks);
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    $status['linked']['count']++;
		}

		/* Release the locks */
		$ret = $gallery->releaseLocks($locks);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Figure out where to redirect upon success */
		$redirect['view'] = 'core:ItemAdmin';
		$redirect['subView'] = 'core:ItemCreateLink';
		$redirect['itemId'] = $itemId;
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemCreateLink';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view lets you choose where you want to put the new link
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemCreateLinkView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($itemId, $selectedId) = GalleryUtilities::getRequestVariables('itemId', 'selectedId');

        if ($form['formName'] != 'ItemCreateLink') {
            /* First time around, load the form with item data */
            if ($selectedId) {
                $form['selectedIds'][$selectedId] = true;
            }
            $form['destination'] = '';
	    $form['formName'] = 'ItemCreateLink';
        }

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Get all peers that we can link */
	list ($ret, $peerIds) =
	    GalleryItemHelper::fetchChildItemIdsWithPermission($item->getId(), 'core.view');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	/* Load all the peers */
	list ($ret, $peerItems) = $gallery->loadEntitiesById($peerIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Build our peers table (linkable items only) */
	$peers = array();
	foreach ($peerItems as $peerItem) {
	    if ($peerItem->isLinkable()) {
		$peers[$peerItem->getId()] = $peerItem->getMemberData();
		$peers[$peerItem->getId()]['selected'] =
		    isset($form['selectedIds'][$peerItem->getId()]);
	    }
	}

	/* Find all the possible locations where this item can be linked. */
	list ($ret, $ids) = GalleryItemHelper::fetchAllItemIds('GalleryAlbumItem', 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load all the album entities */
	list ($ret, $albums) = $gallery->loadEntitiesById($ids);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ItemCreateLink = array();
	$ItemCreateLink['albumTree'] = GalleryUtilities::createAlbumTree($albums);
	$ItemCreateLink['peers'] = $peers;

	$template->setVariable('ItemCreateLink', $ItemCreateLink);
        $template->setVariable('controller', 'core:ItemCreateLink');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemCreateLink.tpl'));
    }
}
?>

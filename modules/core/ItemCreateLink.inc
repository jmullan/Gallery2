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
		$peers[$peerItem->getId()]['selected'] = isset($form['selectedIds'][$peerItem->getId()]);
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
	$template->setVariable('controller', '');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemCreateLink.tpl'));
    }
}
?>

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
 * This controller will handle moving one or more items from one album to
 * another.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemReorderController extends GalleryController {

    /**
     * Move the selected items into the destination album, if all the
     * permissions are set correctly.
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Check permissions */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = false;
	if (isset($form['action']['reorder'])) {

	    /* Verify that we've got what we need */
	    if (empty($form['selectedId'])) {
		GalleryUtilities::putRequestVariable('form.error.selectedId.missing', 1);
		$error = true;
	    }

	    if (empty($form['targetId'])) {
		GalleryUtilities::putRequestVariable('form.error.targetId.missing', 1);
		$error = true;
	    }

	    $before = 0;
	    if (empty($form['placement']) || $form['placement'] == 'before') {
		$before = 1;
	    }

	    /*
	     * Make sure that the selectedId and targetId are children of the album
	     */
	    if (!$error) {
		$selectedId = $form['selectedId'];
		$targetId = $form['targetId'];
		list ($ret, $entities) = $gallery->loadEntitiesById(array($selectedId, $targetId));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($entities[0]->getParentId() != $itemId ||
		    $entities[1]->getParentId() != $itemId) {
		    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
		}
	    }

	    if (!$error) {
		$loopCount = 0;
		while (true) {
		    /*
		     * Get the current and target order weights (have to do
		     * this after every rebalance, too)
		     */
		    list ($ret, $orderWeights) =
			    GalleryItemAttributesMap::fetchOrderWeights(array($selectedId, $targetId));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    list ($ret, $next) = GalleryItemAttributesMap::fetchNextWeight($targetId,
                        $before ? LOWER_WEIGHT : HIGHER_WEIGHT);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (isset($next)) {
			/* Floor rounds down, so separate the sign and the magnitude */
			$delta = (int)(($next - $orderWeights[$targetId]) / 2);
		    } else {
			/*
			 * We couldn't get a weight, which means that the
			 * target is at the edge.  So go beyond the edge
			 */
			$delta = $before ? -1000 : 1000;
		    }

		    if (abs($delta) > 0) {
			break;
		    }
			
		    if ($loopCount++ > 0) {
			/*
			 * If we have to rebalance more than once then something went wrong!
			 */
			return array(GalleryStatus::error(ERROR_UNKNOWN, __FILE__, __LINE__), null);
		    }

		    /* A delta of 0 means that we don't have room, so rebalance */
		    $ret = GalleryItemAttributesMap::rebalanceChildOrderWeights($itemId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$newWeight = $orderWeights[$targetId] + $delta;
		
		$ret = GalleryItemAttributesMap::setOrderWeight($selectedId, $newWeight);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		// Redirect back to the same page so that we can do more reordering
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemReorder';
		$redirectParams['itemId'] = $itemId;
	    }
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemReorder');
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
class ItemReorderView extends GalleryView {

    /**
     * 
     */
    function renderBody($form) {
	global $gallery;

	/* itemId is the album where we want to move items from */
	$itemId = GalleryUtilities::getRequestVariables('itemId');

        if ($form['formName'] == 'ItemReorder') {
	    /* No validation at the moment */
        } else {
            /* First time around, load the form with item data */
            $form = array();
        }

        list ($ret, $item) = $gallery->loadEntitiesById($itemId);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	/* Get all peers that we can see */
        list ($ret, $peerIds) = $item->fetchChildIds();
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

        /* Render the HTML body */
        $template = $this->_getTemplate();
        $template->setVariable('item', $item->getMemberData());
        $template->setVariable('form', $form);
        $template->setVariable('peers', $peers);
        $template->setVariable('peerTypes', $peerTypes);
        $template->setVariable('controller', 'core:ItemReorder');
        list($ret, $html) = $template->render('ItemReorder.tpl');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), $html);
        }
	
        return array(GalleryStatus::success(), $html);
    }
}
?>

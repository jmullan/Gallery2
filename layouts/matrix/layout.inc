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
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/** 
 * This implements the standard gallery layout 
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class MatrixLayout extends GalleryLayout {

    /**
     * @see GalleryLayout::init()
     */
    function init() {
	global $gallery;
	
	$this->setId('matrix');
	$this->setName('Matrix');
	$this->setDescription($gallery->i18n('Classic Gallery2 look and feel'));
	$this->setVersion('1.0');
	$this->setL10Domain('layouts_matrix');
	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryLayout::getSettings()
     */
    function getSettings($itemId=null) {
	global $gallery;

	list ($ret, $params) = $this->fetchParameters($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($params['rows'])) {
	    $params['rows'] = 3;
	}
	
	if (!isset($params['columns'])) {
	    $params['columns'] = 3;
	}
	
	$settings = array();
	$settings[] = array('key' => 'rows',
			    'name' => $gallery->i18n('Rows per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['rows']);
	$settings[] = array('key' => 'columns',
			    'name' => $gallery->i18n('Columns per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['columns']);
	return array(GalleryStatus::success(), $settings);
    }

    /**
     * @see GalleryLayout::validateSettings
     */
    function validateSettings($settings) {
	$error = array();
	if (empty($settings['rows']) || !is_numeric($settings['rows'])) {
	    $error['rows'] = $this->translate('You must enter a number greater than 0');
	}
	
	if (empty($settings['columns']) || !is_numeric($settings['columns'])) {
	    $error['columns'] = $this->translate('You must enter a number greater than 0');
	}

	return $error;
    }
    
    /**
     * @see GalleryLayout::render
     */
    function loadTemplate(&$template, $item) {
	GalleryProfiler::start('layouts.matrix.layout::loadTemplate');

	list ($ret, $params) = $this->fetchParameters($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($params['rows'])) {
	    $params['rows'] = 3;
	}
	
	if (!isset($params['columns'])) {
	    $params['columns'] = 3;
	}

	if ($item->getCanContainChildren()) {
	    list ($ret, $file) = $this->_loadAlbumTemplate($template, $item, $params);
	} else {
	    list ($ret, $file) = $this->_loadSingleTemplate($template, $item, $params);
	}

	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	GalleryProfiler::stop('layouts.matrix.layout::loadTemplate');
	return array(GalleryStatus::success(), $file);
    }

    /**
     * Render an album
     *
     * @param object GalleryItem the item to render.  Can be any subclass of
     *               GalleryItem
     * @param array the layout properties
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     */
    function _loadAlbumTemplate(&$template, $item, $properties) {
	global $gallery;

	$rows = $properties['rows'];
	$columns = $properties['columns'];
	$perPage = $rows * $columns;
	
	/* Figure out what page we're on */
	$page = GalleryUtilities::getRequestVariables('page');
	if (empty($page)) {
	    /*
	     * We don't have a page number.  If we have a highlight id, then figure out what
	     * page that id is on and redirect to that page.
	     */
	    $highlightId = GalleryUtilities::getRequestVariables('highlightId');
	    if (!empty($highlightId)) {
		list ($ret, $childIds) = $item->fetchChildIds();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$page = 1;
		for ($i = 0; $i < sizeof($childIds); $i++) {
		    if ($childIds[$i] == $highlightId) {
			/* Found it */
			$page = ceil(($i+1) / $perPage);
			break;
		    }
		}

		/* Redirect to the new page */
		$results['redirect'] = array('view' => 'core:ShowItem',
					     'itemId' => $item->getId(),
					     'page' => $page);
		return array(GalleryStatus::success(), $results);
	    } else {
		$page = 1;
	    }
	}

	$start = $perPage * ($page - 1);
	$children = array();

	/* Count the total number of children */
	/* XXX: we could combine this with the other fetchChildCounts() call below */
	list ($ret, $totalChildCount) = GalleryItemHelper::fetchChildCounts(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($totalChildCount)) {
	    $totalChildCount = 0;
	} else {
	    $totalChildCount = $totalChildCount[$item->getId()];
	}

	/* Get the child id => child types */
	list ($ret, $childIds) = $item->fetchChildIds($start, $perPage);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$childItems = array();
	if (!empty($childIds)) {
	    /* Load the children */
	    list ($ret, $childItems) = $gallery->loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /*
	     * Study all the entities that we're going to work with.  This
	     * gives us a chance to perform any database operations in the
	     * aggregate to save us having to do them individually for each
	     * entity later on.
	     */
	    $this->_studyItems(array_merge(array($item->getId()), $childIds));

	    /* Get item summaries */
	    list ($ret, $moduleChildSummaries) = $this->_getModuleItemSummaries($childItems);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get the "grandchild" counts */
	    list ($ret, $childCounts) = GalleryItemHelper::fetchChildCounts($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

            /* Create a table of child id -> child data */
	    $childTable = array();
	    foreach ($childItems as $child) {
		$childId = $child->getId();
		$childTable[$childId] = $child->getMemberData();

		if (!empty($moduleChildSummaries[$childId])) {
		    /*
		     * $moduleChildSummaries[$childId] is:
		     *   $array[<moduleId>] = <html>
		     */
		    $childTable[$childId]['moduleSummaries'] = $moduleChildSummaries[$childId];
		} else {
		    $childTable[$childId]['moduleSummaries'] = array();
		}

		if (!empty($childCounts[$childId])) {
		    $childTable[$childId]['childCount'] = $childCounts[$childId];
		} else {
		    $childTable[$childId]['childCount'] = 0;
		}
	    }

	    /* Load the thumbnails */
	    list ($ret, $thumbTable) =
		    GalleryDerivativeHelper::fetchThumbnailsByItemIds($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* put it all together */
	    $i = 0;
	    if ($gallery->getDebug()) {
		$gallery->debug("Begin: Rebuilding cache");
	    }
	    foreach ($childIds as $id) {
		$children[$i] = $childTable[$id];
		if (isset($thumbTable[$id])) {
		    /* Rebuild cache, to be prepared to the getMemberData() call */
		    list ($ret, $thumbTable[$id]) =
			GalleryDerivativeHelper::rebuildCacheIfNotCurrent($thumbTable[$id]->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $children[$i]['thumbnail'] = $thumbTable[$id]->getMemberData();
		}
		$i++;
	    }
	    if ($gallery->getDebug()) {
		$gallery->debug("End: Rebuilding cache");
	    }
	}

	/* Get the view counts */
	if (empty($childIds)) {
	    $viewCounts = array();
	} else {
	    list ($ret, $viewCounts) = GalleryItemAttributesMap::fetchViewCounts($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	
	/* Set up the navigator */
	$totalPages = ceil($totalChildCount / $perPage);
	$navigator = array();
	if ($page > 1) {
	    $navigator['first'] = array('view' => 'core:ShowItem',
					    'itemId' => $item->getId(),
					    'page' => 1);
	    $navigator['back'] = array('view' => 'core:ShowItem',
					    'itemId' => $item->getId(),
					    'page' => $page-1);
	}
	if ($page < $totalPages) {
	    $navigator['next'] = array('view' => 'core:ShowItem',
					    'itemId' => $item->getId(),
					    'page' => $page+1);
	    $navigator['last'] = array('view' => 'core:ShowItem',
					    'itemId' => $item->getId(),
					    'page' => $totalPages);
	}
	
	/* Show a window of 11 pages in the page navigator */
	$windowSize = 6;
	$jumprange = array();
	$lowerPage = max($page - (int)($windowSize / 2), 1);
	$upperPage = min($page + (int)($windowSize / 2), $totalPages);
	if ($upperPage == 0) {
	    $upperPage = 1;
	}
	if ($upperPage == $totalPages) {
	    $lowerPage = max($upperPage - $windowSize, 1);
	} else if ($lowerPage == 1) {
	    $upperPage = min($lowerPage + ($windowSize-1), $totalPages);
	}
	for ($i = $lowerPage; $i <= $upperPage; $i++) {
	    $jumprange[] = $i;
	}
	if ($lowerPage > 1) {
	    array_unshift($jumprange, 1);
	}
	if ($upperPage < $totalPages) {
	    $jumprange[] = $totalPages;
	}

	/* Get peer info */
	list ($ret, $peers, $peerIds, $totalPeerCount, $itemIndex) = $this->_loadPeerInfo($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item links and flatten out the modules */
	$moduleItemLinks = array();
	list ($ret, $tmp) =
	    $this->_getModuleItemLinks(array_merge(array($item), $childItems));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($tmp as $tmpItem => $moduleLinks) {
	    $moduleItemLinks[$tmpItem] = array();
	    foreach ($moduleLinks as $module => $links) {
		$moduleItemLinks[$tmpItem] = array_merge($moduleItemLinks[$tmpItem], $links);
	    }
	    usort($moduleItemLinks[$tmpItem], array($this, '_sortItemLinks'));
	}

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item details */
	list ($ret, $moduleItemDetailFiles) = $this->_loadModuleItemDetails($template, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system content */
	list ($ret, $moduleSystemContentFiles) = $this->_loadModuleSystemContent($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the active user */
	list ($ret, $user) = $gallery->getActiveUser();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get all the owners */
	$ownerIds = array($item->getOwnerId() => 1);
	$owners = array();
	foreach ($childIds as $childId) {
	    $ownerIds[$childTable[$childId]['ownerId']] = 1;
	}
	list ($ret, $tmp) = $gallery->loadEntitiesById(array_keys($ownerIds));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($tmp as $owner) {
	    $owners[$owner->getId()] = $owner->getMemberData();
	}

	/* Assemble the children into rows of columns */
	$r = 0;
	$c = 0;
	$childRows = array();
	foreach ($children as $child) {
	    $width = $child['canContainChildren'] ? $properties['columns'] : 1;

	    if ($c + $width > $properties['columns']) {
		$r++;
		$c = 0;
	    }
	    $childRows[$r][$c] = $child;
	    $c += $width;
	}

	list ($ret, $rootAlbumId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$show = array();
	$show['peerSidebarBox'] = ($item->getId() != $rootAlbumId);

	$layout['show'] = $show;
	$layout['user'] = $user->getMemberData();
	$layout['owners'] = $owners;
	$layout['viewCounts'] = $viewCounts;
	$layout['owner'] = $owners[$item->getOwnerId()];
	$layout['moduleItemLinks'] = $moduleItemLinks;
	$layout['moduleSystemContentFiles'] = $moduleSystemContentFiles;
	$layout['moduleSystemLinks'] = $moduleSystemLinks;
	$layout['moduleItemDetailFiles'] = $moduleItemDetailFiles;
	$layout['childRows'] = $childRows;
	$layout['columnSize'] = $properties['columns'];
	$layout['currentPage'] = $page;
	$layout['totalPageCount'] = $totalPages;
	$layout['totalChildCount'] = $totalChildCount;
	$layout['totalPeerCount'] = $totalPeerCount;
	$layout['peers'] = $peers;
	$layout['navigator'] = $navigator;
	$layout['jumprange'] = $jumprange;
	$layout['layoutUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));
	$layout['parents'] = $parents;
	if (!empty($parents)) {
	    $layout['parent'] = $parents[sizeof($parents)-1];
	} else {
	    $layout['parent'] = null;
	}
	$layout['item'] = $item->getMemberData();

	$template->setVariable('layout', $layout);
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/matrix/templates/albumBody.tpl'));
    }


    /**
     * Render a single item
     *
     * @param object GalleryItem the item to render.  Can be any subclass of
     *               GalleryItem
     * @param array the layout properties
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     * @todo Maybe display the sizes of an image in increasing order
     */
    function _loadSingleTemplate($template, $item, $properties) {
	global $gallery;

	/*
	 * Figure out all possible views of this item that the user can see and
	 * get them into an acceptable format for the template engine.
	 */
	$imageViews = array();
	$can = array();
	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Can we see this item at all? */
	if (!isset($permissions['core.view'])) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__, "Permission denied"), null);
	}

	/* If the user can see resized versions, add those to the list */
	if (isset($permissions['core.viewResizes'])) {
	    /* Load the resizes */
	    list ($ret, $resizes) =
		GalleryDerivativeHelper::fetchResizesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($gallery->getDebug()) {
		$gallery->debug("Begin: Rebuilding cache");
	    }
	    if (!empty($resizes)) {
		foreach ($resizes[$item->getId()] as $resize) {
		    /* Rebuild cache, to be prepared to the getMemberData() call */
		    list ($ret, $resize) = GalleryDerivativeHelper::rebuildCacheIfNotCurrent($resize->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $imageViews[] = $resize->getMemberData();
		    $can['viewInline'][] = 1;
		}
	    }
	    if ($gallery->getDebug()) {
		$gallery->debug("End: Rebuilding cache");
	    }
	}

	/* If the user can see the full version, add it to the list */
	$sourceImage = null;
	if (isset($permissions['core.viewSource'])) {
	    /* Add the full version */
	    list ($ret, $preferred) =
		GalleryDerivativeHelper::fetchPreferredsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Show the preferred item, if it's there */
	    if (empty($preferred)) {
		$sourceImage = $item->getMemberData();
		if ($item->canBeViewedInline()) {
		    $can['viewInline'][] = 1;
		} else {
		    $can['viewInline'][] = 0;
		}
	    } else {
		$sourceImage = $preferred[$item->getId()]->getMemberData();
		$can['viewInline'][] = 1;
	    }
	    $imageViews[] = $sourceImage;
	    $sourceImageViewIndex = sizeof($imageViews)-1;
	}

	/*
	 * If all else fails, just show the thumbnail.
	 */
	if (empty($imageViews)) {

	    /* Load the thumbnail */
	    list ($ret, $thumbnails) =
		GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($thumbnails)) {
		$imageViews[] = $thumbnails[$item->getId()]->getMemberData();
		$can['viewInline'][] = 1;
	    }
	}

	$imageViewsIndex = GalleryUtilities::getRequestVariables('imageViewsIndex');
	if (empty($imageViewsIndex)) {
	    $imageViewsIndex = 0;
	}

	/* Don't let the index overflow the images array */
	$imageViewsIndex = min($imageViewsIndex, sizeof($imageViews) - 1);

	/* Get peer info */
	list ($ret, $peers, $peerIds, $totalPeerCount, $itemIndex) = $this->_loadPeerInfo($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

        $navigator = array();
        if ($itemIndex > 0) {
            $navigator['first'] = array('view' => 'core:ShowItem', 'itemId' => $peerIds[0]);
            $navigator['back'] = array('view' => 'core:ShowItem', 'itemId' => $peerIds[$itemIndex-1]);
	}
	
        if ($itemIndex < $totalPeerCount-1) {
            $navigator['next'] = array('view' => 'core:ShowItem', 'itemId' => $peerIds[$itemIndex+1]);
            $navigator['last'] = array('view' => 'core:ShowItem', 'itemId' => $peerIds[sizeof($peerIds)-1]);
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item links and flatten out the modules */
	$moduleItemLinks = array();
	list ($ret, $tmp) = $this->_getModuleItemLinks($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($tmp as $tmpItem => $moduleLinks) {
	    $moduleItemLinks[$tmpItem] = array();
	    foreach ($moduleLinks as $module => $links) {
		$moduleItemLinks[$tmpItem] = array_merge($moduleItemLinks[$tmpItem], $links);
	    }
	    usort($moduleItemLinks[$tmpItem], array($this, '_sortItemLinks'));
	}

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item details */
	list ($ret, $moduleItemDetailFiles) = $this->_loadModuleItemDetails($template, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system content */
	list ($ret, $moduleSystemContentFiles) = $this->_loadModuleSystemContent($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Tell Smarty about everything we've learned */
	$layout['can'] = $can;
	if (isset($sourceImageViewIndex)) {
	    $layout['sourceImageViewIndex'] = $sourceImageViewIndex;
	}

	/* Get the active user */
	list ($ret, $user) = $gallery->getActiveUser();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the owner */
	list ($ret, $owner) = $gallery->loadEntitiesById($item->getOwnerId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$show = array();
	$show['peerSidebarBox'] = 1;

	$layout['show'] = $show;
	$layout['user'] = $user->getMemberData();
	$layout['owner'] = $owner->getMemberData();
	$layout['moduleItemLinks'] = $moduleItemLinks;
	$layout['moduleSystemLinks'] = $moduleSystemLinks;
	$layout['moduleSystemContentFiles'] = $moduleSystemContentFiles;
	$layout['moduleItemDetailFiles'] = $moduleItemDetailFiles;
	$layout['baseUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));
	$layout['parents'] = $parents;
	$layout['peers'] = $peers;
	if (!empty($parents)) {
	    $layout['parent'] = $parents[sizeof($parents)-1];
	} else {
	    $layout['parent'] = null;
	}
	$layout['item'] = $item->getMemberData();
	$layout['imageViews'] = $imageViews;
	$layout['sourceImage'] = $sourceImage;
	$layout['imageViewsIndex'] = $imageViewsIndex;
	$layout['totalPeerCount'] = $totalPeerCount;
	$layout['item'] = $item->getMemberData();
	$layout['navigator'] = $navigator;

	$template->setVariable('layout', $layout);
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/matrix/templates/singleBody.tpl'));
    }

    function _loadPeerInfo($item) {
	global $gallery;

	if ($item->getParentId() == null) {
	    return array(GalleryStatus::success(), array(), array(), 0, 0);
	}

	/*
	 * In order to figure out where we are, we have to load the entire list
	 * of children of my parent and then iterate through it to find our
	 * current index.
	 */
	list ($ret, $parent) = $gallery->loadEntitiesById($item->getParentId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $peerIds) = $parent->fetchChildIds();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$totalPeerCount = sizeof($peerIds);

	for ($i = 0; $i < $totalPeerCount; $i++) {
	    if ($peerIds[$i] == $item->getId()) {
		$itemIndex = $i;
	    }
	}
	
	/* Get a window of peer ids around us */
	$windowSize = 6;
	$peers = array();
	$neighborStart = max($itemIndex - (int)($windowSize/2), 0);
	$neighborEnd = min($itemIndex + (int)($windowSize/2), sizeof($peerIds)-1);

	/* If the window is pinned to one end, expand it to the entire windowSize */
	if ($neighborStart == 0) {
	    $neighborEnd = min(sizeof($peerIds)-1, $windowSize-1);
	} else if ($neighborEnd == sizeof($peerIds)-1) {
	    $neighborStart = max(sizeof($peerIds)-1 - $windowSize, 0);
	}

	if ($neighborStart > 0) {
	    $peers[] = $peerIds[0];
	}
	for ($i = $neighborStart; $i <= $neighborEnd; $i++) {
	    $peers[] = $peerIds[$i];
	}
	if ($neighborEnd < sizeof($peerIds) - 1) {
	    $peers[] = $peerIds[sizeof($peerIds)-1];
	}

	/* Load them all */
	list ($ret, $peers) = $gallery->loadEntitiesById($peers);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tag them with their index and convert to member data */
	$j = 0;
	if ($neighborStart > 0) {
	    $peers[0] = array('index' => 1, 'peer' => $peers[0]->getMemberData());
	    $j++;
	}

	for ($i = $neighborStart; $i <= $neighborEnd; $i++) {
	    $peers[$j] = array('index' => $i + 1, 'peer' => $peers[$j]->getMemberData());
	    $j++;
	}

	/* Load the last peer, if its not in the window */
 	if ($neighborEnd < sizeof($peerIds)-1) {
	    $peers[$j] = array('index' => sizeof($peerIds), 'peer' => $peers[$j]->getMemberData());
 	}

	return array(GalleryStatus::success(), $peers, $peerIds, $totalPeerCount, $itemIndex);
    }

    function _sortItemLinks($a, $b) {
	return strcmp($a['text'], $b['text']);
    }
}
?>

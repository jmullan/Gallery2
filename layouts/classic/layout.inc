<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class ClassicLayout extends GalleryLayout {

    /**
     * @see GalleryLayout::render
     */
    function render($item, $urlParams) {
	GalleryProfiler::start('GalleryLayout::render');

	/* Look up my properties */
	//list ($ret, $properties) = GalleryItemPropertiesMap::getProperties('layout');
	$properties = array('rows' => 3,
			    'columns' => 3);

	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('properties', $properties);
	$this->_setTemplateVariable('item', $item->getMemberData());
	
	if ($item->canContainChildren()) {
	    list ($ret, $html) = $this->_renderAlbum($item, $urlParams, $properties);
	} else {
	    list ($ret, $html) = $this->_renderSingle($item, $urlParams, $properties);
	}

	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	GalleryProfiler::stop('GalleryLayout::render');
	return array(GalleryStatus::success(), $html);
    }

    /**
     * Render an album
     *
     * @param object GalleryItem the item to render.  Can be any subclass of
     *               GalleryItem
     * @param array key => value url parameters provided by the
     *              parent view -- the module can augment or override these.
     * @param array the layout properties
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     */
    function _renderAlbum($item, $urlParams, $properties) {
	global $gallery;

	/* Figure out what page we're on */
	$pageNumber = GalleryUtilities::getRequestVariables('layoutPage');
	if (empty($pageNumber)) {
	    $pageNumber = 1;
	}

	$rows = $properties['rows'];
	if (empty($rows)) {
	    $rows = 3;
	}
	
	$columns = $properties['columns'];
	if (empty($columns)) {
	    $columns = 3;
	}

	$perPage = $rows * $columns;
	$start = $perPage * ($pageNumber - 1);
	$children = array();

	/* Count the total number of children */
	/* XXX: we could combine this with the other getChildCounts() call below */
	list ($ret, $totalChildCount) =
	    GalleryItemHelper::getChildCounts(array($item->getId()),
					      $gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($totalChildCount)) {
	    $totalChildCount = 0;
	} else {
	    $totalChildCount = $totalChildCount[$item->getId()];
	}

	/* Get the child id => child types */
	list ($ret, $childIds) =
	    $item->fetchChildIds($gallery->getActiveUserId(), $start, $perPage);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($childIds)) {
	    /* Load the children */
	    list ($ret, $childEntities) = $gallery->loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get item summaries */
	    list ($ret, $moduleChildSummaries) =
		$this->_getModuleItemSummaries($childEntities, $urlParams);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get the "grandchild" counts */
	    list ($ret, $childCounts) =
		GalleryItemHelper::getChildCounts($childIds, $gallery->getActiveUserId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

            /* Create a table of child id -> child data */
	    $childTable = array();
	    foreach ($childEntities as $child) {
		$childId = $child->getId();
		$childTable[$childId] = $child->getMemberData();

		if (!empty($moduleChildSummaries[$childId])) {
		    $childTable[$childId]['moduleSummaries'] = $moduleChildSummaries[$childId];
		} else {
		    $childTable[$childId]['moduleSummaries'] = array();
		}

		if (!empty($childCounts[$childId])) {
		    $childTable[$childId]['childCount'] = $childCounts[$childId];
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
	    foreach ($childIds as $id) {
		$children[$i] = $childTable[$id];
		if (isset($thumbTable[$id])) {
		    $children[$i]['thumbnail'] = $thumbTable[$id]->getMemberData();
		}
		$i++;
	    }
	}
	
	/* Set up the navigator */
	$totalPages = ceil($totalChildCount / $perPage);
	$navigator = array();
	if ($pageNumber > 1) {
	    $navigator['firstPage'] = 1;
	    $navigator['previousPage'] = $pageNumber-1;
	}
	if ($pageNumber < $totalPages) {
	    $navigator['lastPage'] = $totalPages;
	    $navigator['nextPage'] = $pageNumber+1;
	}

	/* Show a window of 11 pages in the page navigator */
	$windowSize = 11;
	$lowerPage = max($pageNumber - (int)($windowSize / 2), 1);
	$upperPage = min($pageNumber + (int)($windowSize / 2), $totalPages);
	if ($upperPage == $totalPages) {
	    $lowerPage = max($upperPage - $windowSize, 1);
	} else if ($lowerPage == 1) {
	    $upperPage = min($lowerPage + ($windowSize-1), $totalPages);
	}
	for ($i = $lowerPage; $i <= $upperPage; $i++) {
	    $navigator['jumprange'][] = $i;
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item links */
	list ($ret, $moduleItemLinks) = $this->_getModuleItemLinks($item, $urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item details */
	list ($ret, $moduleItemDetails) = $this->_getModuleItemDetails($item, $urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks($urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tell Smarty about everything we've learned */
	$this->_setTemplateVariable('moduleItemLinks', $moduleItemLinks);
	$this->_setTemplateVariable('moduleSystemLinks', $moduleSystemLinks);
	$this->_setTemplateVariable('moduleItemDetails', $moduleItemDetails);
	$this->_setTemplateVariable('navigator', $navigator);
	$this->_setTemplateVariable('children', $children);
	$this->_setTemplateVariable('pageNumber', $pageNumber);
	$this->_setTemplateVariable('totalPageCount', $totalPages);
	$this->_setTemplateVariable('totalChildCount', $totalChildCount);
	$this->_setTemplateVariable('layoutUrl',
            GalleryUtilities::convertPathToRelativeUrl(dirname(__FILE__)));
	$this->_setTemplateVariable('parents', $parents);
	
	/* Parse the body template and send it back */
	$html = $this->_renderTemplate('classic', 'albumBody.tpl');
	return array(GalleryStatus::success(), $html);
    }


    /**
     * Render a single item
     *
     * @param object GalleryItem the item to render.  Can be any subclass of
     *               GalleryItem
     * @param array key => value url parameters provided by the
     *              parent view -- the module can augment or override these.
     * @param array the layout properties
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     */
    function _renderSingle($item, $urlParams, $properties) {
	global $gallery;

	/*
	 * Figure out all possible views of this item that the user can see and
	 * get them into an acceptable format for the template engine.
	 */
	$imageViews = array();
	    
	/* Load the resizes */
	$gallery->debug('XXX: missing view-resize permission check');
	list ($ret, $resizes) =
	    GalleryDerivativeHelper::fetchResizesByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$imageViewsIndex = GalleryUtilities::getRequestVariables('imageViewsIndex');
	if (empty($imageViewsIndex)) {
	    $imageViewsIndex = 0;
	}

	if (!empty($resizes)) {
	    foreach ($resizes[$item->getId()] as $resize) {
		$imageViews[] = array('inline' => true,
				      'height' => $resize->getHeight(),
				      'width' => $resize->getWidth(),
				      'size' => $resize->getDerivativeSize(),
				      'id' => $resize->getId());
	    }
	}

	/* Add the full version */
	$gallery->debug('XXX: missing view-full permission check');
	list ($ret, $preferred) =
	    GalleryDerivativeHelper::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Show the preferred item, if it's there */
	if (empty($preferred)) {
	    if (is_subclass_of($item, 'GalleryDataItem')) {
		$dataItem = array('size' => $item->getSize(),
				  'id' => $item->getId());

		if ($item->canBeViewedInline()) {
		    $dataItem['inline'] = true;
		    $dataItem['height'] = $item->getHeight();
		    $dataItem['width'] = $item->getWidth();
		} else {
		    $dataItem['inline'] = false;
		}
		
		$imageViews[] = $dataItem;
	    }
	} else {
	    $preferred = $preferred[$item->getId()];
	    $imageViews[] = array('inline' => true,
				  'height' => $preferred->getHeight(),
				  'width' => $preferred->getWidth(),
				  'size' => $preferred->getDerivativeSize(),
				  'id' => $preferred->getId());
	}

	/*
	 * In order to figure out where we are, we have to load the entire list
	 * of children of my parent and then iterate through it to find our
	 * current index.
	 *
	 * XXX SCALE: this doesn't scale well
	 */
	list ($ret, $parent) =
	    $gallery->loadEntitiesById($item->getParentId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Count the total number peers */
	/* Get the child id => child types */
	list ($ret, $peerIds) =
	    $parent->fetchChildIds($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$totalPeerCount = sizeof($peerIds);
	
	for ($i = 0; $i < $totalPeerCount; $i++) {
	    if ($peerIds[$i] == $item->getId()) {
		$itemIndex = $i;
	    }
	}

	$navigator = array();
	if ($itemIndex > 0) {
	    $navigator['firstItem'] = $peerIds[0];
	    $navigator['previousItem'] = $peerIds[$itemIndex-1];
	}
	
	if ($itemIndex < $totalPeerCount-1) {
	    $navigator['nextItem'] = $peerIds[$itemIndex+1];
	    $navigator['lastItem'] = $peerIds[sizeof($peerIds)-1];
	}

	/* Load the parents */
	list ($ret, $parents) = $item->fetchParents();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item links */
	list ($ret, $moduleItemLinks) = $this->_getModuleItemLinks($item, $urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get item details */
	list ($ret, $moduleItemDetails) = $this->_getModuleItemDetails($item, $urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks($urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tell Smarty about everything we've learned */
	$this->_setTemplateVariable('navigator', $navigator);
	$this->_setTemplateVariable('moduleItemLinks', $moduleItemLinks);
	$this->_setTemplateVariable('moduleSystemLinks', $moduleSystemLinks);
	$this->_setTemplateVariable('moduleItemDetails', $moduleItemDetails);
	$this->_setTemplateVariable('layoutUrl',
	    GalleryUtilities::convertPathToRelativeUrl(dirname(__FILE__)));
	$this->_setTemplateVariable('parents', $parents);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$this->_setTemplateVariable('itemIndex', $itemIndex+1);
	$this->_setTemplateVariable('imageViews', $imageViews);
	$this->_setTemplateVariable('imageViewsIndex', $imageViewsIndex);
	$this->_setTemplateVariable('totalPeerCount', $totalPeerCount);
	
	/* Parse the header and body and send them back */
	$html = $this->_renderTemplate('classic', 'singleBody.tpl');
	return array(GalleryStatus::success(), $html);
    }
}
?>

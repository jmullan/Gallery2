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
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/** 
 * This implements the standard gallery layout 
 *
 * @package GalleryLayout
 * @subpackage Layout
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

	$template =& $this->getTemplate();
	$template->setVariable('properties', $properties);
	$template->setVariable('item', $item->getMemberData());
	
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
	    list ($ret, $moduleChildSummaries) =
		$this->_getModuleItemSummaries($childItems, $urlParams);
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
	    foreach ($childItems as $child) {
		$childId = $child->getId();
		$childTable[$childId] = $child->getMemberData();

		if (!empty($moduleChildSummaries[$childId])) {
		    /*
		     * $moduleChildSummaries[$childId] is:
		     *   $array[<modulename>] = <html>
		     */
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
		    /* Rebuild cache, to be prepared to the getMemberData() call */
		    list ($ret, $rebuild) = $thumbTable[$id]->rebuildCacheIfNotCurrent();
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
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
	list ($ret, $moduleItemLinks) =
	    $this->_getModuleItemLinks(array_merge(array($item), $childItems),
				       $urlParams);
	    

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

	/* Get system content */
	list ($ret, $moduleSystemContent) = $this->_getModuleSystemContent($urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tell Smarty about everything we've learned */
	$template =& $this->getTemplate();
	$template->setVariable('moduleItemLinks', $moduleItemLinks);
	$template->setVariable('moduleSystemLinks', $moduleSystemLinks);
	$template->setVariable('moduleSystemContent', $moduleSystemContent);
	$template->setVariable('moduleItemDetails', $moduleItemDetails);
	$template->setVariable('navigator', $navigator);
	$template->setVariable('children', $children);
	$template->setVariable('pageNumber', $pageNumber);
	$template->setVariable('totalPageCount', $totalPages);
	$template->setVariable('totalChildCount', $totalChildCount);
	$template->setVariable('layoutUrl',
			       GalleryUtilities::convertPathToRelativeUrl(dirname(__FILE__)));
	$template->setVariable('parents', $parents);
	
	/* Parse the body template and send it back */
	$html = $template->render('albumBody.tpl');
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
     * @todo Maybe display the sizes of an image in increasing order
     */
    function _renderSingle($item, $urlParams, $properties) {
	global $gallery;

	/*
	 * Figure out all possible views of this item that the user can see and
	 * get them into an acceptable format for the template engine.
	 */
	$imageViews = array();

	list ($ret, $permissions) =
	    GalleryItemHelper::getPermissions($item->getId(),
					      $gallery->getActiveUserId());

	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Can we see this item at all? */
	if (!isset($permissions['core.view'])) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
	}

	/* If the user can see resized versions, add those to the list */
	if (isset($permissions['core.viewResizes'])) {
	    /* Load the resizes */
	    list ($ret, $resizes) =
		GalleryDerivativeHelper::fetchResizesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($resizes)) {
		foreach ($resizes[$item->getId()] as $resize) {
		    list ($ret, $rebuild) = $resize->rebuildCacheIfNotCurrent();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $imageViews[] = array('inline' => true,
					  'height' => $resize->getHeight(),
					  'width' => $resize->getWidth(),
					  'size' => $resize->getDerivativeSize(),
					  'id' => $resize->getId());
		}
	    }
	}

	/* If the user can see the full version, add it to the list */
	if (isset($permissions['core.viewSource'])) {
	    /* Add the full version */
	    list ($ret, $preferred) =
		GalleryDerivativeHelper::fetchPreferredsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Show the preferred item, if it's there */
	    if (empty($preferred)) {
		if (GalleryUtilities::isA($item, 'GalleryDataItem')) {
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
		$thumbnail = $thumbnails[$item->getId()];
		$imageViews[] = array('inline' => true,
				      'height' => $thumbnail->getHeight(),
				      'width' => $thumbnail->getWidth(),
				      'size' => $thumbnail->getDerivativeSize(),
				      'id' => $thumbnail->getId());
	    }
	}

	$imageViewsIndex = GalleryUtilities::getRequestVariables('imageViewsIndex');
	if (empty($imageViewsIndex)) {
	    $imageViewsIndex = 0;
	}

	/* Don't let the index overflow the images array */
	$imageViewsIndex = min($imageViewsIndex, sizeof($imageViews) - 1);

	/*
	 * In order to figure out where we are, we have to load the entire list
	 * of children of my parent and then iterate through it to find our
	 * current index.
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

	/* Get system content */
	list ($ret, $moduleSystemContent) = $this->_getModuleSystemContent($urlParams);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Tell Smarty about everything we've learned */
	$template =& $this->getTemplate();
	$template->setVariable('navigator', $navigator);
	$template->setVariable('moduleItemLinks', $moduleItemLinks);
	$template->setVariable('moduleSystemLinks', $moduleSystemLinks);
	$template->setVariable('moduleSystemContent', $moduleSystemContent);
	$template->setVariable('moduleItemDetails', $moduleItemDetails);
	$template->setVariable('layoutUrl',
			       GalleryUtilities::convertPathToRelativeUrl(dirname(__FILE__)));
	$template->setVariable('parents', $parents);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('itemIndex', $itemIndex+1);
	$template->setVariable('imageViews', $imageViews);
	$template->setVariable('imageViewsIndex', $imageViewsIndex);
	$template->setVariable('totalPeerCount', $totalPeerCount);
	
	/* Parse the header and body and send them back */
	$html = $template->render('singleBody.tpl');
	return array(GalleryStatus::success(), $html);
    }
}
?>

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
     * Render the item
     *
     * @param object GalleryItem the item to render.  Can be any subclass of
     *               GalleryItem
     * @param array the layout properties
     * @return array object GalleryStatus a status code
     *         string the html body
     */
    function render($item) {

	/* Look up my properties */
	//list ($ret, $properties) =
	//GalleryLayoutPropertiesMap::getProperties('BasicLayout');
	$properties = array('rows' => 3,
			    'columns' => 3);

	if ($item->canContainChildren()) {
	    return $this->_renderAlbum($item, $properties);
	} else {
	    return $this->_renderSingle($item, $properties);
	}
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
    function _renderAlbum($item, $properties) {
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
	list ($ret, $totalChildCount) =
	    $item->countChildren($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the child id => child types */
	list ($ret, $childIds) =
	    $item->getChildren($gallery->getActiveUserId(), $start, $perPage);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($childIds)) {
	    /* Load the children */
	    list ($ret, $childEntities) = $gallery->loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

            /* Create a table of child id -> child data */
	    $childTable = array();
	    foreach ($childEntities as $child) {
		$childTable[$child->getId()] = $child->getMemberData();
	    }
	    
	    /* Load the thumbnails */
	    list ($ret, $imageTable) =
		$this->_loadDerivativeImages($childIds, IMAGE_TYPE_THUMBNAIL);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    /* put it all together */
	    $i = 0;
	    foreach ($childIds as $id) {
		$children[$i] = $childTable[$id];
		if (isset($imageTable[$id])) {
		    $children[$i]['thumbnail'] = $imageTable[$id][0];
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

	/*
	 * XXX: make the page navigator use a very small range for now as a
	 * test, since we have very small albums.
	 */
	$lowerPage = max($pageNumber - 2, 1);
	$upperPage = min($lowerPage + 4, $totalPages);
	for ($i = $lowerPage; $i <= $upperPage; $i++) {
	    $navigator['jumprange'][] = $i;
	}

	/* Load the parents */
	list ($ret, $parents) = $this->_loadParents($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tell Smarty about everything we've learned */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$smarty->assign('item', $item->getMemberData());
	$smarty->assign('navigator', $navigator);
	$smarty->assign('children', $children);
	$smarty->assign('properties', $properties);
	$smarty->assign('pageNumber', $pageNumber);
	$smarty->assign('totalPageCount', $totalPages);
	$smarty->assign('totalChildCount', $totalChildCount);
	$smarty->assign('layoutUrl', GalleryUtilities::convertPathToRelativeUrl(__FILE__));
	$smarty->assign('parents', $parents);

	/* Parse the body template and send it back */
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	return array(GalleryStatus::success(),
		     $smarty->fetch('albumBody.tpl'));
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
     */
    function _renderSingle($item, $properties) {
	global $gallery;

	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$smarty->assign('layout', $properties);
	$smarty->assign('item', $item->getMemberData());

	$showMode = GalleryUtilities::getRequestVariables('showMode');
	if ($showMode == 'full') {
	    /* XXX: perform permission check here ("can user see full size")*/
	    $smarty->assign('image', $item->getMemberData());
	    
	} else {

	    /* Which resize are we displaying? */
	    $resizeIndex = GalleryUtilities::getRequestVariables('resizeIndex');
	    if (empty($resizeIndex)) {
		$resizeIndex = 0;
	    }

	    /* Load the resizes */
	    list ($ret, $imageTable) =
		$this->_loadDerivativeImages($item->getId(),
					     IMAGE_TYPE_RESIZE);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($imageTable[$item->getId()])) {
		// No resizes -- what do we do? -- fail for now
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
						  __FILE__, __LINE__),
			     null);
	    }

	    $resizes = $imageTable[$item->getId()];

	    if ($resizeIndex >= sizeof($resizes)) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER,
						  __FILE__, __LINE__),
			     null);
	    }

	    /* XXX: perform permission check here ("can user see resizes ")*/
	    
	    $smarty->assign('image', $resizes[$resizeIndex]);
	}

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
	    $parent->getChildren($gallery->getActiveUserId());
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
	list ($ret, $parents) = $this->_loadParents($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Tell Smarty about everything we've learned */
	$smarty->assign('navigator', $navigator);
	$smarty->assign('layoutUrl', GalleryUtilities::convertPathToRelativeUrl(__FILE__));
	$smarty->assign('parents', $parents);
	$smarty->assign('itemIndex', $itemIndex+1);
	$smarty->assign('totalPeerCount', $totalPeerCount);
	
	/* Parse the header and body and send them back */
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	return array(GalleryStatus::success(),
		     $smarty->fetch('singleBody.tpl'));
    }

}
?>

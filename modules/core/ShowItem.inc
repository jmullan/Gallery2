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

class ShowItemView /* extends GalleryView */ {

    function render() {
	global $gallery;

	/* If we don't have an item id, default to the root */
	$itemId = GalleryUtilities::getRequestVariables('gItemId');
	if (empty($itemId)) {
	    $itemId = $gallery->getConfig('core.id.rootAlbum');
	}

	/* Load the item */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Update the view count */
	$ret = $item->incrementViewCount();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Find the right layout for this item  */
	$layout = $item->getLayout();
	if (empty($layout)) {
	    $layout = $gallery->getConfig('core.default.layout');
	}

	/* Load data for the layout */
	// XXX: get this from the DB
	$layoutInfo = array('rows' => 4, 'columns' => 4);

	/* Load the correct layout */
	require_once($gallery->getConfig('core.directory.layouts') .
		     $layout . '/layout.inc');
	$layoutClassName = $layout . 'Layout';
	if (!class_exists($layoutClassName)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER,
					__FILE__, __LINE__);
	}
	$layout = new $layoutClassName($layoutInfo);

	/* Load the requested range of children for this item */
	$children = array();
	if ($item->canContainChildren()) {

	    /* Learn what children the layout wants */
	    list ($start, $count) = $layout->getChildItemRange();

	    /* Get the child id => child types */
	    list ($ret, $childIds) =
		$item->getChildren($gallery->getActiveUserId(), $start, $count);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* We only want the ids */
	    $childIds = array_keys($childIds);

	    /* Load the children */
	    list ($ret, $childEntities) = $gallery->loadEntitiesById($childIds);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* Create a table of child id -> child data */
	    foreach ($childEntities as $child) {
		$childTable[$child->getId()] = $child->getMemberData();
	    }

	    /* Look up the ids of all their derivative images */
	    $markers = GalleryUtilities::makeMarkers(sizeof($childIds));
	    $data = array_merge(array('GalleryDerivativeImage'), $childIds);
	    list ($ret, $searchResults) = 
		$gallery->search(array('select' => ('[GalleryDerivativeImage::id], ' .
						    '[GalleryChildEntity::parentId]'),
				       'where' => ('[GalleryEntity::entityType]=? AND ' .
						   '[GalleryChildEntity::parentId] in (' .
						   $markers . ')')),
				 $data);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $imageTable = array();
	    if ($searchResults->resultCount() > 0) {
		$imageIds = array();
		while ($result = $searchResults->nextResult()) {
		    $imageIds[] = $result[0];
		}
		
		/* Load all the derivative images */
		list ($ret, $imageEntities) = $gallery->loadEntitiesById($imageIds);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		/* Create a table of child id -> image data */
		foreach ($imageEntities as $image) {
		    $imageTable[$image->getParentId()][] = $image->getMemberData();
		}
	    }

	    /* put it all together */
	    $i = 0;
	    foreach ($childIds as $id) {
		$children[$i] = $childTable[$id];
		if (isset($imageTable[$id])) {
		    $children[$i]['images'] = $imageTable[$id];
		}
		$i++;
	    }
	}

	/* Assemble the data to pass to the layout */
	$layoutInputs = array();
	$layoutInputs['item'] = $item->getMemberData();
	$layoutInputs['children'] = $children;

	/* Render and retrieve the results */
	if ($item->canContainChildren()) {
	    $master['layout'] = $layout->renderContainer($item, $children);
	} else {
	    $master['layout'] = $layout->renderSingle($item);
	}

	if ($gallery->getDebug() == 'buffered') {
	    $master['debug'] = $gallery->getDebugBuffer();
	}

	/* Display the global output */
	$smarty = $gallery->getSmarty();
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$smarty->assign('master', $master);
	
	$smarty->display('global.tpl');

	return GalleryStatus::success();
    }
}
?>

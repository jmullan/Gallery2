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
 * @package Search
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/* Pull in required classes */
require_once(dirname(__FILE__) . '/classes/SearchUtilities.class');

/**
 * @package Search
 * @subpackage UserInterface
 */
class SearchShowAllController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	if (isset($form['action']['scan'])) {
	    $results['delegate']['view'] = 'search:SearchScan';
	} else {
	    $results['delegate']['view'] = 'search:SearchShowAll';
	}

	$results['status'] = array();
	$results['error'] = array();
	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Search
 * @subpackage UserInterface
 */
class SearchShowAllView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	// XXX: Parameterize this
	$pageSize = 10;

	$items = array();
	$thumbnails = array();
	$results = array();
	$searchResultThumbnails = array();
	if ($form['formName'] == 'SearchShowAll' ||
	    $form['formName'] == 'SearchScan') {
	    
	    if (empty($form['searchCriteria'])) {
		$form['error']['searchCriteria']['missing'] = 1;
	    } else {

		$form['searchCriteria'] =
		    SearchUtilities::sanitizeSearchCriteria($form['searchCriteria']);
		    
		if (isset($form['action']['showAll'])) {
		    $form['moduleId'] = array_pop(array_keys($form['action']['showAll']));
		    $form['page'] = 1;
		}

		/* Reset the page number if we start a new search */
		if (isset($form['action']['search'])) {
		    $form['page'] = 1;
		}

		if (isset($form['action']['nextPage'])) {
		    $form['page']++;
		} else if (isset($form['action']['previousPage'])) {
		    $form['page']--;
		}

		if ($form['page'] < 1) {
		    $form['page'] = 1;
		}

		$moduleId = $form['moduleId'];
		list ($ret, $searchInstance) =
		    GalleryFactory::newInstanceById('GallerySearchInterface_1_0', $form['moduleId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($searchInstance)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}
		
		list ($ret, $moduleInfo) = $searchInstance->getSearchModuleInfo();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		if (isset($form['options'][$moduleId])) {
		    list ($ret, $results) =
			$searchInstance->search($form['options'][$moduleId],
						$form['searchCriteria'],
						($form['page']-1) * $pageSize,
						$pageSize);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$maxPages = ceil($results['count'] / $pageSize);
	    }

	    $itemIds = array();
	    $thumbnails = array();
	    if (!empty($results['results'])) {
		foreach ($results['results'] as $result) {
		    if (isset($result['itemId'])) {
			$itemIds[$result['itemId']] = 1;
		    }
		}
		$itemIds = array_keys($itemIds);

		if (!empty($itemIds)) {
		    /* Fetch items */
		    list ($ret, $itemList) = $gallery->loadEntitiesById($itemIds);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    foreach ($itemList as $item) {
			$items[$item->getId()] = $item->getMemberData();
		    }
		
		    /* Fetch thumbnails */
		    list ($ret, $thumbnailList) = GalleryDerivativeHelper::fetchThumbnailsByItemIds($itemIds);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    foreach ($thumbnailList as $thumbnail) {
			$thumbnails[$thumbnail->getParentId()] = $thumbnail->getMemberData();
		    }
		}
	    }
	} else {
	    $form['searchCriteria'] = '';
	}

	/* Render the HTML body */
	$SearchShowAll = array();
	$SearchShowAll['maxPages'] = $maxPages;
	$SearchShowAll['moduleInfo'] = $moduleInfo;
	$SearchShowAll['moduleId'] = $moduleId;
	$SearchShowAll['results'] = $results;
	$SearchShowAll['thumbnails'] = $thumbnails;
	$SearchShowAll['items'] = $items;
	$SearchShowAll['controller'] = 'search:SearchShowAll';

	$template->setVariable('SearchShowAll', $SearchShowAll);
	
	return array(GalleryStatus::success(),
		     array('head' => 'modules/search/templates/SearchHead.tpl',
			   'body' => 'modules/search/templates/SearchShowAll.tpl'));
    }
}
?>

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
	    $results['view'] = 'search:SearchScan';
	} else {
	    $results['view'] = 'search:SearchShowAll';
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Search
 * @subpackage UserInterface
 */
class SearchShowAllView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$html = $template->render('SearchHead.tpl');
	
	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;

	// XXX: Parameterize this
	$pageSize = 10;

	$return = GalleryUtilities::getFormVariables('return.');
	
	$searchResults = array();
	$searchResultThumbnails = array();
	if ($form['formName'] == 'SearchShowAll' || $form['formName'] == 'SearchScan') {
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
		    list ($ret, $searchResults) =
			$searchInstance->search($form['options'][$moduleId],
						$form['searchCriteria'],
						($form['page']-1) * $pageSize,
						$pageSize);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		$maxPages = ceil($searchResults['count'] / $pageSize);
	    }

	    $itemIds = array();
	    $thumbnails = array();
	    if (!empty($searchResults['results'])) {
		foreach ($searchResults['results'] as $result) {
		    if (isset($result['itemId'])) {
			$itemIds[$result['itemId']] = 1;
		    }
		}
		$itemIds = array_keys($itemIds);

		if (!empty($itemIds)) {
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
	$template = $this->_getTemplate();
	$template->setVariable('controller', 'search:SearchShowAll');
	$template->setVariable('form', $form);
	$template->setVariable('maxPages', $maxPages);
	$template->setVariable('moduleInfo', $moduleInfo);
	$template->setVariable('moduleId', $moduleId);
	$template->setVariable('return', $return);
	$template->setVariable('searchResults', $searchResults);
	$template->setVariable('thumbnails', $thumbnails);
	$html = $template->render('SearchShowAll.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

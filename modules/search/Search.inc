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

class SearchView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	/* Render the HTML body */
	$template = $this->getTemplate();
	$html = $template->render('SearchHead.tpl');
	
	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	// XXX: Parameterize this
	$searchLimit = 3;

	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');
	$formName = GalleryUtilities::getRequestVariables('formName');
	
	/* Find all the modules that support the Search interface */
	$ids = GalleryFactory::getAllImplementationIds('GallerySearchInterface_1_0');
	foreach ($ids as $id => $className) {
	    list ($ret, $searchInstances[$id]) =
		GalleryFactory::newInstance('GallerySearchInterface_1_0', $className);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load the search info for each module */
	foreach ($searchInstances as $id => $instance) {
	    list ($ret, $modules[$id]) = $instance->getSearchModuleInfo();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$searchResults = array();
	$searchResultItems = array();
	$searchResultThumbnails = array();
	if ($formName == 'Search') {
	    if (empty($form['searchCriteria'])) {
		$form['error']['searchCriteria']['missing'] = 1;
	    } else {
		if (isset($form['useDefaultSettings'])) {
		    foreach ($searchInstances as $id => $instance) {
			$form['options'][$id] = $modules[$id]['options'];
		    }
		}

		/* Execute a limited search */
		foreach ($searchInstances as $id => $instance) {
		    if (isset($form['options'][$id])) {
			list ($ret, $searchResults[$id]) =
			    $instance->search($form['options'][$id],
					      $form['searchCriteria'],
					      $searchLimit);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}
	    }

	    $itemIds = array();
	    foreach ($searchResults as $id => $results) {
		$itemIds = array_merge($itemIds, $results);
	    }

	    if (!empty($itemIds)) {
		list ($ret, $items) = $gallery->loadEntitiesById($itemIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Convert them to member data */
		foreach ($items as $item) {
		    $searchResultItems[$item->getId()] = $item->getMemberData();
		}

		/* Fetch thumbnails */
		list ($ret, $thumbnails) =
		    GalleryDerivativeHelper::fetchThumbnailsByItemIds($itemIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		foreach ($thumbnails as $thumbnail) {
		    $searchResultThumbnails[$thumbnail->getParentId()] = $thumbnail->getMemberData();
		}
	    }
	} else {
	    $form['searchCriteria'] = '';
	}

	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('view', 'search:Search');
	$template->setVariable('modules', $modules);
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$template->setVariable('searchResults', $searchResults);
	$template->setVariable('searchResultItems', $searchResultItems);
	$template->setVariable('searchResultThumbnails', $searchResultThumbnails);
	$html = $template->render('Search.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

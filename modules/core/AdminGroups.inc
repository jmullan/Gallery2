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

class AdminGroupsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$form = GalleryUtilities::getFormVariables('form.');

	$group = null;
	if (!empty($form['text']['groupName'])) {
	    list ($ret, $group) =
		GalleryGroupHelper::fetchGroupByGroupName($form['text']['groupName']);
	    if ($ret->isError()) {
		if (!($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}
	
	if (isset($form['action']['firstPage'])) {

	    /* Go to the first page */
	    $form['list']['page'] = 1;
	    
	} else if (isset($form['action']['backPage'])) {

	    /* Go back a page */
	    $form['list']['page'] = max(0, $form['list']['page']-1);
	    
	} else if (isset($form['action']['nextPage'])) {
	    
	    /* Go forward a page */
	    $form['list']['page'] = min($form['list']['page']+1,
					    $form['list']['maxPages']);
	    
	} else if (isset($form['action']['lastPage'])) {

	    /* Go to the last page */
	    $form['list']['page'] = $form['list']['maxPages'];
	    
	} else if (isset($form['action']['filterClear'])) {

	    /* Clear the filter */
	    GalleryUtilities::putRequestVariable('form.list.filter', null);
	    
	} else if (isset($form['action']['create'])) {

	    /* Show the "create group" view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateGroup');
	    
	} else if (isset($form['action']['editFromList'])) {

	    if (empty($form['list']['groupId'])) {
		GalleryUtilities::putRequestVariable('form.error.list.noGroupSelected', 1);
	    } else {
		/* Show the "edit group" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroup');
		GalleryUtilities::putRequestVariable('groupId', $form['list']['groupId']);
	    }
	    
	} else if (isset($form['action']['addRemoveUsersFromList'])) {

	    if (empty($form['list']['groupId'])) {
		GalleryUtilities::putRequestVariable('form.error.list.noGroupSelected', 1);
	    } else {
		/* Show the "edit group" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroupUsers');
		GalleryUtilities::putRequestVariable('groupId', $form['list']['groupId']);
	    }
	    
	} else if (isset($form['action']['deleteFromList'])) {

	    if (empty($form['list']['groupId'])) {
		GalleryUtilities::putRequestVariable('form.error.list.noGroupSelected', 1);
	    } else {
		/* Show the "delete group" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('groupId', $form['list']['groupId']);
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteGroup');
	    }
	    
	} else if (isset($form['action']['editFromText'])) {

	    if (empty($form['text']['groupName'])) {
		GalleryUtilities::putRequestVariable('form.error.text.noGroupSpecified', 1);
	    } else if ($group == null) {
		GalleryUtilities::putRequestVariable('form.error.text.noSuchGroup', 1);
	    } else {
		/* Show the "delete group" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('groupId', $group->getId());
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroup');
	    }
	    
	} else if (isset($form['action']['deleteFromText'])) {

	    if (empty($form['text']['groupName'])) {
		GalleryUtilities::putRequestVariable('form.error.text.noGroupSpecified', 1);
	    } else if ($group == null) {
		GalleryUtilities::putRequestVariable('form.error.text.noSuchGroup', 1);
	    } else {
		/* Show the "delete group" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteGroup');
		GalleryUtilities::putRequestVariable('groupId', $group->getId());
	    }
		
	} else if (isset($form['action']['addRemoveUsersFromText'])) {

	    if (empty($form['text']['groupName'])) {
		GalleryUtilities::putRequestVariable('form.error.text.noGroupSpecified', 1);
	    } else if ($group == null) {
		GalleryUtilities::putRequestVariable('form.error.text.noSuchGroup', 1);
	    } else {
		/* Show the "edit group's users" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroupUsers');
		GalleryUtilities::putRequestVariable('groupId', $group->getId());
	    }
		
	}

	if (empty($results['view'])) {
	    /*
	     * We're staying on the same page, so pass on our navigation
	     * parameters.
	     */
	    
	    GalleryUtilities::putRequestVariable('form.list.page',
						 $form['list']['page']);

	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminGroups');
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminGroupsView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Load some standard form parameters */
	$form = GalleryUtilities::getFormVariables('form.');

	/* Set some defaults, if necessary */
	if (!isset($form['list']['filter'])) {
	    $form['list']['filter'] = '';
	}
	
	if (empty($form['list']['page'])) {
	    $form['list']['page'] = 1;
	}

	if (empty($form['text']['groupName'])) {
	    $form['text']['groupName'] = '';
	}

	list ($ret, $totalGroupCount) = GalleryGroupHelper::fetchGroupCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$form['list']['count'] = $totalGroupCount;
	$form['list']['pageSize'] = 15;

	/* If we have a filter, find out how many groups match it */
	if (!empty($form['list']['filter'])) {
	    list ($ret, $form['list']['count']) = GalleryGroupHelper::fetchGroupCount($form['list']['filter']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out our max pages, make sure our current page fits in it */
	$form['list']['maxPages'] = ceil($form['list']['count'] / $form['list']['pageSize']);
	if ($form['list']['page'] > $form['list']['maxPages']) {
	    $form['list']['page'] = $form['list']['maxPages'];
	}
	
	list ($ret, $form['list']['groupNames']) =
	    GalleryGroupHelper::fetchGroupNames($form['list']['pageSize'],
						(($form['list']['page'] - 1) *
						 $form['list']['pageSize']),
						$form['list']['filter']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('totalGroupCount', $totalGroupCount);
	$this->_setTemplateVariable('controller', 'core:AdminGroups');
	$html = $this->_renderTemplate('core', 'AdminGroups.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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

class AdminUsersController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$form = GalleryUtilities::getFormVariables('form');
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
	    $form['list']['filter'] = null;
	    
	} else if (isset($form['action']['create'])) {

	    /* Show the "create user" view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateUser');
	    
	} else if (isset($form['action']['editFromText'])) {

	    /* Show the "edit user" view */
	    if (!empty($form['text']['username'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
		GalleryUtilities::putRequestVariable('username', $form['text']['username']);
	    }
	    
	} else if (isset($form['action']['editFromList'])) {

	    if (!empty($form['list']['username'])) {
		/* Show the "edit user" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
		GalleryUtilities::putRequestVariable('username', $form['list']['username']);
	    }
	    
	} else if (isset($form['action']['deleteFromText'])) {

	    /* Show the "delete user" view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('username', $form['text']['username']);
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteUser');
	    
	}

	if (empty($results['view'])) {
	    /*
	     * We're staying on the same page, so pass on our navigation
	     * parameters.
	     */
	    
	    GalleryUtilities::putRequestVariable('form.list.page',
						 $form['list']['page']);

	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminUsersView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	return array(GalleryStatus::success(), false);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Specify our translation module */
	$ret = $this->_setTranslationModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load some standard form parameters */
	list ($form['list']['filter'],
	      $form['list']['page'],
	      $form['text']['username']) =
	    GalleryUtilities::getRequestVariables('form.list.filter',
						  'form.list.page',
						  'form.text.username');

	list ($ret, $totalUserCount) = GalleryUserHelper::fetchUserCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$list = array();
	$form['list']['count'] = $totalUserCount;
	$form['list']['pageSize'] = 15;
	if (empty($form['list']['page'])) {
	    $form['list']['page'] = 1;
	}

	if (!empty($form['list']['filter'])) {
	    list ($ret, $form['list']['count']) = GalleryUserHelper::fetchUserCount($form['list']['filter']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$form['list']['maxPages'] = ceil($form['list']['count'] / $form['list']['pageSize']);
	if ($form['list']['page'] > $form['list']['maxPages']) {
	    $form['list']['page'] = $form['list']['maxPages'];
	}
	
	list ($ret, $form['list']['usernames']) =
	    GalleryUserHelper::fetchUserNames($form['list']['pageSize'],
					      ($form['list']['page'] - 1) * $form['list']['pageSize'],
					      $form['list']['filter']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('form', $form);
	$smarty->assign('totalUserCount', $totalUserCount);
	$smarty->assign('controller', 'core:AdminUsers');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminUsers.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

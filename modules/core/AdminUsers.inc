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

	/* Generally, we'll want to redirect back to this page */
	$urlParams['view'] = 'core:SiteAdmin';
	$urlParams['subView'] = 'core:AdminUsers';

	list ($form['text']['username'],
	      $form['userList']['page'],
	      $form['userList']['maxPages'],
	      $form['userList']['username'],
	      $form['userList']['filter']) =
	    GalleryUtilities::getRequestVariables('form.text.username',
						  'form.userList.page',
						  'form.userList.maxPages',
						  'form.userList.username',
						  'form.userList.filter');
	foreach (array('firstPage', 'backPage', 'nextPage', 'lastPage',
		       'filterClear', 'filterBySubstring',
		       'create',
		       'editFromText', 'deleteFromText')
		 as $actionName) {
	    $action = GalleryUtilities::getRequestVariables('form.action.' . $actionName);
	    if (!empty($action)) {
		switch ($actionName) {
		case 'firstPage':
		    $form['userList']['page'] = 1;
		    break;

		case 'backPage':
		    $form['userList']['page'] = max(0, $form['userList']['page']-1);
		    break;

		case 'nextPage':
		    $form['userList']['page'] = min($form['userList']['page']+1,
						    $form['userList']['maxPages']);
		    break;

		case 'lastPage':
		    $form['userList']['page'] = $form['userList']['maxPages'];
		    break;

		case 'filterClear':
		    $form['userList']['filter'] = null;
		    break;

		case 'create':
		    $urlParams['subView'] = 'core:AdminCreateUser';
		    break;
		}
	    }
	}

	/* Pass on our navigation parameters */
	if ($form['userList']['page'] != 1) {
	    $urlParams['form.userList.page'] = $form['userList']['page'];
	}

	if (!empty($form['text']['username'])) {
	    $urlParams['form.text.username'] = $form['text']['username'];
	}
	
	if (!empty($form['userList']['filter'])) {
	    $urlParams['form.userList.filter'] = $form['userList']['filter'];
	}
	    
	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($urlParams);

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
	list ($form['userList']['filter'],
	      $form['userList']['page'],
	      $form['text']['username']) =
	    GalleryUtilities::getRequestVariables('form.userList.filter',
						  'form.userList.page',
						  'form.text.username');

	list ($ret, $totalUserCount) = GalleryUserHelper::fetchUserCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$userList = array();
	$form['userList']['count'] = $totalUserCount;
	$form['userList']['pageSize'] = 15;
	if (empty($form['userList']['page'])) {
	    $form['userList']['page'] = 1;
	}

	if (!empty($form['userList']['filter'])) {
	    list ($ret, $form['userList']['count']) = GalleryUserHelper::fetchUserCount($form['userList']['filter']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$form['userList']['maxPages'] = ceil($form['userList']['count'] / $form['userList']['pageSize']);
	if ($form['userList']['page'] > $form['userList']['maxPages']) {
	    $form['userList']['page'] = $form['userList']['maxPages'];
	}
	
	list ($ret, $form['userList']['usernames']) =
	    GalleryUserHelper::fetchUserNames($form['userList']['pageSize'],
					      ($form['userList']['page'] - 1) * $form['userList']['pageSize'],
					      $form['userList']['filter']);
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

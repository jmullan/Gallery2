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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will send the user to the chosen subView in the AdminUsers
*  View
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminUsersController extends GalleryController {

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

	if (!empty($form['text']['username'])) {
	    list ($ret, $user) =
		GalleryUserHelper::fetchUserByUsername($form['text']['username']);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		    $user = null;
		} else {
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

	    /* Show the "create user" view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateUser');
	    
	} else if (isset($form['action']['editFromText'])) {

	    if ($user == null) {
		GalleryUtilities::putRequestVariable('form.error.text.noSuchUser', 1);
	    } else {
		/* Show the "delete user" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('userId', $user->getId());
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
	    }
	    
	} else if (isset($form['action']['editFromList'])) {

	    /* Show the "edit user" view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminEditUser');
	    GalleryUtilities::putRequestVariable('userId', $form['list']['userId']);
	    
	} else if (isset($form['action']['deleteFromText'])) {

	    if ($user == null) {
		GalleryUtilities::putRequestVariable('form.error.text.noSuchUser', 1);
	    } else {
		/* Show the "delete user" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteUser');
		GalleryUtilities::putRequestVariable('userId', $user->getId());
	    }
		
	} else if (isset($form['action']['deleteFromList'])) {

	    list ($ret, $anonymousUserId) =
		$gallery->getModuleParameter('core', 'id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($form['list']['userId'] == $gallery->getActiveUserId()) {
		GalleryUtilities::putRequestVariable('form.error.list.cantDeleteActiveUser', 1);
	    } else if ($form['list']['userId'] == $anonymousUserId) {
		GalleryUtilities::putRequestVariable('form.error.list.cantDeleteActiveUser', 1);
	    } else {
		/* Show the "delete user" view */
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteUser');
		GalleryUtilities::putRequestVariable('userId', $form['list']['userId']);
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
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show available options to administer the users of Gallery
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminUsersView extends GalleryView {

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

	if (empty($form['text']['username'])) {
	    $form['text']['username'] = '';
	}

	list ($ret, $totalUserCount) = GalleryUserHelper::fetchUserCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$form['list']['count'] = $totalUserCount;
	$form['list']['pageSize'] = 15;

	/* If we have a filter, find out how many users match it */
	if (!empty($form['list']['filter'])) {
	    list ($ret, $form['list']['count']) = GalleryUserHelper::fetchUserCount($form['list']['filter']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out our max pages, make sure our current page fits in it */
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
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('totalUserCount', $totalUserCount);
	$template->setVariable('controller', 'core:AdminUsers');
	$html = $template->render('AdminUsers.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

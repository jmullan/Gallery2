<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * This controller will handle changes made to the user-group mapping
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminEditGroupUsersController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$error = array();
	$status = array();

	/* Load the group */
	$groupId = GalleryUtilities::getRequestVariables('groupId');
	list ($ret, $group) = GalleryCoreApi::loadEntitiesById($groupId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['done'])) {

	    /* Go back to the AdminGroups view */
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminGroups';
	    
	} else if ($group->getGroupType() != GROUP_ALL_USERS) {
	    if (isset($form['action']['remove'])) {

		/* Remove the user from the group */
		if (!empty($form['list']['userId'])) {

		    /* Can't remove yourself from the site admins list */
		    if ($group->getGroupType() == GROUP_SITE_ADMINS &&
			$form['list']['userId'] == $gallery->getActiveUserId()) {
			$error[] = 'form[error][list][cantRemoveSelf]';
		    } else {
			list ($ret, $user) = GalleryCoreApi::loadEntitiesById($form['list']['userId']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$ret = GalleryCoreApi::removeUserFromGroup($user->getId(), $groupId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			/* Redirect back to the same view */
			$redirect['view'] = 'core:SiteAdmin';
			$redirect['subView'] = 'core:AdminEditGroupUsers';
			$redirect['groupId'] = $group->getId();
			$status['removedUser'] = $user->getUsername();
		    }
		}
	    
	    } else if (isset($form['action']['add'])) {

		/* Add the user to the group */
		if (empty($form['text']['userName'])) {
		    $error[] = 'form[error][text][userName][missing]';
		} else {
		    list ($ret, $user) =
			GalleryCoreApi::fetchUserByUsername($form['text']['userName']);

		    if ($ret->isError() && ($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
			$error[] = 'form[error][text][userName][invalid]';
		    } else if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    } else {
			$ret = GalleryCoreApi::addUserToGroup($user->getId(), $groupId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			/* Redirect back to the same view */
			$redirect['view'] = 'core:SiteAdmin';
			$redirect['subView'] = 'core:AdminEditGroupUsers';
			$redirect['groupId'] = $group->getId();
			$status['addedUser'] = $user->getUsername();
		    }
		}
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'core:AdminEditGroupUsers';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show the possibilities of user-group mappings for a specified group.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminEditGroupUsersView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Load the group */
	$groupId = GalleryUtilities::getRequestVariables('groupId');
	list ($ret, $group) = GalleryCoreApi::loadEntitiesById($groupId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* First time on this page, initialize form fields */
	if ($form['formName'] != 'AdminEditGroupUsers') {
	    $form['text']['userName'] = '';
	    $form['formName'] = 'AdminEditGroupUsers';
	}

	/* Initialize the user list */
	list ($ret, $users) = GalleryCoreApi::fetchUsersForGroup($group->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$form['userCount'] = sizeof($users);
	$form['list']['users'] = $users;

	$AdminEditGroupUsers = array();
	$AdminEditGroupUsers['group'] = $group->getMemberData();

	/* Render the HTML body */
	$template->setVariable('AdminEditGroupUsers', $AdminEditGroupUsers);
	$template->setVariable('controller', 'core:AdminEditGroupUsers');

	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/AdminEditGroupUsers.tpl'));
    }
}
?>

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
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();
	$formName = GalleryUtilities::getRequestVariables('formName');
	$form = GalleryUtilities::getFormVariables('form.');

	list ($ret, $group) = $gallery->loadEntitiesById($form['groupId']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['done'])) {

	    /* Go back to the AdminGroups view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminGroups');
	    
	} else if ($group->getGroupType() != GROUP_ALL_USERS) {
	    if (isset($form['action']['remove'])) {

		/* Remove the user from the group */
		if (!empty($form['list']['userId'])) {
		    list ($ret, $user) = $gallery->loadEntitiesById($form['list']['userId']);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if ($ret->isError()) {
			if (!($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			$ret = GalleryUserGroupMap::removeUserFromGroup($user->getId(),
									$form['groupId']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			/* Request a redirect back to this page */
			$redirectParams['view'] = 'core:SiteAdmin';
			$redirectParams['subView'] = 'core:AdminEditGroupUsers';
			$redirectParams['groupId'] = $group->getId();
			$redirectParams['userRemoved'] = $user->getUsername();
		    }
		}
	    
	    } else if (isset($form['action']['add'])) {

		/* Remove the user from the group */
		if (!empty($form['text']['userName'])) {
		    list ($ret, $user) =
			GalleryUserHelper::fetchUserByUsername($form['text']['userName']);

		    if ($ret->isError()) {
			if (!($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			$ret = GalleryUserGroupMap::addUserToGroup($user->getId(),
								   $form['groupId']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			/* Request a redirect back to this page */
			$redirectParams['view'] = 'core:SiteAdmin';
			$redirectParams['subView'] = 'core:AdminEditGroupUsers';
			$redirectParams['groupId'] = $group->getId();
			$redirectParams['userAdded'] = $user->getUsername();
		    }
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroupUsers');
	    }
	}

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
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$userAdded = GalleryUtilities::getRequestVariables('userAdded');
	$userRemoved = GalleryUtilities::getRequestVariables('userRemoved');
	$groupId = GalleryUtilities::getRequestVariables('groupId');
	$formName = GalleryUtilities::getRequestVariables('formName');
	$form = GalleryUtilities::getFormVariables('form.');

	if (!empty($groupId)) {
	    $form['groupId'] = $groupId;
	}

	/* Load the group */
	list ($ret, $group) = $gallery->loadEntitiesById($form['groupId']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the form with group data */
	if (empty($form['groupName'])) {
	    $form['groupName'] = $group->getGroupName();
	}

	$form['groupType'] = $group->getGroupType();

	/*
	 * If the last form submitted wasn't our form, then we don't expect the
	 * form data to line up (ie, this is the first time we've been on this
	 * view
	 */
	if ($formName != 'AdminEditGroupUsers') {
	    $form['text']['userName'] = '';
	} else {

	    /*
	     * But if it does match, then we should audit the form data.
	     */
	    if (empty($form['text']['userName'])) {
		$form['error']['text']['missingUserName'] = 1;
	    } else {
		list ($ret, $user) = GalleryUserHelper::fetchUserByUsername($form['text']['userName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			$form['error']['text']['noSuchUser'] = 1;
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	}

	list ($ret, $users) = GalleryUserGroupMap::fetchUsersForGroup($group->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$userCount = sizeof($users);
	$form['list']['users'] = $users;

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('userCount', $userCount);
	$template->setVariable('userAdded', $userAdded);
	$template->setVariable('userRemoved', $userRemoved);
	$template->setVariable('controller', 'core:AdminEditGroupUsers');
	$html = $template->render('AdminEditGroupUsers.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

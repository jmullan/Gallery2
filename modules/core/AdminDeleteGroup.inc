<?php
/*
 * $RCSfile
 *
 * Gallery - a web based photo album viewer and deleteor
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
 * This controller will handle the deletion of a group
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminDeleteGroupController extends GalleryController {

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
	$groupId = GalleryUtilities::getRequestVariables('groupId');
	$form = GalleryUtilities::getFormVariables('form.');
	
	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminGroups view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminGroups');
	    
	} else if (isset($form['action']['delete'])) {

	    /*
	     * Check to see if we're trying to delete the anonymous group, or
	     * ourself (can't do either of those).
	     */
	    list ($ret, $group) = $gallery->loadEntitiesById($groupId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($group->getGroupType() == GROUP_NORMAL) {

		/* Delete the group */
		list ($ret, $lockId) = $gallery->acquireWriteLock($groupId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $group->delete();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $gallery->releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Request a redirect to the confirmation screen */
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'core:AdminDeleteGroupConfirmation';
		$redirectParams['groupName'] = $group->getGroupName();
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteGroup');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for confirmation ot delete a group
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminDeleteGroupView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$groupId = GalleryUtilities::getRequestVariables('groupId');

	/*
	 * Check to see if we're trying to delete the anonymous group, or
	 * ourself (can't do either of those).
	 */
	list ($ret, $group) = $gallery->loadEntitiesById($groupId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$isAllUsers = ($group->getGroupType() == GROUP_ALL_USERS);
	$isAllAdmins = ($group->getGroupType() == GROUP_SITE_ADMINS);
	
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('groupId', $groupId);
	$template->setVariable('groupName', $group->getGroupName());
	$template->setVariable('isAllUsers', $isAllUsers);
	$template->setVariable('isAllAdmins', $isAllAdmins);
	$template->setVariable('controller', 'core:AdminDeleteGroup');
	$html = $template->render('AdminDeleteGroup.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

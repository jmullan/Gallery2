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
 * This controller will handle changes made to a group
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminEditGroupController extends GalleryController {

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

	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminGroups view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminGroups');
	    
	} else if (isset($form['action']['undo'])) {

	    /* Reset our form */
	    GalleryUtilities::putRequestVariable('form.groupName', $group->getGroupName());
	    
	} else if (isset($form['action']['save'])) {

	    if (!empty($form['groupName'])) {
		/* Save our changes */
		list ($ret, $lockId) = $gallery->acquireWriteLock($form['groupId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Refresh our object, now that it's locked */
		list ($ret, $group) = $group->refresh();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$group->setGroupName($form['groupName']);

		$ret = $group->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		$ret = $gallery->releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Request a redirect to the confirmation screen */
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'core:AdminEditGroupConfirmation';
		$redirectParams['groupName'] = $form['groupName'];
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminEditGroup');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show options available to groups
 *
 * Only the 'groupname' is editable. Display a notice if editing special
 * (non-GROUP_NORMAL) groups.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminEditGroupView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$groupid = GalleryUtilities::getRequestVariables('groupId');
	$form = GalleryUtilities::getFormVariables('form.');

	if (!empty($groupid)) {
	    $form['groupId'] = $groupid;
	}

	list ($ret, $group) = $gallery->loadEntitiesById($form['groupId']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the form with group data */
	if (empty($form['groupName'])) {
	    $form['groupName'] = $group->getGroupName();
	}

	if (empty($form['groupType'])) {
	    $form['groupType'] = $group->getGroupType();
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('controller', 'core:AdminEditGroup');
	$html = $template->render('AdminEditGroup.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

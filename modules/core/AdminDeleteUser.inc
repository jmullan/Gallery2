<?php
/*
 * $RCSfile$
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
 * This controller will handle the deletion of an user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminDeleteUserController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();
	$userId = GalleryUtilities::getRequestVariables('userId');
	
	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminUsers view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['delete'])) {

	    /*
	     * Check to see if we're trying to delete the anonymous user, or
	     * ourself (can't do either of those).
	     */
	    list ($ret, $anonymousUserId) =
		$gallery->getModuleParameter('core', 'id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /*
	     * In theory we should never get to this point unless we're
	     * operating on a valid user, so don't bother sending errors back
	     * in case we can't delete.
	     */
	    if ($userId != $anonymousUserId && $userId != $gallery->getActiveUserId()) {
		list ($ret, $user) = $gallery->loadEntitiesById($userId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/* Delete the user */
		$ret = $gallery->deleteEntityById($user->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Request a redirect to the confirmation screen */
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'core:AdminUsers';
		$redirectParams['form.status.deletedUser'] = $user->getUsername();
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteUser');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for confirmation ot delete an user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminDeleteUserView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$userId = GalleryUtilities::getRequestVariables('userId');
	list ($ret, $user) = $gallery->loadEntitiesById($userId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'AdminDeleteUser') {
	    /* First time around initialize our form */
	    $form['userName'] = $user->getUserName();
	}


	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('controller', 'core:AdminDeleteUser');
	$html = $template->render('AdminDeleteUser.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

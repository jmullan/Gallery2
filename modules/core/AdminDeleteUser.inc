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

class AdminDeleteUserController extends GalleryController {

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
	$userid = GalleryUtilities::getRequestVariables('userid');
	$form = GalleryUtilities::getFormVariables('form.');
	
	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminUsers view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminUsers');
	    
	} else if (isset($form['action']['delete'])) {

	    /*
	     * Check to see if we're trying to delete the anonymous user, or
	     * ourself (can't do either of those).
	     */
	    list ($ret, $user) = $gallery->loadEntitiesById($userid);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $anonymousUserId) =
		$gallery->getModuleParameter('core', 'id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $isAnonymous = ($userid == $anonymousUserId);
	    $isSelf = ($userid == $gallery->getActiveUserId());

	    if (!$isAnonymous && !$isSelf) {
		/* Delete the user */
		list ($ret, $lockId) = $gallery->acquireWriteLock($userid);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $user->delete();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = $gallery->releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Request a redirect to the confirmation screen */
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'core:AdminDeleteUserConfirmation';
		$redirectParams['username'] = $user->getUsername();
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminDeleteUser');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminDeleteUserView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$userid = GalleryUtilities::getRequestVariables('userid');

	/*
	 * Check to see if we're trying to delete the anonymous user, or
	 * ourself (can't do either of those).
	 */
	list ($ret, $user) = $gallery->loadEntitiesById($userid);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $anonymousUserId) =
	    $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$isAnonymous = ($userid == $anonymousUserId);
	$isSelf = ($userid == $gallery->getActiveUserId());

	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('userid', $userid);
	$template->setVariable('username', $user->getUserName());
	$template->setVariable('isSelf', $isSelf);
	$template->setVariable('isAnonymous', $isAnonymous);
	$template->setVariable('controller', 'core:AdminDeleteUser');
	$html = $template->render('AdminDeleteUser.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * This view will present the available options to administrate a user
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class UserAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$user = $gallery->getActiveUser();

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	foreach ($moduleStatus as $moduleId => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    if (in_array('getUserAdminViews', explode('|', $status['callbacks']))) {
		list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH) {
			continue;
		    }
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		list ($ret, $moduleViews) = $module->getUserAdminViews($user);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		$subViewChoices = array_merge($subViewChoices, $moduleViews);
	    }
	}

	list ($ret, $anonymousUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$show['userInPathbar'] = ($user->getId() != $anonymousUserId);

	/* If we have a specific sub view, load it now */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (empty($subViewName) && !empty($subViewChoices)) {
	    $subViewName = $subViewChoices[0]['view'];
	}

	list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Our sub view may have set some hints, like the encoding type */
	if ($template->hasVariable('UserAdmin')) {
	    $UserAdmin =& $template->getVariableByReference('UserAdmin');
	} else {
	    $UserAdmin = array();
	    $template->setVariableByReference('UserAdmin', $UserAdmin);
	}

	/* Get the links for navigating back to where we came from */
	$urlGenerator =& $gallery->getUrlGenerator();
	list ($ret, $navigationLinks) = $urlGenerator->getNavigationLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}


	/* Set up my view parameters */
	$UserAdmin['moduleSystemLinks'] = $moduleSystemLinks;
	$UserAdmin['navigationLinks'] = $navigationLinks;
	$UserAdmin['user'] = $user->getMemberData();
	$UserAdmin['show'] = $show;
	$UserAdmin['subViewChoices'] = $subViewChoices;
	$UserAdmin['subViewName'] = $subViewName;
	$UserAdmin['isSiteAdmin'] = $isSiteAdmin;

	if (!empty($subViewName)) {
	    list ($ret, $subView) = GalleryView::loadView($subViewName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $results) = $subView->loadTemplate($template, $form);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $UserAdmin['viewBodyFile'] = $results['body'];
	    $UserAdmin['viewL10Domain'] = $subView->getL10Domain();
	}

	$template->setVariable('UserAdmin', $UserAdmin);
	return array(GalleryStatus::success(),
		     array('head' => 'modules/core/templates/UserAdminHead.tpl',
			   'body' => 'modules/core/templates/UserAdmin.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	global $gallery;
	
	/* Get the description from the current subView */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (empty($subViewName)) {
	    $subViewName = 'core:ItemEdit';
	}
	list ($ret, $subView) = GalleryView::loadView($subViewName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	return $subView->getViewDescription();
    }
}
?>
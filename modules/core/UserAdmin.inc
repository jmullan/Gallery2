<?php
/*
 * $RCSfile$
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

	$userId = $gallery->getActiveUserId();
	list ($ret, $user) = $gallery->getActiveUser();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	    
	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryPluginMap::getPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	foreach ($moduleStatus as $moduleId => $moduleStatus) {
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $moduleViews) = $module->getUserAdminViews($user);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $subViewChoices = array_merge($subViewChoices, $moduleViews);
	}

	list ($ret, $anonymousUserId) = $gallery->getModuleParameter('core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$show['userInPathbar'] = ($userId != $anonymousUserId);

	/* If we have a specific sub view, load it now */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (empty($subViewName) && !empty($subViewChoices)) {
	    $subViewName = $subViewChoices[0]['view'];
	}

	/* Set up my view parameters */
	$UserAdmin = array('user' => $user->getMemberData(),
			   'show' => $show,
			   'subViewChoices' => $subViewChoices,
			   'subViewName' => $subViewName);

	if (!empty($subViewName)) {
	    list ($ret, $subView) = GalleryView::loadView($subViewName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    
	    list ($ret, $UserAdmin['viewHeadFile'], $UserAdmin['viewBodyFile']) = 
		$subView->loadTemplate($template, $form);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    $UserAdmin['viewL10Domain'] = $subView->getL10Domain();
	}

	$template->setVariable('UserAdmin', $UserAdmin);
	return array(GalleryStatus::success(),
		     'modules/core/templates/UserAdminHead.tpl',
		     'modules/core/templates/UserAdmin.tpl');
    }
}
?>

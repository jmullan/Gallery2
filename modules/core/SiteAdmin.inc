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
 * This view will show the availiable site-admin options
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class SiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	ksort($moduleStatus);
	foreach ($moduleStatus as $moduleName => $moduleStatus) {
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $moduleViews) = $module->getSiteAdminViews();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $subViewChoices = array_merge($subViewChoices, $moduleViews);
	}

	/* If we have a specific sub view, render it now */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (empty($subViewName)) {
	    $subViewName = 'core:AdminCore';
	}

	/* Set up my view parameters */
	$SiteAdmin = array('subViewChoices' => $subViewChoices,
			   'subViewName' => $subViewName);
	
	list ($ret, $subView) = GalleryView::loadView($subViewName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	list ($ret, $SiteAdmin['viewHeadFile'], $SiteAdmin['viewBodyFile']) =
	    $subView->loadTemplate($template, $form);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$SiteAdmin['viewL10Domain'] = $subView->getL10Domain();

	$template->setVariable('SiteAdmin', $SiteAdmin);
	return array(GalleryStatus::success(),
		     'modules/core/templates/SiteAdminHead.tpl',
		     'modules/core/templates/SiteAdmin.tpl');
    }
}
?>

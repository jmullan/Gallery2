<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class SiteAdminView extends GalleryView {

    /**
     * @see GalleryView::fetchHead
     */
    function fetchHead() {
	return array(GalleryStatus::success(), false);
    }

    /**
     * @see GalleryView::fetchBody
     */
    function fetchBody() {
	global $gallery;

	/* Figure out which tab is active (default to 'core') */
	$selectedTab = GalleryUtilities::getRequestVariables('selectedTab');
	if (empty($selectedTab)) {
	    $selectedTab = 'core';
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Build a tab for each module */
	$tabs = array();
	ksort($moduleStatus);
	foreach ($moduleStatus as $moduleName => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    $tab = array('name' => $moduleName,
			 'selected' => 0);
	    if ($selectedTab == $moduleName) {
		$tab['selected'] = 1;
	    }
	    $tabs[] = $tab;
	}

	/* Get the selected module's admin view */
	list($ret, $module) = $gallery->loadModule($selectedTab);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $view) = $module->getAdminView();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $moduleHtml) = $view->fetchBody();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render our HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('tabs', $tabs);
	$smarty->assign('moduleHtml', $moduleHtml);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('SiteAdminBody.tpl');

	return array(GalleryStatus::success(), $html);
    }    
}
?>

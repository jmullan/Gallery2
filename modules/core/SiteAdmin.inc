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
	global $gallery;
	
	/* Get our style */
	list ($ret, $style) = $gallery->getModuleParameter('core', 'default.style');
	if ($ret->isError()) {
	    return $ret;
	}

	$style = $gallery->getConfig('code.gallery.styles') . $style . '/style.css';
	$style = GalleryUtilities::convertPathToRelativeUrl($style);
	
	/* Render the HTML head */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('style', $style);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('SiteAdminHead.tpl');

	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::fetchBody
     */
    function fetchBody() {
	global $gallery;

	/* Make sure we have adequate permissions */
	list ($ret, $inGroup) =
	    GalleryUserGroupMap::isUserInAdminGroup($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!$inGroup) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__),
			 null);
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	foreach ($moduleStatus as $moduleName => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $moduleViews) = $module->getAdminViews();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $subViewChoices = array_merge($subViewChoices, $moduleViews);
	}

	/* If we have a specific sub view, render it now */
	$subView = GalleryUtilities::getRequestVariables('subView');
	if (!empty($subView)) {
	    ereg('^([[:alnum:]]+):([[:alnum:]]+)$', $subView, $regs);
	    if (sizeof($regs) != 3) {
		$module = 'core';
		$class = 'SecurityViolation';
	    } else {
		$module = $regs[1];
		$class = $regs[2];
	    }

	    require_once($gallery->getConfig('code.gallery.modules') .
			 $module . '/' . $class . '.inc');
	    $viewClassName = $class . 'View';
	    $view = new $viewClassName();

	    list ($ret, $subViewHtml) = $view->fetchBody();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $subViewHtml = "";
	}

	/* Render our HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$smarty->assign('subViewChoices', $subViewChoices);
	$smarty->assign('subViewHtml', $subViewHtml);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('SiteAdmin.tpl');

	return array(GalleryStatus::success(), $html);
    }    
}
?>

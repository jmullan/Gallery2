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

class SiteAdminView extends GalleryView {

    /**
     * @see GalleryView::useDefaultTheme
     */
    function useDefaultTheme() {
	return true;
    }

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	global $gallery;
	
	/* Make sure we have adequate permissions */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$html = $this->_renderTemplate('core', 'SiteAdminHead.tpl');
	return array(GalleryStatus::success(), $html);
    }

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	ksort($moduleStatus);
	foreach ($moduleStatus as $moduleName => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $moduleViews) = $module->getSiteAdminViews();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $subViewChoices = array_merge($subViewChoices, $moduleViews);
	}

	/* If we have a specific sub view, render it now */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (!empty($subViewName)) {
	    list ($ret, $subView) = GalleryView::loadView($subViewName);

	    list ($ret, $subViewHtml) = $subView->renderBody();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $subViewHtml = '';
	}

	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('subViewChoices', $subViewChoices);
	$this->_setTemplateVariable('subViewHtml', $subViewHtml);
	$html = $this->_renderTemplate('core', 'SiteAdmin.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

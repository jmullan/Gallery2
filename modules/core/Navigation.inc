<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
 * This controller will handle the rendering of an album or item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class NavigationView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Get system links */
	list ($ret, $moduleSystemLinks) = $this->_getModuleSystemLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get system content */
	list ($ret, $systemContent) = $this->_loadSystemContent($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the links for navigating back to where we came from */
	$urlGenerator =& $gallery->getUrlGenerator();
	list ($ret, $navigationLinks) = $urlGenerator->getNavigationLinks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$Navigation = array();
	$Navigation['l10Domain'] = 'modules_core';
	$Navigation['sidebar'] = 'modules/core/templates/NavigationSidebar.tpl';
	$Navigation['systemContent'] = $systemContent;
	$Navigation['moduleSystemLinks'] = $moduleSystemLinks;
	$Navigation['navigationLinks'] = $navigationLinks;
	$template->setVariable('Navigation', $Navigation);

	return array(GalleryStatus::success(), null);
    }

    /**
     * Call loadSystemContent on every active module
     *
     * @param object GalleryTemplate a template instance
     * @return array object GalleryStatus a status code
     *               array('moduleId' => 'template file path',
     *                     ...)
     * @access private
     */
    function _loadSystemContent(&$template) {
	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$systemContent = array();
	foreach ($moduleStatus as $moduleId => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH) {
		    continue;
		}
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Load all module-related content for these items */
	    list ($ret, $systemContent[$moduleId]) = $module->loadSystemContent($template);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($systemContent[$moduleId])) {
		unset($systemContent[$moduleId]);
	    }
	}

	return array(GalleryStatus::success(), $systemContent);
    }

    /**
     * Call getModuleSystemLinks on every active module
     *
     * @param object GalleryTemplate a template instance
     * @return array object GalleryStatus a status code
     *               array(array('moduleId' => array('text' => ...,
     *                                               'params' => ...,
     *                                               'url' => ...)),
     * @access private
     */
    function _getModuleSystemLinks() {
	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$links = array();
	foreach ($moduleStatus as $moduleId => $status) {
	    if (empty($status['active'])) {
		continue;
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH) {
		    continue;
		}
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Get all module-related links for these items */
	    list ($ret, $links[$moduleId]) = $module->getSystemLinks();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($links[$moduleId])) {
		unset($links[$moduleId]);
	    }
	}

	return array(GalleryStatus::success(), $links);
    }
}
?>

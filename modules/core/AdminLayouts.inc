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
 * This controller will handle an administration request for a module
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminLayoutsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	$errorMessage = array();

	$layoutId = GalleryUtilities::getRequestVariables('layoutId');
	if (!empty($layoutId) && !empty($form['action'])) {
	    list ($ret, $layoutStatusList) = GalleryPluginMap::getPluginStatus('layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!isset($layoutStatusList[$layoutId])) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
						  "Invalid layout: $layoutId"),
			     null);
	    }
	    
	    $layoutStatus = $layoutStatusList[$layoutId];

	    list ($ret, $layout) = GalleryPluginMap::loadPlugin('layout', $layoutId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (isset($form['action']['activate'])) {
	    /* Only activate if we're not already active! */
	    if (empty($layoutStatus['active'])) {
		$ret = GalleryPluginMap::activate('layout', $layoutId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$status['activated'] = $layout->getName();
	    }
	} else if (isset($form['action']['deactivate'])) {
	    /* Can't deactivate the last layout */
	    $count = 0;
	    foreach ($layoutStatusList as $tmp) {
		$count += !empty($tmp['active']);
	    }
	    if ($count == 1) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
						  "Can't deactivate the last layout"),
			     null);
	    }

	    /* Only deactivate if we're not already deactive! */
	    if (!empty($layoutStatus['active'])) {
		$ret = GalleryPluginMap::deactivate('layout', $layoutId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$status['deactivated'] = $layout->getName();
	    }
	} else if (isset($form['action']['saveLayout'])) {

	    /* Get all the possible settings */
	    list ($ret, $settings) = $layout->getSettings(null);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Validate the settings */
	    $validationErrors = $layout->validateSettings($form['key']);
	    if (empty($validationErrors)) {
		/* Save any settings that have changed */
		foreach ($settings as $setting) {
		    if ($setting['key'] != $form['key'][$setting['key']]) {
			$ret = $layout->setParameter($setting['key'], $form['key'][$setting['key']]);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}

		/* Redirect upon success */
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'editLayout';
		$redirect['layoutId'] = $layoutId;
		$status['savedLayout'] = $layout->getName();
	    } else {
		foreach ($validationErrors as $validationKey => $validationMessage) {
		    $error[] = sprintf('form.error.key.%s.invalid', $validationKey);
		    $errorMessage[$validationKey] = $validationMessage;
		}
		GalleryUtilities::putRequestVariable('form.errorMessage', $errorMessage);
	    }
	} else if (isset($form['action']['undoLayout'])) {
	    /* Redirect back to ourselves to reset the form */
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminLayouts';
	    $redirect['mode'] = 'editLayout';
	    $redirect['layoutId'] = $layoutId;
	    $status['restoredLayout'] = $layout->getName();
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'core:AdminLayouts';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show administration possibilities for available layouts
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminLayoutsView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

        list ($ret, $coreModule) = $gallery->loadModule('core');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($layoutId, $mode) = GalleryUtilities::getRequestVariables('layoutId', 'mode');
	if (empty($mode)) {
	    $mode = 'config';
	}
	
	/* Load the module list */
	list ($ret, $layouts) = GalleryPluginMap::getPluginStatus('layout');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Transform it to include all the layout data that we want to display */
	$activeCount = 0;
	foreach ($layouts as $id => $layoutStatus) {
	    list ($ret, $layout) = GalleryPluginMap::loadPlugin('layout', $id);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $layouts[$id]['active'] = empty($layoutStatus['active']) ? 0 : 1;
	    $layouts[$id]['name'] = $layout->getName();
	    $layouts[$id]['description'] = $layout->getDescription();
	    $layouts[$id]['version'] = $layout->getVersion();
	    $layouts[$id]['l10Domain'] = $layout->getL10Domain();

	    $activeCount += $layouts[$id]['active'];
	}

	switch($mode) {
	case 'config':
	    foreach (array_keys($layouts) as $id) {
		$actions = array();
		if (empty($layouts[$id]['active'])) {
		    $actions['activate'] = 1;
		} else {
		    /* Can't deactivate the last layout */
		    if ($activeCount > 1) {
			$actions['deactivate'] = 1;
		    }
		}
		$layouts[$id]['actions'] = $actions;
	    }
	    break;

	case 'editLayout':
	    /* Load the config settings from the active layout */
	    list ($ret, $layout) = GalleryPluginMap::loadPlugin('layout', $layoutId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $AdminLayouts['settings']) = $layout->getSettings(null);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    break;
	}

	if ($form['formName'] != 'AdminLayouts') {
	    $form['formName'] = 'AdminLayouts';

	    switch ($mode) {
	    case 'editLayout':
		foreach ($AdminLayouts['settings'] as $setting) {
		    $form['key'][$setting['key']] = $setting['values'][0];
		}
	    }
	}

	$AdminLayouts['mode'] = $mode;
	$AdminLayouts['layouts'] = $layouts;
	$AdminLayouts['layoutId'] = $layoutId;

	/* Render the HTML body */
	$template->setVariable('AdminLayouts', $AdminLayouts);
	$template->setVariable('controller', 'core:AdminLayouts');
	
	return array(GalleryStatus::success(), '', 'modules/core/templates/AdminLayouts.tpl');
    }
}
?>

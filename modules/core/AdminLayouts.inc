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
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	
	list($layoutName, $action) = GalleryUtilities::getRequestVariables('layoutName', 'action');
	if (!empty($layoutName) && !empty($action)) {
	    list ($ret, $layoutStatusList) = GalleryPluginMap::getPluginStatus('layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!isset($layoutStatusList[$layoutName])) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
						  "Invalid layout: $layoutName"),
			     null);
	    }
	    
	    $layoutStatus = $layoutStatusList[$layoutName];

	    switch($action) {
	    case 'activate':
		/* Only activate if we're not already active! */
		if (empty($layoutStatus['active'])) {
		    $ret = GalleryPluginMap::activate('layout', $layoutName);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminLayouts';
		    $status['activated'] = $layoutName;
		}
		break;
		
	    case 'deactivate':
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
		    $ret = GalleryPluginMap::deactivate('layout', $layoutName);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminLayouts';
		    $status['deactivated'] = $layoutName;
		}
		break;

	    default:
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
			     null);
	    }
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
	
	if ($form['formName'] != 'AdminLayouts') {
	    /* We have no form variables */
	    $form['formName'] = 'AdminLayouts';
	}

	/* Load the module list */
	list ($ret, $layoutStatusList) = GalleryPluginMap::getPluginStatus('layout');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Can't deactivate the last layout */
	$activeCount = 0;
	foreach ($layoutStatusList as $tmp) {
	    $activeCount += !empty($tmp['active']);
	}

	/* Add the l10 domain for convenience */
	$layouts = array();
	foreach ($layoutStatusList as $layoutName => $layoutStatus) {
	    list ($ret, $layout) = GalleryPluginMap::loadPlugin('layout', $layoutName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    if (empty($layoutStatus['active'])) {
		$action = array('text' => $coreModule->translate('activate'),
				'controller' => 'core:AdminLayouts',
				'layoutName' => $layoutName,
				'action' => 'activate');
	    } else {
		if ($activeCount > 1) {
		    $action = array('text' => $coreModule->translate('deactivate'),
				    'controller' => 'core:AdminLayouts',
				    'layoutName' => $layoutName,
				    'action' => 'deactivate');
		} else {
		    $action = array();
		}
	    }

	    $layouts[] = array('name' => $layout->getName(),
			       'description' => $layout->getDescription(),
			       'version' => $layout->getVersion(),
			       'l10Domain' => $layout->getL10Domain(),
			       'action' => $action);
	}

	$AdminLayouts['layouts'] = $layouts;

	/* Render the HTML body */
	$template->setVariable('AdminLayouts', $AdminLayouts);
	$template->setVariable('controller', 'core:AdminLayouts');
	
	return array(GalleryStatus::success(), '', 'modules/core/templates/AdminLayouts.tpl');
    }
}
?>

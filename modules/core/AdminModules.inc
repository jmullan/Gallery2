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
 * This controller will handle an administration request for a module
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminModulesController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	
	list($moduleId, $action) = GalleryUtilities::getRequestVariables('moduleId', 'action');
	if (!empty($moduleId) && !empty($action)) {
	    list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $isActive) = $module->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    switch($action) {
		
	    case 'install':
		$ret = $module->installOrUpgrade();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminModules';
		$status['available'] = $module->getName();
		break;
		
	    case 'activate':
		/* Can't activate if we're already active! */
		if (!$isActive) {
		    list ($ret, $needsConfiguration) = $module->needsConfiguration();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		
		    /* Can't activate if we need to be configured! */
		    if ($needsConfiguration) {
			return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
		    }
		
		    list ($ret, $redirect) = $module->activate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (empty($redirect)) {
			$redirect['view'] = 'core:SiteAdmin';
			$redirect['subView'] = 'core:AdminModules';
		    }
		    $status['activated'] = $module->getName();
		}
		break;
		
	    case 'deactivate':
		/* Can't deactivate if we're not active! */
		if ($isActive) {
		    list ($ret, $redirect) = $module->deactivate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    if (empty($redirect)) {
			$redirect['view'] = 'core:SiteAdmin';
			$redirect['subView'] = 'core:AdminModules';
		    }
		    $status['deactivated'] = $module->getName();
		}
		break;

	    case 'uninstall':
		/* Show the confirmation view */
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminModulesVerifyUninstall';
		$redirect['moduleId'] = $module->getId();
		break;
		
	    default:
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
			     null);
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    if (empty($delegate)) {
		$results['delegate']['view'] = 'core:SiteAdmin';
		$results['delegate']['subView'] = 'core:AdminModules';
	    } else {
		$results['delegate'] = $delegate;
	    }
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show administration possibilities for available modules
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminModulesView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

        list ($ret, $coreModule) = GalleryCoreApi::loadPlugin('module', 'core');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module', true);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'AdminModules') {
	    /* We have no form variables */
	    $form['formName'] = 'AdminModules';
	}

	foreach ($moduleStatus as $moduleId => $status) {
	    /* Get the selected module's admin view */
	    list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $entry = array();
	    $entry['name'] = $module->getName();
	    $entry['l10Domain'] = 'modules_' . $moduleId;
	    $entry['action'] = array();
	    if ($moduleId != 'core') {
		if (empty($status['active'])) {
		    list ($ret, $version) = $module->getModuleParameter('version');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /*
		     * If the database versions doesn't match the module
		     * version, we need to get the user to install the module.
		     */
		    if ($version != $module->getVersion()) {
			$entry['action'][] = array('text' => $coreModule->translate('install'),
						   'controller' => 'core:AdminModules',
						   'moduleId' => $module->getId(),
						   'action' => 'install');
		    } else {
			/*
			 * The versions match, but the module can still demand
			 * to be configured before being activated.
			 */
			list ($ret, $needsConfig) = $module->needsConfiguration();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			if ($needsConfig) {
			    $configView = $module->getConfigurationView();
			    $entry['action'][] = array('text' => $coreModule->translate('configure'),
						       'view' => $configView);
			} else {
			    $entry['action'][] = array('text' => $coreModule->translate('activate'),
						       'controller' => 'core:AdminModules',
						       'moduleId' => $moduleId,
						       'action' => 'activate');
			}
			$entry['action'][] = array('text' => $coreModule->translate('uninstall'),
						   'controller' => 'core:AdminModules',
						   'moduleId' => $moduleId,
						   'action' => 'uninstall');
		    }
		} else {
		    $entry['action'][] = array('text' => $coreModule->translate('deactivate'),
					       'controller' => 'core:AdminModules',
					       'moduleId' => $moduleId,
					       'action' => 'deactivate');
		}
	    }
	    
	    $entry['description'] = $module->getDescription();
	    $entry['version'] = $module->getVersion();
	    $group = $module->getGroup();
	    $entry = array_merge($entry, empty($group) ?
		array('group' => 'other', 'groupLabel' => $module->translate('Other')) : $group);
	    $modules[] = $entry;
	}

	usort($modules, array($this, 'moduleSort'));
	$AdminModules['modules'] = $modules;

	/* Render the HTML body */
	$template->setVariable('AdminModules', $AdminModules);
	$template->setVariable('controller', 'core:AdminModules');
	
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/AdminModules.tpl'));
    }

    function moduleSort($a, $b) {
	static $groupOrder;
	if (!isset($groupOrder)) {
	    // gallery first, toolkits second, other last
	    $groupOrder = array('gallery' => 1, 'toolkits' => 2, '' => 3, 'other' => 4);
	}
	$ag = $a['group'];
	$bg = $b['group'];
	if ($ag != $bg) {
	    $ao = isset($groupOrder[$ag]) ? $groupOrder[$ag] : $groupOrder[''];
	    $bo = isset($groupOrder[$bg]) ? $groupOrder[$bg] : $groupOrder[''];
	    if ($ao != $bo) {
		return ($ao > $bo) ? 1 : -1;
	    }
	    $ag = isset($a['groupLabel']) ? $a['groupLabel'] : $ag;
	    $bg = isset($b['groupLabel']) ? $b['groupLabel'] : $bg;
	    return ($ag > $bg) ? 1 : -1;
	} else {
	    $an = $a['name'];
	    $bn = $b['name'];
	    if ($an == $bn) {
		return 0;
	    } else {
		return ($an > $bn) ? 1 : -1;
	    }
	}
    }
}
?>

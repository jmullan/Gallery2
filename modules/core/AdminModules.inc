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
class AdminModulesController extends GalleryController {

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
	
	list($moduleName, $action) = GalleryUtilities::getRequestVariables('moduleName', 'action');
	if (!empty($moduleName) && !empty($action)) {
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $isActive) = $module->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    switch($action) {
		
	    case 'install':
		$ret = $module->install();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminModules';
		$status['installed'] = $moduleName;
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
			return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
				     null);
		    }
		
		    $ret = $module->activate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminModules';
		    $status['activated'] = $moduleName;
		}
		break;
		
	    case 'deactivate':

		/* Can't deactivate if we're not active! */
		if ($isActive) {
		    $ret = $module->deactivate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminModules';
		    $status['deactivated'] = $moduleName;
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
	    $results['delegate']['subView'] = 'core:AdminModules';
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
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

        list ($ret, $coreModule) = $gallery->loadModule('core');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($form['formName'] != 'AdminModules') {
	    /* We have no form variables */
	    $form['formName'] = 'AdminModules';
	}

	ksort($moduleStatus);

	foreach ($moduleStatus as $moduleName => $status) {
	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $entry = array();
	    $entry['name'] = $moduleName;
	    $entry['l10Domain'] = 'modules_' . $moduleName;
	    if ($moduleName != 'core') {
		if (empty($status['active'])) {
		    list ($ret, $version) = $module->getModuleParameter('version');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    /*
		     * If the database versions doesn't match the module
		     * version, we need to get the user to install the module.
		     */
		    if ($version != $module->getVersion()) {
			$entry['action'] = array('text' => $coreModule->translate('install'),
						 'controller' => 'core:AdminModules',
						 'moduleName' => $module->getName(),
						 'action' => 'install');
		    } else {

			/*
			 * The versions match, but the module can still demand
			 * to be configured before being activated.
			 */
			list ($ret, $needsConfig) = $module->needsConfiguration();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			if ($needsConfig) {
			    list ($ret, $configView) = $module->getConfigurationView();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null, null);
			    }
			    $entry['action'] = array('text' => $coreModule->translate('configure'),
						     'view' => $configView);
			} else {
			    $entry['action'] = array('text' => $coreModule->translate('activate'),
						     'controller' => 'core:AdminModules',
						     'moduleName' => $moduleName,
						     'action' => 'activate');
			}
		    }
		} else {
		    $entry['action'] = array('text' => $coreModule->translate('deactivate'),
					     'controller' => 'core:AdminModules',
					     'moduleName' => $moduleName,
					     'action' => 'deactivate');
		}
	    }
	    
	    $entry['description'] = $module->getDescription();
	    $entry['version'] = $module->getVersion();
	    $modules[] = $entry;
	}

	$AdminModules['modules'] = $modules;

	/* Render the HTML body */
	$template->setVariable('AdminModules', $AdminModules);
	$template->setVariable('controller', 'core:AdminModules');
	
	return array(GalleryStatus::success(), '', 'modules/core/templates/AdminModules.tpl');
    }
}
?>

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

class AdminModulesController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	list($module, $action) = GalleryUtilities::getRequestVariables('module', 'action');
	if (!empty($module) && !empty($action)) {
	    list($ret, $module) = $gallery->loadModule($module);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $isActive) = $module->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    switch($action) {
	    case 'activate':

		/* Can't activate if we're already active! */
		if ($isActive) {
		    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
				 null);
		}

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
		break;
		
	    case 'deactivate':

		/* Can't deactivate if we're not active! */
		if (!$isActive) {
		    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
				 null);
		}

		$ret = $module->deactivate();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		break;

	    default:
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__),
			     null);
	    }
	}

	/* Figure out where to redirect upon success */
	$urlParams['view'] = 'core:SiteAdmin';
	$urlParams['subView'] = 'core:AdminModules';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($urlParams);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminModulesView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	return array(GalleryStatus::success(), false);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Load the module list */
	list ($ret, $moduleStatus) = $gallery->getModuleStatus();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	ksort($moduleStatus);

	foreach ($moduleStatus as $moduleName => $status) {
	    /* Get the selected module's admin view */
	    list($ret, $module) = $gallery->loadModule($moduleName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $entry = array();
	    $entry['name'] = $moduleName;
	    if ($moduleName != 'core') {
		if (empty($status['active'])) {
		    list ($ret, $needsConfig) = $module->needsConfiguration();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if ($needsConfig) {
			list ($ret, $configView) = $module->getConfigurationView();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
			$entry['action'] = array('text' => $gallery->translate('configure'),
						 'view' => $configView);
		    } else {
			$entry['action'] = array('text' => $gallery->translate('activate'),
						 'controller' => 'core:AdminModules',
						 'module' => $moduleName,
						 'action' => 'activate');
		    }
		} else {
		    $entry['action'] = array('text' => $gallery->translate('deactivate'),
					     'controller' => 'core:AdminModules',
					     'module' => $moduleName,
					     'action' => 'deactivate');
		}
	    }
	    
	    $entry['description'] = $module->getDescription();
	    $entry['version'] = $module->getVersion();
	    $modules[] = $entry;
	}

	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$smarty->assign('modules', $modules);
	$smarty->assign('controller', 'core:AdminModules');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminModules.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

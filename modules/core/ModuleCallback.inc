<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
/**
 * @version $Revision$ $Date$
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This view lets you make very simple callbacks to the framework to
 * get very specific data.  Eventually this will probably get refactored
 * into a much more sophisticated framework.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ModuleCallbackView extends GalleryView {

    /**
     * @see GalleryView::isImmediate()
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::isImmediate()
     */
    function renderImmediate($status, $error) {
	global $gallery;
	$session =& $gallery->getSession();

	$command = GalleryUtilities::getRequestVariables('command');
	if (!headers_sent()) {
	    header("Content-type: text/plain; charset=UTF-8");
	}

	list ($ret, $beforeStates) = $this->getModuleStates();
	if ($ret) {
	    $result['status'] = 'error';
	    $session->put('core.error', serialize($ret));
	}

	if (!$ret) {
	    $ret = $this->handleCallback($command, $result);
	    if ($ret) {
		$result['status'] = 'error';
		$session->put('core.error', serialize($ret));
	    }

	    if ($result['status'] == 'redirect') {
		$urlGenerator =& $gallery->getUrlGenerator();
		$result['redirect'] =
		    $urlGenerator->generateUrl($result['redirect'], array('htmlEntities' => 0));
	    }
	}

	if (!$ret) {
	    list ($ret, $afterStates) = $this->getModuleStates();
	    if ($ret) {
		$result['status'] = 'error';
		$session->put('core.error', serialize($ret));
	    }
	    $result['states'] = $this->calculateStateChanges($beforeStates, $afterStates);
	}

	GalleryCoreApi::requireOnce('lib/JSON/JSON.php');
	$json = new Services_JSON();
	print $json->encode($result);
	return null;
    }

    /**
     * Given two sets of states, figure out what's changed from before to after.
     *
     * @param array before states (moduleId => state, ...)
     * @param array after states (moduleId => state, ...)
     * @return array changed states (moduleId => state, ...)
     */
    function calculateStateChanges($beforeStates, $afterStates) {
	$changes = array();
	foreach ($afterStates as $moduleId => $state) {
	    if (!isset($beforeStates[$moduleId]) ||
		$beforeStates[$moduleId] != $state) {
		$changes[$moduleId] = $state;
	    }
	}
	return $changes;
    }

    /**
     * Handle the specific callback, and store its result in the
     * given output array.
     *
     * @param string the command (eg, "installModule")
     * @param array the location for result data to be sent back to the browser
     * @return object GalleryStatus a status code
     * @static
     */
    function handleCallback($command, &$result) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return $ret;
	}

	$result = array();
	$moduleId = GalleryUtilities::getRequestVariables('moduleId');

	list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId, true);
	if ($ret) {
	    return $ret;
	}

	switch($command) {
	case 'activateModule':
	    list ($ret, $isActive) = $module->isActive();
	    if ($ret) {
		return $ret;
	    }

	    list ($ret, $needsConfiguration) = $module->needsConfiguration();
	    if ($ret) {
		return $ret;
	    }

	    if ($isActive || $needsConfiguration) {
		/* UI shouldn't let us come here anyway */
		$result['status'] = 'invalid';
		return null;
	    }

	    list ($ret, $redirect) = $module->activate();
	    if ($ret) {
		return $ret;
	    }

	    if ($redirect) {
		$result['status'] = 'redirect';
		$result['redirect'] = $redirect;
	    } else {
		$result['status'] = 'success';
	    }
	    break;

	case 'deactivateModule':
	    list ($ret, $isActive) = $module->isActive();
	    if ($ret) {
		return $ret;
	    }

	    if (!$isActive) {
		/* UI shouldn't let us come here anyway */
		$result['status'] = 'invalid';
		return null;
	    }

	    list ($ret, $redirect) = $module->deactivate();
	    if ($ret) {
		return $ret;
	    }

	    if ($redirect) {
		$result['status'] = 'redirect';
		$result['redirect'] = $redirect;
	    } else {
		$result['status'] = 'success';
	    }
	    break;

	case 'upgradeModule':
	case 'installModule':
	    $ret = $module->installOrUpgrade();
	    if ($ret) {
		return $ret;
	    }

	    list($ret, $autoConfigured) = $module->autoConfigure();
	    if ($ret) {
		return $ret;
	    }

	    if ($autoConfigured) {
		list ($ret, $redirect) = $module->activate();
		if ($ret) {
		    return $ret;
		}

		if ($redirect) {
		    $result['status'] = 'redirect';
		    $result['redirect'] = $redirect;
		} else {
		    $result['status'] = 'success';
		}
	    } else {
		$result['status'] = 'success';
	    }
	    break;

	case 'uninstallModule':
	    $result['status'] = 'redirect';
	    $result['redirect'] = array('view' => 'core.SiteAdmin',
					'subView' => 'core.AdminModulesVerifyUninstall',
					'moduleId' => $moduleId);
	    break;

	case 'configureModule':
	    $result['status'] = 'redirect';
	    $result['redirect'] = array('view' => 'core.SiteAdmin',
					'subView' => $module->getConfigurationView());
	    break;
	}

	return null;
    }

    /**
     * Get the state ('active', 'inactive', 'uninstalled', etc) of all modules
     *
     * @return array object GalleryStatus a status code
     *               array(moduleId => state, ...)
     * @static
     */
    function getModuleStates() {
	$states = array();

	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module', true);
	if ($ret) {
	    return array($ret, null);
	}
	foreach ($moduleStatus as $moduleId => $status) {
	    list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId, true);
	    if ($ret) {
		return array($ret, null);
	    }

	    list ($ret, $states[$moduleId]) = $this->getModuleState($module, $status);
	    if ($ret) {
		return array($ret, null);
	    }
	}

	return array(null, $states);
    }

    /**
     * Get the state ('active', 'inactive', 'uninstalled', etc) of a given module
     *
     * @return array object GalleryStatus a status code
     *               string a state
     * @static
     */
    function getModuleState($module, $status) {
	if ($module->getId() == 'core') {
	    return array(null, 'active');
	}

	$coreApiCompatible = GalleryUtilities::isCompatibleWithApi(
	    $module->getRequiredCoreApi(), GalleryCoreApi::getApiVersion());
	$moduleApiCompatible = GalleryUtilities::isCompatibleWithApi(
	    $module->getRequiredModuleApi(), GalleryModule::getApiVersion());
	if ($coreApiCompatible && $moduleApiCompatible) {
	    if (empty($status['active'])) {
		$version = $status['version'];
		$state = 'inactive';

		/*
		 * If the database versions doesn't match the module
		 * version, we need to get the user to install the module.
		 */
		if ($version != $module->getVersion()) {
		    if (empty($version)) {
			$state = 'uninstalled';
		    } else {
			$state = 'unupgraded';
		    }
		} else {
		    /*
		     * The versions match, but the module can still demand
		     * to be configured before being activated.
		     */
		    list ($ret, $needsConfig) = $module->needsConfiguration();
		    if ($ret) {
			return array($ret, null);
		    }

		    if ($needsConfig) {
			$state = 'unconfigured';
		    } else {
			$state = 'inactive';
		    }
		}
	    } else {
		$state = 'active';
	    }
	} else {
	    $state = 'incompatible';
	}

	return array(null, $state);
    }
}
?>

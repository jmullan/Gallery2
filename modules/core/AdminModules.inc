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
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret, null);
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module', true);
	if ($ret) {
	    return array($ret, null);
	}

	/*
	 * It's possible that we have some out-of-date modules which haven't
	 * been deactivated yet, since the deactivation only occurs when we try
	 * to load the module.  Load all the active modules now to force the
	 * version check, then reload the module status when we're done to pick
	 * up any changes we trigger.
	 */
	foreach ($moduleStatus as $moduleId => $status) {
	    if (!empty($status['active'])) {
		list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
		if ($ret && !($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
		    return array($ret, null);
		}
	    }
	}

	/* Reload the module list, which may now be updated because of obsolete modules. */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module', true);
	if ($ret) {
	    return array($ret, null);
	}

	if ($form['formName'] != 'AdminModules') {
	    /* We have no form variables */
	    $form['formName'] = 'AdminModules';
	}

	GalleryCoreApi::requireOnce('modules/core/ModuleCallback.inc');
	foreach ($moduleStatus as $moduleId => $status) {
	    /* Get the selected module's admin view (even if the module needs upgrading)  */
	    list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId, true);
	    if ($ret) {
		return array($ret, null);
	    }

	    $entry = array();
	    $entry['name'] = $module->translate($module->getName());
	    $entry['id'] = $module->getId();
	    $entry['description'] = $module->translate($module->getDescription());
	    $entry['version'] = $module->getVersion();
	    $entry['installedVersion'] = isset($status['version']) ? $status['version'] : null;

	    list ($ret, $entry['state']) = ModuleCallbackView::getModuleState($module, $status);
	    if ($ret) {
		return array($ret, null);
	    }

	    if ($entry['state'] == 'incompatible') {
		$entry['api']['required']['module'] =
		    join('.', $module->getRequiredModuleApi());
		$entry['api']['provided']['module'] = join('.', GalleryModule::getApiVersion());
		$entry['api']['required']['core'] = join('.', $module->getRequiredCoreApi());
		$entry['api']['provided']['core'] = join('.', GalleryCoreApi::getApiVersion());
	    }

	    $modules[] = array_merge($entry, $module->getGroup());
	}

	usort($modules, array($this, 'moduleSort'));
	$template->setVariable('AdminModules', array('modules' => $modules));
	$template->setVariable('controller', 'core.AdminModules');
	$template->javascript('lib/javascript/XmlHttp.js');

	return array(null,
		     array('body' => 'modules/core/templates/AdminModules.tpl'));
    }

    function moduleSort($a, $b) {
	static $groupOrder;
	if (!isset($groupOrder)) {
	    /* gallery first, toolkits second, other last */
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

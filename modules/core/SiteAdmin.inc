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
 * This view will show the availiable site-admin options
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class SiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get a list of all the admin views for each module */
	$subViewChoices = array();
	ksort($moduleStatus);
	foreach ($moduleStatus as $moduleId => $moduleStatus) {
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    /* Get the selected module's admin view */
	    list($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH) {
		    continue;
		}
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $moduleViews) = $module->getSiteAdminViews();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $group = $module->getGroup();
	    if (empty($group)) {
		$group = array('group' => 'other');
	    }
	    foreach (array_keys($moduleViews) as $i) {
		$moduleViews[$i] = array_merge($group, $moduleViews[$i]);
	    }

	    $subViewChoices = array_merge($subViewChoices, $moduleViews);
	}
	// Sort and group..
	$subViewGroups = $groupLabels = array();
	foreach ($subViewChoices as $adminView) {
	    $group = $adminView['group'];
	    $subViewGroups[$group][] = $adminView;

	    if (!empty($adminView['groupLabel'])) {
		$label = $adminView['groupLabel'];
		if (!isset($groupLabels[$group][$label])) {
		    $groupLabels[$group][$label] = 1;
		} else {
		    $groupLabels[$group][$label]++;
		}
	    }
	}
	// Set labels..
	foreach (array_keys($subViewGroups) as $group) {
	    $data =& $subViewGroups[$group];
	    if ($data[0]['group'] != 'gallery') {
		usort($data, 'SiteAdminView_nameSort');
	    }
	    if (isset($groupLabels[$group])) {
		$tmp = -1;
		foreach ($groupLabels[$group] as $label => $count) {
		    if ($count > $tmp) {
			$tmp = $count;
			$data[0]['groupLabel'] = $label;
		    }
		}
	    } else {
		$data[0]['groupLabel'] = ucwords($data[0]['group']);
	    }
	}
	usort($subViewGroups, 'SiteAdminView_groupSort');

	/* If we have a specific sub view, render it now */
	$subViewName = GalleryUtilities::getRequestVariables('subView');
	if (empty($subViewName)) {
	    $subViewName = 'core:AdminCore';
	}

	list ($ret, $subView) = GalleryView::loadView($subViewName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	list ($ret, $results) = $subView->loadTemplate($template, $form);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Our sub view may have set some hints, like the encoding type */
	if ($template->hasVariable('SiteAdmin')) {
	    $SiteAdmin =& $template->getVariableByReference('SiteAdmin');
	} else {
	    $SiteAdmin = array();
	}

	/* Set up my view parameters */
	$SiteAdmin['subViewGroups'] = $subViewGroups;
	$SiteAdmin['subViewName'] = $subViewName;
	$SiteAdmin['viewBodyFile'] = $results['body'];
	$SiteAdmin['viewL10Domain'] = $subView->getL10Domain();

	$template->setVariable('SiteAdmin', $SiteAdmin);
	return array(GalleryStatus::success(),
		     array('head' => 'modules/core/templates/SiteAdminHead.tpl',
			   'body' => 'modules/core/templates/SiteAdmin.tpl'));
    }
}

function SiteAdminView_groupSort($a, $b) {
    static $groupOrder;
    if (!isset($groupOrder)) {
	// gallery first, toolkits second, other last
	$groupOrder = array('gallery' => 1, 'toolkits' => 2, '' => 3, 'other' => 4);
    }
    $ag = $a[0]['group'];
    $bg = $b[0]['group'];
    $ao = isset($groupOrder[$ag]) ? $groupOrder[$ag] : $groupOrder[''];
    $bo = isset($groupOrder[$bg]) ? $groupOrder[$bg] : $groupOrder[''];
    if ($ao != $bo) {
	return ($ao > $bo) ? 1 : -1;
    }
    $ag = isset($a[0]['groupLabel']) ? $a[0]['groupLabel'] : $ag;
    $bg = isset($b[0]['groupLabel']) ? $b[0]['groupLabel'] : $bg;
    return ($ag > $bg) ? 1 : -1;
}

function SiteAdminView_nameSort($a, $b) {
    $an = $a['name'];
    $bn = $b['name'];
    if ($an == $bn) {
	return 0;
    }
    return ($an > $bn) ? 1 : -1;
}
?>

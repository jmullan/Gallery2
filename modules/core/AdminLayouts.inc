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
class AdminLayoutsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	$error = array();
	$errorMessage = array();

	$layoutId = GalleryUtilities::getRequestVariables('layoutId');
	if (!empty($layoutId) && !empty($form['action'])) {
	    list ($ret, $layoutStatusList) = GalleryCoreApi::fetchPluginStatus('layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!isset($layoutStatusList[$layoutId])) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
						  "Invalid layout: $layoutId"),
			     null);
	    }

	    $layoutStatus = $layoutStatusList[$layoutId];

	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (isset($form['action']['activate'])) {
	    /* Only activate if we're not already active! */
	    if (empty($layoutStatus['active'])) {
		list ($ret, $redirect) = $layout->activate();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (empty($redirect)) {
		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminLayouts';
		    $redirect['mode'] = 'config';
		}
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
		list ($ret, $redirect) = $layout->deactivate();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (empty($redirect)) {
		    $redirect['view'] = 'core:SiteAdmin';
		    $redirect['subView'] = 'core:AdminLayouts';
		    $redirect['mode'] = 'config';
		}
		$status['deactivated'] = $layout->getName();
	    }
	} else if (isset($form['action']['saveDefaults'])) {
	    foreach (array(
			   'default.orderBy',
			   'default.orderDirection',
			   'default.layout',
			   'default.theme',
			   'default.newAlbumsUseDefaults',
			   ) as $key) {
		list ($outer, $inner) = explode('.', $key);
		if (isset($form[$outer][$inner])) {
		    $value = $form[$outer][$inner];
		    if ($key == 'default.orderBy' && isset($form['default']['presort'])) {
			$value = $form['default']['presort'] . '|' . $value;
		    }
		    $ret = GalleryCoreApi::setPluginParameter('module', 'core', $key, $value);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    /* Redirect upon success */
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminLayouts';
	    $redirect['mode'] = 'defaults';
	    $status['savedDefaults'] = 1;
	} else if ($layout->isAdvancedSettings()) {
	    list ($ret, $error, $statusKey) = $layout->handleSettingsRequest($form);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (empty($error)) {
		/* Redirect upon success */
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'editLayout';
		$redirect['layoutId'] = $layoutId;
		$status[$statusKey] = $layout->getName();
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
		    if ($setting['type'] == 'checkbox') {
			$value = isset($form['key'][$setting['key']]) ? 1 : 0;
		    } else {
			$value = $form['key'][$setting['key']];
		    }
		    if ($setting['value'] !== $value) {
			$ret = $layout->setParameter($setting['key'], $value);
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
		    $error[] = sprintf('form[error][key][%s][invalid]', $validationKey);
		    $errorMessage[$validationKey] = $validationMessage;
		}
		GalleryUtilities::putRequestVariable('form[errorMessage]', $errorMessage);
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

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $coreModule) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($layoutId, $mode) = GalleryUtilities::getRequestVariables('layoutId', 'mode');
	if (empty($mode)) {
	    $mode = 'defaults';
	}

	/* Load the module list */
	list ($ret, $layouts) = GalleryCoreApi::fetchPluginStatus('layout', true);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Transform it to include all the layout data that we want to display */
	$activeCount = 0;
	$layoutList = array();
	foreach ($layouts as $id => $layoutStatus) {
	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $id);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $layouts[$id]['active'] = empty($layoutStatus['active']) ? 0 : 1;
	    $layouts[$id]['name'] = $layout->getName();
	    $layouts[$id]['description'] = $layout->getDescription();
	    $layouts[$id]['version'] = $layout->getVersion();
	    $layouts[$id]['l10Domain'] = $layout->getL10Domain();


	    if (!empty($layouts[$id]['active'])) {
		$activeCount++;
		$layoutList[$id] = $layout->getName();
	    }
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$AdminLayouts = array();
	switch($mode) {
	case 'defaults':
	    /* Load up the stored defaults */
	    foreach (array(
			   'default.orderBy',
			   'default.orderDirection',
			   'default.layout',
			   'default.theme',
			   'default.newAlbumsUseDefaults',
			   ) as $key) {

		list ($ret, $value) =
		    GalleryCoreApi::getPluginParameter('module', 'core', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($key == 'default.orderBy') {
		    $tmp = explode('|', $value, 2);
		    if (count($tmp) == 2) {
			$value = $tmp[1];
			$form['default']['presort'] = $tmp[0];
		    } else {
			$form['default']['presort'] = '';
		    }
		}

		list ($outer, $inner) = explode('.', $key);
		$form[$outer][$inner] = $value;
	    }

	    $newAlbumsUseDefaultsList = array(
		'false' => $module->translate('Inherit settings from parent album'),
		'true' => $module->translate('Use these settings')
	    );

	    /* Set up our sort order selection list */
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GallerySortInterface_1_1.class');
	    list ($ret, $orderByList, $presortList, $orderDirectionList) =
		GallerySortInterface_1_1::getAllSortOrders(false);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $AdminLayouts['orderByList'] = $orderByList;
	    $AdminLayouts['presortList'] = $presortList;
	    $AdminLayouts['orderDirectionList'] = $orderDirectionList;
	    $AdminLayouts['layoutList'] = $layoutList;
	    $AdminLayouts['themeList'] = GalleryTheme::getThemeList();
	    $AdminLayouts['newAlbumsUseDefaultsList'] = $newAlbumsUseDefaultsList;
	    break;

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
	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($layout->isAdvancedSettings()) {
		list ($ret, $tpl) = $layout->loadSettingsTemplate($template, $form);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$AdminLayouts['customTemplate'] = $tpl;
	    } else {
		list ($ret, $AdminLayouts['settings']) = $layout->getSettings(null);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    break;
	}

	if ($form['formName'] != 'AdminLayouts') {
	    $form['formName'] = 'AdminLayouts';

	    switch ($mode) {
	    case 'editLayout':
		if (isset($AdminLayouts['settings'])) {
		    foreach ($AdminLayouts['settings'] as $setting) {
			$form['key'][$setting['key']] = $setting['value'];
		    }
		}
	    }
	}

	$AdminLayouts['mode'] = $mode;
	$AdminLayouts['layouts'] = $layouts;
	$AdminLayouts['layoutId'] = $layoutId;

	/* Render the HTML body */
	$template->setVariable('AdminLayouts', $AdminLayouts);
	$template->setVariable('controller', 'core:AdminLayouts');

	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/AdminLayouts.tpl'));
    }
}
?>

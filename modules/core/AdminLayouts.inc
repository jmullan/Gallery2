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
	$layout = null;
	if (!empty($layoutId) && !empty($form['action'])) {
	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH &&
		    isset($form['action']['upgrade'])) {
		    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId, true);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    list ($ret, $isActive) = $layout->isActive();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($form['action']['activate'])) {
		/* Only activate if we're not already active! */
		if (!$isActive) {
		    list ($ret, $redirect) = $layout->activate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['activated'] = $layout->getName();
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'config';
	    } else if (isset($form['action']['install'])) {
		$ret = $layout->installOrUpgrade();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'config';
		$status['installed'] = $layout->getName();
	    } else if (isset($form['action']['upgrade'])) {
		$ret = $layout->installOrUpgrade();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'config';
		$status['upgraded'] = $layout->getName();
	    } else if (isset($form['action']['uninstall'])) {
		if (!$isActive) {
		    $ret = $layout->uninstall();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['uninstalled'] = $layout->getName();
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'config';
	    } else if (isset($form['action']['deactivate'])) {
		list ($ret, $defaultLayoutId) =
		    GalleryCoreApi::getPluginParameter('module', 'core', 'default.layout');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/* Only deactivate if we're not already deactive and not the default! */
		if ($isActive && $layout->getId() != $defaultLayoutId) {
		    list ($ret, $redirect) = $layout->deactivate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['deactivated'] = $layout->getName();
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminLayouts';
		$redirect['mode'] = 'config';
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
	} else {  /* no layout id provided */
	    if (isset($form['action']['saveDefaults'])) {
		foreach (array('default.orderBy',
			       'default.orderDirection',
			       'default.layout',
			       'default.theme',
			       'default.newAlbumsUseDefaults')
			 as $key) {
		    list ($outer, $inner) = explode('.', $key);
		    if (isset($form[$outer][$inner])) {
			$value = $form[$outer][$inner];
			if ($key == 'default.orderBy' && !empty($form['default']['presort'])) {
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

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($layoutId, $mode) = GalleryUtilities::getRequestVariables('layoutId', 'mode');
	if (empty($mode)) {
	    $mode = 'defaults';
	}

	/* Load the layout list */
	list ($ret, $layouts) = GalleryCoreApi::fetchPluginStatus('layout', true);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * It's possible that we have some out-of-date layouts which haven't
	 * been deactivated yet, since the deactivation only occurs when we try
	 * to load the layout.  Load all the active layouts now to force the
	 * version check, then reload the layout status when we're done to pick
	 * up any changes we trigger.
	 */
	foreach ($layouts as $id => $status) {
	    if (!empty($status['active'])) {
		list($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $id);
		if ($ret->isError() && !($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Reload the layout list, which may now be updated because of obsolete modules. */
	list ($ret, $layouts) = GalleryCoreApi::fetchPluginStatus('layout', true);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * Figure out how many active layouts we have (because we don't allow
	 * deactivating the last one.
	 */
	$activeCount = 0;
	foreach (array_keys($layouts) as $id) {
	    $activeCount += !empty($layouts[$id]['active']);
	}

	list ($ret, $defaultLayoutId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'default.layout');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Transform it to include all the layout data that we want to display */
	$layoutList = array();
	foreach ($layouts as $id => $status) {
	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $id, true);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $entry = array();
	    $entry['name'] = $layout->getName();
	    $entry['active'] = !empty($status['active']);
	    $entry['l10Domain'] = $layout->getL10Domain();
	    $entry['action'] = array();
	    $coreApiCompatible = GalleryUtilities::isCompatibleWithApi(
                $layout->getRequiredCoreApi(), GalleryCoreApi::getApiVersion());
	    $layoutApiCompatible = GalleryUtilities::isCompatibleWithApi(
                $layout->getRequiredLayoutApi(), GalleryLayout::getApiVersion());
	    if ($coreApiCompatible && $layoutApiCompatible) {
		if (empty($status['active'])) {
		    $entry['state'] = 'inactive';

		    /*
		     * If the database versions doesn't match the layout
		     * version, we need to get the user to install the layout.
		     */
		    if ($status['version'] != $layout->getVersion()) {
			if (empty($status['version'])) {
			    $entry['action'][] =
				array('text' => $module->translate('install'),
				      'params' => array('controller' => 'core:AdminLayouts',
							'layoutId' => $id,
							'form[action][install]' => 1));
			    $entry['state'] = 'install';
			} else {
			    $entry['action'][] =
				array('text' => $module->translate('upgrade'),
				      'params' => array('controller' => 'core:AdminLayouts',
							'layoutId' => $id,
							'form[action][upgrade]' => 1));
			    $entry['state'] = 'upgrade';
			}
		    } else {
			$entry['action'][] =
			    array('text' => $module->translate('activate'),
				  'params' => array('controller' => 'core:AdminLayouts',
						    'layoutId' => $id,
						    'form[action][activate]' => 1));
			$entry['action'][] =
			    array('text' => $module->translate('uninstall'),
				  'params' => array('controller' => 'core:AdminLayouts',
						    'layoutId' => $id,
						    'form[action][uninstall]' => 1));
		    }
		} else {
		    $entry['state'] = 'active';
		    if ($id != $defaultLayoutId) {
			$entry['action'][] =
			    array('text' => $module->translate('deactivate'),
				  'params' => array('controller' => 'core:AdminLayouts',
						    'layoutId' => $id,
						    'form[action][deactivate]' => 1));
		    }
		}
	    } else {
		$entry['state'] = 'incompatible';
		$entry['api']['required']['layout'] = join('.', $layout->getRequiredLayoutApi());
		$entry['api']['required']['core'] = join('.', $layout->getRequiredCoreApi());
		$entry['api']['provided']['layout'] = join('.', GalleryLayout::getApiVersion());
		$entry['api']['provided']['core'] = join('.', GalleryCoreApi::getApiVersion());
	    }

	    $entry['description'] = $layout->getDescription();
	    $entry['version'] = $layout->getVersion();
	    $entry['installedVersion'] = isset($status['version']) ? $status['version'] : null;
	    $layouts[$id] = $entry;

	    if (!empty($status['active'])) {
		$layoutList[$id] = $layout->getName();
	    }
	}

	$AdminLayouts = array();
	switch($mode) {
	case 'defaults':
	    /* Load up the stored defaults */
	    foreach (array('default.orderBy',
			   'default.orderDirection',
			   'default.layout',
			   'default.theme',
			   'default.newAlbumsUseDefaults')
		     as $key) {

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
	    GalleryCoreApi::relativeRequireOnce(
                'modules/core/classes/GallerySortInterface_1_1.class');
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
	    $AdminLayouts['defaultLayoutId'] = $defaultLayoutId;
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

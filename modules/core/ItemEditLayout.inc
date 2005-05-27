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
 * This controller will handle the changes users make to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditLayout extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;

	list ($ret, $layoutId) = GalleryCoreApi::fetchLayoutId($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($layout->isAdvancedSettings()) {
	    list ($ret, $error, $status) = $layout->handleSettingsRequest($form, $item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    return array(GalleryStatus::success(), $error, $status);
	}

	$status = null;
	$error = array();
	$errorMessage = array();

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if (isset($form['action']['save'])) {
	    /* Validate the settings */
	    $validationErrors = $layout->validateSettings($form['key']);
	    if (empty($validationErrors)) {
		/* Get the item settings */
		list ($ret, $settings) = $layout->getSettings($item->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		/*
		 * Any settings that are marked as "use global" should be removed from this item.
		 * Others should be updated in the database.  Note that we set the parameter even
		 * if it is the same as the original setting value, since we want to make sure
		 * that the value is stored per item, and the original setting value could have
		 * been from the global space.
		 */
		foreach ($settings as $setting) {
		    $key = $setting['key'];
		    if (!empty($form['useGlobal'][$key])) {
			$ret = $layout->removeItemParameter($key, $item->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    } else {
			if ($setting['type'] == 'checkbox') {
			    $value = isset($form['key'][$setting['key']]) ? 1 : 0;
			} else {
			    $value = $form['key'][$setting['key']];
			}

			if ($setting['value']  != $value) {
			    $ret = $layout->setParameter($key, $value, $item->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null, null);
			    }
			}
		    }
		}

		$status = $module->translate('Successfully saved layout settings');
	    } else {
		foreach ($validationErrors as $validationKey => $validationMessage) {
		    $error[] = sprintf('form[error][key][%s][invalid]', $validationKey);
		    $errorMessage[$validationKey] = $validationMessage;
		}
		GalleryUtilities::putRequestVariable('form[errorMessage]', $errorMessage);
	    }
	} else if (isset($form['action']['undo'])) {
	    /*
	     * Take no action and we'll be redirected back to the same page which will reset
	     * the form
	     */
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;
	$ItemEditLayout = array();

	list ($ret, $layoutId) = GalleryCoreApi::fetchLayoutId($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($layout->isAdvancedSettings()) {
	    list ($ret, $tpl) = $layout->loadSettingsTemplate($template, $form, $item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ItemEditLayout['customTemplate'] = $tpl;
	    if ($form['formName'] != 'ItemEditLayout') {
		$form['formName'] = 'ItemEditLayout';
	    }
	} else {
	    /* Get the per-item settings (global + item) */
	    list ($ret, $settings) = $layout->getSettings($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Fetch the global-only params */
	    list ($ret, $globalParams) =
	    GalleryCoreApi::fetchAllPluginParameters('layout', $layout->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Fetch the item-only params */
	    list ($ret, $itemParams) =
	    GalleryCoreApi::fetchAllPluginParameters('layout', $layout->getId(), $item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($form['formName'] != 'ItemEditLayout') {
		$form['formName'] = 'ItemEditLayout';
		foreach ($settings as $setting) {
		    $key = $setting['key'];
		    $form['key'][$key] = $setting['value'];

		    /* If the key doesn't exist in the item params then it's a global setting */
		    $form['useGlobal'][$key] = isset($itemParams[$key]) ? 0 : 1;
		}
	    } else {
		/* Make sure all checkbox values are defined */
		foreach ($settings as $setting) {
		    $key = $setting['key'];
		    if (!isset($form['useGlobal'][$key])) {
			$form['useGlobal'][$key] = 0;
		    }
		}
	    }
	    $ItemEditLayout['settings'] = $settings;
	    $ItemEditLayout['globalParams'] = $globalParams;
	}

	$ItemEditLayout['layout']['name'] = $layout->getName();
	$ItemEditLayout['layout']['l10Domain'] = $layout->getL10Domain();

	$template->setVariable('ItemEditLayout', $ItemEditLayout);
	$template->setVariable('controller', 'core.ItemEditLayout');
	return array(GalleryStatus::success(), 'modules/core/templates/ItemEditLayout.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return (GalleryUtilities::isA($item, 'GalleryAlbumItem'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('Layout'));
    }
}
?>

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
 * This controller will handle the editing of a photo
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	list ($itemId, $editPlugin) = GalleryUtilities::getRequestVariables('itemId', 'editPlugin');

	/* Make sure we have permission do edit this item */
	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Check to see if we have a preferred source */
	list ($ret, $preferredTable) = GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$preferred = null;
	if (!empty($preferredTable[$item->getId()])) {
	    $preferred = $preferredTable[$item->getId()];
	}

	$status = array();
	$error = array();

	/* Load the correct edit plugin */
	list ($ret, $plugin) = GalleryCoreApi::newFactoryInstanceById('ItemEditPlugin', $editPlugin);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($plugin)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}

	list ($ret, $error, $statusMessage) = $plugin->handleRequest($form, $item, $preferred);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (empty($error)) {
	    $results['redirect'] = array('view' => 'core:ItemAdmin',
					 'subView' => 'core:ItemEdit',
					 'editPlugin' => $editPlugin,
					 'itemId' => $item->getId());
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemEdit';
	    $results['delegate']['editPlugin'] = $editPlugin;
	}

	$results['status'] = array();
	if (isset($statusMessage)) {
	    $results['status']['editMessage'] = $statusMessage;
	}
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show options to edit a photo
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($itemId, $editPlugin) = GalleryUtilities::getRequestVariables('itemId', 'editPlugin');

	/* Make sure we have permission do edit this item */
	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the thumbnail */
	list ($ret, $thumbnails) =
	    GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($thumbnails)) {
	    list ($ret, $thumbnail) =
		GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($thumbnails[$item->getId()]->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $thumbnail = null;
	}

	/* Get the edit plugins that support this item type */
	$allPluginIds = GalleryCoreApi::getAllFactoryImplementationIds('ItemEditPlugin');
	$pluginInstances = array();
	foreach (array_keys($allPluginIds) as $pluginId) {
	    list ($ret, $plugin) = GalleryCoreApi::newFactoryInstanceById('ItemEditPlugin', $pluginId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    if ($plugin->isSupported($item, $thumbnail)) {
		$pluginInstances[$pluginId] = $plugin;
	    }
	}

	/*
	 * If the plugin is empty get it from the session.  If it's empty there,
	 * default to the first plugin we find.  Either way, save the user's
	 * preference in the session.
	 */
	$session =& $gallery->getSession();
	$editPluginSessionKey = 'core.view.ItemEdit.editPlugin.' . get_class($item);
	if (empty($editPlugin)) {
	    $editPlugin = $session->get($editPluginSessionKey);
	    if (empty($editPlugin) || !in_array($editPlugin, array_keys($pluginInstances))) {
		$ids = array_keys($pluginInstances);
		$editPlugin = $ids[0];
	    }
	}
	$session->put($editPluginSessionKey, $editPlugin);

	/* Get display data for all plugins */
	$plugins = array();
	foreach ($pluginInstances as $pluginId => $plugin) {
	    list ($ret, $title) =  $plugin->getTitle();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $plugins[] = array('title' => $title,
			       'id' => $pluginId,
			       'isSelected' => ($pluginId == $editPlugin));
	}

	/* Record our item serial number in the form so that all plugins can use it */
	$form['serialNumber'] = $item->getSerialNumber();

	$ItemEdit = array();
	$ItemEdit['editPlugin'] = $editPlugin;
	$ItemEdit['plugins'] = $plugins;
	$ItemEdit['itemTypeNames'] = $item->itemTypeName();
	$ItemEdit['showEditThumbnail'] = $thumbnail != null;

	list ($ret, $ItemEdit['isAdmin']) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $ItemEdit['pluginFile']) =
	    $pluginInstances[$editPlugin]->loadTemplate($template, $form, $item, $thumbnail);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$template->setVariable('ItemEdit', $ItemEdit);
	$template->setVariable('controller', 'core:ItemEdit');
	return array(GalleryStatus::success(), array('body' => 'modules/core/templates/ItemEdit.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	global $gallery;

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $core) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$itemTypeNames = $item->itemTypeName(true);

	return array(GalleryStatus::success(), $core->translate(array('text' => 'edit %s',
								      'arg1' => $itemTypeNames[1])));
    }
}

/**
 * Interface for plugins to th ItemEdit view and controller
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditPlugin {
    /** 
     * Does this plugin support the given item type?
     *
     * @param the item
     * @param the item's thumbnail
     * @return boolean true if it's supported
     */
    function isSupported($item, $thumbnail) {
	return false;
    }

    /**
     * Load the template with data from this plugin
     * @see GalleryView::loadTemplate
     *
     * @param object GalleryTemplate the template instance
     * @param array the form values
     * @param the item
     * @param the item's thumbnail
     * @return array object GalleryStatus a status code
     *               string the path to a template file to include
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	return GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__);
    }

    /**
     * Let the plugin handle the incoming request
     * @see GalleryController::handleRequest
     *
     * @param array the form values
     * @param the item 
     * @param the item's preferred derivative, if there is one 
     * @return array object GalleryStatus a status code
     *               array error messages
     *               string status message
     */
    function handleRequest($form, &$item, &$preferred) {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null, null);
    }

    /**
     * Return a localized title for this plugin, suitable for display to the user
     *
     * @return array object GalleryStatus a status code
     *               return-array (same as GalleryController::handleRequest)
     */
    function getTitle() {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null);
    }
}
?>

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
 * This controller will handle the addition of an item as a children to
 * another item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	list ($itemId, $addPlugin) = GalleryUtilities::getRequestVariables('itemId', 'addPlugin');

	/* Make sure we have permission to add to this item */
	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLock($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the correct add plugin */
	list ($ret, $plugin) = GalleryCoreApi::newFactoryInstanceById('ItemAddPlugin', $addPlugin);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($plugin)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}

	list ($ret, $optionInstances) = ItemAddOption::getAllAddOptions();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $error, $status) = $plugin->handleRequest($form, $item, $optionInstances);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = GalleryCoreApi::releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (empty($error) && isset($status['addedFiles'])) {
	    $results['redirect'] = array('view' => 'core:ItemAdmin',
					 'subView' => 'core:ItemAddConfirmation',
					 'itemId' => $item->getId());
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemAdd';
	    $results['delegate']['addPlugin'] = $addPlugin;
	}

	$results['status'] = $status;
	$results['error'] = $error;
	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for files to add as children to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($itemId, $addPlugin) = GalleryUtilities::getRequestVariables('itemId', 'addPlugin');

	/* Make sure we have permission to add to this item */
	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $isAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get all the add plugins */
	$allPluginIds = GalleryCoreApi::getAllFactoryImplementationIds('ItemAddPlugin');
	$pluginInstances = array();
	foreach (array_keys($allPluginIds) as $pluginId) {
	    list ($ret, $plugin) = GalleryCoreApi::newFactoryInstanceById('ItemAddPlugin', $pluginId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $pluginInstances[$pluginId] = $plugin;
	}

	/* Get all the add options */
	list ($ret, $optionInstances) = ItemAddOption::getAllAddOptions();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * If the plugin is empty get it from the session.  If it's empty there,
	 * default to the first plugin we find.  Either way, save the user's
	 * preference in the session.
	 */
	$session =& $gallery->getSession();
	$addPluginSessionKey = 'core.view.ItemAdd.addPlugin.' . get_class($item);
	if (empty($addPlugin)) {
	    $addPlugin = $session->get($addPluginSessionKey);
	    if (empty($addPlugin)) {
		$ids = array_keys($pluginInstances);
		$addPlugin = $ids[0];
	    }
	}
	$session->put($addPluginSessionKey, $addPlugin);

	/* Get display data for all plugins */
	$plugins = array();
	foreach ($pluginInstances as $pluginId => $plugin) {
	    list ($ret, $title) =  $plugin->getTitle();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $plugins[] = array('title' => $title,
			       'id' => $pluginId,
			       'isSelected' => ($pluginId == $addPlugin));
	}

	$ItemAdd = array();
	$ItemAdd['addPlugin'] = $addPlugin;
	$ItemAdd['plugins'] = $plugins;
	$ItemAdd['isAdmin'] = $isAdmin;

	/* Let the plugin load its template data */
	list ($ret, $ItemAdd['pluginFile'], $ItemAdd['pluginL10Domain']) =
	    $pluginInstances[$addPlugin]->loadTemplate($template, $form, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Now let all options load their template data */
	$ItemAdd['options'] = array();
	foreach ($optionInstances as $option) {
	    list ($ret, $entry['file'], $entry['l10Domain']) =
		$option->loadTemplate($template, $form, $item);
	    $ItemAdd['options'][] = $entry;
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

 	/* Make sure that we've got some toolkits */
	list ($ret, $operations) = GalleryCoreApi::getToolkitOperations('image/jpeg');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ItemAdd['hasToolkit'] = false;
	for ($i = 0; $i < sizeof($operations); $i++) {
	    if ($operations[$i]['name'] == 'thumbnail') {
		$ItemAdd['hasToolkit'] = true;
		break;
	    }
	}

	$template->setVariable('ItemAdd', $ItemAdd);
	$template->setVariable('controller', 'core:ItemAdd');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemAdd.tpl'));
    }
}


/**
 * Interface for plugins to the ItemAdd view and controller
 * Plugins provide alternate ways to add items into Gallery.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddPlugin {

    /**
     * Load the template with data from this plugin
     * @see GalleryView::loadTemplate
     *
     * @param object GalleryTemplate the template instance
     * @param array the form values
     * @param the item
     * @return array object GalleryStatus a status code
     *               string the path to a template file to include
     *               string localization domain for the template file
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null);
    }

    /**
     * Let the plugin handle the incoming request
     * @see GalleryController::handleRequest
     *
     * @param array the form values
     * @param the item
     * @param array object ItemAddOption add options to apply to each item added
     * @return array object GalleryStatus a status code
     *               array error messages
     *               array files that were added: array(array('file' => '...', 'id' => ##), ...)
     */
    function handleRequest($form, &$item, $options) {
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

/**
 * Interface for options to the ItemAdd view and controller.
 * Options allow us to provide extra UI in the views and extra
 * processing in the controller so that we can add new functionality
 * like watermarking, quotas, etc to every ItemAddPlugin
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddOption {

    /**
     * Return all the available option plugins
     *
     * @return array object GalleryStatus a status code
     *               array object ItemAddOption instances
     * @static
     */
    function getAllAddOptions() {
	/* Get all the option plugins */
	$allOptionIds = GalleryCoreApi::getAllFactoryImplementationIds('ItemAddOption');
	$optionInstances = array();
	foreach (array_keys($allOptionIds) as $optionId) {
	    list ($ret, $option) = GalleryCoreApi::newFactoryInstanceById('ItemAddOption', $optionId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $isAppropriate) = $option->isAppropriate();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($isAppropriate) {
		$optionInstances[$optionId] = $option;
	    }
	}

	return array(GalleryStatus::success(), $optionInstances);
    }

    /**
     * Load the template with data from this plugin
     * @see GalleryView::loadTemplate
     *
     * @param object GalleryTemplate the template instance
     * @param array the form values
     * @param the item
     * @return array object GalleryStatus a status code
     *               string the path to a template file to include
     *               string localization domain for the template file
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null, null);
    }

    /**
     * Let the plugin handle the incoming request.  We expect the $item to be locked.
     * @see GalleryController::handleRequest
     *
     * @param array the form values
     * @param reference to the item
     * @return array object GalleryStatus a status code
     *               array localized error messages
     *               array localized warning messages
     */
    function handleRequestAfterAdd($form, &$item) {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null);
    }

    /**
     * Is this option appropriate at this time?
     *
     * @return array object GalleryStatus a status code
     *               boolean true or false
     */
    function isAppropriate() {
	return array(GalleryStatus::success(), false);
    }
}
?>

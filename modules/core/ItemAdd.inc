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
 * This controller will handle the addition of an item as a children to
 * another item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddController extends GalleryController {
    /**
     * ItemAddOption instances to use when handling this request.  Only used by
     * test code.
     *
     * @var array (optionId => object ItemAddOption) $_optionInstances
     * @private
     */
    var $_optionInstances;

    /**
     * Tests can use this method to hardwire a specific set of option instances to use.
     * This avoids situations where some of the option instances will do unpredictable
     * things and derail the tests.
     *
     * @param array (optionId => ItemAddOption, ...)
     */
    function setOptionInstances($optionInstances) {
	$this->_optionInstances = $optionInstances;
    }

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

	list ($ret, $error, $status) = $plugin->handleRequest($form, $item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (empty($error) && isset($status['addedFiles'])) {
	    if (isset($this->_optionInstances)) {
		$optionInstances = $this->_optionInstances;
	    } else {
		list ($ret, $optionInstances) = ItemAddOption::getAllAddOptions();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    $addedItems = array();
	    for ($i = 0; $i < count($status['addedFiles']); $i++) {
		$file =& $status['addedFiles'][$i];
		list ($ret, $addedItem) = GalleryCoreApi::loadEntitiesById($file['id']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Check if we should extract individual files out of an archive */
		if (GalleryUtilities::isA($addedItem, 'GalleryDataItem')) {
		    list ($ret, $toolkit) =
			GalleryCoreApi::getToolkitByOperation($addedItem->getMimeType(), 'extract');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		if (isset($toolkit)) {
		    list ($ret, $addedFiles) = $this->_extractAndAddFiles($addedItem, $toolkit);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $ret = GalleryCoreApi::deleteEntityById($addedItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    unset($status['addedFiles'][$i--]);
		    $status['addedFiles'] = array_merge($status['addedFiles'], $addedFiles);
		} else {
		    /* This is not an archive, add it to our array of item objects */
		    $addedItems[] = $addedItem;
		}
	    }

	    /* Allow ItemAddOptions to process added item(s) */
	    foreach ($optionInstances as $option) {
		list ($ret, $optionErrors, $optionWarnings) =
		    $option->handleRequestAfterAdd($form, $addedItems);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$error = array_merge($error, $optionErrors);
		/* for each item, put the items warnings into our status array */
		for ($j = 0; $j < count($optionWarnings); $j++) {
		    $status['addedFiles'][$j]['warnings'] =
			array_merge($status['addedFiles'][$j]['warnings'], $optionWarnings[$j]);
		}
	    }

	    $results['redirect'] = array('view' => 'core:ItemAdmin',
					 'subView' => 'core:ItemAddConfirmation',
					 'itemId' => $item->getId());
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemAdd';
	    $results['delegate']['addPlugin'] = $addPlugin;
	}

	$ret = GalleryCoreApi::releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results['status'] = $status;
	$results['error'] = $error;
	return array(GalleryStatus::success(), $results);
    }

    /**
     * Extract files from an archive item and add new items to the same album.
     * @param object GalleryDataItem archive
     * @param object GalleryToolkit toolkit that supports extract operation
     * @return array object GalleryStatus a status code
     *               array of array('fileName' => '..', 'id' => ##, 'warnings' => array of string)
     * @private
     */
    function _extractAndAddFiles($archiveItem, $toolkit) {
	global $gallery;
	$platform = $gallery->getPlatform();

	list ($ret, $file) = $archiveItem->fetchPath();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$base = $platform->tempnam($gallery->getConfig('data.gallery.tmp'), 'tmp_');
	$tmpDir = $base . '.dir';
	if (!$platform->mkdir($tmpDir)) {
	    return array(GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__), null);
	}

	list ($ret) = $toolkit->performOperation($archiveItem->getMimeType(), 'extract',
						 $file, $tmpDir, array());
	if ($ret->isError()) {
	    @$platform->recursiveRmdir($tmpDir);
	    @$platform->unlink($base);
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$list = array();
	$dh = $platform->opendir($tmpDir);
	while (($file = $platform->readdir($dh)) !== false) {
	    if ($platform->is_file("$tmpDir/$file")) {
		$list[] = "$tmpDir/$file";
	    }
	}
	$platform->closedir($dh);

	/*
	 * If archive title matches the filename or base filename then name new items
	 * with the same strategy; otherwise just use the archive title.
	 */
	$archiveTitle = $title = $archiveItem->getTitle();
	$archiveName = $archiveItem->getPathComponent();
	list ($archiveBase) = GalleryUtilities::getFileNameComponents($archiveName);

	$addedFiles = array();
	foreach ($list as $file) {
	    $extension = GalleryUtilities::getFileExtension($file);
	    list ($ret, $mimeType) = GalleryCoreApi::convertExtensionToMime($extension);
	    if ($ret->isError()) {
		$mimeType = 'application/unknown';
	    }
	    $filename = basename($file);
	    if ($archiveTitle == $archiveName) {
		$title = $filename;
	    } else if ($archiveTitle == $archiveBase) {
		list ($title) = GalleryUtilities::getFileNameComponents($filename);
	    }
	    list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum(
		$file, $filename, $title, $archiveItem->getSummary(),
		$archiveItem->getDescription(), $mimeType, $archiveItem->getParentId());
	    if ($ret->isError()) {
		@$platform->recursiveRmdir($tmpDir);
		@$platform->unlink($base);
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $addedFiles[] = array('fileName' => basename($file), 'id' => $newItem->getId(),
				  'warnings' => array());
	}

	@$platform->recursiveRmdir($tmpDir);
	@$platform->unlink($base);

	return array(GalleryStatus::success(), $addedFiles);
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
	list ($ret, $allPluginIds) =
	    GalleryCoreApi::getAllFactoryImplementationIds('ItemAddPlugin');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$pluginInstances = array();
	foreach (array_keys($allPluginIds) as $pluginId) {
	    list ($ret, $plugin) =
		GalleryCoreApi::newFactoryInstanceById('ItemAddPlugin', $pluginId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $isAppropriate) = $plugin->isAppropriate();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($isAppropriate) {
		$pluginInstances[$pluginId] = $plugin;
	    }
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
	if (empty($addPlugin) || !isset($pluginInstances[$addPlugin])) {
	    $addPlugin = $session->get($addPluginSessionKey);
	    if (empty($addPlugin) || !isset($pluginInstances[$addPlugin])) {
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
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!empty($entry['file'])) {
		$ItemAdd['options'][] = $entry;
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
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null, null);
    }

    /**
     * Let the plugin handle the incoming request
     * @see GalleryController::handleRequest
     *
     * @param array the form values
     * @param the item
     * @return array object GalleryStatus a status code
     *               array error messages
     *               array status data, 'addedFiles' entry should contain:
     *                                   array(array('fileName' => '...', 'id' => ##,
     *                                               'warnings' => array of strings), ...)
     */
    function handleRequest($form, &$item) {
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

    /**
     * Is this plugin appropriate at this time?  Default is true.
     *
     * @return array object GalleryStatus a status code
     *               boolean true or false
     */
    function isAppropriate() {
	return array(GalleryStatus::success(), true);
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
	list ($ret, $allOptionIds) =
	    GalleryCoreApi::getAllFactoryImplementationIds('ItemAddOption');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$optionInstances = array();
	foreach (array_keys($allOptionIds) as $optionId) {
	    list ($ret, $option) =
		GalleryCoreApi::newFactoryInstanceById('ItemAddOption', $optionId);
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
	return array(GalleryStatus::success(), null, null);
    }

    /**
     * Let the plugin handle the incoming request.  We expect the $item to be locked.
     * @see GalleryController::handleRequest
     *
     * @param array the form values
     * @param array GalleryDataItem
     * @return array object GalleryStatus a status code
     *               array localized error messages
     *               array localized warning messages
     */
    function handleRequestAfterAdd($form, $items) {
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

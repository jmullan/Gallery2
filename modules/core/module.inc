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
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * The implementation of the core-module
 *
 * @package GalleryCore
 */
class CoreModule extends GalleryModule {

    function CoreModule() {
	global $gallery;

	$this->setId('core');
	$this->setName($gallery->i18n('Core'));
	$this->setGalleryVersion('2.0-beta-3+');
	$this->setVersion('0.9.25'); /*Update CoreModuleExtras::upgrade,_prepareConfigUpgrade too!*/
	$this->setDescription($gallery->i18n('Gallery 2 Core Module'));
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('registerEventListeners|' .
			    'getItemLinks|getSystemLinks|loadSystemContent|' .
			    'getSiteAdminViews|getUserAdminViews|getItemAdminViews');
	$this->setRequiredCoreApi(array(6, 2));
	$this->setRequiredModuleApi(array(1, 0));
    }

    /**
     * @see GalleryModule::registerEventListeners();
     */
    function registerEventListeners() {
	GalleryCoreApi::relativeRequireOnce(
	    'modules/core/classes/helpers/GalleryItemHelper_medium.class');
	GalleryCoreApi::registerEventListener('Gallery::ViewableTreeChange',
					      new GalleryItemHelper_medium());
	GalleryCoreApi::registerEventListener('Gallery::RemovePermission',
					      new GalleryItemHelper_medium());
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items, $wantsDetailedLinks, $permissions) {
	list ($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Fetch child counts */
	$itemIds = array();
	foreach ($items as $item) {
	    $itemIds[] = $item->getId();
	}

	/*
	 * We're not doing this as the acting user id, but that's ok because we're not displaying
	 * the result; we're only using it as a gating factor for whether or not we show a link,
	 * and that'll also be gated by the permissions we receive which *will* be for the acting
	 * user.
	 */
	list ($ret, $childCounts) = GalleryCoreApi::fetchChildCounts($itemIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Fetch thumbnail ids */
	list ($ret, $thumbTable) =
	    GalleryCoreApi::fetchThumbnailsByItemIds($itemIds, DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$links = array();
	foreach ($items as $item) {
	    $itemId = $item->getId();
	    $isRoot = ($itemId == $rootId);
	    $isAlbum = $item->getCanContainChildren();

	    /* Permissions for its parent */
	    list ($ret, $parentPermissions) = GalleryCoreApi::getPermissions($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($wantsDetailedLinks[$itemId]) && $isAlbum &&
		    isset($permissions[$itemId]['core.addDataItem'])) {
		$links[$itemId][] =
		    array('text' => $this->translate('add items'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemAdd',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    $itemTypeNames = $item->itemTypeName();
	    if (isset($permissions[$itemId]['core.edit'])) {
		$links[$itemId][] =
		    array('text' => $this->translate(array('text' => 'edit %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemEdit',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    if (isset($wantsDetailedLinks[$itemId]) &&
		    isset($permissions[$itemId]['core.viewSource']) &&
		    GalleryCapabilities::can('link')) {
		if ($item->getIsLinkable()) {
		    if ($isAlbum) {
			list ($ret, $count) = GalleryCoreApi::fetchItemIdCount(
			    'GalleryAlbumItem', 'core.addAlbumItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			list ($ret, $count) = GalleryCoreApi::fetchItemIdCount(
			    'GalleryAlbumItem', 'core.addDataItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    if ($count > 0) {
			$links[$itemId][] =
			    array('text' => $this->translate('create link'),
				  'params' => array('view' => 'core.ItemAdmin',
						    'subView' => 'core.ItemCreateLink',
						    'itemId' => $item->getParentId(),
						    'selectedId' => $itemId,
						    'return' => 1));
		    }
		}
	    }

	    if (isset($wantsDetailedLinks[$itemId]) &&
		    $isAlbum && isset($permissions[$itemId]['core.addAlbumItem'])) {
		$links[$itemId][] =
		    array('text' => $this->translate('add album'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemAddAlbum',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    if (isset($permissions[$itemId]['core.changePermissions'])) {
		$links[$itemId][] =
		    array('text' => $this->translate('edit permissions'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemPermissions',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    if (!$isRoot && isset($permissions[$itemId]['core.delete'])) {
		$links[$itemId][] =
		    array('text' => $this->translate(array('text' => 'delete %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemDelete',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $itemId,
					    'return' => 1));
	    }

	    if (!$isRoot && isset($permissions[$itemId]['core.delete'])) {
		$links[$itemId][] =
		    array('text' => $this->translate(array('text' => 'move %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemMove',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $itemId,
					    'return' => 1));
	    }

	    if (isset($wantsDetailedLinks[$itemId]) &&
		    $isAlbum &&
		    isset($permissions[$itemId]['core.edit']) &&
		    !empty($childCounts[$itemId]) &&
		    $childCounts[$itemId] > 0) {
		$links[$itemId][] =
		    array('text' => $this->translate('edit captions'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemEditCaptions',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    if (!$isRoot && isset($thumbTable[$itemId]) &&
		    isset($permissions[$itemId]['core.edit'])) {
		$links[$itemId][] =
		    array('text' => $this->translate('make highlight'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemMakeHighlight',
					    'itemId' => $itemId,
					    'return' => 1));
	    }

	    if ($isAlbum && isset($permissions[$itemId]['core.edit']) &&
		    !empty($childCounts[$itemId]) &&
		    $childCounts[$itemId] > 1) {
		$links[$itemId][] =
		    array('text' => $this->translate('reorder items'),
			  'params' => array('view' => 'core.ItemAdmin',
					    'subView' => 'core.ItemReorder',
					    'itemId' => $itemId,
					    'return' => 1));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks() {
	global $gallery;

	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$links = array();
	list ($ret, $isAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($isAdmin) {
	    $links[] = array('text' => $this->translate('Site Admin'),
			     'params' => array('view' => 'core.SiteAdmin',
					       'return' => 1));
	}

	if (GalleryCapabilities::can('login')) {
	    if ($gallery->getActiveUserId() == $param['id.anonymousUser']) {
		if ($param['misc.login'] != 'form') {
		    $links[] = array('text' => $this->translate('Login'),
				     'params' => array('view' => 'core.UserAdmin',
						       'subView' => 'core.UserLogin',
						       'return' => 1));
		}
	    } else {
		$links[] = array('text' => $this->translate('Your Account'),
				 'params' => array('view' => 'core.UserAdmin',
						   'subView' => 'core.UserPreferences',
						   'return' => 1));
		$links[] = array('text' => $this->translate('Logout'),
				 'params' => array('controller' => 'core.Logout',
						   'return' => 1));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	global $gallery;
	$content = array();

	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Need a login form? */
	$anonymousUserId = $param['id.anonymousUser'];
	if ($gallery->getActiveUserId() == $anonymousUserId
		&& GalleryCapabilities::can('login') && $param['misc.login'] != 'link') {
	    $content['login'] = 'modules/core/templates/LoginSystemContent.tpl';
	}

	/* Get the language selector */
	$languageSelector = $param['language.selector'];
	if ($languageSelector == 'all' || ($languageSelector == 'guest'
		&& $gallery->getActiveUserId() == $anonymousUserId)) {
	    /* Set up our language selection list */
	    $languageList = array();
	    $translator =& $gallery->getTranslator();
	    $supportedLanguages = $translator->getSupportedLanguages();
	    foreach ($supportedLanguages as $language => $countryList) {
		foreach ($countryList as $country => $languageData) {
		    $languageList[$language . '_' . $country] = $languageData['description'];
		}
	    }

	    list ($ret, $language) = $gallery->getActiveLanguageCode();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $LanguageSelector = array('list' => $languageList, 'language' => $language);

	    $template->setVariable('LanguageSelector', $LanguageSelector);
	    $content['languageSelector'] = 'modules/core/templates/LanguageSelector.tpl';
	}

	return array(GalleryStatus::success(), $content);
    }

    /**
     * @see GalleryModule::getSiteAdminViews();
     */
    function getSiteAdminViews() {
	$data = array(array('name' => $this->translate('General'),
			    'view' => 'core.AdminCore'),
		      array('name' => $this->translate('Modules'),
			    'view' => 'core.AdminModules'),
		      array('name' => $this->translate('Layouts and Themes'),
			    'view' => 'core.AdminLayouts',
			    'group' => 'display',
			    'groupLabel' => $this->translate('Display')),
		      array('name' => $this->translate('Users'),
			    'view' => 'core.AdminUsers'),
		      array('name' => $this->translate('Groups'),
			    'view' => 'core.AdminGroups'),
		      array('name' => $this->translate('Maintenance'),
			    'view' => 'core.AdminMaintenance'),
		      );
	list ($ret, $list) = GalleryCoreApi::getRedundantToolkitPriorities();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($list)) {
	    $data[] = array('name' => $this->translate('Toolkit Priority'),
			    'view' => 'core.AdminToolkitPriority',
			    'group' => 'toolkits',
			    'groupLabel' => $this->translate('Graphics Toolkits'));
	}
	return array(GalleryStatus::success(), $data);
    }

    /**
     * @see GalleryModule::getUserAdminViews();
     */
    function getUserAdminViews($user) {
	$views = array();

	if (GalleryCapabilities::can('login')) {
	    list ($ret, $anonymousUserId) = $this->getParameter('id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($user->getId() != $anonymousUserId) {
		$views[] = array('name' => $this->translate('Account Settings'),
				 'view' => 'core.UserPreferences');
		$views[] = array('name' => $this->translate('Change Password'),
				 'view' => 'core.UserChangePassword');
	    } else {
		$views[] = array('name' => $this->translate('Login'),
				 'view' => 'core.UserLogin');
	    }
	}

	return array(GalleryStatus::success(), $views);
    }

    /**
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	$views = array();
	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$isAlbum = $item->getCanContainChildren();
	if ($isAlbum) {
	    list ($ret, $childCounts) = GalleryCoreApi::fetchChildCounts(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $childCount = empty($childCounts[$item->getId()]) ? 0 : $childCounts[$item->getId()];
	} else {
	    $childCount = 0;
	}

	/* Fetch thumbnail ids */
	list ($ret, $thumbTable) =
	    GalleryCoreApi::fetchDerivativesBySourceIds(array($item->getId()),
							DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$hasThumb = !empty($thumbTable[$item->getId()]);

	$parentId = $item->getParentId();
	list ($ret, $parentPermissions) = GalleryCoreApi::getPermissions($parentId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$itemTypeNames = $item->itemTypeName();
	if (isset($permissions['core.edit'])) {
	    if ($isAlbum) {
		if ($childCount > 1) {
		    $views[] = array('name' => $this->translate('Reorder Items'),
				     'view' => 'core.ItemReorder');
		}
	    }

	    /* Edit view for all item types */
	    $views[] = array('name' => $this->translate(
					array('text' => 'Edit %s', 'arg1' => $itemTypeNames[0])),
			     'view' => 'core.ItemEdit');

	    if (!empty($parentId) && $hasThumb && $parentId != $rootId
		    && isset($parentPermissions['core.edit'])) {
		$views[] = array('name' => $this->translate('Make Highlight'),
				 'view' => 'core.ItemMakeHighlight');
	    }
	}

	if (isset($permissions['core.viewSource']) && GalleryCapabilities::can('link')) {
	    if ($item->getIsLinkable()) {
		if ($isAlbum) {
		    list ($ret, $count) =
			GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addAlbumItem');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    list ($ret, $count) =
			GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addDataItem');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		if ($count > 0) {
		    $views[] = array('name' => $this->translate(
					array('text' => 'Link %s', 'arg1' => $itemTypeNames[0])),
				     'view' => 'core.ItemCreateLinkSingle');
		}
	    }
	}

	if (isset($permissions['core.delete'])) {
	    if ($item->getId() != $rootId) {
		$views[] = array('name' => $this->translate(
					array('text' => 'Delete %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core.ItemDeleteSingle');

		$views[] = array('name' => $this->translate(
					array('text' => 'Move %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core.ItemMoveSingle');
	    }
	}

	if (isset($permissions['core.changePermissions'])) {
	    $views[] = array('name' => $this->translate('Edit Permissions'),
			     'view' => 'core.ItemPermissions');
	}

	if (isset($permissions['core.addDataItem'])) {
	    if ($item->getCanContainChildren()) {
		$views[] = array('name' => $this->translate('Add Items'),
				 'view' => 'core.ItemAdd');
	    }
	}

	if (isset($permissions['core.addAlbumItem'])) {
	    if ($item->getCanContainChildren()) {
		$views[] = array('name' => $this->translate('Add Album'),
				 'view' => 'core.ItemAddAlbum');
	    }
	}

	return array(GalleryStatus::success(), $views);
    }

    /**
     * @see GalleryModule::install
     *
     * We pushed all this code into its own file since we need it very rarely so it doesn't
     * make sense to load it every single time.
     */
    function upgrade($currentVersion, $statusMonitor) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/CoreModuleExtras.inc');
	$ret = CoreModuleExtras::upgrade($this, $currentVersion, $statusMonitor);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Set the current version of Gallery
     */
    function setGalleryVersion($version) {
	$this->_galleryVersion = $version;
    }

    /**
     * Get the current version of Gallery
     */
    function getGalleryVersion() {
	return $this->_galleryVersion;
    }

    /**
     * Get the version of the core module and of Gallery itself.  We store this
     * on disk to avoid having to load up the database (which can be problematic
     * if we're doing an upgrade and don't want to count a specific database
     * schema.
     *
     * @return array 'core' => core module version, 'gallery' => gallery version
     * @static
     */
    function getInstalledVersions() {
	global $gallery;
	static $versions;

	if (!isset($versions)) {
	    $platform = $gallery->getPlatform();
	    $baseDir = $gallery->getConfig('data.gallery.base');
	    $versionFile = sprintf('%s%s%s',
				   $baseDir,
				   $platform->getDirectorySeparator(),
				   'versions.dat');

	    $moduleVersion = null;
	    $galleryVersion = null;
	    if ($platform->file_exists($versionFile)) {
		$versionArray = $platform->file($versionFile);
		if (count($versionArray) >= 2) {
		    $versions['core'] = rtrim($versionArray[0]);
		    $versions['gallery'] = rtrim($versionArray[1]);
		}
	    }
	}

	return $versions;
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/CoreModuleExtras.inc');
	$ret = CoreModuleExtras::performFactoryRegistrations($this);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }
}
?>

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
	$this->setName('Core');
	$this->setGalleryVersion('2.0-alpha-4');
	$this->setVersion('0.8.4');
	$this->setDescription($gallery->i18n('Gallery 2 Core Module'));
	$this->setGroup('gallery', $gallery->i18n('Gallery'));
	$this->setCallbacks('registerEventListeners|performFactoryRegistrations|' .
			    'getItemLinks|getSystemLinks|loadSystemContent|' .
			    'getSiteAdminViews|getUserAdminViews|getItemAdminViews');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
	/*
	 * We can't set our description until we have a $gallery object so
	 * that we can call $gallery->i18n().  Defer this to the bootstrap code.
	 */
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our entity implementations */
	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryEntity',
						      'GalleryEntity',
						      $classDir . 'GalleryEntity.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryChildEntity',
						      'GalleryChildEntity',
						      $classDir . 'GalleryChildEntity.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryAlbumItem',
						      'GalleryAlbumItem',
						      $classDir . 'GalleryAlbumItem.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryUser',
						      'GalleryUser',
						      $classDir . 'GalleryUser.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryGroup',
						      'GalleryGroup',
						      $classDir . 'GalleryGroup.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryDerivative',
						      'GalleryDerivative',
						      $classDir . 'GalleryDerivative.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryDerivativeImage',
						      'GalleryDerivativeImage',
						      $classDir . 'GalleryDerivativeImage.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryDerivative',
						      'GalleryDerivativeImage',
						      'GalleryDerivativeImage',
						      $classDir . 'GalleryDerivativeImage.class',
						      array('*'));

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryMovieItem',
						      'GalleryMovieItem',
						      $classDir . 'GalleryMovieItem.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryAnimationItem',
						      'GalleryAnimationItem',
						      $classDir . 'GalleryAnimationItem.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryPhotoItem',
						      'GalleryPhotoItem',
						      $classDir . 'GalleryPhotoItem.class');

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryUnknownItem',
						      'GalleryUnknownItem',
						      $classDir . 'GalleryUnknownItem.class');

	/* Register GalleryItem implementations */
	GalleryCoreApi::registerFactoryImplementation('GalleryItem',
						      'GalleryPhotoItem',
						      'GalleryPhotoItem',
						      $classDir . 'GalleryPhotoItem.class',
						      array('image/*'));

	GalleryCoreApi::registerFactoryImplementation('GalleryItem',
						      'GalleryMovieItem',
						      'GalleryMovieItem',
						      $classDir . 'GalleryMovieItem.class',
						      array('video/x-msvideo',
							    'video/quicktime',
							    'video/mpeg',
							    'video/x-ms-asf',
							    'video/x-ms-wmv'));

	GalleryCoreApi::registerFactoryImplementation('GalleryItem',
						      'GalleryAnimationItem',
						      'GalleryAnimationItem',
						      $classDir . 'GalleryAnimationItem.class',
						      array('application/x-director',
							    'application/x-shockwave-flash'));

	GalleryCoreApi::registerFactoryImplementation('GalleryItem',
						      'GalleryUnknownItem',
						      'GalleryUnknownItem',
						      $classDir . 'GalleryUnknownItem.class',
						      array('*'));

	/* Register our search implementation */
	GalleryCoreApi::registerFactoryImplementation('GallerySearchInterface_1_0',
						      'GalleryCoreSearch',
						      'core',
						      $classDir . 'GalleryCoreSearch.class');

	/* Register our item edit plugins */
	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditItem',
						      'ItemEditItem',
						      dirname(__FILE__) . '/ItemEditItem.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditAnimation',
						      'ItemEditAnimation',
						      dirname(__FILE__) . '/ItemEditAnimation.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditMovie',
						      'ItemEditMovie',
						      dirname(__FILE__) . '/ItemEditMovie.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditAlbum',
						      'ItemEditAlbum',
						      dirname(__FILE__) . '/ItemEditAlbum.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditLayout',
						      'ItemEditLayout',
						      dirname(__FILE__) . '/ItemEditLayout.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditRotateAndScalePhoto',
						      'ItemEditRotateAndScalePhoto',
						      dirname(__FILE__) . '/ItemEditRotateAndScalePhoto.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditPhotoSizes',
						      'ItemEditPhotoSizes',
						      dirname(__FILE__) . '/ItemEditPhotoSizes.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'ItemEditPhotoThumbnail',
						      'ItemEditPhotoThumbnail',
						      dirname(__FILE__) . '/ItemEditPhotoThumbnail.inc');

	/* Register our item add plugins */
	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddFromBrowser',
						      'ItemAddFromBrowser',
						      dirname(__FILE__) . '/ItemAddFromBrowser.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddFromServer',
						      'ItemAddFromServer',
						      dirname(__FILE__) . '/ItemAddFromServer.inc');

	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddFromWeb',
						      'ItemAddFromWeb',
						      dirname(__FILE__) . '/ItemAddFromWeb.inc');

	/* Register our item add plugins */
	GalleryCoreApi::registerFactoryImplementation('ItemAddOption',
						      'CreateThumbnailOption',
						      'CreateThumbnailOption',
						      dirname(__FILE__) . '/CreateThumbnailOption.inc');
    }

    /**
     * @see GalleryModule::registerEventListeners();
     */
    function registerEventListeners() {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/helpers/GalleryItemHelper_medium.class');
	GalleryCoreApi::registerEventListener('Gallery::ViewableTreeChange',
					      new GalleryItemHelper_medium());

    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items) {
	global $gallery;

	list ($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Fetch child counts */
	$itemIds = array();
	foreach ($items as $item) {
	    $itemIds[] = $item->getId();
	}
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
	    /* Permissions for this item */
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $isRoot = ($item->getId() == $rootId);
	    $isParentRoot = ($item->getParentId() == $rootId);
	    $isAlbum = $item->getCanContainChildren();

	    /* Permissions for its parent */
	    list ($ret, $parentPermissions) = GalleryCoreApi::getPermissions($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($isAlbum && isset($permissions['core.addDataItem'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('add items'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemAdd',
					    'itemId' => $item->getId(),
					    'return' => 1));
	    }

	    $itemTypeNames = $item->itemTypeName();
	    if (isset($permissions['core.edit'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'edit %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemEdit',
					    'itemId' => $item->getId(),
					    'return' => 1));
	    }

	    if (isset($permissions['core.viewSource']) && GalleryCapabilities::can('link')) {
		if ($item->getIsLinkable()) {
		    if ($isAlbum) {
			list ($ret, $count) = GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addAlbumItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    } else {
			list ($ret, $count) = GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addDataItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    if ($count > 0) {
			$links[$item->getId()][] =
			    array('text' => $this->translate('create link'),
				  'params' => array('view' => 'core:ItemAdmin',
						    'subView' => 'core:ItemCreateLink',
						    'itemId' => $item->getParentId(),
						    'selectedId' => $item->getId(),
						    'return' => 1));
		    }
		}
	    }

	    if ($isAlbum && isset($permissions['core.addAlbumItem'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('add sub-album'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemAddAlbum',
					    'itemId' => $item->getId(),
					    'return' => 1));
	    }

	    if (isset($permissions['core.changePermissions'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('edit permissions'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemPermissions',
					    'itemId' => $item->getId(),
					    'return' => 1));
	    }

	    if (!$isRoot && isset($permissions['core.delete'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'delete %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemDelete',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $item->getId(),
					    'return' => 1));
	    }

	    if (!$isRoot && isset($permissions['core.delete'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'move %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemMove',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $item->getId(),
					    'return' => 1));
	    }

	    if (!$isRoot && !$isParentRoot && isset($thumbTable[$item->getId()]) && isset($permissions['core.edit'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('make highlight'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemMakeHighlight',
					    'itemId' => $item->getId(),
					    'return' => 1));
	    }

	    if ($isAlbum && isset($permissions['core.edit']) &&
		!empty($childCounts[$item->getId()]) &&
		$childCounts[$item->getId()] > 1) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('reorder items'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemReorder',
					    'itemId' => $item->getId(),
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
			     'params' => array('view' => 'core:SiteAdmin',
					       'return' => 1));
	}

	if (GalleryCapabilities::can('login')) {
	    if ($gallery->getActiveUserId() == $param['id.anonymousUser']) {
		if ($param['misc.login'] != 'form') {
		    $links[] = array('text' => $this->translate('Login'),
				     'params' => array('view' => 'core:UserAdmin',
						       'subView' => 'core:UserLogin',
						       'return' => 1));
		}
	    } else {
		$links[] = array('text' => $this->translate('Your Account'),
				 'params' => array('view' => 'core:UserAdmin',
						   'subView' => 'core:UserPreferences',
						   'return' => 1));
		$links[] = array('text' => $this->translate('Logout'),
				 'params' => array('controller' => 'core:Logout',
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
			    'view' => 'core:AdminCore'),
		      array('name' => $this->translate('Modules'),
			    'view' => 'core:AdminModules'),
		      array('name' => $this->translate('Layouts and Themes'),
			    'view' => 'core:AdminLayouts',
			    'group' => 'display',
			    'groupLabel' => $this->translate('Display')),
		      array('name' => $this->translate('Users'),
			    'view' => 'core:AdminUsers'),
		      array('name' => $this->translate('Groups'),
			    'view' => 'core:AdminGroups')
		      );
	list ($ret, $list) = GalleryCoreApi::getRedundantToolkitPriorities();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($list)) {
	    $data[] = array('name' => $this->translate('Toolkit Priority'),
			    'view' => 'core:AdminToolkitPriority',
			    'group' => 'toolkits',
			    'groupLabel' => $this->translate('Graphics Toolkits'));
	}
	return array(GalleryStatus::success(), $data);
    }

    /**
     * @see GalleryModule::getUserAdminViews();
     */
    function getUserAdminViews($user) {
	global $gallery;

	$views = array();

	if (GalleryCapabilities::can('login')) {
	    list ($ret, $anonymousUserId) = $this->getModuleParameter('id.anonymousUser');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($user->getId() != $anonymousUserId) {
	        $views[] = array('name' => $this->translate('Account Settings'),
				 'view' => 'core:UserPreferences');
	        $views[] = array('name' => $this->translate('Change Password'),
				 'view' => 'core:UserChangePassword');
	    } else {
	        $views[] = array('name' => $this->translate('Login'),
				 'view' => 'core:UserLogin');
	    }
	}

	return array(GalleryStatus::success(), $views);
    }

    /**
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	global $gallery;

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
				     'view' => 'core:ItemReorder');
		}
	    }

	    /* Edit view for all item types */
	    $views[] = array('name' => $this->translate(array('text' => 'Edit %s', 'arg1' => $itemTypeNames[0])),
			     'view' => 'core:ItemEdit');

	    if (!empty($parentId) && $hasThumb && $parentId != $rootId && isset($parentPermissions['core.edit'])) {
		$views[] = array('name' => $this->translate('Make Highlight'),
				 'view' => 'core:ItemMakeHighlight');
	    }
	}

	if (isset($permissions['core.viewSource']) && GalleryCapabilities::can('link')) {
	    if ($item->getIsLinkable()) {
		if ($isAlbum) {
		    list ($ret, $count) = GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addAlbumItem');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    list ($ret, $count) = GalleryCoreApi::fetchItemIdCount('GalleryAlbumItem', 'core.addDataItem');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		if ($count > 0) {
		    $views[] = array('name' => $this->translate(array('text' => 'Link %s', 'arg1' => $itemTypeNames[0])),
				     'view' => 'core:ItemCreateLinkSingle');
		}
	    }
	}

	if (isset($permissions['core.delete'])) {
	    if ($item->getId() != $rootId) {
		$views[] = array('name' => $this->translate(array('text' => 'Delete %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core:ItemDeleteSingle');

		$views[] = array('name' => $this->translate(array('text' => 'Move %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core:ItemMoveSingle');
	    }
	}

	if (isset($permissions['core.changePermissions'])) {
	    $views[] = array('name' => $this->translate('Edit Permissions'),
			     'view' => 'core:ItemPermissions');
	}

	if (isset($permissions['core.addDataItem'])) {
	    if ($item->getCanContainChildren()) {
	        $views[] = array('name' => $this->translate('Add Items'),
				 'view' => 'core:ItemAdd');
	    }
	}

	if (isset($permissions['core.addAlbumItem'])) {
	    if ($item->getCanContainChildren()) {
	        $views[] = array('name' => $this->translate('Add Sub-Album'),
				 'view' => 'core:ItemAddAlbum');
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
    function upgrade($currentVersion) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/CoreModuleExtras.inc');
	$ret = CoreModuleExtras::upgrade($this, $currentVersion);
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
}
?>

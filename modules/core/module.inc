<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
 * Bootstrap code: We have to load a few classes just so that the GalleryModule
 * parent class exists. This is only because we are the core module; other
 * modules should not have to do stuff like this.
 */
$classDir = dirname(__FILE__) . '/classes/';
require_once($classDir . 'GalleryModule.class');

/**
 * The implementation of the core-module
 *
 * @package GalleryCore
 */
class CoreModule extends GalleryModule {

    function CoreModule() {
	$this->setName('core');
	$this->setDescription('Core Gallery functionality');
	$this->setVersion('1.0');
    }

    /**
     * This method is not in GalleryModule.  It's a special method for the
     * CoreModule that allows us to bootstrap G2 far enough up so that we can
     * actually install and initialize the core.  It has no dependencies, so it
     * can be safely called right at the very beginning of the G2 code.
     *
     * @return object GalleryStatus a status code
     */
    function bootstrap() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Load all the core Gallery classes */
	require_once($classDir . 'Gallery.class');
	require_once($classDir . 'GalleryChildEntityHelper.class');
	require_once($classDir . 'GalleryController.class');
	require_once($classDir . 'GalleryDataCache.class');
	require_once($classDir . 'GalleryDerivativeHelper.class');
	require_once($classDir . 'GalleryDerivativePreferencesMap.class');
	require_once($classDir . 'GalleryEvent.class');
	require_once($classDir . 'GalleryEventListener.class');
	require_once($classDir . 'GalleryFileSystemEntityHelper.class');
	require_once($classDir . 'GalleryItemPropertiesMap.class');
	require_once($classDir . 'GalleryItemHelper.class');
	require_once($classDir . 'GalleryLayout.class');
	require_once($classDir . 'GalleryLock.class');
	require_once($classDir . 'GalleryModuleMap.class');
	require_once($classDir . 'GalleryModuleParameterMap.class');
	require_once($classDir . 'GalleryPermissionSetMap.class');
	require_once($classDir . 'GalleryPermissionMap.class');
	require_once($classDir . 'GalleryProfiler.class');
	require_once($classDir . 'GallerySession.class');
	require_once($classDir . 'GalleryStatus.class');
	require_once($classDir . 'GalleryTemplate.class');
	require_once($classDir . 'GalleryTemplateModule.class');
	require_once($classDir . 'GalleryTemplateAdapter.class');
	require_once($classDir . 'GalleryTheme.class');
	require_once($classDir . 'GalleryToolkitHelper.class');
	require_once($classDir . 'GalleryUserGroupMap.class');
	require_once($classDir . 'GalleryUserHelper.class');
	require_once($classDir . 'GalleryGroupHelper.class');
	require_once($classDir . 'GalleryUtilities.class');
	require_once($classDir . 'GalleryUrlGenerator.class');
	require_once($classDir . 'GalleryView.class');
	require_once($classDir . 'GalleryFactory.class');
	require_once($classDir . 'GalleryItemAttributesMap.class');

	/*
	 * Set up our Gallery global.  It's important to use a reference here because
	 * the constructor registers a shutdown function and ties it to the instance in
	 * the constructor.  This global should be the only one that Gallery requires.
	 * Everything else should be inside it so that we do not pollute the namespace
	 * (especially important when we're embedded inside another application).
	 */
	$gallery =& new Gallery();
	$GLOBALS['gallery'] =& $gallery;
	$gallery->setCoreModule($this);

	/* Configure the Platform */
	$gallery->setConfig('platform.type', strtolower(PHP_OS));

	/* Register platform implementations */
	GalleryFactory::registerImplementation('GalleryPlatform',
					       'UnixPlatform',
					       'Unix',
					       $classDir . 'GalleryPlatform/UnixPlatform.class',
					       array('unix', '*'));

	GalleryFactory::registerImplementation('GalleryPlatform',
					       'WinNtPlatform',
					       'WinNT',
					       $classDir . 'GalleryPlatform/WinNtPlatform.class',
					       array('winnt'));

	/* Register our entity implementations */
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryEntity',
					       'GalleryEntity',
					       $classDir . 'GalleryEntity.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryChildEntity',
					       'GalleryChildEntity',
					       $classDir . 'GalleryChildEntity.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryAlbumItem',
					       'GalleryAlbumItem',
					       $classDir . 'GalleryAlbumItem.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryUser',
					       'GalleryUser',
					       $classDir . 'GalleryUser.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryGroup',
					       'GalleryGroup',
					       $classDir . 'GalleryGroup.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryDerivative',
					       'GalleryDerivative',
					       $classDir . 'GalleryDerivative.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryDerivativeImage',
					       'GalleryDerivativeImage',
					       $classDir . 'GalleryDerivativeImage.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryMovieItem',
					       'GalleryMovieItem',
					       $classDir . 'GalleryMovieItem.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryPhotoItem',
					       'GalleryPhotoItem',
					       $classDir . 'GalleryPhotoItem.class');
	
	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryUnknownItem',
					       'GalleryUnknownItem',
					       $classDir . 'GalleryUnknownItem.class');

	/* Register GalleryItem implementations */
	GalleryFactory::registerImplementation('GalleryItem',
					       'GalleryPhotoItem',
					       'GalleryPhotoItem',
					       $classDir . 'GalleryPhotoItem.class',
					       array('image/*'));

	GalleryFactory::registerImplementation('GalleryItem',
					       'GalleryMovieItem',
					       'GalleryMovieItem',
					       $classDir . 'GalleryMovieItem.class',
					       array('video/*'));

	GalleryFactory::registerImplementation('GalleryItem',
					       'GalleryUnknownItem',
					       'GalleryUnknownItem',
					       $classDir . 'GalleryUnknownItem.class',
					       array('*'));

	/* Register our search implementation */
	GalleryFactory::registerImplementation('GallerySearchInterface_1_0',
					       'GalleryCoreSearch',
					       'core',
					       $classDir . 'GalleryCoreSearch.class');

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::init();
     */
    function init() {
	global $gallery;

	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
	global $gallery;

	/*
	 * Installing the core is an unusual case, since the locations where we
	 * keep track of what's versions are installed may not even exist.  So,
	 * we have to work under the assumption that the store itself is
	 * already installed and configured, and our authentication is good.
	 * So then if we ask for the version number of the core and we get a
	 * storage error, we can assume that the core's store has not yet been
	 * configured and do that now.  All other modules can simply ask for
	 * the version number and expect that to succeed.
	 */
	if ($gallery->getDebug()) {
	    $gallery->debug('Trying to load core version.  If you see an error like ' .
			    '<b>table Xxx doesn\'t exist</b> here, that\'s OK.');
	}

	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError() & !($ret->getErrorCode() & ERROR_STORAGE_FAILURE)) {
	    return $ret->wrap(__FILE__, __LINE__);
	} else if ($ret->isError() || $version != $this->getVersion()) {

	    if ($gallery->getDebug()) {
		$gallery->debug('Can\'t load core version -- ' .
				'<b>assuming that the core needs installation</b>');
	    }

	    /*
	     * On some databases, our transaction is hosed at this point.  So
	     * roll back and start again.
	     */
	    $ret = $gallery->rollbackTransaction();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $gallery->beginTransaction();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* The store requires configuration. */
	    $storage = $gallery->getStorage();
	    $ret = $storage->configureStore('core');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/*
		 * This is an initial install.  
		 * Make sure that we have some reasonable defaults for the core.
		 */

		/* Load the translator class since we use it statically */
		$classDir = dirname(__FILE__) . '/classes/';
		require_once($classDir . 'GalleryTranslator.class');
		
		foreach (array('permissions.directory' => '0755',
			       'permissions.file' => '0644',
			       'exec.expectedStatus' => '0',
			       'default.orderBy' => 'id',
			       'default.orderDirection' => '1',
			       'default.layout' => 'classic',
			       'default.theme' => 'classic',
			       'default.language' => GalleryTranslator::getLanguageCodeFromRequest(),
			       'session.idParameter' => 'GALLERYSID',
			       'session.lifetime' => 25 * 365 * 86400, /* 25 years */
			       'session.inactivityTimeout' => 14 * 86400, /* two weeks */
			       )
			 as $key => $value) {

		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}

		/*
		 * Register our permissions.  Since we're storing
		 * internationalized strings in the database, we have to give
		 * our internationalized-string-extractor a clue that these
		 * strings get translated.  So put a line like this
		 * translate('key') in for each description so that our
		 * extractor can find it.
		 */
		/* Register all core permissions */
		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.all',
								   $gallery->i18n('All access'),
								   GALLERY_PERMISSION_ALL_ACCESS);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.view',
								   $gallery->i18n('[core] View item')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.viewResizes',
								   $gallery->i18n('[core] View resized version(s)')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.viewSource',
								   $gallery->i18n('[core] View original version')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.viewAll',
								   $gallery->i18n('[core] View all versions'), 
								   GALLERY_PERMISSION_COMPOSITE,
								   array('core.view',
									 'core.viewResizes',
									 'core.viewSource'));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.addAlbumItem',
								   $gallery->i18n('[core] Add sub-album'), 
								   GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.addDataItem',
								   $gallery->i18n('[core] Add sub-item'), 
								   GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.edit',
								   $gallery->i18n('[core] Edit item'), 
								   GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.changePermissions',
								   $gallery->i18n('[core] Change item permissions'), 
								   GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryPermissionSetMap::registerPermission($this->getName(),
								   'core.delete',
								   $gallery->i18n('[core] Delete item'), 
								   GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	
		$ret = $this->setModuleParameter('version', $this->getVersion());
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		/*
		 * We're going to need a translator in order to run the install
		 * functions below.  At this point in the install process, we
		 * probably don't have one!  Try to get one, and if that fails,
		 * then create one.
		 */
		$translator =& $gallery->getTranslator();
		if (empty($translator)) {
		    $ret = $gallery->initTranslator();
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
		
		foreach (array('_createAllUsersGroup',
			       '_createSiteAdminsGroup',
			       '_createAnonymousUser',
			       '_createAdminUser',
			       '_createRootAlbumItem') as $func) {

		    $ret = $this->$func();
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }
	} 

	/* The core is now guaranteed to be configured and initialized */
			      
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items, $returnUrlParams) {
	global $gallery;

	if (!is_array($items)) {
	    $items = array($items);
	}

	/* Format our return-url params */
	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	/*
	 * Look up all item admin permissions so that we can decide whether or
	 * not to display the "[edit item]" link.
	 */
	list ($ret, $adminPermissions) =
	    GalleryPermissionSetMap::getPermissionIds(GALLERY_PERMISSION_ITEM_ADMIN);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$links = array();
	foreach ($items as $item) {
	    $showEditLink = false;
	    $showAddItemLink = false;
	    $showAddAlbumLink = false;
	    $showDeleteLink = false;
	    $showPermissionsLink = false;
	    $showAddHighlightLink = false;
	    $showMoveItemLink = false;
	    $showReorderItemLink = false;

	    if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
		$itemType = 'album';
	    } else {
		$itemType = 'item';
	    }

	    /* Permissions for this item */
	    list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	
	    if (isset($permissions['core.all'])) {
		$showEditLink = true;
		$showDeleteLink = $item->getId() != $rootId;
		$showAddItemLink = $item->getCanContainChildren();
		$showAddAlbumLink = $item->getCanContainChildren();
		$showPermissionsLink = true;
		$showMoveItemLink = $item->getId() != $rootId;
		$showReorderItemLink = $item->getCanContainChildren();
	    } else {
		if (!empty($permissions) &&
		    array_intersect(array_keys($adminPermissions),
				    array_keys($permissions))) {
		    $showEditLink = true;
		}

		if ($item->getCanContainChildren()) {
		    if (isset($permissions['core.addDataItem'])) {
			$showAddItemLink = true;
		    }
		    
		    if (isset($permissions['core.addAlbumItem'])) {
			$showAddAlbumLink = true;
		    }

		    if (isset($permissions['core.edit'])) {
			$showReorderItemLink = true;
		    }
		}

		if (isset($permissions['core.delete'])) {
		    $showDeleteLink = $item->getId() != $rootId;
		    $showMoveItemLink = $item->getId() != $rootId;
		}

		if (isset($permissions['core.changePermissions'])) {
		    $showPermissionsLink = true;
		}
	    }

	    /* Permissions for its parent */
	    list ($ret, $parentPermissions) = GalleryItemHelper::getPermissions($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if ($item->getParentId() != $rootId) {
		if (isset($parentPermissions['core.edit'])) {
		    $showAddHighlightLink = true;
		}
	    }

	    if ($showEditLink) {
		if ($itemType == 'album') {
		    $text = $this->translate('edit album');
		} else {
		    $text = $this->translate('edit item');
		}
		$links[$item->getId()][] =
		    array('text' => $text,
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'itemId' => $item->getId()),
						  $params));
	    }
	    
	    if ($showAddItemLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('add item'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemAddChildren',
							'itemId' => $item->getId()),
						  $params));
	    }

	    if ($showAddAlbumLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('add album'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemAddAlbum',
							'itemId' => $item->getId()),
						  $params));
	    }
	    
	    if ($showPermissionsLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('permissions'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemEditPermissions',
							'itemId' => $item->getId()),
						  $params));
	    }
	    
	    if ($showDeleteLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('delete item'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemDelete',
							'itemId' => $item->getId()),
						  $params));
	    }

	    if ($showMoveItemLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('move item'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemMove',
							'itemId' => $item->getParentId(),
							'selectedId' => $item->getId()),
						  $params));
	    }

	    if ($showAddHighlightLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('make highlight'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemMakeHighlight',
							'itemId' => $item->getId()),
						  $params));
	    }

	    if ($showReorderItemLink) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('reorder items'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'subView' => 'core:ItemReorder',
							'itemId' => $item->getId()),
						  $params));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }
    
    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks($returnUrlParams) {
	global $gallery;

	list ($ret, $anonymousUserId) = $this->getModuleParameter('id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	$links = array();
	list ($ret, $isAdmin) = GalleryUserGroupMap::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($isAdmin) {
	    $links[] = array('text' => $this->translate('site admin'),
			     'params' => array_merge(array('view' => 'core:SiteAdmin'),
						     $params));
	}

	if ($gallery->getActiveUserId() == $anonymousUserId) {
	    $links[] = array('text' => $this->translate('login'),
			     'params' => array_merge(array('view' => 'core:Login'),
						     $params));
	} else {
	    $links[] = array('text' => $this->translate('preferences'),
			     'params' => array_merge(array('view' => 'core:UserPreferences'),
						     $params));
	    $links[] = array('text' => $this->translate('logout'),
			     'params' => array_merge(array('controller' => 'core:Logout'),
						     $params));
	}

	return array(GalleryStatus::success(), $links);
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews();
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('General'),
				 'view' => 'core:AdminCore'),
			   array('name' => $this->translate('Users'),
				 'view' => 'core:AdminUsers'),
			   array('name' => $this->translate('Groups'),
				 'view' => 'core:AdminGroups'),
			   array('name' => $this->translate('Modules'),
				 'view' => 'core:AdminModules')));
    }

    /**
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	global $gallery;

	$views = array();
	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$parentId = $item->getParentId();
	list ($ret, $parentPermissions) = GalleryItemHelper::getPermissions($parentId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($permissions['core.edit'])) {
	        $views[] = array('name' => $this->translate('General Settings'),
				 'view' => 'core:ItemEditItem');
	}

	if (isset($permissions['core.edit'])) {
	    if (GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
	        $views[] = array('name' => $this->translate('Album Settings'),
				 'view' => 'core:ItemEditAlbum');
	    }

	    if (GalleryUtilities::isA($item, 'GalleryDataItem')) {
		list ($ret, $operations) = GalleryToolkitHelper::getOperations($item->getMimeType());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		if (!empty($operations)) {
		    $views[] = array('name' => $this->translate('Edit Image'),
				     'view' => 'core:ItemEditImage');
		    $views[] = array('name' => $this->translate('Edit Sizes'),
				     'view' => 'core:ItemCreateResizes');
		}
	    }
	    if (!empty($parentId) && $parentId != $rootId && isset($parentPermissions['core.edit'])) {
		$views[] = array('name' => $this->translate('Make Highlight'),
				 'view' => 'core:ItemMakeHighlight');
	    }
	}
	
	if ($item->getId() != $rootId) {
	    if (isset($permissions['core.delete'])) {
		$views[] = array('name' => $this->translate('Delete Item'),
				 'view' => 'core:ItemDelete');
	    }
	}
	
	if (isset($permissions['core.changePermissions'])) {
	    $views[] = array('name' => $this->translate('Permissions'),
			     'view' => 'core:ItemEditPermissions');
	}
	
	if (isset($permissions['core.addDataItem'])) {
	    if ($item->getCanContainChildren()) {
	        $views[] = array('name' => $this->translate('Add Items'),
				 'view' => 'core:ItemAddChildren');
	    }
	}
	
	if (isset($permissions['core.addAlbumItem'])) {
	    if ($item->getCanContainChildren()) {
	        $views[] = array('name' => $this->translate('Add Album'),
				 'view' => 'core:ItemAddAlbum');
	    }
	}
	
	return array(GalleryStatus::success(), $views);
    }
    
    /**
     * Create the initial All Users group
     *
     * @return object GalleryStatus a status code
     */
    function _createAllUsersGroup() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $group) = GalleryFactory::newInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $group->create('All Users', GROUP_ALL_USERS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $this->setModuleParameter('id.allUserGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	return GalleryStatus::success();
    }

    /**
     * Create the Site Admins group
     *
     * @return object GalleryStatus a status code
     */
    function _createSiteAdminsGroup() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $group) = GalleryFactory::newInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $group->create('Site Admins', GROUP_SITE_ADMINS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.adminGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }

    /**
     * Create the initial Anonymous User
     *
     * @return object GalleryStatus a status code
     */
    function _createAnonymousUser() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $user) = GalleryFactory::newInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $user->create($this->translate('anonymous'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->setFullName($this->translate('Anonymous'));
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.anonymousUser', $user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Create the initial admin user
     *
     * @return object GalleryStatus a status code
     */
    function _createAdminUser() {
	global $gallery;

	/* Don't create if there is already a user in the admin group */
	list ($ret, $adminGroupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $results) = GalleryUserGroupMap::fetchUsersForGroup($adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (sizeof($results) > 0) {
	    return GalleryStatus::success();
	}

	/* Create the user */
	list ($ret, $user) = GalleryFactory::newInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $user->create($this->translate('admin'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->changePassword($gallery->getConfig('setup.password'));
	$user->setFullName($this->translate('Gallery Administrator'));
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Add her to the admin group */
	$ret = GalleryUserGroupMap::addUserToGroup($user->getId(),
						   $adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/*
	 * The rest of the bootstrap code won't work so well unless we're
	 * logged in, so log in as the admin user now.
	 */
	$gallery->setActiveUserId($user->getId());

	return GalleryStatus::success();
    }

    /**
     * Create the root album item
     *
     * @return object GalleryStatus a status code
     */
    function _createRootAlbumItem() {
	global $gallery;

	/* Do we already have a root? */
	list ($ret, $rootAlbumId) = $this->getModuleParameter('id.rootAlbum');
	if ($rootAlbumId) {
	    return GalleryStatus::success();
	}

	list ($ret, $album) = GalleryFactory::newInstance('GalleryEntity', 'GalleryAlbumItem');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($album)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $album->createRoot('root');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$album->setTitle($this->translate('Gallery'));
	$album->setDescription($this->translate('This is the top of your Gallery'));

	$ret = $album->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Give all users some permissions */
	list ($ret, $groupId) = $this->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryPermissionMap::addGroupPermission($album->getId(),
							$groupId,
							'core.viewAll');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Grant admin users everything */
	list ($ret, $groupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryPermissionMap::addGroupPermission($album->getId(),
							$groupId,
							'core.all');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.rootAlbum', $album->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }
    
}
?>

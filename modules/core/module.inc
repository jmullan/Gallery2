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
require_once(dirname(__FILE__) . '/classes/GalleryModule.class');

/**
 * The implementation of the core-module
 *
 * @package GalleryCore
 */
class CoreModule extends GalleryModule {

    function CoreModule() {
	$this->setId('core');
	$this->setName('Core');
	$this->setVersion('1.0');

	/*
	 * We can't set our description until we have a $gallery object so
	 * that we can call $gallery->i18n().  Defer this to the bootstrap code.
	 */
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
 	require_once($classDir . 'GalleryConstants.class');
	require_once($classDir . 'Gallery.class');
	require_once($classDir . 'GalleryStatus.class');
 	require_once($classDir . 'GalleryDataCache.class');
	require_once($classDir . 'GalleryCoreApi.class');
 	require_once($classDir . 'GalleryUrlGenerator.class');
 	require_once($classDir . 'GallerySession.class');
 	require_once($classDir . 'GalleryUtilities.class');
 	require_once($classDir . 'GalleryView.class');
	
	/*
	 * Set up our Gallery global.  It's important to use a reference here because
	 * the constructor registers a shutdown function and ties it to the instance in
	 * the constructor.  This global should be the only one that Gallery requires.
	 * Everything else should be inside it so that we do not pollute the namespace
	 * (especially important when we're embedded inside another application).
	 */
	$gallery =& new Gallery();
	$GLOBALS['gallery'] =& $gallery;
	GalleryCoreApi::setPluginInstance('module', 'core', $this);

	/* Configure the Platform */
	$gallery->setConfig('platform.type', strtolower(PHP_OS));

	/* Register platform implementations */
	GalleryCoreApi::registerFactoryImplementation('GalleryPlatform',
						      'UnixPlatform',
						      'Unix',
						      $classDir . 'GalleryPlatform/UnixPlatform.class',
						      array('unix', '*'));

	GalleryCoreApi::registerFactoryImplementation('GalleryPlatform',
						      'WinNtPlatform',
						      'WinNT',
						      $classDir . 'GalleryPlatform/WinNtPlatform.class',
						      array('winnt'));

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
							    'video/x.ms.asf'));

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
	
	/* Now we have a $gallery instance and can set our description */
	$this->setDescription($gallery->i18n('Gallery 2 Core Module'));

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

	/* Register our URL rewriting views */
	$urlGenerator =& $gallery->getUrlGenerator();
	$urlGenerator->registerViewPrefix('view', 'core:ShowItem');
	$urlGenerator->registerViewPrefix('download', 'core:DownloadItem');
	
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
	    return array($ret->wrap(__FILE__, __LINE__), false);
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
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }

	    $ret = $gallery->beginTransaction();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }

	    /* The store requires configuration. */
	    $storage = $gallery->getStorage();
	    $ret = $storage->configureStore('core');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	}

	$installed = false;
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
			       'upload.localServer.dirs' => '',
			       'exec.expectedStatus' => '0',
			       'default.orderBy' => '',
			       'default.orderDirection' => '1',
			       'default.layout' => 'matrix',
			       'default.theme' => 'matrix',
			       'default.language' => GalleryTranslator::getLanguageCodeFromRequest(),
			       'session.idParameter' => 'GALLERYSID',
			       'session.lifetime' => 25 * 365 * 86400, /* 25 years */
			       'session.inactivityTimeout' => 14 * 86400, /* two weeks */
			       'misc.markup' => 'bbcode',
			       'misc.useShortUrls' => 'false',
			       )
			 as $key => $value) {

		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), false);
		    }
		}

		/* Activate the Matrix layout */
		list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', 'matrix');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
		
		$ret = $layout->activate();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
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
		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.all',
							  $gallery->i18n('All access'),
							  GALLERY_PERMISSION_ALL_ACCESS);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.view',
							  $gallery->i18n('[core] View item')); 
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.viewResizes',
							  $gallery->i18n('[core] View resized version(s)')); 
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
	    
		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.viewSource',
							  $gallery->i18n('[core] View original version')); 
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
	    
		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.viewAll',
							  $gallery->i18n('[core] View all versions'), 
							  GALLERY_PERMISSION_COMPOSITE,
							  array('core.view',
								'core.viewResizes',
								'core.viewSource'));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.addAlbumItem',
							  $gallery->i18n('[core] Add sub-album'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.addDataItem',
							  $gallery->i18n('[core] Add sub-item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
	    
		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.edit',
							  $gallery->i18n('[core] Edit item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.changePermissions',
							  $gallery->i18n('[core] Change item permissions'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'core.delete',
							  $gallery->i18n('[core] Delete item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
	
		$ret = $this->setModuleParameter('version', $this->getVersion());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
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
			return array($ret->wrap(__FILE__, __LINE__), false);
		    }
		}

		foreach (array('_createAllUsersGroup',
			       '_createSiteAdminsGroup',
			       '_createEverybodyGroup',
			       '_createAnonymousUser',
			       '_createAdminUser',
			       '_createRootAlbumItem') as $func) {

		    $ret = $this->$func();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), false);
		    }
		}
		$installed = true;
	    }
	}

	/* The core is now guaranteed to be configured and initialized */
	return array(GalleryStatus::success(), $installed);
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
					    'itemId' => $item->getId()));
	    }

	    $itemTypeNames = $item->itemTypeName();
	    if (isset($permissions['core.edit'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'edit %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'return' => true,
					    'subView' => 'core:ItemEdit',
					    'itemId' => $item->getId()));
	    }

	    if ($item->isLinkable()) {
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
						'selectedId' => $item->getId()));
		}
	    }

	    if ($isAlbum && isset($permissions['core.addAlbumItem'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('add sub-album'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemAddAlbum',
					    'itemId' => $item->getId()));
	    }
	    
	    if (isset($permissions['core.changePermissions'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('edit permissions'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemPermissions',
					    'itemId' => $item->getId()));
	    }

	    if (!$isRoot && isset($permissions['core.delete'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'delete %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'return' => true,
					    'subView' => 'core:ItemDelete',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $item->getId()));
	    }

	    if (!$isRoot && isset($permissions['core.delete'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate(array('text' => 'move %s',
							   'arg1' => $itemTypeNames[1])),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemMove',
					    'itemId' => $item->getParentId(),
					    'selectedId' => $item->getId()));
	    }

	    if (!$isRoot && !$isParentRoot && isset($thumbTable[$item->getId()]) && isset($permissions['core.edit'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('make highlight'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'return' => true,
					    'subView' => 'core:ItemMakeHighlight',
					    'itemId' => $item->getId()));
	    }

	    if ($isAlbum && isset($permissions['core.edit']) &&
		!empty($childCounts[$item->getId()]) &&
		$childCounts[$item->getId()] > 1) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('reorder items'),
			  'params' => array('view' => 'core:ItemAdmin',
					    'subView' => 'core:ItemReorder',
					    'itemId' => $item->getId()));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks() {
        global $gallery;
	
        list ($ret, $anonymousUserId) = $this->getModuleParameter('id.anonymousUser');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
        $links = array();
        list ($ret, $isAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
        if ($isAdmin) {
            $links[] = array('text' => $this->translate('Site admin'),
                             'params' => array('view' => 'core:SiteAdmin'));
	}
	
        if ($gallery->getActiveUserId() == $anonymousUserId) {
            $links[] = array('text' => $this->translate('Login'),
                             'params' => array('return' => 'true',
					       'view' => 'core:UserAdmin',
					       'subView' => 'core:UserLogin'));
	} else {
            $links[] = array('text' => $this->translate('Your account'),
                             'params' => array('return' => 'true',
					       'view' => 'core:UserAdmin',
					       'subView' => 'core:UserPreferences'));
            $links[] = array('text' => $this->translate('Logout'),
                             'params' => array('return' => 'true',
					       'controller' => 'core:Logout'));
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
				 'view' => 'core:AdminModules'),
			   array('name' => $this->translate('Layouts'),
				 'view' => 'core:AdminLayouts')
			   ),
		     );
    }

    /**
     * @see GalleryModule::getUserAdminViews();
     */
    function getUserAdminViews($user) {
	global $gallery;
	
	$views = array();

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
	    $views[] = array('name' => $this->translate('Log in'),
			     'view' => 'core:UserLogin');
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
	
	if (isset($permissions['core.delete'])) {
	    if ($item->getId() != $rootId) {
		$views[] = array('name' => $this->translate(array('text' => 'Delete %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core:ItemDelete');

		$views[] = array('name' => $this->translate(array('text' => 'Move %s', 'arg1' => $itemTypeNames[0])),
				 'view' => 'core:ItemMove',
				 'itemId' => $parentId,
				 'selectedId' => $item->getId());
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
    
	list ($ret, $group) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	$groupName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('All Users'));
	$ret = $group->create($groupName, GROUP_ALL_USERS);
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
    
	list ($ret, $group) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$groupName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Site Admins'));
	$ret = $group->create($groupName, GROUP_SITE_ADMINS);
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
     * Create the Site Admins group
     *
     * @return object GalleryStatus a status code
     */
    function _createEverybodyGroup() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.everybodyGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $group) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$groupName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Everybody'));
	$ret = $group->create($groupName, GROUP_EVERYBODY);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.everybodyGroup', $group->getId());
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
    
	list ($ret, $user) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$userName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('guest'));
	$fullName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Guest'));
	$ret = $user->create($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->setFullName($fullName);
	$user->changePassword('');
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Remove the anonymous user from the "all users" group */
	list ($ret, $allUserGroupId) = $this->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	GalleryCoreApi::removeUserFromGroup($user->getId(), $allUserGroupId);

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

	list ($ret, $results) = GalleryCoreApi::fetchUsersForGroup($adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (sizeof($results) > 0) {
	    return GalleryStatus::success();
	}

	/* Create the user */
	list ($ret, $user) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  

	$userName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('admin'));
	$fullName = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Gallery Administrator'));
	$ret = $user->create($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->changePassword($gallery->getConfig('setup.password'));
	$user->setFullName($fullName);
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Add her to the admin group */
	$ret = GalleryCoreApi::addUserToGroup($user->getId(), $adminGroupId);
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

	list ($ret, $album) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryAlbumItem');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	if (!isset($album)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}  
    
	$ret = $album->createRoot();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$title = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Gallery'));
	$description = GalleryUtilities::utf8ToUnicodeEntities($this->translate('This is the top of your Gallery'));
	$album->setTitle($title);
	$album->setDescription($description);

	$ret = $album->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Give everybody some permissions */
	list ($ret, $groupId) = $this->getModuleParameter('id.everybodyGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(), $groupId, 'core.viewAll');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Grant admin users everything */
	list ($ret, $groupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(),
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

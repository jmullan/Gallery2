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
 * Extra, rarely used core module code.  Most modules will not need to push their extra code into a separate
 * class, but the core module has a lot of install code that is very rarely used so we tuck it out of the way.
 *
 * @package GalleryCore
 */
class CoreModuleExtras {
    
    /**
     * @see GalleryModule::install
     * @param object GalleryModule the core module
     */
    function install($module) {
	global $gallery;

	/* The store requires configuration. */
	$storage =& $gallery->getStorage();
	$ret = $storage->configureStore('core');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $version) = $module->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	if ($version != $module->getVersion()) {
	    if (empty($version)) {
		/*
		 * This is an initial install.  
		 * Make sure that we have some reasonable defaults for the core.
		 */

		// Load the translator class since we use it statically
		GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryTranslator.class');
		foreach (array('permissions.directory' => '0755',
			       'permissions.file' => '0644',
			       'uploadLocalServer.dirs' => '',
			       'exec.expectedStatus' => '0',
			       'default.orderBy' => 'orderWeight',
			       'default.orderDirection' => '1',
			       'default.layout' => 'matrix',
			       'default.theme' => 'matrix',
			       'default.language' => GalleryTranslator::getLanguageCodeFromRequest(),
			       'language.selector' => 'none',
			       'session.lifetime' => 25 * 365 * 86400, /* 25 years */
			       'session.inactivityTimeout' => 14 * 86400, /* two weeks */
			       'misc.markup' => 'bbcode',
			       'misc.useShortUrls' => 'false',
			       )
			 as $key => $value) {
		    
		    $ret = $module->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}

		/* Activate the Matrix layout */
		list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', 'matrix');
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		
		$ret = $layout->activate();
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

		/*
		 * Register our permissions.  Since we're storing
		 * internationalized strings in the database, we have to give
		 * our internationalized-string-extractor a clue that these
		 * strings get translated.  So put a line like this
		 * translate('key') in for each description so that our
		 * extractor can find it.
		 */
		/* Register all core permissions */
		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.all',
							  $gallery->i18n('All access'),
							  GALLERY_PERMISSION_ALL_ACCESS);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.view',
							  $gallery->i18n('[core] View item')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.viewResizes',
							  $gallery->i18n('[core] View resized version(s)')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.viewSource',
							  $gallery->i18n('[core] View original version')); 
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.viewAll',
							  $gallery->i18n('[core] View all versions'), 
							  GALLERY_PERMISSION_COMPOSITE,
							  array('core.view',
								'core.viewResizes',
								'core.viewSource'));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.addAlbumItem',
							  $gallery->i18n('[core] Add sub-album'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.addDataItem',
							  $gallery->i18n('[core] Add sub-item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    
		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.edit',
							  $gallery->i18n('[core] Edit item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.changePermissions',
							  $gallery->i18n('[core] Change item permissions'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::registerPermission($module->getId(),
							  'core.delete',
							  $gallery->i18n('[core] Delete item'), 
							  GALLERY_PERMISSION_ITEM_ADMIN);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	
		$ret = $module->setModuleParameter('version', $module->getVersion());
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		foreach (array('_createAllUsersGroup',
			       '_createSiteAdminsGroup',
			       '_createEverybodyGroup',
			       '_createAnonymousUser',
			       '_createAdminUser',
			       '_createRootAlbumItem') as $func) {

		    $ret = CoreModuleExtras::$func($module);
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
     * Create the initial All Users group
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createAllUsersGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getModuleParameter('id.allUserGroup');
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

	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('All Users'));
	$ret = $group->create($groupName, GROUP_ALL_USERS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $module->setModuleParameter('id.allUserGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	return GalleryStatus::success();
    }

    /**
     * Create the Site Admins group
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createSiteAdminsGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getModuleParameter('id.adminGroup');
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
    
	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Site Admins'));
	$ret = $group->create($groupName, GROUP_SITE_ADMINS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setModuleParameter('id.adminGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }

    /**
     * Create the Site Admins group
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createEverybodyGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getModuleParameter('id.everybodyGroup');
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
    
	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Everybody'));
	$ret = $group->create($groupName, GROUP_EVERYBODY);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setModuleParameter('id.everybodyGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }

    /**
     * Create the initial Anonymous User
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createAnonymousUser($module) {
	global $gallery;

	list ($ret, $id) = $module->getModuleParameter('id.anonymousUser');
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
    
	$userName = GalleryUtilities::utf8ToUnicodeEntities('guest');
	$fullName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Guest'));
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
	list ($ret, $allUserGroupId) = $module->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	GalleryCoreApi::removeUserFromGroup($user->getId(), $allUserGroupId);

	$ret = $module->setModuleParameter('id.anonymousUser', $user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Create the initial admin user
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createAdminUser($module) {
	global $gallery;

	/* Don't create if there is already a user in the admin group */
	list ($ret, $adminGroupId) = $module->getModuleParameter('id.adminGroup');
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

	$userName = GalleryUtilities::utf8ToUnicodeEntities('admin');
	$fullName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Gallery Administrator'));
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
	$gallery->setActiveUser($user);

	return GalleryStatus::success();
    }

    /**
     * Create the root album item
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     */
    function _createRootAlbumItem($module) {
	global $gallery;

	/* Do we already have a root? */
	list ($ret, $rootAlbumId) = $module->getModuleParameter('id.rootAlbum');
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
	$title = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Gallery'));
	$description = GalleryUtilities::utf8ToUnicodeEntities($module->translate('This is the top of your Gallery'));
	$album->setTitle($title);
	$album->setDescription($description);

	$ret = $album->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Give everybody some permissions */
	list ($ret, $groupId) = $module->getModuleParameter('id.everybodyGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(), $groupId, 'core.viewAll');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Grant admin users everything */
	list ($ret, $groupId) = $module->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(),
							$groupId,
							'core.all');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setModuleParameter('id.rootAlbum', $album->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }
}
?>

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
     * @see GalleryModule::upgrade()
     * @param object GalleryModule the core module
     * @param string the current installed version
     */
    function upgrade($module, $currentVersion) {
	global $gallery;

	/*
	 * We store our version outside of the database so that we can upgrade
	 * even if the database is in an undependable state.
	 */
	$versions = $this->getInstalledVersions();
	$currentVersion = $versions['core'];

	if (!isset($currentVersion)) {
	    /*
	     * This is either an initial install or an upgrade from version
	     * 0.8 (which didn't have the core versions.dat file).  Use a module
	     * parameter as our acid test.
	     *
	     * TODO: Get rid of this when we get to the final release.  It's
	     * only useful in the alpha -> beta transition.
	     */
	    list ($ret, $paramValue) = $module->getModuleParameter('permissions.directory');
	    if (isset($paramValue)) {
		$currentVersion = '0.8';
	    }
	}

	if (isset($currentVersion)) {
	    list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	}
	if (!isset($param)) {
	    $param = array();
	}

	/* Make sure all our module parameters are set (initial install or upgrade) */
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
		       'misc.login' => 'both',
		       ) as $key => $value) {
	    if (!isset($param[$key])) {
		$ret = $module->setModuleParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	if (!isset($currentVersion)) {
	    /* This is an initial install */
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
	     * Register our permissions.  Since we're storing internationalized
	     * strings in the database, we have to give our internationalized
	     * string extractor a clue that these strings get translated.  So
	     * put a line like this translate('key') in for each description so
	     * that our extractor can find it.
	     */
	    $permissions[] = array('all', $gallery->i18n('All access'),
				   GALLERY_PERMISSION_ALL_ACCESS, array());
	    $permissions[] = array('view', $gallery->i18n('[core] View item'), 0, array());
	    $permissions[] = array('viewResizes', $gallery->i18n('[core] View resized version(s)'), 0, array());
	    $permissions[] = array('viewSource', $gallery->i18n('[core] View original version'), 0, array());
	    $permissions[] = array('viewAll', $gallery->i18n('[core] View all versions'),
				   GALLERY_PERMISSION_COMPOSITE,
				   array('core.view', 'core.viewResizes', 'core.viewSource'));
	    $permissions[] = array('addAlbumItem', $gallery->i18n('[core] Add sub-album'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('addDataItem', $gallery->i18n('[core] Add sub-item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('edit', $gallery->i18n('[core] Edit item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('changePermissions', $gallery->i18n('[core] Change item permissions'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('delete', $gallery->i18n('[core] Delete item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    foreach ($permissions as $p) {
		$ret = GalleryCoreApi::registerPermission($module->getId(), 'core.' . $p[0], $p[1], $p[2], $p[3]);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
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

	$platform = $gallery->getPlatform();
	$baseDir = $gallery->getConfig('data.gallery.base');
	$versionFile = sprintf('%s%s%s',
			       $baseDir,
			       $platform->getDirectorySeparator(),
			       'versions.dat');

	$versionDatError =  0;
	if ($fd = $platform->fopen($versionFile, 'wb')) {
	    $data = sprintf("%s\n%s",
			    $module->getVersion(),
			    $module->getGalleryVersion());
	    if ($platform->fwrite($fd, $data) != strlen($data)) {
		$versionDatError = 1;
	    }
	    $platform->fclose($fd);
	} else {
	    $versionDatError = 1;
	}

	if ($versionDatError) {
	    return GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					'Can\'t write to the versions file');
	}

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

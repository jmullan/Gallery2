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
 * Extra, rarely used core module code.  Most modules will not need to push
 * their extra code into a separate class, but the core module has a lot of
 * install code that is very rarely used so we tuck it out of the way.
 *
 * @package GalleryCore
 * @static
 */
class CoreModuleExtras {

    /**
     * @see GalleryModule::upgrade()
     * @param object GalleryModule the core module
     * @param string the current installed version
     * @static
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
	    list ($ret, $paramValue) = $module->getParameter('permissions.directory');
	    if (isset($paramValue)) {
		$currentVersion = '0.8';
	    } else {
		$currentVersion = '0';
	    }
	}

	/**
	 * README: How to update the block below.
	 *
	 * If you add a new feature to the core module and revise the version,
	 * you should do the following.  Supposing the current version is 1.0.1
	 * and you're adding 1.0.2:
	 *
	 *  1.  Go to the end of the switch and edit the '1.0.0' block and make
	 *      sure that it does not have a 'break' statement.  You'll want it
	 *      to fall through to the new block that you're about to add.
	 *  2.  Add a new block at the end of the switch statement for '1.0.1'
	 *      and add all the changes necessary to go from 1.0.1 to 1.0.2.
	 *      When you're done, set $currentVersion = '1.0.2' and break;
	 *  3.  Update the '0' block to make any appropriate changes for initial
	 *      installs.  Merge them in with the existing install code as
	 *      appropriate.  At the end of the block, set $currentVersion =
	 *      '1.0.2' and break;
	 */
	switch ($currentVersion) {
	case '0':
	    /* Initial install.  Make sure all our module parameters are set. */
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
			   'default.newAlbumsUseDefaults' => 'false',
			   'language.selector' => 'none',
			   'session.lifetime' => 25 * 365 * 86400, /* 25 years */
			   'session.inactivityTimeout' => 14 * 86400, /* two weeks */
			   'misc.markup' => 'bbcode',
			   'misc.useShortUrls' => 'false',
			   'misc.login' => 'both',
			   'lock.system' => 'flock',
			   ) as $key => $value) {
		if (!isset($param[$key])) {
		    $ret = $module->setParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    /* Activate the Matrix layout */
	    list ($ret, $layout) = GalleryCoreApi::loadPlugin('layout', 'matrix');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $layout->installOrUpgrade();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    list ($ret, $ignored) = $layout->activate();
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
	    $permissions[] = array('viewResizes', $gallery->i18n('[core] View resized version(s)'),
				   0, array());
	    $permissions[] = array('viewSource', $gallery->i18n('[core] View original version'),
				   0, array());
	    $permissions[] = array('viewAll', $gallery->i18n('[core] View all versions'),
				   GALLERY_PERMISSION_COMPOSITE,
				   array('core.view', 'core.viewResizes', 'core.viewSource'));
	    $permissions[] = array('addAlbumItem', $gallery->i18n('[core] Add sub-album'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('addDataItem', $gallery->i18n('[core] Add sub-item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('edit', $gallery->i18n('[core] Edit item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('changePermissions',
				   $gallery->i18n('[core] Change item permissions'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    $permissions[] = array('delete', $gallery->i18n('[core] Delete item'),
				   GALLERY_PERMISSION_ITEM_ADMIN, array());
	    foreach ($permissions as $p) {
		$ret = GalleryCoreApi::registerPermission(
		    $module->getId(), 'core.' . $p[0], $p[1], $p[2], $p[3]);
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

		$ret = call_user_func(array('CoreModuleExtras', $func), $module);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	    $currentVersion = '0.8.17';
	    break;

	case '0.8':
	case '0.8.1':
	case '0.8.2':
	    /*
	     * Update our framework module parameters to have a leading
	     * underscore so that we have our own separate namespace.
	     */
	    $storage =& $gallery->getStorage();
	    $query = '
                  UPDATE
                    [GalleryPluginParameterMap]
                  SET
                    [::parameterName] = ?
                  WHERE
                    [GalleryPluginParameterMap::parameterName] = ?
                    AND
                    [GalleryPluginParameterMap::pluginType] = \'module\'
                    AND
                    [GalleryPluginParameterMap::itemId] = 0
                ';
	    $ret = $storage->execute($query, array('_version', 'version'));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $storage->execute($query, array('_callbacks', 'callbacks'));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* Added a new parameter */
	    $ret = $module->setParameter('misc.login', 'both');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $currentVersion = '0.8.3';
	    /* fall through */

	case '0.8.3':
	case '0.8.4':
	case '0.8.5':
	    /*
	     * Copy the information from viewedSinceTimestamp to originationTimestamp
	     * as both default to time()
	     */
	    $storage =& $gallery->getStorage();
	    $query = '
                  UPDATE
                    [GalleryItem]
                  SET
                    [::originationTimestamp] = [::viewedSinceTimestamp]
                ';
	    $ret = $storage->execute($query, array());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $currentVersion = '0.8.6';
	    /* fall through */

	case '0.8.6':
	case '0.8.7':
	    $ret = $module->setParameter('default.newAlbumsUseDefaults', 'false');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $currentVersion = '0.8.8';
	    /* fall through */

	case '0.8.8':
	case '0.8.9':
	    $storage =& $gallery->getStorage();

	    /*
	     * Set all factory implementation weights to 5.  We'll re-register
	     * all core implementations with a weight of 4 so that they get
	     * precedence.
	     */
	    $query = 'UPDATE [GalleryFactoryMap] SET [::orderWeight] = 5';
	    $ret = $storage->execute($query, array());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $currentVersion = '0.8.10';
	    /* fall through */

	case '0.8.10':
	case '0.8.11':
	case '0.8.12':
	    $ret = $module->setParameter('lock.system', 'flock');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $currentVersion = '0.8.13';
	    /* fall through */

	case '0.8.13':
	    /*
	     * We added layout versioning.  We need to call installOrUpgrade()
	     * on the currently active layouts to let them update their
	     * bookkeeping.  Reactivate them too for good measure.
	     */
	    list ($ret, $layouts) = GalleryCoreApi::fetchPluginStatus('layout');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($layouts as $layoutId => $layoutStatus) {
		if (!empty($layoutStatus['active'])) {
		    list($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
		    if ($ret->isError() &&
			!($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $layout->installOrUpgrade();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $ignored) = $layout->activate();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    $currentVersion = '0.8.14';
	    /* fall through */

	case '0.8.14':
	    /* Added Entity::onLoadHandlers; default all values to null, so nothing to do */
	    $currentVersion = '0.8.15';
	    /* fall through */

	case '0.8.15':
	    /* Removed GalleryItemPropertiesMap.. drop the table */
	    $storage =& $gallery->getStorage();

	    $query = '
	    DROP TABLE [GalleryItemPropertiesMap]
	    ';

	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $currentVersion = '0.8.16';
	    /* fall through */

	case '0.8.16':
	    /* Schema updates: GalleryPluginMap, GalleryPluginParameterMap, GalleryGroup */
	    $currentVersion = '0.8.17';
	    break;

	default:
	    return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					sprintf('Unknown module version %s', $currentVersion));
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
     * @static
     */
    function _createAllUsersGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryGroup.class');
	$group = new GalleryGroup();

	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('All Users'));
	$ret = $group->create($groupName, GROUP_ALL_USERS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setParameter('id.allUserGroup', $group->getId());
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
     * @static
     */
    function _createSiteAdminsGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryGroup.class');
	$group = new GalleryGroup();

	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Site Admins'));
	$ret = $group->create($groupName, GROUP_SITE_ADMINS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setParameter('id.adminGroup', $group->getId());
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
     * @static
     */
    function _createEverybodyGroup($module) {
	global $gallery;

	list ($ret, $id) = $module->getParameter('id.everybodyGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryGroup.class');
	$group = new GalleryGroup();

	$groupName = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Everybody'));
	$ret = $group->create($groupName, GROUP_EVERYBODY);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setParameter('id.everybodyGroup', $group->getId());
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
     * @static
     */
    function _createAnonymousUser($module) {
	global $gallery;

	list ($ret, $id) = $module->getParameter('id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryUser.class');
	$user = new GalleryUser();

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
	list ($ret, $allUserGroupId) = $module->getParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	GalleryCoreApi::removeUserFromGroup($user->getId(), $allUserGroupId);

	$ret = $module->setParameter('id.anonymousUser', $user->getId());
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
     * @static
     */
    function _createAdminUser($module) {
	global $gallery;

	/* Don't create if there is already a user in the admin group */
	list ($ret, $adminGroupId) = $module->getParameter('id.adminGroup');
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

	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryUser.class');
	$user = new GalleryUser();

	$userName = GalleryUtilities::utf8ToUnicodeEntities('admin');
	$fullName = GalleryUtilities::utf8ToUnicodeEntities(
		    $module->translate('Gallery Administrator'));
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
     * @static
     */
    function _createRootAlbumItem($module) {
	global $gallery;

	/* Do we already have a root? */
	list ($ret, $rootAlbumId) = $module->getParameter('id.rootAlbum');
	if ($rootAlbumId) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryAlbumItem.class');
	$album = new GalleryAlbumItem();

	$ret = $album->createRoot();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$title = GalleryUtilities::utf8ToUnicodeEntities($module->translate('Gallery'));
	$description = GalleryUtilities::utf8ToUnicodeEntities(
		       $module->translate('This is the top of your Gallery'));
	$album->setTitle($title);
	$album->setDescription($description);

	$ret = $album->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Give everybody some permissions */
	list ($ret, $groupId) = $module->getParameter('id.everybodyGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(), $groupId, 'core.viewAll');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Grant admin users everything */
	list ($ret, $groupId) = $module->getParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::addGroupPermission($album->getId(),
							$groupId,
							'core.all');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setParameter('id.rootAlbum', $album->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations($module) {
	/* Register all of our factory implementations. */
	$regs[] = array('GalleryEntity', 'GalleryEntity', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryChildEntity', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryAlbumItem', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryUser', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryGroup', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryDerivative', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryDerivativeImage', 'class', null);
	$regs[] = array('GalleryDerivative', 'GalleryDerivativeImage', 'class', array('*'));
	$regs[] = array('GalleryEntity', 'GalleryMovieItem', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryAnimationItem', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryPhotoItem', 'class', null);
	$regs[] = array('GalleryEntity', 'GalleryUnknownItem', 'class', null);
	$regs[] = array('GalleryItem', 'GalleryPhotoItem', 'class', array('image/*'));
	$regs[] = array('GalleryItem', 'GalleryMovieItem', 'class',
			array('video/x-msvideo', 'video/quicktime', 'video/mpeg',
			      'video/x-ms-asf', 'video/x-ms-wmv'));
	$regs[] = array('GalleryItem', 'GalleryAnimationItem', 'class',
			array('application/x-director', 'application/x-shockwave-flash'));
	$regs[] = array('GalleryItem', 'GalleryUnknownItem', 'class', array('*'));
	$regs[] = array('GallerySearchInterface_1_0', 'GalleryCoreSearch', 'class', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditItem', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditAnimation', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditMovie', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditAlbum', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditLayout', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditPhoto', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditRotateAndScalePhoto', 'inc', null);
	$regs[] = array('ItemEditPlugin', 'ItemEditPhotoThumbnail', 'inc', null);
	$regs[] = array('ItemAddPlugin', 'ItemAddFromBrowser', 'inc', null);
	$regs[] = array('ItemAddPlugin', 'ItemAddFromServer', 'inc', null);
	$regs[] = array('ItemAddPlugin', 'ItemAddFromWeb', 'inc', null);
	$regs[] = array('ItemAddOption', 'CreateThumbnailOption', 'inc', null);

	/*
	 * Unlike other modules, the core module doesn't get deactivated so its
	 * factory registrations may still be around from before.  Unregister
	 * them now before reregistering them all.
	 */
	/* Unregister all factory implementations */
	$ret = GalleryCoreApi::unregisterFactoryImplementationsByModuleId($module->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	foreach ($regs as $entry) {
	    $ret = GalleryCoreApi::registerFactoryImplementation(
		$entry[0], $entry[1], $entry[1],
                $entry[2] == 'class' ?
		  sprintf('modules/core/classes/%s.class', $entry[1]) :
		  sprintf('modules/core/%s.inc', $entry[1]),
		'core', $entry[3], 4);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	return GalleryStatus::success();
    }
}
?>

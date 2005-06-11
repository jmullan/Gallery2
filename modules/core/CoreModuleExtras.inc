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
    function upgrade($module, $currentVersion, $statusMonitor) {
	global $gallery;
	$storage =& $gallery->getStorage();

	/*
	 * We store our version outside of the database so that we can upgrade
	 * even if the database is in an undependable state.
	 */
	$versions = $module->getInstalledVersions();
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

	$platform = $gallery->getPlatform();

	/**
	 * README: How to update the block below.
	 *
	 * If you add a new feature to the core module and revise the version, you should do the
	 * following.  Supposing the current version is 1.0.1 and you're adding 1.0.2. Go to the
	 * end of the switch and find the 'end of upgrade path' case.  Create a new case *above*
	 * that one with the old version number.  For our example you'd add: "case '1.0.1':" and
	 * then your code.  Do *not* put in a break statement. (Update _prepareConfigUpgrade too)
	 */
	switch ($currentVersion) {
	case '0':
	    if (GalleryUtilities::isA($platform, 'WinNtPlatform')) {
		$flockType = 'database';
	    } else {
		$fileToLock = $platform->fopen(__FILE__, 'r');
		$wouldBlock = false;
		if ($platform->flock($fileToLock, LOCK_SH, $wouldBlock) || $wouldBlock) {
		    $flockType = 'flock';
		} else {
		    $flockType = 'database';
		}
		$platform->fclose($fileToLock);
	    }
	    /* Initial install.  Make sure all our module parameters are set. */
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryTranslator.class');
	    foreach (array('permissions.directory' => '0755',
			   'permissions.file' => '0644',
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
			   'misc.login' => 'both',
			   'lock.system' => $flockType
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

	    foreach (array('_createAccessListCompacterLock',
			   '_createAllUsersGroup',
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

	    GalleryCoreApi::requireOnce(
		dirname(__FILE__) . '/classes/helpers/GalleryMimeTypeHelper_advanced.class');
	    $ret = GalleryMimeTypeHelper_advanced::initializeMimeTypes();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    break;

	case '0.8':
	case '0.8.1':
	case '0.8.2':
	    /*
	     * Update our framework module parameters to have a leading
	     * underscore so that we have our own separate namespace.
	     */
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

	case '0.8.3':
	case '0.8.4':
	case '0.8.5':
	    /*
	     * Copy the information from viewedSinceTimestamp to originationTimestamp
	     * as both default to time()
	     */
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

	case '0.8.6':
	case '0.8.7':
	    $ret = $module->setParameter('default.newAlbumsUseDefaults', 'false');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.8.8':
	case '0.8.9':
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

	case '0.8.10':
	case '0.8.11':
	case '0.8.12':
	    $ret = $module->setParameter('lock.system', 'flock');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.8.13':
	    /*
	     * We added layout versioning.  We need to call installOrUpgrade()
	     * on the currently active layouts to let them update their
	     * bookkeeping.  Reactivate them too for good measure.
	     */
	    list ($ret, $layouts) = GalleryCoreApi::fetchPluginStatus('layout');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    foreach ($layouts as $layoutId => $layoutStatus) {
		$gallery->guaranteeTimeLimit(30);
		if (!empty($layoutStatus['active'])) {
		    list($ret, $layout) = GalleryCoreApi::loadPlugin('layout', $layoutId);
		    if ($ret->isError() &&
			!($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
			return $ret->wrap(__FILE__, __LINE__);
		    }

		    $ret = $layout->installOrUpgrade();
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }

		    list ($ret, $ignored) = $layout->activate();
		    if ($ret->isError() &&
			!($ret->getErrorCode() & ERROR_PLUGIN_VERSION_MISMATCH)) {
			/*
			 * Layout getSettings may try to load ImageFrame interface, but
			 * ImageFrame may need to be upgraded.. ignore version mismatch here.
			 */
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	case '0.8.14':
	    /* Added Entity::onLoadHandlers; default all values to null, so nothing to do */

	case '0.8.15':
	    $gallery->guaranteeTimeLimit(30);
	    /* Removed GalleryItemPropertiesMap.. drop the table */
	    $query = 'DROP TABLE [GalleryItemPropertiesMap]';
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $query = "DELETE FROM [Schema] WHERE [Schema::name] = 'ItemPropertiesMap'";
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.8.16':
	    /* Schema updates: GalleryPluginMap, GalleryPluginParameterMap, GalleryGroup */

	case '0.8.17':
	    /* Beta 1! */

	case '0.9.0':
	    $ret = GalleryCoreApi::removePluginParameter('modules', 'core', 'misc.useShortUrls');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.1':
	    /* Set g2 version to 2.0-beta-1+ */

	case '0.9.2':
	    /* Changed the data cache format */

	case '0.9.3':
	    /* CSS refactor across entire app */

	case '0.9.4':
	    $gallery->guaranteeTimeLimit(30);
	    GalleryCoreApi::requireOnce(
		dirname(__FILE__) . '/classes/helpers/GalleryMimeTypeHelper_advanced.class');
	    $ret = GalleryMimeTypeHelper_advanced::initializeMimeTypes();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.5':
	    $gallery->guaranteeTimeLimit(30);
	    $ret = CoreModuleExtras::_createAccessListCompacterLock($module);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /*
	     * Choose an item that has permission rows.  Find all other items with the same
	     * exact permissions.  Create a new ACL, assign all those items to the ACL, delete
	     * those rows from the permissions table.  Repeat.
	     */
	    $totalRowsQuery = '
	    SELECT
	      COUNT(DISTINCT [GalleryPermissionMap::itemId])
	    FROM
	      [GalleryPermissionMap]
	    ';

	    $findItemIdQuery = '
	    SELECT
	      [GalleryPermissionMap::itemId], COUNT(*) AS C
	    FROM
	      [GalleryPermissionMap]
	    GROUP BY
	      [GalleryPermissionMap::itemId]
	    ORDER BY
	      C DESC
	    ';

	    $permissionRowCountQuery = '
	    SELECT
	      COUNT(*)
	    FROM
	      [GalleryPermissionMap]
	    WHERE
	      [GalleryPermissionMap::itemId] = ?
	    ';

	    $createAclQuery = '
	    INSERT INTO
	      [GalleryAccessMap] ([::accessListId], [::userId], [::groupId], [::permission])
	    SELECT
	      ?, [GalleryPermissionMap::userId],
	      [GalleryPermissionMap::groupId], [GalleryPermissionMap::permission]
	    FROM
	      [GalleryPermissionMap]
	    WHERE
	      [GalleryPermissionMap::itemId] = ?
	    ';

	    $findPossibleDupesQuery = '
	    SELECT
	      [GalleryPermissionMap=2::itemId], COUNT(*)
	    FROM
	      [GalleryPermissionMap=1], [GalleryPermissionMap=2]
	    WHERE
	      [GalleryPermissionMap=1::itemId] = ?
	      AND
	      [GalleryPermissionMap=1::userId] = [GalleryPermissionMap=2::userId]
	      AND
	      [GalleryPermissionMap=1::groupId] = [GalleryPermissionMap=2::groupId]
	      AND
	      [GalleryPermissionMap=1::permission] = [GalleryPermissionMap=2::permission]
	    GROUP BY
	      [GalleryPermissionMap=2::itemId]
	    HAVING
	      COUNT(*) = ?
	    ';

	    $refineDupesQuery = '
	    SELECT
	      [GalleryPermissionMap::itemId], COUNT(*)
	    FROM
	      [GalleryPermissionMap]
	    WHERE
	      [GalleryPermissionMap::itemId] IN (%s)
	    GROUP BY
	      [GalleryPermissionMap::itemId]
	    HAVING
	      COUNT(*) = ?
	    ';

	    $assignAclQuery = '
	    INSERT INTO
	      [GalleryAccessSubscriberMap] ([::itemId], [::accessListId])
	    SELECT DISTINCT
	      [GalleryPermissionMap::itemId], ?
	    FROM
	      [GalleryPermissionMap]
	    WHERE
	      [GalleryPermissionMap::itemId] IN (%s)
	    ';

	    $deleteOldPermsQuery = '
	    DELETE FROM
	      [GalleryPermissionMap]
	    WHERE
	      [GalleryPermissionMap::itemId] IN (%s)
	    ';

	    /* Determine how many items we are going to process for our status message */
	    list ($ret, $results) =
		$gallery->search($totalRowsQuery, array(), array('limit' => array('count' => 1)));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    if ($results->resultCount() == 0) {
		break;
	    }
	    $result = $results->nextResult();
	    $totalPermissionItems = $result[0];

	    $itemsProcessed = 0;
	    if ($totalPermissionItems > 0) {
		$ret = $statusMonitor->renderStatusMessage(
		    $module->translate('Upgrading permissions'),
		    null,
		    $itemsProcessed / $totalPermissionItems);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	    while ($totalPermissionItems > 0 && true) {
		$gallery->guaranteeTimeLimit(60);

		/* Find the next item in the permissions table */
		list ($ret, $results) = $storage->search($findItemIdQuery);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		if ($results->resultCount() == 0) {
		    break;
		}
		$result = $results->nextResult();
		list ($targetItemId, $permissionRowCount) = array((int)$result[0], (int)$result[1]);

		/* Create a new ACL */
		list ($ret, $newAclId) = $storage->getUniqueId();
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = $storage->execute($createAclQuery, array($newAclId, $targetItemId));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		/*
		 * Find all items that share the same permissions as the target.  I haven't
		 * figured out a good way to do aggregation without using temporary tables,
		 * which I'd like to avoid for portability.  So, figure out how many rows
		 * have at least as many matching permissions as our target item.  These
		 * are potentially dupes.  We'll refine them later on.
		 */
		list ($ret, $results) = $gallery->search(
		    $findPossibleDupesQuery, array($targetItemId, $permissionRowCount));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		$possibleDupeIds = array();
		while ($result = $results->nextResult()) {
		    $possibleDupeIds[] = (int)$result[0];
		}

		/*
		 * Process these queries in chunks since we may have thousands of items with the
		 * same permissions and we don't want to give the database a heart attack.
		 */
		$chunkSize = 200;
		while (!empty($possibleDupeIds)) {
		    $chunk = array_splice($possibleDupeIds, 0, $chunkSize);
		    $count = count($chunk);

		    /*
		     * Refine our dupes by eliminating ones that don't have exactly the same
		     * number of permission rows as our target.  Our target item is included
		     * in the dupes, so this will always return at least 1 row.
		     */
		    $markers = GalleryUtilities::makeMarkers($count);
		    $query = sprintf($refineDupesQuery, $markers);
		    list ($ret, $results) = $gallery->search(
			$query, array_merge($chunk, array($permissionRowCount)));
		    $possibleDupeIds = array();

		    $dupeIds = array();
		    while ($result = $results->nextResult()) {
			$dupeIds[] = (int)$result[0];
		    }

		    if (empty($dupeIds)) {
			/* No actual dupes?  Try the next chunk */
			continue;
		    }

		    $count = count($dupeIds);
		    $markers = GalleryUtilities::makeMarkers($count);

		    /* Set all the dupe items in this chunk to use the new ACL */
		    $query = sprintf($assignAclQuery, $markers);
		    $ret = $storage->execute($query, array_merge(array($newAclId), $dupeIds));
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }

		    /* Remove all the permission rows for the migrated items */
		    $query = sprintf($deleteOldPermsQuery, $markers);
		    $ret = $storage->execute($query, $dupeIds);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }

		    $itemsProcessed += $count;

		    $ret = $statusMonitor->renderStatusMessage(
			$module->translate(array(
			    'text' => 'Upgrading permissions (%d items complete, %d remaining)',
			    'arg1' => $itemsProcessed,
			    'arg2' => $totalPermissionItems - $itemsProcessed)),
			'',
			$itemsProcessed / $totalPermissionItems);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    if ($totalPermissionItems > 0) {
		$ret = $statusMonitor->renderStatusMessage(
		    $module->translate('Deleting old permission tables'),
		    '',
		    $itemsProcessed / $totalPermissionItems);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	    /* Removed GalleryPermissionsMap.  Drop the table */
	    $query = 'DROP TABLE [GalleryPermissionMap]';
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $query = "DELETE FROM [Schema] WHERE [Schema::name] = 'PermissionMap'";
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.6':
	    /* Added GalleryMaintenance table */

	case '0.9.7':
	    /*
	     * Change GalleryMaintenance::details column to be a serialized array.  The old data
	     * is transient so just delete it. Added FlushTemplatesTask, FlushDatabaseCacheTask
	     */
	    $gallery->guaranteeTimeLimit(30);
	    GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryMaintenanceMap.class');
	    $ret = GalleryMaintenanceMap::removeAllMapEntries();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.8':
	    /*
	     * Create 'plugins' and 'plugins_data' directories in g2data.  Remove trailing slash
	     * for config paths using substr so file_exists can detect either file or dir.
	     */
	    $gallery->guaranteeTimeLimit(30);
	    foreach (array(substr($gallery->getConfig('data.gallery.plugins'), 0, -1),
			   $gallery->getConfig('data.gallery.plugins') . 'modules',
			   $gallery->getConfig('data.gallery.plugins') . 'layouts',
			   substr($gallery->getConfig('data.gallery.plugins_data'), 0, -1),
			   $gallery->getConfig('data.gallery.plugins_data') . 'modules',
			   $gallery->getConfig('data.gallery.plugins_data') . 'layouts') as $dir) {
		if ($platform->file_exists($dir)) {
		    if ($platform->is_dir($dir)) {
			/* No need to do anything.  Except maybe we could check permissions here. */
		    } else {
			/* There's a file there.  There shouldn't be.  Move it out of the way */
			if (!@$platform->rename($newDir, "$newDir.old") ||
				!@$platform->mkdir($dir)) {
			    return GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
				"$dir already exists; unable to replace it");
			}
		    }
		} else {
		    if (!@$platform->mkdir($dir)) {
			return GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
						    "Unable to create $dir");
		    }
		}
	    }

	case '0.9.9':
	    /* Beta 2 release! */

	case '0.9.10':
	    /* Added BuildDerivativesTask */

	case '0.9.11':
	    /* Added GalleryRecoverPasswordMap */

	case '0.9.12':
	    /* Added ResetViewCountsTask */
	case '0.9.13':
	    /* Added SystemInfoTask */
	case '0.9.14':
	    /* Added SetOriginationTimestampTask */

	case '0.9.15':
	    /*
	     * Changed 'All Users' to 'Registered Users'
	     * Don't change if the user modified the name already!
	     */
	    list ($ret, $allUserGroupId) = $module->getParameter('id.allUserGroup');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($allUserGroupId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $group) = GalleryCoreApi::loadEntitiesById($allUserGroupId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $allUserGroupName = $group->getGroupName();
	    /* We used to entitize data in db; expect that from orignal group name: */
	    $originalGroupName = GalleryUtilities::utf8ToUnicodeEntities(
		$module->translate('All Users'));
	    if (!strcmp($allUserGroupName, $originalGroupName)) {
		$group->setGroupName($module->translate('Registered Users'));
		$ret = $group->save();
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		$ret = GalleryCoreApi::releaseLocks($lockId);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	case '0.9.16':
	    /* Beta 3 release! */

	case '0.9.17':
	    /* Split uploadLocalServer.dirs list into one parameter per entry */
	    list ($ret, $dirList) = $module->getParameter('uploadLocalServer.dirs');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    if (!empty($dirList)) {
		$dirList = explode(',', $dirList);
		for ($i = 1; $i <= count($dirList); $i++) {
		    $ret = $module->setParameter('uploadLocalServer.dir.' . $i, $dirList[$i - 1]);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }
	    $ret = $module->removeItemParameter('uploadLocalServer.dirs', 0);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.18':
	    /* Add image/x-photo-cd mime type */
	    list ($ret, $mimeType) = GalleryCoreApi::convertExtensionToMime('pcd');
	    if ($ret->isSuccess() && $mimeType == 'application/unknown') {
		$ret = GalleryCoreApi::addMimeType('pcd', 'image/x-photo-cd', false);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }

	case '0.9.19':
	    /* New multisite system and support for config.php upgrades */
	case '0.9.20':
	    /* Change view/controller separator: core:ShowItem -> core.ShowItem */
	case '0.9.21':
	    /* Session cookie change, requires new config.php variable */
	case '0.9.22':
	    /* GalleryModule::getItemLinks API change (GalleryModule API bumped to 0.13) */
	case '0.9.23':
	    /* Session cookie change, revert the last change and try something new */
	    foreach (array('cookie.path', 'cookie.domain') as $parameterName) {
		$ret = GalleryCoreApi::setPluginParameter('modules', 'core', $parameterName, '');
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	case 'end of upgrade path':
	    /*
	     * Leave this bogus case at the end of the legitimate case statements so that we
	     * always properly terminate our upgrade path with a break.
	     */
	    break;

	default:
	    return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					sprintf('Unknown module version %s', $currentVersion));
	}

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
     * Determine what changes to config.php are required for this upgrade.
     * @param string current core version
     * @return array of array('remove' => array of string regexp removals,
     *                        'add' => array of string additions)
     * @static
     * @private
     */
    function _prepareConfigUpgrade($currentVersion) {
	global $gallery;
	$configChanges = array();

	/**
	 * README: How to update the block below.
	 *
	 * If you add a new feature to the core module and revise the version, you should do the
	 * following.  Supposing the current version is 1.0.1 and you're adding 1.0.2. Go to the
	 * end of the switch and find the 'end of upgrade path' case.  Create a new case *above*
	 * that one with the old version number.  For our example you'd add: "case '1.0.1':" and
	 * then your code.  Do *not* put in a break statement. (Update upgrade function too)
	 */
	switch ($currentVersion) {
	case '0.8.4':
	case '0.8.5':
	case '0.8.6':
	case '0.8.7':
	case '0.8.8':
	case '0.8.9':
	case '0.8.10':
	case '0.8.11':
	case '0.8.12':
	case '0.8.13':
	case '0.8.14':
	case '0.8.15':
	case '0.8.16':
	case '0.8.17':
	case '0.9.0':
	case '0.9.1':
	case '0.9.2':
	case '0.9.3':
	case '0.9.4':
	case '0.9.5':
	case '0.9.6':
	case '0.9.7':
	case '0.9.8':
	case '0.9.9':
	case '0.9.10':
	case '0.9.11':
	case '0.9.12':
	case '0.9.13':
	case '0.9.14':
	case '0.9.15':
	case '0.9.16':
	case '0.9.17':
	case '0.9.18':
	case '0.9.19':
	    $add = array();
	    if (!isset($gallery->_config['allowSessionAccess'])) {
		/*
		 * This item was added to config.php before config.php upgrades were supported.
		 * Add it only if not already present.
		 */
		$add[] =
'/*
 * Allow a particular IP address to access the session (it still must know the
 * session id) even though it doesn\'t match the address/user agent that created
 * the session.  Put the address of validator.w3.org (\'128.30.52.13\') here to allow
 * validation of non-public Gallery pages from the links at the bottom of the page.
 */
$gallery->setConfig(\'allowSessionAccess\', false);
';
	    }

	    $add[] =
'/*
 * URL of Gallery codebase; required only for multisite install.
 */
$gallery->setConfig(\'galleryBaseUrl\', \'\');
';

	    $configChanges[] = array(
		'remove' => array('{/\*[^/]*\*/\s*\$gallery->setConfig\(\'galleryId\',.*?;\s*}s'),
		'add' => $add);

	case '0.9.20':
	case '0.9.21':
	    $add = array();

	    /* Generate cookieId */
	    list($usec, $sec) = explode(" ", microtime());
	    /* Note: srand() is required for php versions < 4.2  */
	    srand(100000 * ((float)$usec + (float)$sec));
	    $cookieId = substr(md5(rand()), 0, 6);

	    $add[] =
'
/*
 * Set the name for G2 session cookies. The name of the session cookie is
 * a concatenation of \'GALLERYSID_\' and cookieId, which is randomly generated
 * at Gallery installation time. You can change cookieId at any time, but if
 * you change it be aware of two things:
 * 1. Users have to login again after the change. They lose their old session.
 * 2. If multiple G2 installs are running on the same domain (in different paths or
 *    different subdomains) choose cookieId such that it is different for all G2
 *    installs on the same domain.
 */
$gallery->setConfig(\'cookieId\', \'' . $cookieId . '\');
';
	    $configChanges[] = array('remove' => array(), 'add' => $add);

	case '0.9.22':
	case '0.9.23':
	    /* Session cookie change, revert the last change and try something new */
	    $configChanges[] = array(
		'remove' => array('{/\*[^/]*\*/\s*\$gallery->setConfig\(\'cookieId\',.*?;\s*}s'),
		'add' => array());

	case 'end of upgrade path':
	    /*
	     * Leave this bogus case at the end of the legitimate case statements so that we
	     * always properly terminate our upgrade path with a break.
	     */
	    break;

	default:
	    $gallery->debug("Unknown module version $currentVersion in prepareConfigUpgrade()");
	}

	return $configChanges;
    }

    /**
     * Check if any changes to config.php are required for this upgrade.
     * @param string current core version
     * @return boolean true if change is required
     * @static
     */
    function isConfigUpgradeRequired($currentVersion) {
	$configChanges = CoreModuleExtras::_prepareConfigUpgrade($currentVersion);
	return !empty($configChanges);
    }

    /**
     * Perform upgrade of config.php file.
     * @param string current core version
     * @return object GalleryStatus a status code
     * @static
     */
    function performConfigUpgrade($currentVersion) {
	global $gallery;
	$platform = $gallery->getPlatform();

	$configFilePath = GALLERY_CONFIG_DIR . '/config.php';
	$configContents = implode('', $platform->file($configFilePath));
	if (empty($configContents) || strlen($configContents) < 100) {
	    return GalleryStatus::error(ERROR_MISSING_VALUE, __FILE__, __LINE__,
					'Unable to read current config.php contents');
	}

	$configChanges = CoreModuleExtras::_prepareConfigUpgrade($currentVersion);
	foreach ($configChanges as $change) {
	    foreach ($change['remove'] as $regexp) {
		$configContents = preg_replace($regexp, '', $configContents);
	    }
	    foreach ($change['add'] as $content) {
		$configContents = preg_replace('{\?>\s*\z}', $content . "\n?>\n", $configContents);
	    }
	}

	if (!$out = $platform->fopen($configFilePath, 'w')) {
	    return GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					'Unable to write to config.php');
	}
	if ($platform->fwrite($out, $configContents) < strlen($configContents)) {
	    return GalleryStatus::error(ERROR_PLATFORM_FAILURE, __FILE__, __LINE__,
					'Unable to write config.php contents');
	}
	$platform->fclose($out);

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

	$groupName = $module->translate('Registered Users');
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

	$groupName = $module->translate('Site Admins');
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

	$groupName = $module->translate('Everybody');
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

	$userName = 'guest';
	$fullName = $module->translate('Guest');
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

	$userName = 'admin';
	$fullName = $module->translate('Gallery Administrator');
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
	$title = $module->translate('Gallery');
	$description = $module->translate('This is the main page of your Gallery');
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

	$ret = GalleryCoreApi::addGroupPermission($album->getId(), $groupId, 'core.all');
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
     * Create the access list compactor lock entity
     *
     * @param object GalleryModule the core module
     * @return object GalleryStatus a status code
     * @static
     */
    function _createAccessListCompacterLock($module) {
	global $gallery;

	/* Do we already have a root? */
	list ($ret, $compacterLockId) = $module->getParameter('id.accessListCompacterLock');
	if ($compacterLockId) {
	    return GalleryStatus::success();
	}

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryEntity.class');
	$lock = new GalleryEntity();
	$lock->create();
	$ret = $lock->save(false);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $module->setParameter('id.accessListCompacterLock', $lock->getId());
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
	$regs[] = array('MaintenanceTask', 'OptimizeDatabaseTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'FlushTemplatesTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'FlushDatabaseCacheTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'BuildDerivativesTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'ResetViewCountsTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'SystemInfoTask', 'class', null);
	$regs[] = array('MaintenanceTask', 'SetOriginationTimestampTask', 'class', null);

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

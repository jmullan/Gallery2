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
 * @package UserAlbum
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Create a private top level album for new users.
 *
 * @package UserAlbum
 */
class UserAlbumModule extends GalleryModule {

    function UserAlbumModule() {
	global $gallery;
	$this->setId('useralbum');
	$this->setName('User Albums');
	$this->setDescription($gallery->i18n('Create an album for each new user'));
	$this->setVersion('0.8.1');
	$this->setGroup('gallery', $gallery->i18n('Gallery'));
	$this->setCallbacks('getSiteAdminViews');
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	GalleryCoreApi::registerEventListener('GalleryEntity::save', new UserAlbumModule(), true);
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    list($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);   
	    }
	    foreach (array('view' => 'everybody', 'fullSize' => '1', 'targetLocation' => $rootId)
		     as $key => $value) {
		$ret = $this->setModuleParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);   
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('User Albums'),
				 'view' => 'useralbum:UserAlbumSiteAdmin')));
    }

    /**
     * Event handler for GalleryEntity::save event
     * Create new top level album with appropriate permissions when a GalleryUser is created
     *
     * @param object GalleryEvent the event
     * @return object GalleryStatus a status code
     */
    function handleEvent($event) {
	$user = $event->getEntity();
	if (GalleryUtilities::isA($user, 'GalleryUser') &&
		$user->testPersistentFlag(STORAGE_FLAG_NEWLY_CREATED)) {

	    list ($ret, $core) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $module) = GalleryCoreApi::fetchAllPluginParameters('module', 'useralbum');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    // Create top level album..
	    list ($ret, $album) = GalleryCoreApi::createAlbum(
		$module['targetLocation'], $user->getUserName(), $user->getFullName(), '', '', '');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($album->getId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    // Set owner..
	    $album->setOwnerId($user->getId());
	    $ret = $album->save();
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $albumId = $album->getId();

	    // Set permissions..
	    $ret = GalleryCoreApi::removeItemPermissions($albumId);
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $ret = GalleryCoreApi::addGroupPermission($albumId, $core['id.adminGroup'], 'core.all');
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $ret = GalleryCoreApi::addUserPermission($albumId, $user->getId(), 'core.all');
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $viewPermissions = $module['fullSize'] ? array('core.viewAll')
						   : array('core.view', 'core.viewResizes');
	    switch ($module['view']) {
	    case 'everybody':
		$groupId = $core['id.everybodyGroup'];
		break;
	    case 'allusers':
		$groupId = $core['id.allUserGroup'];
		break;
	    }

	    if (isset($groupId)) {
		foreach ($viewPermissions as $permission) {
		    $ret = GalleryCoreApi::addGroupPermission($albumId, $groupId, $permission);
		    if ($ret->isError()) {
			GalleryCoreApi::releaseLocks($lockId);
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    $ret = GalleryCoreApi::releaseLocks($lockId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	return GalleryStatus::success();
    }
}
?>

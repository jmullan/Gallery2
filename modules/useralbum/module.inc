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
class UserAlbumModule extends GalleryModule /* and GalleryEventListener */ {

    function UserAlbumModule() {
	global $gallery;
	$this->setId('useralbum');
	$this->setName('User Albums');
	$this->setDescription($gallery->i18n('Create an album for each new user'));
	$this->setVersion('0.8.6');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('registerEventListeners|getSiteAdminViews|getSystemLinks');
	$this->setRequiredCoreApi(array(2, 0));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	$listener = new UserAlbumModule();
	GalleryCoreApi::registerEventListener('GalleryEntity::save', $listener, true);
	GalleryCoreApi::registerEventListener('GalleryEntity::delete', $listener);
	GalleryCoreApi::registerEventListener('Gallery::Login', $listener);
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'useralbum');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	foreach (array('view' => 'everybody', 'fullSize' => '1', 'targetLocation' => $rootId,
		       'loginRedirect' => 0, 'homeLink' => 0)
		as $key => $value) {
	    if (!isset($params[$key])) {
		$ret = $this->setParameter($key, $value);
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
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks() {
	$links = array();
	/* Check if link is enabled.. */
	list ($ret, $homeLink) =
	    GalleryCoreApi::getPluginParameter('module', 'useralbum', 'homeLink');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($homeLink)) {
	    global $gallery;
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/UserAlbumHelper.class');

	    list ($ret, $albumId) = UserAlbumHelper::fetchUserAlbumId($gallery->getActiveUserId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (isset($albumId)) {
		$links[] = array('text' => $this->translate('Your Album'),
				 'params' => array('view' => 'core:ShowItem', 'itemId' => $albumId));
	    }
	}
	return array(GalleryStatus::success(), $links);
    }

    /**
     * Event handler for GalleryEntity::save, ::delete and Gallery::Login events
     * Create new top level album with appropriate permissions when a GalleryUser is created
     * Reset the targetAlbum to root if the target is ever deleted
     * Redirect to user album after login, if enabled in site admin
     *
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	$result = null;
	switch ($event->getEventName()) {
	case 'GalleryEntity::save':
	    $user = $event->getEntity();
	    if (GalleryUtilities::isA($user, 'GalleryUser') &&
		    $user->testPersistentFlag(STORAGE_FLAG_NEWLY_CREATED)) {
		GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/UserAlbumHelper.class');

		$ret = UserAlbumHelper::createUserAlbum($user);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    break;

	case 'GalleryEntity::delete':
	    $entity = $event->getEntity();

	    /* We don't care unless it's an album */
	    if (!GalleryUtilities::isA($entity, 'GalleryAlbumItem')) {
		break;
	    }

	    list ($ret, $targetId) =
		GalleryCoreApi::getPluginParameter('module', 'useralbum', 'targetLocation');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if ($entity->getId() == $targetId) {
		list ($ret, $rootId) =
		    GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = GalleryCoreApi::setPluginParameter('module', 'useralbum',
							  'targetLocation', $rootId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    break;

	case 'Gallery::Login':
	    /* Check if redirect is enabled.. */
	    list ($ret, $loginRedirect) =
		GalleryCoreApi::getPluginParameter('module', 'useralbum', 'loginRedirect');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (empty($loginRedirect)) {
		break;
	    }

	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/UserAlbumHelper.class');
	    $user = $event->getEntity();

	    list ($ret, $albumId) = UserAlbumHelper::fetchUserAlbumId($user->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($albumId)) {
		/* Return a redirect to the user album.. */
		$result = array('view' => 'core:ShowItem', 'itemId' => $albumId);
	    }
	    break;
	}
	return array(GalleryStatus::success(), $result);
    }
}
?>

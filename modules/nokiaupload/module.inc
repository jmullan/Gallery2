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
 * @package NokiaUpload
 * @author Jerome Rannikko <jeromer@hotpop.com>
 */

/**
 * This module implements the Nokia Image Upload Server API v1.0.
 * With this module users can upload pictures straight from their 
 * mobile phone (e.g. Nokia 3650 and 6600) to their Gallery account.
 * See README file in this directory for more information and instructions.
 *
 * @package NokiaUpload
 */
class NokiaUploadModule extends GalleryModule {

    function NokiaUploadModule() {
	global $gallery;
	
	$this->setId('nokiaupload');
	$this->setName('Nokia Image Uploader');
	$this->setVersion('0.5');
	$this->setDescription($gallery->i18n('Module implementing Nokia Image Upload Server API v1.1'));
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
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), false);
	}

	$installed = false;
	if ($version != $this->getVersion()) {

	    if (empty($version)) {
		/* This is an initial install. */

		/* Create group for the mobile users. */
		list ($ret, $groupId) = $this->_createMobileUserGroup();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}


		list ($ret, $albumId) = $this->_createUploadAlbum();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/*
		 * Set permissions for the mobile upload album. 
		 * Only members of Mobile Users group can add data and albums to Phone Uploads
		 * album. Admins can do everything and other users can only view items.
		 * First we remove all possible inherited permissions and then add
		 * only the permissions we want.
		 */
		$ret = GalleryCoreApi::removeItemPermissions($albumId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/* Few ids that we will need. */
		list ($ret, $everybodyId) = 
		    GalleryCoreApi::getPluginParameter('module', 'core', 'id.everybodyGroup');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		list ($ret, $adminGroupId) = 
		    GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/* Admin permissions */
		$ret = GalleryCoreApi::addGroupPermission($albumId, $adminGroupId, 'core.all');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/* Mobile user group permissions */
		$ret = GalleryCoreApi::addGroupPermission($albumId, $groupId, 'core.addDataItem');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
		$ret = GalleryCoreApi::addGroupPermission($albumId, $groupId, 'core.addAlbumItem');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		/* Everybody else can only view the items. */
		$ret = GalleryCoreApi::addGroupPermission($albumId, $everybodyId, 'core.viewAll');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}

		$installed = true;
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), false);
	    }
	}
	
	return array(GalleryStatus::success(), $installed);
    }


    /**
     * @see GalleryModule::canBeAutoInstalled
     */
    function canBeAutoInstalled() {
	return true;
    }
	

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration. */
	return array(GalleryStatus::success(), true);
    }


    /*
     * Create new group for mobile phone users. 
     *
     * All users who try to use the Nokia Image Uploader module 
     * will be added to this group in LoginController.
     *
     * @return object GalleryStatus a status code
     *         int id of the Mobile user group
     */
    function _createMobileUserGroup() {
	/* Check if group already exists. */
	list ($ret, $id) = $this->getModuleParameter('id.mobileGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($id)) {
	    return array(GalleryStatus::success(), $id);
	}

	/* Create new group. */
	list ($ret, $group) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($group)) {
	    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	}
	
	$name = GalleryUtilities::utf8ToUnicodeEntities($this->translate('Mobile Users'));
	$ret = $group->create($name);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$ret = $this->setModuleParameter('id.mobileGroup', $group->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $group->getId());
    }
    

    /* 
     * Create new album on the top level of gallery for uploading images.
     * 
     * @return object GalleryStatus a status code
     *         int id of the upload album
     */
    function _createUploadAlbum() {
	global $gallery;

	/* Check if album already exists. */
	list ($ret, $id) = $this->getModuleParameter('id.uploadAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($id)) {
	    return array(GalleryStatus::success(), $id);
	}

	/* 
	 * We want admin user to own our album, so we need to make sure 
	 * we are logged is as admin user. 
	 */
	list ($ret, $adminGroupId) = 
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $isAdmin) = 
	    GalleryCoreApi::isUserInGroup($gallery->getActiveUserId(), $adminGroupId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!$isAdmin) {
	    list ($ret, $results) = GalleryCoreApi::fetchUsersForGroup($adminGroupId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* $results is array(user id => user name), we need one user name. */
	    $username = $results[key($results)];

	    list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($username);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $gallery->setActiveUser($user);
	}

        /* Get the root album id and get lock to the album. */
	list ($ret, $rootAlbumId) = 
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLock($rootAlbumId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Create new album item. */
	list ($ret, $instance) =
	    GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryAlbumItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	if (!isset($instance)) {
	    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	}

	/* Choose a name for the album. Hopefully it's unique.*/
	$albumName = 
	    GalleryUtilities::utf8ToUnicodeEntities($this->translate('nokia-image-upload-album'));
	$ret = $instance->create($rootAlbumId, $albumName);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Set the album info and save it. */
	$urlGen = $gallery->getUrlGenerator();
	$url = $urlGen->generateUrl(array('controller' => 'nokiaupload:Login'));
	/* We don't want the session id in our url. */
	$session =& $gallery->getSession();
	list($sidParam, $sid) = $session->getSessionDescriptor();
	$pattern = '/&(amp;)?'. GALLERY_FORM_VARIABLE_PREFIX. $sidParam. '='. $sid. '/';
	$url = preg_replace($pattern, '', $url);
	
	$title = GalleryUtilities::utf8ToUnicodeEntities($this->translate(
	    'Pictures from mobile phones'));
	$summary = GalleryUtilities::utf8ToUnicodeEntities($this->translate(
	    'To upload to this album you need Image Uploader enabled mobile phone '
	    . '(e.g. Nokia 3650 and 6600). See album description for more details.'));
	$description = GalleryUtilities::utf8ToUnicodeEntities($this->translate(
	    'You can  upload images to this album from your Image Uploader enabled mobile phone '
	    . "(e.g. Nokia 3650 and 6600) using the phone's built-in Image Uploader. "
	    . 'New albums will be created under this folder.'
	    . "<br />Web address is $url"
	    . '<br />Username and Password are your Gallery 2 username and password.'));
	
	$instance->setTitle($title);
	$instance->setSummary($summary);
	$instance->setDescription($description);
	
	$ret = $instance->save();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $this->setModuleParameter('id.uploadAlbum', $instance->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $instance->getId());
    }

}
?>

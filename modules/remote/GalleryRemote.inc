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
 * @package Remote
 * @subpackage UserInterface
 * @author Pierre-Luc Paour <paour@users.sourceforge.net>
 */

/**
 * Required classes
 */
require(dirname(__FILE__) . '/classes/GalleryRemoteProperties.class');
require(dirname(__FILE__) . '/classes/GalleryRemoteConstants.class');

/**
 * This controller fields requests from Gallery Remote and perform any required changes
 * to the data model.
 *
 * @package Remote
 * @subpackage UserInterface
 */
class GalleryRemoteController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
    	$status = array();
    	$error = array();
        $response = new GalleryRemoteProperties();
	$grStatusCodes = GalleryRemoteConstants::getStatusCodes();

	if (!empty($form['cmd'])) {
	    switch ($form['cmd']) {
	    case 'login':
		$ret = $this->login($form, $response);
		if ($ret->isError()) {
		    $status['controllerError'] = $ret->wrap(__FILE__, __LINE__);
		}
		break;
                        
	    case 'fetch-albums-prune':
		$ret = $this->fetchAlbums($form, $response);
		if ($ret->isError()) {
		    $status['controllerError'] = $ret->wrap(__FILE__, __LINE__);
		}
		break;
                    
	    case 'add-item':
		$ret = $this->addDataItem($form, $response);
		if ($ret->isError()) {
		    $response->setProperty('status', $grStatusCodes['UPLOAD_PHOTO_FAIL']);
		    $response->setProperty('status_text', sprintf("Upload failed: '%s'.", $ret->getErrorMessage()));
		}
		break;                  
                    
	    default:
		$response->setProperty('status', $grStatusCodes['UNKNOWN_COMMAND']);
		$response->setProperty('status_text', "Command '$cmd' unknown.");
		break;
	    }
	} else {
	    $response->setProperty('status', $grStatusCodes['UNKNOWN_COMMAND']);
	    $response->setProperty('status_text', 'No cmd passed');
	}
        
    	$status['controllerResponse'] = $response;
    
    	$results['delegate']['view'] = 'remote:GalleryRemote';
	$results['status'] = $status;
	$results['error'] = $error;
    	return array(GalleryStatus::success(), $results);
    }

    /**
     * Log into Gallery
     *
     * @param form array key value pairs from Gallery Remote
     * @param object GalleryRemoteProperties a reference to our response object
     * @return object GalleryStatus a status code
     */
    function login($form, &$response) {
	global $gallery;
		    
	$grStatusCodes = GalleryRemoteConstants::getStatusCodes();
	$grVersionCodes = GalleryRemoteConstants::getVersionCodes();

	/* If they don't provide a username, try the anonymous user */
	if (!empty($form['uname'])) {
	    list ($ret, $user) = GalleryCoreApi::fetchUserByUsername($form['uname']);
	    if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $password = isset($form['password']) ? $form['password'] : '';
	    if ($user != null && $user->isCorrectPassword($password)) {
		// login successful
		$gallery->setActiveUserId($user->getId());
		$response->setProperty('server_version', sprintf('%d.%d', $grVersionCodes['MAJ'], $grVersionCodes['MIN']));
		$response->setProperty('status', $grStatusCodes['SUCCESS']);
		$response->setProperty('status_text', 'Login successful.');
		return GalleryStatus::success();
	    } else {
		// login unsuccessful
		$response->setProperty('status', $grStatusCodes['PASSWORD_WRONG']);
		$response->setProperty('status_text', 'Password incorrect.');
		return GalleryStatus::success();
    	    }
	} else {
	    // They're logged in as the guest account
	    list ($ret, $anonymousUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	    if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $gallery->setActiveUserId($anonymousUserId);

	    $response->setProperty('debug_anonymous_login', true);
	    $response->setProperty('server_version', sprintf('%d.%d', $grVersionCodes['MAJ'], $grVersionCodes['MIN']));
	    $response->setProperty('status', $grStatusCodes['SUCCESS']);
	    $response->setProperty('status_text', 'Login successful.');
	    return GalleryStatus::success();
	}
    }
    
    /**
     * Load the album list into our response object
     *
     * @param form array key value pairs from Gallery Remote
     * @param object GalleryRemoteProperties a reference to our response object
     * @return object GalleryStatus a status code
     */
    function fetchAlbums($form, &$response) {
	global $gallery;

	$grStatusCodes = GalleryRemoteConstants::getStatusCodes();
	
	// find and load the list of albums we can view
        list ($ret, $albumIds) = GalleryCoreApi::fetchAllItemIds('GalleryAlbumItem');
    	if ($ret->isError()) {
    	    return $ret->wrap(__FILE__, __LINE__);
    	}

    	if (empty($albumIds)) {
	    $response->setProperty('status', $grStatusCodes['SUCCESS']);
	    $response->setProperty('status_text', 'No viewable albums.');
	    return GalleryStatus::success();
    	}

	// Load the permissions for all those albums
	list ($ret, $permissionsTable) = GalleryCoreApi::fetchPermissionsForItems($albumIds);
    	if ($ret->isError()) {
    	    return $ret->wrap(__FILE__, __LINE__);
    	}

	// And load all the entities
	list ($ret, $albums) = GalleryCoreApi::loadEntitiesById($albumIds);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	// Now add all the albums to the tree
	$i = 1;
	foreach ($albums as $album) {
	    $perms = $permissionsTable[$album->getId()];
	    
	    /* Use id because path component is not unique (BM guessing at PLP's logic) */
	    $response->setProperty('album.name.' . $i, $album->getId());
	    $response->setProperty('album.title.' . $i, $album->getTitle());
	    $response->setProperty('album.summary.' . $i, $album->getSummary());
	    $response->setProperty('album.parent.' . $i, $album->getParentId());
	    $response->setProperty('album.perms.add.' . $i, isset($perms['core.addDataItem']) ? 'true' : 'false');
	    $response->setProperty('album.perms.write.' . $i, isset($perms['core.edit']) ? 'true' : 'false');
	    $response->setProperty('album.perms.del_alb.' . $i, isset($perms['core.delete']) ? 'true' : 'false');
	    $response->setProperty('album.perms.create_sub.' . $i, isset($perms['core.addAlbumItem']) ? 'true' : 'false');

	    $i++;
	}
	
	$response->setProperty('album_count', sizeof($albums));
	$response->setProperty('status', $grStatusCodes['SUCCESS']);
	$response->setProperty('status_text', 'Fetch-albums successful.');

        return GalleryStatus::success();
    }

    /**
     * Add a data item to Gallery
     *
     * @param form array key value pairs from Gallery Remote
     * @param object GalleryRemoteProperties a reference to our response object
     * @return object GalleryStatus a status code
     */
    function addDataItem($form, &$response) {
	global $gallery;

	$grStatusCodes = GalleryRemoteConstants::getStatusCodes();

	$file = GalleryUtilities::getFile('userfile');
	$parentId = $form['set_albumName'];	  // TODO: Eliminate this throwback to G1  
	    
	/* Make sure we have permission do edit this item */
	$ret = GalleryCoreApi::assertHasItemPermission($parentId, 'core.addDataItem');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
        
	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLock($parentId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (empty($file['name'])) {
	    $response->setProperty('status', $grStatusCodes['NO_FILENAME']);
	    $response->setProperty('status_text', 'Filename not specified.');
	    return GalleryStatus::success();
    	}

	/* Get the mime type from the upload info. */
	$mimeType = $file['type'];

	/*
	 * If we don't get useful data from that or its a type we don't
	 * recognize, take a swing at it using the file name.
	 */
	if ($mimeType == 'application/octet-stream' ||
	    $mimeType == 'application/unknown' ||
	    GalleryUtilities::convertMimeToExtension($mimeType) == null) {
	    $extension = GalleryUtilities::getFileExtension($file['name']);
	    $mimeType = GalleryUtilities::convertExtensionToMime($extension);
	}

	list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum($file['tmp_name'],
							       basename($file['name']),
							       basename($file['name']),
							       $form['caption'],
							       $form['caption'],
							       $mimeType,
							       $parentId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::releaseLocks($lockIds);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$response->setProperty('status', $grStatusCodes['SUCCESS']);
	$response->setProperty('status_text', 'Add photo successful.');

    	return GalleryStatus::success();
    }
}

/**
 * This is an immediate view that emits well formed Gallery Remote protocol 2 output
 *
 * @package Remote
 * @subpackage UserInterface
 */
class GalleryRemoteView extends GalleryView {
    
    /**
     * @see GalleryView::isImmediate()
     */
    function isImmediate() {
        return true;
    }
    
    /**
     * @see GalleryView::isImmediate()
     */
    function renderImmediate($status, $error) {
        header("Content-type: text/plain");

	if (isset($status['controllerError'])) {
            echo 'Error: ' . $status['controllerError']->getAsText();
        }

	if (isset($status['controllerResponse'])) {
	    echo $status['controllerResponse']->listProperties();
	}
        
        if (isset($controllerError)) {
            return $ret->wrap(__FILE__, __LINE__);
        } else {
            return GalleryStatus::success();
        }
    }
}
?>

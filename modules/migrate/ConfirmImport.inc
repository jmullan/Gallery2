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
 * @package Migrate
 * @subpackage UserInterface
 * @author Jesse Mullan <jmullan@visi.com>
 */

class ConfirmImportController extends GalleryController {
    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
        global $gallery;

        // Verify that active user is an admin
        $ret = GalleryUserHelper::assertSiteAdministrator();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
	
	$albumsPath = GalleryUtilities::getRequestVariables('albumsPath');

	$error = array();
	$status = array('userImportFailure'=>array(),
			'userImportSuccess'=>array(),
			'albumImportFailure'=>array(),
			'albumImportSuccess'=>array()
			);
	if (isset($form['action']['import'])) {
	    list ($ret, $uidMap) = Gallery1DataParser::getUserUids($albumsPath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!isset($form['migrateUser'])) {
		$form['migrateUser']=array();
	    }
	    foreach (array_keys ($form['migrateUser']) as $uid) {
		$userName = $uidMap[$uid];
		list ($ret, $fields) =
		    Gallery1DataParser::getUserFieldsByUsername($albumsPath, $userName);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/*
		 * If all the right fields are in place then go ahead and
		 * create the user.
		 */
		list ($ret, $user) = GalleryFactory::newInstance('GalleryEntity', 'GalleryUser');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if (!isset($user)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}
		
		$ret = $user->create($fields['username']);
		if ($ret->isError()) {
		    if (!($ret->getErrorCode() & ERROR_COLLISION)) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    // Set our error status and fall back to the view.
		    $status['userImportFailure'][$userName] = 1;
		} else {
		    $user->setEmail($fields['email']);
		    $user->setHashedPassword($fields['password']);
		    $user->setFullName($fields['fullname']);

		    /*
		     $fields['isAdmin'] // see core/module.inc:_createAdminUser() to see how to do that
		     $fields['canCreateAlbums'] // if they have that perm, give them "core.addAlbumItem"
		                                // permission on the root album
		     */
		    
		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['userImportSuccess'][$userName] = 1;
		}
	    }
	    
            /* Import Any Selected Albums */
	    /* First initialize the $form['sourceAlbums'] array to avoid php
	     * warnings
	     */

            if (!isset($form['sourceAlbums'])) {
		$form['sourceAlbums']=array();
	    }
	    if (!isset($form['destinationAlbumID'])) {
		/* Get all possible destinations (where user has write
		permission) */
		list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$form['destinationAlbumID']=$rootId;
	    }
	    $destinationAlbumID = $form['destinationAlbumID'];
	    foreach (array_keys ($form['sourceAlbums']) as $sourceAlbumName) {
		list ($ret, $albumfields[$sourceAlbumName]) =
			Gallery1DataParser::loadAlbumFields($albumsPath.$sourceAlbumName);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $i=0;
	    if(!isset($albumfields)){
		$albumfields = array();
	    }
	    while ($albumfields && $i<count($form['sourceAlbums'])^2) {
		$album = array_shift($albumfields);
		if (!in_array($album['parentAlbumName'],array_keys($form['sourceAlbums']))) {
		    list ($ret, $finishedAlbums[$album['name']])=ConfirmImportController::importAlbum($destinationAlbumID,$album);
		} else if (in_array($album['parentAlbumName'],array_keys($finishedAlbums))){
		    list ($ret, $finishedAlbums[$album['name']])=ConfirmImportController::importAlbum($finishedAlbums[$album['parentAlbumName']],$album);
		}
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		} else {
		    $status['albumImportSuccess'][$album['name']] = 1;
		}
		$i++;
	    }


	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'migrate:ImportResults';
	}
	
	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'migrate:ConfirmImport';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
    function importAlbum($itemId,$album) {
	global $gallery;

	/* $itemId = GalleryUtilities::getRequestVariables('itemId'); */

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addAlbumItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Try to load targeted parent */
	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get a lock on said parent */
	list ($ret, $lockIds[]) = $gallery->acquireReadLock($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* create arrays to return indicating success/failure of importation */
	$status = array();
	$error = array();

	/* Check the new album's path component to see if it is valid on the
	 * local filesystem
	 */
	$platform = $gallery->getPlatform();
	if (empty($album['name'])) {
	    $error[] = 'form.error.pathComponent.missing';
	} else if (!$platform->isLegalPathComponent($album['name'])) {
	    $error[] = 'form.error.pathComponent.invalid';
	}
	/* If everything is good so far, we create a new instance to be our new
	 * album
	 */
	if (empty($error)) {
	    list ($ret, $instance) =
		    GalleryFactory::newInstance('GalleryEntity', 'GalleryAlbumItem');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (!isset($instance)) {
		return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
			     null);
	    }  
	    /* this is where the album is actually created */	    
	    $ret = $instance->create($itemId, $album['name']);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_COLLISION) {
		    $error[] = 'form.error.pathComponent.collision';
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    if (empty($error)) {
		$id = $instance->getId();
	    /*
             * Array of example data
	     * (
	     *   +[title] => Test Album One
	     *   +[description] => No description
	     *   +[summary] =>
	     *    [nextname] => aaa
	     *    [bgcolor] =>
	     *    [textcolor] =>
	     *    [linkcolor] =>
	     *    [font] => verdana
	     *    [border] => 1
	     *    [bordercolor] => black
	     *    [returnto] => yes
	     *    [thumb_size] => 150
	     *    [resize_size] => 400
	     *    [rows] => 5
	     *    [cols] => 5
	     *    [fit_to_window] => no
	     *    [use_fullOnly] => no
	     *    [print_photos] => none
	     *    [use_exif] => yes
	     *    [perms] => Array
	     *        ( [canRead] => Array
	     *            ( [everybody] => 1 )
	     *            [canViewFullImages] => Array
	     *            ( [everybody] => 1 )
	     *        )
	     *   +[parentAlbumName] => .root
	     *   +[clicks] => 0
	     *   +[clicks_date] => 1056014708
	     *    [display_clicks] => yes
	     *    [public_comments] => yes
	     *    [serial_number] => 8
	     *    [extra_fields] => Array
	     *        ( [0] => Description
	     *        )
	     *    [cached_photo_count] => 2
	     *    [photos_separate] => 1
	     *    [name] => album01
	     *    [owner] => 1054014347u1233740678
	     *    [last_mod_time] => 1056015246
	     */

		/* load up the album with metadata from the old album */ 
		$instance->setTitle($album['title']);
		$instance->setSummary($album['summary']);
		$instance->setKeywords('');
		$instance->setDescription($album['description']);

# setorderBy
# setorderDirection
# setownerId
# settheme
		$instance->setcreationTimestamp($album['last_mod_time']);
		$instance->setviewedSinceTimestamp($album['clicks_date']);
		/* Save the new album */	    
		$ret = $instance->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		/* Click counts must be set after the item is first saved */
		$ret = GalleryItemAttributesMap::setViewCount($id, $album['clicks']);
		if ($ret->isError()) {
		    return $this->failWithStatus($ret->wrap(__FILE__, __LINE__));
		}
	    }
	}
	/* we can let the parent album (and anything else that we might
	 * have tied up) be edited by others now
	 */
	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($id)) {
	    return array(GalleryStatus::success(), $id);
	} else {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}	
    }
}	    

class ConfirmImportView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;
	$existingAlbums = array();
	if (!isset($form['sourceAlbums'])) {
	    $form['sourceAlbums']=array();
	}
	$albumsPath = GalleryUtilities::getRequestVariables('albumsPath');
        $destinationAlbumID = $form['destinationAlbumID'];
	list ($ret, $uids) = Gallery1DataParser::getUserUids($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	list ($ret, $albums) = Gallery1DataParser::getAlbumList($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	list ($ret, $targetAlbum) = $gallery->loadEntitiesById($destinationAlbumID);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	foreach ($form['sourceAlbums'] as $sourceAlbumName) {
	    list ($ret, $albumfields[$sourceAlbumName]) = Gallery1DataParser::loadAlbumFields($albumsPath.$sourceAlbumName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	$i=0;
	if(!isset($albumfields)){
	    $albumfields = array();
	}
	while ($albumfields && $i<count($form['sourceAlbums'])^2) {
	    $existingAlbumId = FALSE;
	    $album = array_shift($albumfields);
	    if (!in_array($album['parentAlbumName'],$form['sourceAlbums'])) {
		list ($ret, $existingAlbumId) =
			GalleryFileSystemEntityHelper::fetchItemIdByPath($album['name']);
	    }
	    if ($ret->isError()) {
		echo "<pre>err:\n";
		print_r($ret);
		echo "</pre>";
		if (!$ret->getErrorCode() & MISSING_OBJECT) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    } else {
		$existingAlbums[$album['name']] = $existingAlbumId;
	    }
	    $i++;
	}

	$ConfirmImport = array();
	$ConfirmImport['uids'] = $uids;
	$ConfirmImport['albums'] = $albums;
	$ConfirmImport['albumsPath'] = $albumsPath;
	$ConfirmImport['existingAlbums'] = $existingAlbums;
        $ConfirmImport['destinationAlbumID'] = $destinationAlbumID;
        $ConfirmImport['targetAlbum'] = $targetAlbum;
        $template->setVariable('controller', 'migrate:ConfirmImport');
	$template->setVariable('ConfirmImport', $ConfirmImport);
	return array(GalleryStatus::success(), '', 'modules/migrate/templates/ConfirmImport.tpl');
    }
}
?>
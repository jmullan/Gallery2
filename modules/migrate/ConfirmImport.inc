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
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();
	
        /* Verify that active user is an admin */
        $ret = GalleryUserHelper::assertSiteAdministrator();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
	
	$albumsPath = GalleryUtilities::getRequestVariables('albumsPath');

	/* build framework for error and status arrays */
	$error = array();
	$status = array('userImportFailure'=>array(),
			'userImportSuccess'=>array(),
			'albumImportFailure'=>array(),
			'albumImportSuccess'=>array()
			);
	/* The other option is "cancel", I believe */
	if (isset($form['action']['import'])) {

	    /* get list of userids in advance */
	    list ($ret, $uidMap) = Gallery1DataParser::getUserUids($albumsPath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* if no users were selected, create an empty array to avoid later
	     *php warnings
	     */
	    if (!isset($form['migrateUser'])) {
		$form['migrateUser']=array();
	    }

	    /* go through the list of chosen users */
	    foreach (array_keys ($form['migrateUser']) as $uid) {

		/* convert from uid to username */
		$userName = $uidMap[$uid];
		list ($ret, $fields) =
		    Gallery1DataParser::getUserFieldsByUsername($albumsPath, $userName);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/*
		 * Go ahead and create the user instance
		 */
		list ($ret, $user) = GalleryFactory::newInstance('GalleryEntity', 'GalleryUser');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Verify that the user was created successfully */
		if (!isset($user)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}
		
		/* Turn the instance into a real boy/girl
		 * This is where the user is actually created, everything
		 * before this was simply building the framework.
		 */
		$ret = $user->create($fields['username']);

		/* Was there an error? */
		if ($ret->isError()) {
		    /* ERROR_COLLISION is when you try to create something that
		     * already exists.
		     */
		    if (!($ret->getErrorCode() & ERROR_COLLISION)) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    /* Other errors are apparently okay.  Note them and
		     * continue
		     */
		    // Set our error status and fall back to the view.
		    $status['userImportFailure'][$userName] = 1;
		} else {
		    /* Apparently the creation was successful.  Now we can
		     * start setting the various metadata associated with the
		     * user
		     */
		    $user->setEmail($fields['email']);
		    $user->setHashedPassword($fields['password']);
		    $user->setFullName($fields['fullname']);

		    /*
		     * Here's some stuff to add
		     * TODO
		     * $fields['isAdmin'] see core/module.inc:_createAdminUser() to see how to do that
		     * $fields['canCreateAlbums'] if they have that perm, give them "core.addAlbumItem"
		     * permission on the root album
		     */

		    /* Save this user to the database */
		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    /* Set a positive note for later.  Hooray! */
		    $status['userImportSuccess'][$userName] = 1;
		}
	    }
	    
            /* Import Any Selected Albums
	     *
	     */
	    
	    /* First initialize the $form['sourceAlbums'] array to avoid php
	     * warnings
	     */
            if (!isset($form['sourceAlbums'])) {
		$form['sourceAlbums']=array();
	    }

	    /* Check to see if the user selected a destination.  If not,
	     * default to the root album of the new gallery install.
	     */
	    if (!isset($form['destinationAlbumID'])) {
		list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$form['destinationAlbumID']=$rootId;
	    }
	    /* Convert the form variable into a local temporary variable */
	    $destinationAlbumID = $form['destinationAlbumID'];

	    /* Go through the list of selected gallery1 albums to import */
	    foreach (array_keys ($form['sourceAlbums']) as $sourceAlbumName) {
		/* attempt to load the metadata from the selected album into a
		 * local cache for later manipulation
		 */
		list ($ret, $albumfields[$sourceAlbumName]) =
			Gallery1DataParser::loadAlbumFields($albumsPath.$sourceAlbumName);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $i=0;
	    /* First initialize the $albumfields array to avoid php warnings */
	    if(!isset($albumfields)){
		$albumfields = array();
	    }
	    /* Go through the array of albums' metadata one album at a time.
	     * We limit the number of passes through this list to n^2 times to
	     * avoid an infinite loop.  This allows us to make sure that we add
	     * parent albums first by taking albums out of the list as they are
	     * handled.
	    */
	    while ($albumfields && $i<count($form['sourceAlbums'])^2) {
		$album = array_shift($albumfields);
		/* if the album's parent is not in the list of sourcealbums,
		 * load it into the targeted G2 top album as set in
		 * $destinationAlbumID
		 */
		$targetAlbumID = FALSE;
		$newAlbumInstanceId = FALSE;
		if (!in_array($album['parentAlbumName'],array_keys($form['sourceAlbums']))) {
		    $targetAlbumID= $destinationAlbumID;
		} else if (in_array($album['parentAlbumName'],array_keys($finishedAlbums))){
		    /* if the album's parent has already been imported, import
		     * it into the parent
		     */
		    $targetAlbumID = $finishedAlbums[$album['parentAlbumName']];
		}
		if ($targetAlbumID) {
		    // list ($ret, $importedAlbumID)=ConfirmImportController::importAlbum($targetAlbumID,$album);
		    /* crappy procedural code ;) */
		    /* Make sure we have permission do edit the target item */
		    $ret = GalleryUserHelper::assertHasItemPermission($targetAlbumID, 'core.addAlbumItem');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    /* Try to load targeted parent */
		    list ($ret, $targetAlbumObject) = $gallery->loadEntitiesById($targetAlbumID);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    /* Get a lock on said parent */
		    list ($ret, $importLockIds[]) = $gallery->acquireReadLock($targetAlbumObject->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Check the new album's path component to see if it is valid on the
		     * local filesystem
		     */
		    $platform = $gallery->getPlatform();
		    if (empty($album['name'])) {
			$error[] = 'form[error][pathComponent][missing]';
		    } else if (!$platform->isLegalPathComponent($album['name'])) {
			$error[] = 'form[error][pathComponent][invalid]';
		    }
		    /* If everything is good so far, we create a new instance to be our new
		     * album
		     */
		    if (empty($error)) {
			list ($ret, $newAlbumInstance) =
				GalleryFactory::newInstance('GalleryEntity', 'GalleryAlbumItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
			if (!isset($newAlbumInstance)) {
			    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					 null);
			}  
			/* this is where the album is actually created */	    
			$ret = $newAlbumInstance->create($targetAlbumID, $album['name']);
			if ($ret->isError()) {
			    if ($ret->getErrorCode() & ERROR_COLLISION) {
				$error[] = 'form[error][pathComponent][collision]';
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
			if (empty($error)) {
			    $newAlbumInstanceId = $newAlbumInstance->getId();
			    /*
			     * Array of example data
			     * (
			     *   +[title] => Test Album One
			     *   +[description] => No description
			     *   +[summary] =>
			     *   -[nextname] => aaa
			     *    [bgcolor] =>
			     *    [textcolor] =>
			     *    [linkcolor] =>
			     *    [font] => verdana
			     *    [border] => 1
			     *    [bordercolor] => black
			     *    [returnto] => yes
			     *   +[thumb_size] => 150
			     *   +[resize_size] => 400
			     *   +[rows] => 5
			     *   +[cols] => 5
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
			     *   -[serial_number] => 8
			     *    [extra_fields] => Array
			     *        ( [0] => Description
			     *        )
			     *   -[cached_photo_count] => 2
			     *   -[photos_separate] => 1
			     *   +[name] => album01
			     *    [owner] => 1054014347u1233740678
			     *    [last_mod_time] => 1056015246
			     */
			    
			    /* load up the album with metadata from the old album */ 
			    $newAlbumInstance->setTitle($album['title']);
			    $newAlbumInstance->setSummary($album['summary']);
			    $newAlbumInstance->setKeywords('');
			    $newAlbumInstance->setDescription($album['description']);
			    
			    // $newAlbumInstance->setorderBy
			    // $newAlbumInstance->setorderDirection
			    // $newAlbumInstance->setownerId
			    // $newAlbumInstance->settheme
			    $newAlbumInstance->setcreationTimestamp($album['last_mod_time']);
			    $newAlbumInstance->setviewedSinceTimestamp($album['clicks_date']);
			    /* Save the new album */	    
			    $ret = $newAlbumInstance->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    /* Click counts must be set after the item is first saved */
			    $ret = GalleryItemAttributesMap::setViewCount($newAlbumInstanceId, $album['clicks']);
			    if ($ret->isError()) {
				return $this->failWithStatus($ret->wrap(__FILE__, __LINE__));
			    }

			    
			    /* Delete existing derivative preferences */
			    $ret = GalleryDerivativePreferencesMap::removeMapEntry(array('itemId' => $newAlbumInstanceId));
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    
			    /* Add the thumbnail size back in */
			    $ret = GalleryDerivativePreferencesMap::addMapEntry(
										array('order' => 0,
										      'itemId' => $newAlbumInstanceId,
										      'derivativeType' => DERIVATIVE_TYPE_IMAGE_THUMBNAIL,
										      'derivativeOperations' => 'thumbnail|' . $album['thumb_size']));
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    

			    $ret = GalleryDerivativePreferencesMap::addMapEntry(
										array('order' => $i,
										      'itemId' => $newAlbumInstanceId,
										      'derivativeType' => DERIVATIVE_TYPE_IMAGE_RESIZE,
										      'derivativeOperations' => 'scale|' . $album['resize_size']));
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			   

			    list ($ret, $layout) = GalleryItemHelper::fetchLayout($newAlbumInstance);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    list ($ret, $settings) = $layout->getSettings($newAlbumInstanceId);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    $ret = $layout->setParameter('rows', $album['rows'], $newAlbumInstanceId);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    
			    $ret = $layout->setParameter('columns', $album['cols'], $newAlbumInstanceId);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    }
		    /* we can let the parent album (and anything else that we might
		     * have tied up) be edited by others now
		     */
		    $ret = $gallery->releaseLocks($importLockIds);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    } else {
			$importLockIds = array();
		    }
		    if (isset($newAlbumInstanceId)) {
			$finishedAlbums[$album['name']] = $newAlbumInstanceId;
			$status['albumImportSuccess'][$album['name']] = true;
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }	
		    
		    unset($photos);
		    list ($ret, $photos)=Gallery1DataParser::getPhotos($albumsPath . $album['name']);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    foreach($photos as $j => $importAlbumItem) {
			if (!isset($importAlbumItem->isAlbumName) || !$importAlbumItem->isAlbumName) {
			    list ($ret, $item) = $gallery->loadEntitiesById($newAlbumInstanceId);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    
			    list ($ret, $lockIds[]) = $gallery->acquireReadLock($item->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    list ($ret, $thumbnailTable) = GalleryDerivativeHelper::fetchThumbnailsByItemIds($item->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    $albumNeedsThumbnail = empty($thumbnailTable) ? true : false;
			    
			    $dir = $albumsPath . $album['name'] . $slash;
			    $filename = $importAlbumItem->image->name . '.' . $importAlbumItem->image->type;
			    $filepath = $dir . $filename;
			    //echo "<p>$filepath</p>";
			    list ($base, $extension) = GalleryUtilities::getFileNameComponents($filename);
			    $mimeType = GalleryUtilities::convertExtensionToMime($extension);
			    
			    list ($ret, $newItem) = GalleryItemHelper::addItemToAlbum($filepath,
										      $base,
										      $base,
										      $base,
										      $base,
										      $mimeType,
										      $item->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    
			    list ($ret, $lockIds[]) = $gallery->acquireWriteLock($newItem->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    $newItem->setTitle($importAlbumItem->caption);
			    $newItem->setSummary('');
			    $newItem->setKeywords($importAlbumItem->keywords);
			    //$newItem->setDescription($importAlbumItem->extraFields['description']);

			    // $instance->setownerId
			    if (isset($importAlbumItem->itemCaptureDate[0])){
				$newItem->setcreationTimestamp($importAlbumItem->itemCaptureDate[0]);
			    }
			    $newItem->setviewedSinceTimestamp($album['clicks_date']);
			    
			    if ($albumNeedsThumbnail || $importAlbumItem->highlight) {
				list ($ret, $success) =
					GalleryItemHelper::setThumbnailFromItem($item->getId(), $newItem->getId());
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				$albumNeedsThumbnail = !$success;
			    }
			    $ret = $newItem->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    /* Click counts must be set after the item is firstsaved */
			    //$ret = GalleryItemAttributesMap::setViewCount($newItem->getId(), $importAlbumItem->clicks);
			    //if ($ret->isError()) {
			    //	return $this->failWithStatus($ret->wrap(__FILE__, __LINE__));
			    //}
			    $status['addFromLocalServer'][] = array('fileName' => $filename,
								    'id' => $newItem->getId());
			    /* albumitem Object
			     * (
			     *   +[image] => image Object
			     *        (
			     *           +[name] => canon_ae_1
			     *           +[type] => jpg
			     *           -[width] => 225
			     *           -[height] => 165
			     *           -[resizedName] =>
			     *            {thumb_x] =>
			     *            [thumb_y] =>
			     *            [thumb_width] =>
			     *            [thumb_height] =>
			     *            [raw_width] => 225
			     *            [raw_height] => 165
			     *           -[version] => 10
			     *        )
			     *
			     *   -[thumbnail] => image Object
			     *        (
			     *           -[name] => canon_ae_1.thumb
			     *           -[type] => jpg
			     *           -[width] => 150
			     *           -[height] => 110
			     *           -[resizedName] =>
			     *           -[thumb_x] =>
			     *           -[thumb_y] =>
			     *           -[thumb_width] =>
			     *           -[thumb_height] =>
			     *           -[raw_width] => 150
			     *           -[raw_height] => 110
			     *           -[version] => 10
			     *        )
			     *
			     *   -[caption] => canon_ae_1
			     *    [hidden] =>
			     *   +[highlight] => 1
			     *   -[highlightImage] => image Object
			     *        (
			     *           -[name] => canon_ae_1.highlight
			     *           -[type] => jpg
			     *           -[width] => 200
			     *           -[height] => 147
			     *           -[resizedName] =>
			     *           -[thumb_x] =>
			     *           -[thumb_y] =>
			     *           -[thumb_width] =>
			     *           -[thumb_height] =>
			     *           -[raw_width] => 200
			     *           -[raw_height] => 147
			     *           -[version] => 10
			     *        )
			     *
			     *   +[isAlbumName] =>
			     *   +[clicks] =>
			     *   +[keywords] =>
			     *    [comments] =>
			     *    [uploadDate] => 1056014783
			     *   +[itemCaptureDate] => Array
			     *        (
			     *           -[seconds] => 23
			     *           -[minutes] => 26
			     *           -[hours] => 04
			     *           -[mday] => 19
			     *           -[wday] => 4
			     *           -[mon] => 06
			     *           -[year] => 2003
			     *           -[yday] => 169
			     *           -[weekday] => Thursday
			     *           -[month] => June
			     *           +[0] => 1056014783
			     *        )
			     *
			     *   -[exifData] => Array
			     *        (
			     *           -[File name] => /www/dev.jpmullan.com/albums/album01/canon_ae_1.jpg
			     *           -[File size] => 8070 bytes
			     *           -[File date] => 2003:06:19 04:26:23
			     *           -[Resolution] => 225 x 165
			     *           -[Jpeg process] => Baseline
			     *        )
			     *
			     *    [extraFields] => Array
			     *        (
			     *        )
			     *
			     *   -[version] => 10
			     *)
			     */
			}
		    }
		}
		
		/* $i keeps track of how many passes we make over the data */
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
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $albums) = Gallery1DataParser::getAlbumList($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
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
		if (!$ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$existingAlbums[$album['name']] = FALSE;
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
	return array(GalleryStatus::success(),
		     array('body' => 'modules/migrate/templates/ConfirmImport.tpl'));
    }
}
?>
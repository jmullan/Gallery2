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
 * @package Migrate
 * @subpackage UserInterface
 * @author Jesse Mullan <jmullan@visi.com>
 */

GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/G1MigrateMap.class');

/**
 * @package Migrate
 * @subpackage UserInterface
 */
class ConfirmImportController extends GalleryController {
    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
        global $gallery;
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();

	list ($ret, $moduleStatusList) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return $this->failWithStatus($ret->wrap(__FILE__, __LINE__));
	}
	if (!empty($moduleStatusList['comment']['active'])) {
	    $importComments = TRUE;
	} else {
	    $importComments = FALSE;
	}

	/* owner => core.all (which also gives comment.all)
	 *
	 * canRead => core.view,core.viewResizes
	 * canViewFullImages => core.viewSource
	 * canViewComments =>
	 * comment.view,comment.search
	 * canAddComments => comment.add
	 * canChangeText => core.edit
	 * canAddTo => core.addDataItem
	 * canWrite => core.edit
	 * canDeleteFrom => core.delete
	 * canCreateSubAlbum => core.addAlbumItem
	 *
	 */

	$permissionTranslation = array('canRead' => array('core.view',
							  'core.viewResizes'
							  ),
				       'canViewFullImages' => array('core.viewSource'),
				       'canChangeText' => array('core.edit'),
				       'canAddTo' => array('core.addDataItem'),
				       'canWrite' => array('core.edit'),
				       'canDeleteFrom' => array('core.delete'),
				       'canCreateSubAlbum' => array('core.addAlbumItem')
				       );
	if ($importComments) {
	    $permissionTranslation['canAddComments'] = array('comment.add');
	    $permissionTranslation['canViewComments'] = array('comment.view', 'comment.search');
	} else {
	    $permissionTranslation['canAddComments'] = array();
	    $permissionTranslation['canViewComments'] = array();
	}
	/* Get GroupIds for "everybody" and "all users" */
	list ($ret, $everybodyGroupId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.everybodyGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $allUsersGroupId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.allUserGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $adminUsersGroupId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $guestUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}


        /* Verify that active user is an admin */
        $ret = GalleryCoreApi::assertUserIsSiteAdministrator();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	$albumsPath = GalleryUtilities::getRequestVariables('albumsPath');

	/* build framework for error and status arrays */
	$error = array();
	$status = array('userImportFailure'=>array(),
			'userImportSuccess'=>array(),
			'albumImportFailure'=>array(),
			'albumImportSuccess'=>array(),
			'urlRedirect' => isset($form['urlRedirect'])
			);
	$finishedAlbums = array();
	$albumPosition = array();
	if (!isset($form['sourceEncoding'])) {
	    $form['sourceEncoding']='UTF-8';
	}
	$sourceEncoding = $form['sourceEncoding'];

	/* The other option is "cancel", I believe */
	if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'migrate:SelectGallery';
	}
	if (isset($form['action']['import'])) {
	    $itemsCreated = array();

	    /* get list of userids in advance */
	    require_once(dirname(__FILE__) . '/classes/Gallery1DataParser.class');
	    list($ret, $albumList) = Gallery1DataParser::getAlbumList($albumsPath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $uidMap) = Gallery1DataParser::getUserUids($albumsPath);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* if no users were selected, create an empty array to avoid later
	     * php warnings
	     */
	    if (!isset($form['migrateUser'])) {
		$form['migrateUser']=array();
	    }

	    /* go through the list of chosen users */
	    foreach (array_keys ($form['migrateUser']) as $uid) {
		/* convert from uid to username */
		list ($ret, $fields) =
		    Gallery1DataParser::getUserFieldsByUid($albumsPath, $uid);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$userName = Gallery1DataParser::convertString($fields['username'],$sourceEncoding);;
		/*
		 * Go ahead and create the user instance
		 */
		list ($ret, $user) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryUser');
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
		$ret = $user->create($userName);
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
		    $user->setFullName(Gallery1DataParser::convertString($fields['fullname'],$sourceEncoding));

		    /*
		     * $fields['canCreateAlbums'] if they have that perm, give them "core.addAlbumItem"
		     * permission on the root album
		     */
		    /* Save this user to the database */
		    $ret = $user->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    if (isset($fields['isAdmin']) && $fields['isAdmin']) {
			/* Add her to the admin group */
			$ret = GalleryCoreApi::addUserToGroup($user->getId(), $adminUsersGroupId);
			if ($ret->isError()) {
			    return $ret->wrap(__FILE__, __LINE__);
			}

		    }
		    /* Set a positive note for later.  Hooray! */
		    $status['userImportSuccess'][$userName] = 1;
		    $user = null;
		}
		$uid = null;
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
		list ($ret, $rootId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
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
		$sourceAlbumName = urldecode($sourceAlbumName);
		if (!in_array($sourceAlbumName,array_keys($albumList))) {
		    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
		}
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
	    $albumHighlight = array();
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
		if (!in_array(urlencode($album['parentAlbumName']),array_keys($form['sourceAlbums']))) {
		    $targetAlbumID = $destinationAlbumID;
		} else if (in_array($album['parentAlbumName'],array_keys($finishedAlbums))){
		    /* if the album's parent has already been imported, import
		     * it into the parent
		     */
		    $targetAlbumID = $finishedAlbums[$album['parentAlbumName']];
		} else {
		    $albumfields[$album['name']] = $album;
		    $album = NULL;
		}
		if ($targetAlbumID && $album) {
		    list($ret, $parent) = GalleryCoreApi::loadEntitiesById($targetAlbumID);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list($ret, $parentPath) = $parent->fetchPath();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $desiredname = $platform->legalizePathComponent($album['name']);
		    $k = 0;
		    $invalidName = TRUE;
		    while($invalidName) {
			list ($ret, $existingAlbumId) =
			    GalleryCoreApi::fetchChildIdByPathComponent($targetAlbumID, $desiredname);
			if ($ret->isError()) {
			    if (!$ret->getErrorCode() & ERROR_MISSING_OBJECT) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    } else {
				$invalidName = FALSE;
			    }
			} else {
			    $desiredname = $album['name'] . '_' . $k++;
			}
		    }

		    if ($targetAlbumID) {
			/* Make sure we have permission to edit the target item */
			$ret = GalleryCoreApi::assertHasItemPermission($targetAlbumID, 'core.addAlbumItem');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/* Try to load targeted parent */
			list ($ret, $targetAlbumObject) = GalleryCoreApi::loadEntitiesById($targetAlbumID);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/* Get a lock on said parent */
			list ($ret, $importLockIds[]) = GalleryCoreApi::acquireReadLock($targetAlbumObject->getId());
			// list ($ret, $importLockIds[$targetAlbumObject->getId()]) = GalleryCoreApi::acquireReadLock($targetAlbumObject->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/* Check the new album's path component to see if it is valid on the
			 * local filesystem
			 */
			$platform = $gallery->getPlatform();
			if (empty($desiredname)) {
			    $error[] = 'form[error][pathComponent][missing]';
			} else if (!$platform->isLegalPathComponent($desiredname)) {
			    $error[] = 'form[error][pathComponent][invalid]';
			}
			/* If everything is good so far, we create a new instance to be our new
			 * album
			 */
			if (empty($error)) {
			    list ($ret, $newAlbumInstance) =
				    GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryAlbumItem');
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    if (!isset($newAlbumInstance)) {
				return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					     null);
			    }
			    /* this is where the album is actually created */
			    $ret = $newAlbumInstance->create($targetAlbumID, $desiredname);
			    if ($ret->isError()) {
				if ($ret->getErrorCode() & ERROR_COLLISION) {
				    $error[] = 'form[error][pathComponent][collision]';
				}
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    if (isset($form['urlRedirect'])) {
				$ret = $this->createG1ToG2Mapping(
						$newAlbumInstance->getId(), $album['name']);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
			    }

			    if (empty($error)) {
				$newAlbumInstanceId = $newAlbumInstance->getId();
				/* load up the album with metadata from the old
				 * album */
				if (isset($album['title'])) {
				    $newAlbumInstance->setTitle(
                                        GalleryUtilities::entityTruncate(
					    $this->convertHtmlToBbcode($album['title'], $sourceEncoding)),
					        128);
				}
				if (isset($album['summary'])) {
				    $newAlbumInstance->setDescription($this->convertHtmlToBbcode($album['summary'], $sourceEncoding));
				}
				$newAlbumInstance->setKeywords('');
				if (isset($album['description'])) {
				    $newAlbumInstance->setSummary(
				        GalleryUtilities::entityTruncate(
			                    $this->convertHtmlToBbcode($album['description'], $sourceEncoding),
						255));
				}
				// $newAlbumInstance->settheme
				if (isset($album['last_mod_time']) && $album['last_mod_time']) {
				    if (isset($album['clicks_date']) && $album['clicks_date']>0 && $album['clicks_date']<$album['last_mod_time']){
					$newAlbumInstance->setCreationTimestamp($album['clicks_date']);
					$newAlbumInstance->setOriginationTimestamp($album['clicks_date']);
				    } else {
					$newAlbumInstance->setCreationTimestamp($album['last_mod_time']);
					$newAlbumInstance->setOriginationTimestamp($album['last_mod_time']);
				    }
				}
				if (isset($album['clicks_date']) && $album['clicks_date']>0) {
				    $newAlbumInstance->setviewedSinceTimestamp($album['clicks_date']);
				}

				// $newAlbumInstance->setorderBy
				// $newAlbumInstance->setorderDirection

				// Set album owner
				if (isset($album['owner'])) {
				    $validUID = Gallery1DataParser::isValidUid($albumsPath,$album['owner']);
				    if ($validUID) {
					list($ret, $albumUserFields) = Gallery1DataParser::getUserFieldsByUid($albumsPath, $album['owner']);
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					list($ret, $owner) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($albumUserFields['username'],$sourceEncoding));
					if ($ret->isError()) {
					    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
						$owner = $gallery->getActiveUser();
					    } else {
						return array($ret->wrap(__FILE__, __LINE__), null);
					    }
					}
					$newAlbumInstance->setOwnerId($owner->getId());
				    }
				}
				    /* Save the new album */
				$ret = $newAlbumInstance->save();
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}

				$itemsCreated[] = $newAlbumInstance->getId();

				// Set order weight
				if (isset($albumPosition[$album['name']])) {
				    $weight = $albumPosition[$album['name']];
				} else {
				    list ($ret, $weight) = GalleryCoreApi::fetchExtremeChildWeight($targetAlbumID, HIGHER_WEIGHT);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				    $weight += 1000;
				}
				$ret = GalleryCoreApi::setItemOrderWeight($newAlbumInstance->getId(), $weight);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}

				$ret = GalleryCoreApi::removeItemPermissions($newAlbumInstance->getId());
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				if ($adminUsersGroupId) {
				    $ret = GalleryCoreApi::addGroupPermission($newAlbumInstance->getId(),
									      $adminUsersGroupId,
									      'core.all',
									      FALSE
									      );
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}

				// Set album owner permissions
				$validUID = Gallery1DataParser::isValidUid($albumsPath,$album['owner']);
				if ($validUID) {
				    list($ret, $albumUserFields) = Gallery1DataParser::getUserFieldsByUid($albumsPath, $album['owner']);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				    list($ret, $owner) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($albumUserFields['username'],$sourceEncoding));
				    if ($ret->isError()) {
					if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
					    $owner = $gallery->getActiveUser();
					} else {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
				    }
				    $ret = GalleryCoreApi::addUserPermission($newAlbumInstance->getId(),
									     $owner->getId(),
									     'core.all',
									     true
									     );
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}

				if (isset($album['perms'])) {
				    foreach($album['perms'] as $tmpperm => $tmpusers) {
					foreach($permissionTranslation[$tmpperm] as $tmpTranslatedPerm) {
					    foreach(array_keys($tmpusers) as $tmpuser) {
						switch ($tmpuser) {
						case 'Logged In':
						    if ($allUsersGroupId) {
							$ret = GalleryCoreApi::addGroupPermission($newAlbumInstance->getId(),
												     $allUsersGroupId,
												     $tmpTranslatedPerm,
												     FALSE
												     );
							if ($ret->isError()) {
							    return array($ret->wrap(__FILE__, __LINE__), null);
							}
						    }
						    break;
						case 'everybody':
						    if ($everybodyGroupId) {
							$ret = GalleryCoreApi::addGroupPermission($newAlbumInstance->getId(),
												     $everybodyGroupId,
												     $tmpTranslatedPerm,
												     FALSE
												     );
							if ($ret->isError()) {
							    return array($ret->wrap(__FILE__, __LINE__), null);
							}
						    }
						    break;
						case 'Nobody':
						    break;
						case 'admin':
						    break;
						default:
						    $validPermUID = Gallery1DataParser::isValidUid($albumsPath,$tmpuser);
						    if ($validPermUID) {
							list($ret, $permsUserFields) = Gallery1DataParser::getUserFieldsByUid($albumsPath, $tmpuser);
							if ($ret->isError()) {
							    return array($ret->wrap(__FILE__, __LINE__), null);
							}
							$permUsername = $permsUserFields['username'];
							list($ret, $permUser) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($permUsername,$sourceEncoding));
							if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
							    return array($ret->wrap(__FILE__, __LINE__), null);
							}
							if ($permUser) {
							    $ret = GalleryCoreApi::addUserPermission($newAlbumInstance->getId(),
												     $permUser->getId(),
												     $tmpTranslatedPerm,
												     FALSE
												 );
							    if ($ret->isError()) {
								return array($ret->wrap(__FILE__, __LINE__), null);
							    }
							}
						    }
						}
					    }
					}
				    }
				}


				/* Click counts must be set after the item is
				 * first saved */
				if (isset($album['clicks'])) {
				    $ret = GalleryCoreApi::setItemViewCount($newAlbumInstanceId, $album['clicks']);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}

				/* Delete existing derivative preferences */
				$ret = GalleryCoreApi::removeDerivativePreferencesForItem($newAlbumInstanceId);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}

				/* Add the thumbnail size back in */
				if (isset($album['thumb_size'])) {
				    $ret = GalleryCoreApi::addDerivativePreference(0, $newAlbumInstanceId,
										   DERIVATIVE_TYPE_IMAGE_THUMBNAIL,
										   'thumbnail|' . $album['thumb_size']);
				}
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}

				if (isset($album['resize_size']) && strcmp($album['resize_size'],'off')) {
				    $ret = GalleryCoreApi::addDerivativePreference(1, $newAlbumInstanceId,
										   DERIVATIVE_TYPE_IMAGE_RESIZE,
										   'scale|' . $album['resize_size']);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}

				list ($ret, $layout) = GalleryCoreApi::fetchLayout($newAlbumInstance);
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

				if (isset($newAlbumInstanceId)) {
				    $finishedAlbums[$album['name']] = $newAlbumInstanceId;
				    $status['albumImportSuccess'][$album['name']] = $newAlbumInstanceId;
				} else {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
			    }
			}
			/* we can let the parent album (and anything else that we might
			 * have tied up) be edited by others now
			 */
			$ret = GalleryCoreApi::releaseLocks($importLockIds);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			} else {
			    $importLockIds = array();
			}

			unset($photos);
			list ($ret, $photos)=Gallery1DataParser::getPhotos($albumsPath . $album['name']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
			if (!isset($photos)) {
			    $photos = array();
			}

			$albumHighlight[$newAlbumInstanceId]=FALSE;
			list ($ret, $item) = GalleryCoreApi::loadEntitiesById($newAlbumInstanceId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			list ($ret, $importLockIds[]) = GalleryCoreApi::acquireReadLock($item->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
			list ($ret, $thumbnailTable) = GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
			$albumNeedsThumbnail = empty($thumbnailTable) ? true : false;

			foreach($photos as $j => $importAlbumItem) {
			    if (isset($importAlbumItem->isAlbumName) && $importAlbumItem->isAlbumName) {
				if ($importAlbumItem->highlight == 1) {
				    $albumHighlight[$newAlbumInstanceId]=$importAlbumItem->isAlbumName;
				}
				list ($ret, $weight) = GalleryCoreApi::fetchExtremeChildWeight(
							$newAlbumInstanceId, HIGHER_WEIGHT);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				$albumPosition[$importAlbumItem->isAlbumName] = $weight + 100 + $j;
				$importAlbumItem = NULL;
			    } else {
				$dir = $albumsPath . $album['name'] . $slash;
				$filename = $importAlbumItem->image->name . '.' . $importAlbumItem->image->type;
				$filepath = $dir . $filename;
				list ($base, $extension) = GalleryUtilities::getFileNameComponents($filename);
				$mimeType = GalleryCoreApi::convertExtensionToMime($extension);

				list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum($filepath,
										       $filename,
										       $filename,
										       $base,
										       $base,
										       $mimeType,
										       $item->getId());
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				$itemsCreated[] = $newItem->getId();

				if (isset($form['urlRedirect'])) {
				    $ret = $this->createG1ToG2Mapping($newItem->getId(),
						  $album['name'], $importAlbumItem->image->name);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}
				$itemLockIds = array();
				list ($ret, $itemLockIds[]) = GalleryCoreApi::acquireWriteLock($newItem->getId());
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				$caption = $importAlbumItem->caption;

				$convertedCaption = $this->convertHtmlToBbcode($caption,$sourceEncoding);
				if (strlen($convertedCaption) > 128) {
				    $newItem->setTitle(GalleryUtilities::entityTruncate($convertedCaption, 128));
				    if (isset($importAlbumItem->extraFields['description']) && $importAlbumItem->extraFields['description'] != '') {
					$newItem->setDescription($convertedCaption
								 . "\n"
								 . $this->convertHtmlToBbcode($importAlbumItem->extraFields['description'],$sourceEncoding));
				    } else {
					$newItem->setDescription($convertedCaption);
				    }
				} else {
				    $newItem->setTitle($convertedCaption);
				    if (isset($importAlbumItem->extraFields['description']) && $importAlbumItem->extraFields['description'] != '') {
					$newItem->setDescription($this->convertHtmlToBbcode($importAlbumItem->extraFields['description'],$sourceEncoding));
				    }
				}

				$newItem->setSummary('');
				$newItem->setKeywords(Gallery1DataParser::convertString($importAlbumItem->keywords,$sourceEncoding));


				/*
			    if (isset($importAlbumItem->itemCaptureDate[0])){
				$newItem->setcreationTimestamp($importAlbumItem->itemCaptureDate[0]);
			    }
				*/
				if (isset($importAlbumItem->uploadDate)){
				    $newItem->setCreationTimestamp($importAlbumItem->uploadDate);
				    $newItem->setOriginationTimestamp($importAlbumItem->uploadDate);
				}
				if (isset($album['clicks_date']) && $album['clicks_date']>0) {
				    $newItem->setviewedSinceTimestamp($album['clicks_date']);
				}
				if (isset($importAlbumItem->clicks) && $importAlbumItem->clicks > 0) {
				    $ret = GalleryCoreApi::setItemViewCount($newItem->getId(), $importAlbumItem->clicks);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				}
				if (isset($importAlbumItem->image->thumb_x) &&
				    isset($importAlbumItem->image->thumb_y) &&
				    isset($importAlbumItem->image->thumb_width) &&
				    isset($importAlbumItem->image->thumb_height) &&
				    $importAlbumItem->image->thumb_width > 0 &&
				    $importAlbumItem->image->thumb_height > 0){

				    /* Load the thumbnail */
				    $thumbnails = array();
				    list ($ret, $thumbnails) = GalleryCoreApi::fetchThumbnailsByItemIds(array($newItem->getId()));
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }

				    if (!empty($thumbnails)) {
					$thumbnail = $thumbnails[$newItem->getId()];

					list ($ret, $lock) = GalleryCoreApi::acquireWriteLock($thumbnail->getId());
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}

					list ($ret, $thumbnail) = $thumbnail->refresh();
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}

					$width = $importAlbumItem->image->raw_width;
					$height = $importAlbumItem->image->raw_height;
					$xPerc = round($importAlbumItem->image->thumb_x * 100 / $width, 3);
					$yPerc = round($importAlbumItem->image->thumb_y * 100 / $height, 3);
					$widthPerc = round($importAlbumItem->image->thumb_width * 100 / $width, 3);
					$heightPerc = round($importAlbumItem->image->thumb_height * 100 / $height, 3);
					list ($ret, $operations) =
						GalleryCoreApi::mergeDerivativeOperations($thumbnail->getDerivativeOperations(),
											  sprintf('crop|%s,%s,%s,%s',
												  $xPerc, $yPerc,
												  $widthPerc, $heightPerc),
											  true);
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					$thumbnail->setDerivativeOperations($operations);

					$thumbnail->setWidth(0);
					$thumbnail->setHeight(0);

					$ret = $thumbnail->save();
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					$ret = GalleryCoreApi::releaseLocks($lock);
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}

					/*
					 * Changing the crop size causes our derivative dimensions to change,
					 * which affects all our dependent derivatives also.
					 */
					$ret = GalleryCoreApi::invalidateDerivativeDimensionsBySourceIds(
					    array($thumbnail->getId()));
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
				    }
				}

				$validItemUID = FALSE;
				$itemUID = FALSE;
				$defaultToAlbumUID = TRUE;
				if (isset($importAlbumItem->owner)) {
				    if (!strcmp('everybody',$importAlbumItem->owner)
					|| !strcmp('nobody',$importAlbumItem->owner)
					) {
					$defaultToAlbumUID = FALSE;
					$newItem->setownerId($guestUserId);
				    } else if (strcmp('logged-in',$importAlbumItem->owner)) {
					$validItemUID = Gallery1DataParser::isValidUid($albumsPath,$importAlbumItem->owner);
					if ($validItemUID) {
					    $defaultToAlbumUID = FALSE;
					    $itemUID = $importAlbumItem->owner;
					}
				    }
				}
				if ($defaultToAlbumUID) {
				    $validItemUID = Gallery1DataParser::isValidUid($albumsPath,$album['owner']);
				    if ($validItemUID) {
					$itemUID = $album['owner'];
				    }
				}
				if ($validItemUID && $itemUID) {
				    list($ret, $albumItemUserFields) =
					    Gallery1DataParser::getUserFieldsByUid($albumsPath, $itemUID);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				    list($ret, $itemOwner) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($albumItemUserFields['username'],$sourceEncoding));
				    if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
					return array($ret->wrap(__FILE__, __LINE__), null);
				    }
				    if ($itemOwner) {
					$newItem->setownerId($itemOwner->getId());
				    }
				}

				if (isset($importAlbumItem->hidden) && $importAlbumItem->hidden) {
				    /* delete group perm actions */
				    $allPerms = array('core.view','core.viewSource','core.viewResizes');
				    foreach ($allPerms as $perm) {
					$ret = GalleryCoreApi::removeGroupPermission($newItem->getId(), $everybodyGroupId, $perm, FALSE);
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					$ret = GalleryCoreApi::removeGroupPermission($newItem->getId(), $allUsersGroupId, $perm, FALSE);
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
				    }
				}

				$ret = $newItem->save();
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
				if ($importComments && isset($importAlbumItem->comments) && count($importAlbumItem->comments)>0) {
				    foreach ($importAlbumItem->comments AS $importCommentId => $importComment) {
					if (strcmp($importComment->UID,'everybody')) {
					    $validCommentUid = Gallery1DataParser::isValidUid($albumsPath,$album['owner']);
					    if ($validCommentUid){
						list($ret, $commentG1User) = Gallery1DataParser::getUserFieldsByUid($albumsPath, $album['owner']);
						if ($ret->isError()) {
						    return array($ret->wrap(__FILE__, __LINE__), null);
						}
						list($ret, $commentG2User) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($commentG1User['username'],$sourceEncoding));
						if ($ret->isError()) {
						    if (!($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
							return array($ret->wrap(__FILE__, __LINE__), null);
						    } else {
							$commenterId = $guestUserId;
						    }
						} else {
						    $commenterId = $commentG2User->getId();
						}
					    }
					} else {
					    $commenterId = $guestUserId;
					}

					/* Add the comment */
					list ($ret, $comment) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryComment');
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					
					if (!isset($comment)) {
					return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
						     null);
					}

					$ret = $comment->create($newItem->getId());
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}

					$comment->setCommenterId($commenterId);
					$comment->setHost($importComment->IPNumber);
					if ($commenterId == $guestUserId) {
					    $comment->setSubject($importComment->name);
					} else {
					    $comment->setSubject('');
					}
					$comment->setComment(ConfirmImportController::convertHtmlToBbcode($importComment->commentText,$sourceEncoding));
					$comment->setDate($importComment->datePosted);

					$ret = $comment->save();
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
				    }
				}
				$ret = GalleryCoreApi::releaseLocks($itemLockIds);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				} else {
				    $itemLockIds = array();
				}
				/* Click counts must be set after the item is firstsaved */
				//$ret = GalleryCoreApi::setItemViewCount($newItem->getId(), $importAlbumItem->clicks);
				//if ($ret->isError()) {
				//	return $this->failWithStatus($ret->wrap(__FILE__, __LINE__));
				//}
				$status['addFromLocalServer'][] = array('fileName' => $filename,
									'id' => $newItem->getId());
				if (($albumNeedsThumbnail || $importAlbumItem->highlight == 1)) {
				    $toolkit = NULL;

				    list ($ret, $toolkit, $outputMimeType) =
					    GalleryCoreApi::getToolkitByOperation($newItem->getMimeType(), 'thumbnail');
				    if ($ret->isError()) {
					return $ret->wrap(__FILE__, __LINE__);
				    }

				    if (isset($toolkit)) {
					list ($ret, $success) = GalleryCoreApi::setThumbnailFromItem($item->getId(), $newItem->getId());
					if ($ret->isError()) {
					    return array($ret->wrap(__FILE__, __LINE__), null);
					}
					$albumNeedsThumbnail = FALSE;
				    }
				}
			    }
			}
		    }
		    $album = null;
		    /* $i keeps track of how many passes we make over the data */
		    $i++;
		}
	    }
	    //$albumHighlight[$newAlbumInstanceId]=$importAlbumItem->isAlbumName;
	    //$finishedAlbums[$album['name']] = $newAlbumInstanceId;
	    foreach ($albumHighlight as $highlightRecipientId => $nameOfAlbumToHighlight) {
		if (isset ($finishedAlbums[$nameOfAlbumToHighlight]) && $finishedAlbums[$nameOfAlbumToHighlight]) {
		    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($highlightRecipientId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    list ($ret, $importLockIds[]) = GalleryCoreApi::acquireReadLock($item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    list ($ret, $success) = GalleryCoreApi::setThumbnailFromItem($item->getId(), $finishedAlbums[$nameOfAlbumToHighlight]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }

	    if (!empty($form['generateThumbnails'])) {
		/*
		 * Get the thumbnails for all of the items we created, in 20 item
		 * increments so that we don't consume too much memory.
		 *
		 * Note: this destroys the $itemsCreated array!
		 */
		while (!empty($itemsCreated)) {
		    $chunk = array_splice($itemsCreated, 0, 20);
		    list ($ret, $thumbTable) = GalleryCoreApi::fetchThumbnailsByItemIds($chunk);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    foreach ($thumbTable as $thumbnail) {
			list ($ret, $newThumbnail, $wasRebuilt) =
			    GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($thumbnail->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}

	    }

	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'migrate:ImportResults';
	}
	if (isset($importLockIds)) {
	    $ret = GalleryCoreApi::releaseLocks($importLockIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    } else {
		$importLockIds = array();
	    }
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

    /**
     *
     * Converts HTML to BBCode
     *
     * @param string $item item to convert
     * @return string
     */
    function convertHtmlToBbcode($item, $sourceEncoding='UTF-8') {
	$item = Gallery1DataParser::convertString($item,$sourceEncoding);
	$item = preg_replace('/<br\s*[\/]?>/i', "\n", $item);
	$item = preg_replace('/<strong>/i', '[b]', $item);
	$item = preg_replace('/<\/strong>/i', '[/b]', $item);
	$item = preg_replace('/<em>/i', '[i]', $item);
	$item = preg_replace('/<\/em>/i', '[/i]', $item);
	$item = preg_replace('/<b>/i', '[b]', $item);
        $item = preg_replace('/<\/b>/i', '[/b]', $item);
        $item = preg_replace('/<i>/i', '[i]', $item);
        $item = preg_replace('/<\/i>/i', '[/i]', $item);
        $item = preg_replace('/<ul>/i', '[list]', $item);
        $item = preg_replace('/<\/ul>/i', '[/list]', $item);
        $item = preg_replace('/<li>/i', '[*]', $item);
        $item = preg_replace('/<\/li>/i', '', $item);
        $item = preg_replace('/<img([^>]*)?\s*src\s*=\s*["\']{0,1}([^\s\'">]*)["\']{0,1}([^>]*)>/is', '[img]$2[/img]', $item);
        $item = preg_replace('/<a([^>]*)?\s*href\s*=\s*["\']{0,1}([^\s\'">]*)["\']{0,1}([^>]*)>(.*?)?<\/a>/is', '[url=$2]$4[/url]', $item);
        $item = strip_tags($item);
        GalleryUtilities::sanitizeInputValues($item);
        return $item;
    }

    /**
     * Create the G1->G2 map entries so that Gallery1 links
     * can be redirected to Gallery2 links.
     * @param int item id
     * @param string G1 album name
     * @param string (optional) G1 item name
     * @return object GalleryStatus a status code
     * @author Joseph Elwell <jelwell@yahoo.com>
     */
    function createG1ToG2Mapping($itemId, $g1AlbumName, $g1ItemName=null) {
	$ret = G1MigrateMap::addMapEntry(
		array('itemId' => $itemId, 'g1album' => $g1AlbumName, 'g1item' => $g1ItemName) );
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }
}

/**
 * @package Migrate
 * @subpackage UserInterface
 */
class ConfirmImportView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;
	$platform = $gallery->getPlatform();
	$illegalAlbumNames = array();
	$existingAlbums = array();
	$albumValidOwner = array();
	$urlDecoded = array();
	$albumOwnerUserName = array();
	$albumOwnerUid = array();
	$titles = array();
	if (!isset($form['sourceAlbums'])) {
	    $form['sourceAlbums']=array();
	}
	if (!isset($form['sourceEncoding'])) {
	    $form['sourceEncoding']='ISO-8859-1';
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
	list ($ret, $targetAlbum) = GalleryCoreApi::loadEntitiesById($destinationAlbumID);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
	foreach ($form['sourceAlbums'] as $sourceAlbumName) {
	    $urlDecoded[$sourceAlbumName] = urldecode($sourceAlbumName);
	    if (!in_array($urlDecoded[$sourceAlbumName],array_keys($albums))) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	    }
	    list ($ret, $albumfields[$sourceAlbumName]) = Gallery1DataParser::loadAlbumFields($albumsPath.$urlDecoded[$sourceAlbumName]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	$i=0;
	if(!isset($albumfields)){
	    $albumfields = array();
	}
	while ($albumfields) {
	    $existingAlbumId = FALSE;
	    $album = array_shift($albumfields);
	    $encodedName = urlencode($album['name']);
	    if (!in_array($album['parentAlbumName'],$form['sourceAlbums'])) {
		list ($ret, $existingAlbumId) =
			GalleryCoreApi::fetchChildIdByPathComponent($destinationAlbumID, $album['name']);
	    }
	    if ($ret->isError()) {
		if (!$ret->getErrorCode() & ERROR_MISSING_OBJECT) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$existingAlbums[$encodedName] = FALSE;
	    } else {
		$existingAlbums[$encodedName] = $existingAlbumId;
	    }
	    $titles[$encodedName] = $album['title'];
	    if (!$platform->isLegalPathComponent($album['name'])){
		$illegalAlbumNames[$encodedName] = $platform->legalizePathComponent($album['name']);
	    } else {
		$illegalAlbumNames[$encodedName] = FALSE;
	    }

	    $validUid = Gallery1DataParser::isValidUid($albumsPath,$album['owner']);
	    if ($validUid){
		list($ret, $testUser) = Gallery1DataParser::getUserFieldsByUid($albumsPath, $album['owner']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$albumOwnerUserName[$encodedName] = $testUser['username'];
		$albumOwnerUid[$encodedName] = $album['owner'];
		list($ret, $owner) = GalleryCoreApi::fetchUserByUsername(Gallery1DataParser::convertString($testUser['username'],$form['sourceEncoding']));
		if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if (isset($form['migrateUser'][$album['owner']])) {
		    $importingOwner = TRUE;
		} else {
		    $importingOwner = FALSE;
		}
		if ($owner || $importingOwner) {
		    $albumValidOwner[$encodedName] = TRUE;
		} else {
		    $albumValidOwner[$encodedName] = FALSE;
		}
	    } else {
		$albumValidOwner[$encodedName] = TRUE;
		$albumOwnerUserName[$encodedName] = 'admin';
		$albumOwnerUid[$encodedName] = NULL;
	    }
	    $i++;
	}

	$ConfirmImport = array();
	$ConfirmImport['uids'] = $uids;
	$ConfirmImport['albums'] = $albums;
	$ConfirmImport['albumsPath'] = $albumsPath;
	$ConfirmImport['existingAlbums'] = $existingAlbums;
	$ConfirmImport['illegalAlbumNames'] = $illegalAlbumNames;
        $ConfirmImport['destinationAlbumID'] = $destinationAlbumID;
	$ConfirmImport['albumValidOwner'] = $albumValidOwner;
	$ConfirmImport['albumOwnerUserName'] = $albumOwnerUserName;
	$ConfirmImport['albumOwnerUid'] = $albumOwnerUid;
        $ConfirmImport['targetAlbum'] = $targetAlbum->getMemberData();
	$ConfirmImport['urlDecoded'] = $urlDecoded;
	$ConfirmImport['titles'] = $titles;
        $template->setVariable('controller', 'migrate:ConfirmImport');
	$template->setVariable('ConfirmImport', $ConfirmImport);
	return array(GalleryStatus::success(),
		     array('body' => 'modules/migrate/templates/ConfirmImport.tpl'));
    }
}
?>

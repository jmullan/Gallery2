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
		    list ($ret, $finishedAlbums[$album['name']])=Gallery1DataParser::importAlbum($destinationAlbumID,$album);
		} else if (in_array($album['parentAlbumName'],array_keys($finishedAlbums))){
		    list ($ret, $finishedAlbums[$album['name']])=Gallery1DataParser::importAlbum($finishedAlbums[$album['parentAlbumName']],$album);
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
}	    

class ConfirmImportView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;
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
	$ConfirmImport = array();
	$ConfirmImport['uids'] = $uids;
	$ConfirmImport['albums'] = $albums;
	$ConfirmImport['albumsPath'] = $albumsPath;
        $ConfirmImport['destinationAlbumID'] = $destinationAlbumID;
        $ConfirmImport['targetAlbum'] = $targetAlbum;
	if (!isset($form['sourceAlbums'])) {
	    $form['sourceAlbums']=array();
	}
        $template->setVariable('controller', 'migrate:ConfirmImport');
	$template->setVariable('ConfirmImport', $ConfirmImport);

        return array(GalleryStatus::success(), '', 'modules/migrate/templates/ConfirmImport.tpl');
    }
}
?>
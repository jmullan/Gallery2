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
 * @package Migrate
 * @subpackage UserInterface
 */

class ChooseObjectsController extends GalleryController {
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

	$error = array();
	$status = array();

	/* Make sure the user selected *something* to migrate */
	if (isset($form['action']['import'])) {
	    if (empty($form['migrateUser']) && empty($form['sourceAlbums'])) {
		$error[] = 'form.error.nothingSelected';
	    }

	    if ($error) {
		$results['delegate']['view'] = 'core:SiteAdmin';
		$results['delegate']['subView'] = 'migrate:ChooseObjects';
	    } else {
		$results['delegate']['view'] = 'core:SiteAdmin';
		$results['delegate']['subView'] = 'migrate:ConfirmImport';
	    }
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'migrate:ConfirmImport';
	}
	
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}	    

class ChooseObjectsView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;

	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();

	$albumsPath = GalleryUtilities::getRequestVariables('albumsPath');
	if ($albumsPath == null) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null, null);
	}

	$existingUsers = array();
	$newUsers = array();
	list($ret, $allUsers) = Gallery1DataParser::getUserUids($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	    
	foreach($allUsers as $uid => $userName) {
	    list($ret, $testUser) = GalleryUserHelper::fetchUserByUsername($userName);
	    if ($ret->isError() && !($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    if ($testUser) {
		$existingUsers[$uid] = $allUsers[$uid];
	    } else {
		$newUsers[$uid] = $allUsers[$uid];
	    }
	}

	if ($form['formName'] == 'ChooseObjects') {

	    /* Init the checkboxes to not-checked */
	    foreach ($newUsers as $uid => $username) {
		if (!isset($form['migrateUser'][$uid])) {
		    $form['migrateUser'][$uid] = null;
		}
	    }
	    
	} else {
	    $form['formName'] = 'ChooseObjects';

	    /* Init the checkboxes to not-checked */
	    foreach ($newUsers as $uid => $username) {
		$form['migrateUser'][$uid] = null;
	    }
	}

	list ($ret, $g1AlbumTree) = $this->_createG1AlbumTree($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Get all possible destinations (where user has write permission) */
        list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	/* Get ids of all all albums where we can add new album items */
        list ($ret, $albumIds) =
	    GalleryItemHelper::fetchAllItemIds('GalleryAlbumItem', 'core.addAlbumItem');
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
	
	/* Load all the album entities */
        list ($ret, $albums) = $gallery->loadEntitiesById($albumIds);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
	$g2AlbumTree = $this->_createG2AlbumTree($albums);

	$ChooseObjects['albumsPath'] = $albumsPath;
	$ChooseObjects['newUsers'] = $newUsers;
	$ChooseObjects['existingUsers'] = $existingUsers;
	$ChooseObjects['g1AlbumTree'] = $g1AlbumTree;
	$ChooseObjects['g2AlbumTree'] = $g2AlbumTree;

	$template->setVariable('ChooseObjects', $ChooseObjects);
        $template->setVariable('controller', 'migrate:ChooseObjects');
	
        return array(GalleryStatus::success(), '', 'modules/migrate/templates/ChooseObjects.tpl');
    }

    /**
     * Extract all G1 albums and turn it into a depth tree suitable for display
     * in a hierarchical format.
     */
    function _createG1AlbumTree($albumsPath) {

	list($ret, $albumList) = Gallery1DataParser::getAlbumList($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list($ret, $hierarchy) = Gallery1DataParser::getAlbumHierarchy($albumsPath);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$tree = array();
	foreach ($hierarchy as $albumName => $subHierarchy) {
	    $tree = array_merge($tree, $this->_createG1DepthTree($albumList, $albumName, $subHierarchy));
	}

	return array(GalleryStatus::success(), $tree);
    }

    /**
     * Recursively walk a parent/child map and build the depth tree.
     *
     * @access private
     */
    function _createG1DepthTree(&$albumList, $albumName, $hierarchy, $depth=0) {
	$data = array();
	$data[] = array('depth' => $depth, 'data' => $albumList[$albumName]);
	foreach ($hierarchy as $childAlbumName => $subHierarchy) {
	    $data = array_merge($data, $this->_createG1DepthTree($albumList,
								 $childAlbumName, $subHierarchy,
								 $depth + 1));
	}

	return $data;
    }
    
    /**
     * Turn a set of G2 albums into a depth tree suitable for display in a
     * hierarchical format.
     *
     * @access private
     */
    function _createG2AlbumTree($albums) {
	/* Index the albums by id */
	$map = array();
	foreach ($albums as $album) {
	    $albumId = $album->getId();
	    $parentId = $album->getParentId();
	    $map[$albumId]['instance'] = $album;
	    if (!empty($parentId)) {
		$map[$albumId]['parent'] = $parentId;
		$map[$parentId]['children'][] = $albumId;
	    }
	}

	/*
	 * Prune parents that don't exist.  This can occur if we have multiple
	 * roots (unusual) or an album in the middle of the hierarchy that is
	 * not viewable.
	 */
	foreach ($map as $id => $info) {
	    if (isset($info['parent']) && !isset($map[$info['parent']]['instance'])) {
		unset($map[$info['parent']]);
	    }
	}

	/* Find root albums */
	foreach ($map as $id => $info) {
	    if (!isset($info['parent']) || !isset($map[$info['parent']])) {
		$roots[] = $id;
	    }
	}

	/* Walk the root albums */
	$tree = array();
	foreach ($roots as $id) {
	    $tree = array_merge($tree, $this->_createG2DepthTree($map, $id));
	}

	return $tree;
    }

    /**
     * Recursively walk a parent/child map and build the depth tree.
     *
     * @access private
     */
    function _createG2DepthTree(&$map, $id, $depth=0) {
	$data = array();
	$data[] = array('depth' => $depth, 'data' => $map[$id]['instance']->getMemberData());
	if (isset($map[$id]['children'])) {
	    foreach ($map[$id]['children'] as $childId) {
		$data = array_merge($data, $this->_createG2DepthTree($map, $childId, $depth+1));
	    }
	}

	return $data;
    }
}
?>
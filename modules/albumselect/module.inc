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
 * @package AlbumSelect
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * The implementation of the AlbumSelect module
 *
 * @package AlbumSelect
 */
class AlbumSelectModule extends GalleryModule {

    function AlbumSelectModule() {
	global $gallery;
	$this->setId('albumselect');
	$this->setName('Album Select');
	$this->setDescription($gallery->i18n('Jump directly to any album using a select box'));
	$this->setVersion('0.8.3');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('getSiteAdminViews|loadSystemContent');
	$this->setRequiredCoreApi(array(3, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return false;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'albumselect');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	foreach (array('show' => 1, 'sort' => 0) as $key => $value) {
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
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Album Select'),
				 'view' => 'albumselect:AlbumSelectSiteAdmin')));
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	/* Load template data, but only show in systemContent if module param is set */
	list ($ret, $tree) = GalleryCoreApi::fetchAlbumTree();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($tree)) {
	    return array(GalleryStatus::success(), null);
	}
	list ($ret, $items) =
	    GalleryCoreApi::loadEntitiesById(GalleryUtilities::arrayKeysRecursive($tree));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach ($items as $treeItem) {
	    $treeItems[$treeItem->getId()] = $treeItem->getMemberData();
	}
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'albumselect');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$treeList = array();
	$sorter = $params['sort'] ? new AlbumSelectTreeSorter('title', $treeItems) : null;
	$this->_parseTree($tree, $treeList, $sorter);
	$template->setVariable('AlbumSelectSystemContent',
	    array('tree' => $treeList, 'treeItems' => $treeItems,
		  'template' => 'modules/albumselect/templates/AlbumSelect.tpl'));
	return array(GalleryStatus::success(),
		     $params['show'] ? 'modules/albumselect/templates/AlbumSelect.tpl' : null);
    }

    /**
     * Build template data for subalbum tree
     * @private
     */
    function _parseTree($tree, &$treeList, &$sorter, $depth=0) {
	if (isset($sorter)) {
	    uksort($tree, array($sorter, 'sort'));
	}
	foreach ($tree as $id => $list) {
	    $treeList[] = array('id' => $id, 'depth' => $depth);
	    if (!empty($list)) {
		$this->_parseTree($list, $treeList, $sorter, $depth+1);
	    }
	}
    }
}

/**
 * Sort albums on a specific field
 */
class AlbumSelectTreeSorter {
    function AlbumSelectTreeSorter($field, &$treeItems) {
	$this->_field = $field;
	$this->_treeItems =& $treeItems;
    }
    function sort($a, $b) {
	return strcmp($this->_treeItems[$a][$this->_field], $this->_treeItems[$b][$this->_field]);
    }
}
?>

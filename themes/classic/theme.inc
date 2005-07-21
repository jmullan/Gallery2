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
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This implements the standard gallery theme
 *
 * @package GalleryTheme
 * @subpackage Theme
 */
class ClassicTheme extends GalleryTheme {

    /**
     * Constructor
     */
    function ClassicTheme() {
	global $gallery;

	$this->setId('classic');
	$this->setName($gallery->i18n('Classic'));
	$this->setDescription($gallery->i18n('Classic Gallery2 root album look and feel'));
	$this->setVersion('0.9.2');
	$this->setRequiredThemeApi(array(2, 1));
	$this->setRequiredCoreApi(array(6, 4));
	$this->setStandardSettings(
	    array('rows' => 10, 'columns' => 1,
		  'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'showMicroThumbs' => 0,
		  'colorpack' => '',
		  'sidebarBlocks' => serialize(
		      array(
			  array('search.SearchBlock', array('showAdvancedLink' => true)),
			  array('core.ItemLinks', array('useDropdown' => false)),
			  array('core.PeerList', array()),
			  array('imageblock.ImageBlock', array()))),
		  'albumBlocks' => serialize(
		      array(array('comment.ViewComments', array()))),
		  'photoBlocks' => serialize(
		      array(
			  array('exif.ExifInfo', array()),
			  array('comment.ViewComments', array())))));
    }

    /**
     * @see GalleryLayout::getSettings()
     */
    function getSettings($itemId=null) {
	list ($ret, $settings) = parent::getSettings($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $params) = $this->fetchParameters($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our custom settings */
	$params = array_merge(array('showSubalbums' => 1, 'subalbumDepth' => 0), $params);
	$settings[] = array('key' => 'showSubalbums',
			    'name' => $this->translate('Show subalbum links'),
			    'type' => 'checkbox',
			    'value' => $params['showSubalbums']);
	$settings[] = array('key' => 'subalbumDepth',
			    'name' => $this->translate('Depth of subalbums links (0=no limit)'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 2),
			    'value' => $params['subalbumDepth']);

	return array(GalleryStatus::success(), $settings);
    }

    /**
     * @see GalleryLayout::validateSettings
     */
    function validateSettings($settings) {
	$error = parent::validateSettings($settings);
	if (!is_numeric($settings['subalbumDepth'])) {
	    $error['subalbumDepth'] = $this->translate('You must enter a number');
	}
	return $error;
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'descendentCount', 'parents', 'peers',
		  'systemLinks', 'itemLinks', 'itemSummaries', 'permissions',
		  'itemDetailFiles', 'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$theme =& $template->getVariableByReference('theme');
	if ($params['showSubalbums']) {
	    list ($ret, $tree) = GalleryCoreApi::fetchAlbumTree($item->getId(),
		$params['subalbumDepth'] > 0 ? $params['subalbumDepth'] + 1 : null);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $treeIds = $treeList = $treeItems = array();
	    foreach ($theme['children'] as $child) {
		$childId = $child['id'];
		if (isset($tree[$childId])) {
		    $treeList[$childId] = array();
		    $this->_parseTree($tree[$childId], $treeList[$childId], $treeIds);
		}
	    }
	    if (!empty($treeIds)) {
		list ($ret, $treeItems) = GalleryCoreApi::loadEntitiesById($treeIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $theme['tree'] = $treeList;
	    $theme['treeItems'] = array();
	    foreach ($treeItems as $treeItem) {
		$theme['treeItems'][$treeItem->getId()] = $treeItem->getMemberData();
	    }
	}

	/* Add our header and styles */
	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'peers', 'systemLinks', 'permissions',
			   'itemLinks', 'itemLinksDetailed', 'itemDetailFiles', 'itemNavigator',
			   'imageViews');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'peerThumbnails';
	}
	$ret = $this->loadCommonTemplateData($template, $item, $params, $dataTypes);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showModulePage
     */
    function showModulePage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showAdminPage
     */
    function showAdminPage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showErrorPage
     */
    function showErrorPage(&$template) {
	return array(GalleryStatus::success(), 'error.tpl');
    }

    /**
     * @see GalleryTheme::showProgressBarPage
     */
    function showProgressBarPage(&$template, $item, $params) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * Build template data for subalbum tree
     * @access private
     */
    function _parseTree($tree, &$treeList, &$treeIds, $depth=0) {
	foreach ($tree as $id => $list) {
	    $treeIds[] = $id;
	    $treeList[] = array('id' => $id, 'depth' => $depth);
	    if (!empty($list)) {
		$this->_parseTree($list, $treeList, $treeIds, $depth+1);
	    }
	}
    }
}
?>

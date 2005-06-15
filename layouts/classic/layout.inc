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
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This implements the classic gallery layout
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class ClassicLayout extends GalleryLayout {

    /**
     * Constructor
     */
    function ClassicLayout() {
	global $gallery;

	$this->setId('classic');
	$this->setName($gallery->i18n('Classic'));
	$this->setDescription(
	    $gallery->i18n('Columns for thumbnails, item info and links to subalbums'));
	$this->setVersion('0.9.6');
	$this->setL10Domain('layouts_classic');
	$this->setRequiredLayoutApi(array(1, 1));
	$this->setRequiredCoreApi(array(6, 0));
	$this->setStandardSettings(
	    array('rows' => 10, 'columns' => 1,
		  'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'showMicroThumbs' => 0));
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
     * @see GalleryLayout::loadAlbumTemplate
     */
    function loadAlbumTemplate(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'descendentCount', 'parents', 'peers',
		  'systemLinks', 'systemContent', 'itemLinks', 'itemSummaries',
		  'itemDetailFiles', 'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$layout =& $template->getVariableByReference('layout');
	if ($params['showSubalbums']) {
	    list ($ret, $tree) = GalleryCoreApi::fetchAlbumTree($item->getId(),
		$params['subalbumDepth'] > 0 ? $params['subalbumDepth'] + 1 : null);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $treeIds = $treeList = $treeItems = array();
	    foreach ($layout['children'] as $child) {
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
	    $layout['tree'] = $treeList;
	    $layout['treeItems'] = array();
	    foreach ($treeItems as $treeItem) {
		$layout['treeItems'][$treeItem->getId()] = $treeItem->getMemberData();
	    }
	}

	$template->head('layouts/classic/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/classic/layout.css');
	return array(GalleryStatus::success(), 'layouts/classic/templates/albumBody.tpl');
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

    /**
     * @see GalleryLayout::loadItemTemplate
     */
    function loadItemTemplate(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'peers', 'systemLinks', 'systemContent',
			   'itemLinks', 'itemDetailFiles', 'itemNavigator', 'imageViews');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'peerThumbnails';
	}
	$ret = $this->loadCommonTemplateData($template, $item, $params, $dataTypes);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$template->head('layouts/classic/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/classic/layout.css');
	return array(GalleryStatus::success(), 'layouts/classic/templates/singleBody.tpl');
    }
}
?>

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

/* Load parent class */
GalleryCoreApi::relativeRequireOnce('layouts/matrix/layout.inc');

/**
 * This implements the classic gallery layout
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class ClassicLayout extends MatrixLayout {

    /**
     * Constructor
     */
    function ClassicLayout() {
	global $gallery;

	$this->setId('classic');
	$this->setName('Classic');
	$this->setDescription($gallery->i18n('Columns for thumbnails, item info and links to subalbums'));
	$this->setVersion('0.5');
	$this->setL10Domain('layouts_classic');
	$this->setRequiredLayoutApi(array(0, 8));
	$this->setRequiredCoreApi(array(3, 2));
    }

    /**
     * @see GalleryLayout::getSettings()
     */
    function getSettings($itemId=null) {
	global $gallery;

	list ($ret, $params) = $this->fetchParameters($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$params = array_merge(
	    array('rows' => 10, 'columns' => 1, 'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '', 'showSubalbums' => 1,
		  'subalbumDepth' => 0),
	    $params);

	$settings = array();
	$settings[] = array('key' => 'rows',
			    'name' => $gallery->i18n('Rows per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['rows']);
	$settings[] = array('key' => 'columns',
			    'name' => $gallery->i18n('Columns of thumbnails per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['columns']);
	$settings[] = array('key' => 'showSubalbums',
			    'name' => $gallery->i18n('Show subalbum links'),
			    'type' => 'checkbox',
			    'value' => $params['showSubalbums']);
	$settings[] = array('key' => 'subalbumDepth',
			    'name' => $gallery->i18n('Depth of subalbums links (0=no limit)'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['subalbumDepth']);
	$settings[] = array('key' => 'showImageOwner',
			    'name' => $gallery->i18n('Show image owners'),
			    'type' => 'checkbox',
			    'value' => $params['showImageOwner']);
	$settings[] = array('key' => 'showAlbumOwner',
			    'name' => $gallery->i18n('Show album owners'),
			    'type' => 'checkbox',
			    'value' => $params['showAlbumOwner']);

	/* ImageFrame settings, if available */
	list ($ret, $imageframe) = GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($imageframe)) {
	    list ($ret, $list) = $imageframe->getImageFrameList();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $sampleUrl) = $imageframe->getSampleUrl($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $sample = ' (<a href="' . $sampleUrl . '">' .  $gallery->i18n('View Samples') . '</a>)';

	    $settings[] = array('key' => 'albumFrame',
				'name' => $gallery->i18n('Album Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['albumFrame']);
	    $settings[] = array('key' => 'itemFrame',
				'name' => $gallery->i18n('Item Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['itemFrame']);
	    $settings[] = array('key' => 'photoFrame',
				'name' => $gallery->i18n('Photo Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['photoFrame']);
	}

	return array(GalleryStatus::success(), $settings);
    }

    /**
     * @see MatrixLayout::validateSettings
     */
    function validateSettings($settings) {
	$error = parent::validateSettings($settings);
	if (!is_numeric($settings['subalbumDepth'])) {
	    $error['subalbumDepth'] = $this->translate('You must enter a number');
	}
	return $error;
    }

    /**
     * @see MatrixLayout::_loadAlbumTemplate
     */
    function _loadAlbumTemplate(&$template, $item, $properties) {
	list ($ret, $matrixResult) = parent::_loadAlbumTemplate($template, $item, $properties);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (is_array($matrixResult)) {
	    // Return now if we are doing a redirect..
	    return array(GalleryStatus::success(), $matrixResult);
	}

	$layout =& $template->getVariableByReference('layout');
	$layout['showSubalbums'] = $properties['showSubalbums'];

	if ($properties['showSubalbums']) {
	    list ($ret, $tree) = GalleryCoreApi::fetchAlbumTree($item->getId(),
			$properties['subalbumDepth'] > 0 ? $properties['subalbumDepth'] + 1 : null);
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

	return array(GalleryStatus::success(), 'layouts/classic/templates/albumBody.tpl');
    }

    /**
     * Build template data for subalbum tree
     * @private
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

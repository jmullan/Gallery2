<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
/**
 * @version $Revision$ $Date$
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This implements the standard gallery theme
 *
 * @package GalleryTheme
 * @subpackage Theme
 */
class MatrixTheme extends GalleryTheme {

    /**
     * Constructor
     */
    function MatrixTheme() {
	global $gallery;

	$this->setId('matrix');
	$this->setName($gallery->i18n('Matrix'));
	$this->setDescription($gallery->i18n('Standard Gallery2 look and feel'));
	$this->setVersion('1.0.2');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredThemeApi(array(2, 1));
	$this->setStandardSettings(
	    array('rows' => 3, 'columns' => 3,
		  'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'colorpack' => '',
		  'showMicroThumbs' => 0, 'useFloatingDivs' => 0,
		  'sidebarBlocks' => serialize(array(
			array('search.SearchBlock', array('showAdvancedLink' => true)),
			array('core.ItemLinks', array('useDropdown' => false)),
			array('core.PeerList', array()),
			array('imageblock.ImageBlock', array()))),
		  'albumBlocks' => serialize(array(
			array('comment.ViewComments', array()))),
		  'photoBlocks' => serialize(array(
			array('exif.ExifInfo', array()),
			array('comment.ViewComments', array())))));
    }

    /**
     * @see GalleryTheme::getSettings()
     */
    function getSettings($itemId=null) {
	list ($ret, $settings, $params) = parent::getSettings($itemId);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our custom settings */
	$settings[] = array(
	    'key' => 'useFloatingDivs',
	    'name' => $this->translate(
		'Use floating divs instead of a table to display thumbnails'),
	    'type' => 'checkbox',
	    'value' => isset($params['useFloatingDivs']) ? $params['useFloatingDivs'] : false);
	$settings[] = array(
	    'key' => 'floatCount',
	    'name' => $this->translate('Items per page'),
	    'type' => 'text-field',
	    'typeParams' => array('size' => 3),
	    'value' => isset($params['floatCount']) ? $params['floatCount'] : 12);
	$settings[] = array(
	    'key' => 'floatWidth',
	    'name' => $this->translate('Width of floating items'),
	    'type' => 'text-field',
	    'typeParams' => array('size' => 3),
	    'value' => isset($params['floatWidth']) ? $params['floatWidth'] : 200);
	$settings[] = array(
	    'key' => 'floatHeight',
	    'name' => $this->translate('Height of floating items'),
	    'type' => 'text-field',
	    'typeParams' => array('size' => 3),
	    'value' => isset($params['floatHeight']) ? $params['floatHeight'] : 250);

	return array(null, $settings);
    }

    /**
     * If floating divs, override getPageSize to use floatCount
     */
    function getPageSize($params) {
	if (empty($params['useFloatingDivs'])) {
	    return parent::getPageSize($params);
	} elseif (!empty($params['floatCount'])) {
	    return $params['floatCount'];
	}
	return 0;
    }

    /**
     * @see GalleryTheme::validateSettings
     */
    function validateSettings($settings) {
	$error = parent::validateSettings($settings);
	if (!empty($settings['useFloatingDivs'])) {
	    if (!is_numeric($settings['floatCount'])) {
		$error['floatCount'] = $this->translate('You must enter a number');
	    }
	    if (!is_numeric($settings['floatWidth'])) {
		$error['floatWidth'] = $this->translate('You must enter a number');
	    }
	    if (!is_numeric($settings['floatHeight'])) {
		$error['floatHeight'] = $this->translate('You must enter a number');
	    }
	}
	return $error;
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'childCount', 'descendentCount', 'parents',
		  'systemLinks', 'itemLinks', 'itemSummaries', 'permissions',
		  'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$theme =& $template->getVariableByReference('theme');
	$theme['columnWidthPct'] = floor(100 / $params['columns']);

	/* Add our header and styles */
	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'systemLinks', 'itemLinks', 'permissions',
			   'itemLinksDetailed', 'itemNavigator', 'imageViews');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'navThumbnails';
	}
	$ret = $this->loadCommonTemplateData($template, $item, $params, $dataTypes);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showModulePage
     */
    function showModulePage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showAdminPage
     */
    function showAdminPage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showErrorPage
     */
    function showErrorPage(&$template) {
	return array(null, 'error.tpl');
    }

    /**
     * @see GalleryTheme::showProgressBarPage
     */
    function showProgressBarPage(&$template, $item, $params) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }
}
?>

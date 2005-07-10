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
	$this->setVersion('0.9.8');  /* Update MatrixTheme::upgrade also */
	$this->setL10Domain('themes_matrix');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredThemeApi(array(2, 0));
	$this->setStandardSettings(
	    array('rows' => 3, 'columns' => 3,
		  'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'colorpack' => '',
		  'showMicroThumbs' => 0,
		  'sidebarBlocks' => '',
		  'albumBlocks' => '',
		  'photoBlocks' => ''));
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
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
	$theme =& $template->getVariableByReference('theme');
	$theme['columnWidthPct'] = floor(100 / $params['columns']);

	/* Add our header and styles */
	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'peers', 'systemLinks', 'systemContent',
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
	    $template, $item, $params,
	    array('parents', 'systemLinks', 'systemContent'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$theme =& $template->getVariableByReference('theme');
	$theme['moduleTemplate'] = $templateFile;

	/* Add our header and styles */
	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showAdminPage
     */
    function showAdminPage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('parents', 'systemLinks', 'systemContent'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$theme =& $template->getVariableByReference('theme');
	$theme['adminTemplate'] = $templateFile;

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
	    $template, $item, $params,
	    array('parents', 'systemLinks', 'systemContent'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::upgrade
     */
    function upgrade($installedVersion) {
	if (version_compare($installedVersion, '0.9.7', '<')) {
	    /* Older than the big theme changeover.  Set some default blocks */
	    foreach (array(
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
				 array('comment.ViewComments', array()))))
		     as $key => $value) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	    $installedVersion = '0.9.7';
	}

	switch ($installedVersion) {
	case '0.9.7':
	    $ret = $this->setParameter('colorpack', '');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case 'end of upgrade path':
	    break;

	default:
	    return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
					sprintf('Unknown theme version %s', $installedVersion));
	}

	return GalleryStatus::success();
    }
}
?>

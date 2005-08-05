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
class SiriuxTheme extends GalleryTheme {

    /**
     * Constructor
     */
    function SiriuxTheme() {
	global $gallery;

	$this->setId('siriux');
	$this->setName($gallery->i18n('Siriux'));
	$this->setDescription($gallery->i18n('Siriux.net Gallery theme'));
	$this->setVersion('0.9.8');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredThemeApi(array(2, 0));
	$this->setStandardSettings(
	    array('showImageOwner' => 0,
		  'perPage' => 9,
		  'albumBlocks' => serialize(array(
			array('comment.ViewComments', array()))),
		  'photoBlocks' => serialize(array(
			array('exif.ExifInfo', array()),
			array('comment.ViewComments', array())))));
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'childCount', 'descendentCount', 'parents', 'peers',
		  'systemLinks', 'itemLinks', 'itemSummaries', 'permissions',
		  'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Override some navigator settings */
	$theme =& $template->getVariableByReference('theme');
	if (!isset($theme['navigator']['back']) && isset($theme['navigator']['first'])) {
	    $theme['navigator']['back'] = $theme['navigator']['first'];
	}
	$theme =& $template->getVariableByReference('theme');
	if (!isset($theme['navigator']['next']) && isset($theme['navigator']['last'])) {
	    $theme['navigator']['next'] = $theme['navigator']['last'];
	}

	/* Add our header and styles */
	return array(GalleryStatus::success(), 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'peers', 'systemLinks', 'itemLinks', 'permissions',
			   'itemLinksDetailed', 'itemNavigator', 'imageViews');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'peerThumbnails';
	}
	$ret = $this->loadCommonTemplateData($template, $item, $params, $dataTypes);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Override some navigator settings */
	$theme =& $template->getVariableByReference('theme');
	if (!isset($theme['navigator']['back']) && isset($theme['navigator']['first'])) {
	    $theme['navigator']['back'] = $theme['navigator']['first'];
	}
	$theme =& $template->getVariableByReference('theme');
	if (!isset($theme['navigator']['next']) && isset($theme['navigator']['last'])) {
	    $theme['navigator']['next'] = $theme['navigator']['last'];
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
	    $template, $item, $params, array('parents', 'systemLinks'));
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
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), 'theme.tpl');
    }
}
?>

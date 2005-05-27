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
 * @author Nico Kaiser <nico@siriux.net>
 */

/**
 * siriux.net Layout for Gallery
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class SiriuxLayout extends GalleryLayout {

    /**
     * Constructor
     */
    function SiriuxLayout() {
	global $gallery;

	$this->setId('siriux');
	$this->setName($gallery->i18n('Siriux'));
	$this->setDescription($gallery->i18n('Siriux.net Gallery layout'));
	$this->setVersion('0.9.4');
	$this->setL10Domain('layouts_siriux');
	$this->setRequiredLayoutApi(array(0, 12));
	$this->setRequiredCoreApi(array(5, 0));
	$this->setStandardSettings(array('showImageOwner' => 0, 'perPage' => 9));
    }

    /**
     * @see GalleryLayout::loadAlbumTemplate
     */
    function loadAlbumTemplate(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'childCount', 'descendentCount', 'parents', 'peers',
		  'systemLinks', 'systemContent', 'itemLinks', 'itemSummaries',
		  'itemDetailFiles', 'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Override some navigator settings */
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['back']) && isset($layout['navigator']['first'])) {
	    $layout['navigator']['back'] = $layout['navigator']['first'];
	}
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['next']) && isset($layout['navigator']['last'])) {
	    $layout['navigator']['next'] = $layout['navigator']['last'];
	}

	$template->head('layouts/siriux/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/siriux/layout.css');
	return array(GalleryStatus::success(), 'layouts/siriux/templates/albumBody.tpl');
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

	/* Override some navigator settings */
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['back']) && isset($layout['navigator']['first'])) {
	    $layout['navigator']['back'] = $layout['navigator']['first'];
	}
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['next']) && isset($layout['navigator']['last'])) {
	    $layout['navigator']['next'] = $layout['navigator']['last'];
	}

	$template->head('layouts/siriux/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/siriux/layout.css');
	return array(GalleryStatus::success(), 'layouts/siriux/templates/singleBody.tpl');
    }
}
?>

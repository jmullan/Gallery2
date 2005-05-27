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
 * This implements the standard gallery layout
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class MatrixLayout extends GalleryLayout {

    /**
     * Constructor
     */
    function MatrixLayout() {
	global $gallery;

	$this->setId('matrix');
	$this->setName($gallery->i18n('Matrix'));
	$this->setDescription($gallery->i18n('Standard Gallery2 look and feel'));
	$this->setVersion('0.9.3');
	$this->setL10Domain('layouts_matrix');
	$this->setRequiredLayoutApi(array(0, 12));
	$this->setRequiredCoreApi(array(5, 0));
	$this->setStandardSettings(array('rows' => 3, 'columns' => 3,
					 'showImageOwner' => 0, 'showAlbumOwner' => 1,
					 'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
					 'showMicroThumbs' => 0));
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
	$layout['columnWidthPct'] = floor(100 / $params['columns']);

	/* Add our header and styles */
	$template->head('layouts/matrix/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/matrix/layout.css');
	return array(GalleryStatus::success(), 'layouts/matrix/templates/albumBody.tpl');
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

	$template->head('layouts/matrix/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/matrix/layout.css');
	return array(GalleryStatus::success(), 'layouts/matrix/templates/singleBody.tpl');
    }
}
?>

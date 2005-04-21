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
	$this->setName('Matrix');
	$this->setDescription($gallery->i18n('Standard Gallery2 look and feel'));
	$this->setVersion('0.9.1');
	$this->setL10Domain('layouts_matrix');
	$this->setRequiredLayoutApi(array(0, 9));
	$this->setRequiredCoreApi(array(5, 0));
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
	    array('rows' => 3, 'columns' => 3, 'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'showMicroThumbs' => 0),
	    $params);

	$settings = array();
	$settings[] = array('key' => 'rows',
			    'name' => $gallery->i18n('Rows per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['rows']);
	$settings[] = array('key' => 'columns',
			    'name' => $gallery->i18n('Columns per album page'),
			    'type' => 'text-field',
			    'type-params' => array('size' => 2),
			    'value' => $params['columns']);
	$settings[] = array('key' => 'showImageOwner',
			    'name' => $gallery->i18n('Show image owners'),
			    'type' => 'checkbox',
			    'value' => $params['showImageOwner']);
	$settings[] = array('key' => 'showAlbumOwner',
			    'name' => $gallery->i18n('Show album owners'),
			    'type' => 'checkbox',
			    'value' => $params['showAlbumOwner']);
	$settings[] = array('key' => 'showMicroThumbs',
			    'name' => $gallery->i18n('Show micro navigation thumbnails'),
			    'type' => 'checkbox',
			    'value' => $params['showMicroThumbs']);

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
	    $sample = ' (<a href="' . $sampleUrl . '">'
		    . $this->translate('View Samples') . '</a>)';

	    $settings[] = array('key' => 'albumFrame',
				'name' => $this->translate('Album Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['albumFrame']);
	    $settings[] = array('key' => 'itemFrame',
				'name' => $this->translate('Item Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['itemFrame']);
	    $settings[] = array('key' => 'photoFrame',
				'name' => $this->translate('Photo Frame') . $sample,
				'type' => 'single-select',
				'choices' => $list,
				'value' => $params['photoFrame']);
	}

	return array(GalleryStatus::success(), $settings);
    }

    /**
     * @see GalleryLayout::validateSettings
     */
    function validateSettings($settings) {
	$error = array();
	if (empty($settings['rows']) || !is_numeric($settings['rows'])) {
	    $error['rows'] = $this->translate('You must enter a number greater than 0');
	}

	if (empty($settings['columns']) || !is_numeric($settings['columns'])) {
	    $error['columns'] = $this->translate('You must enter a number greater than 0');
	}

	return $error;
    }

    /**
     * @see GalleryLayout::loadTemplate
     */
    function loadTemplate(&$template, $item) {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();

	if ($item->getCanContainChildren()) {
	    list ($ret, $params) = $this->fetchParameters($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $bodyFile) = $this->_loadAlbumTemplate($template, $item, $params);
	} else {
	    list ($ret, $params) = $this->fetchParameters($item->getParentId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $bodyFile) = $this->_loadSingleTemplate($template, $item, $params);
	}
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$layout =& $template->getVariableByReference('layout');

	/* Prepare image frames, if available */
	list ($ret, $imageframe) = GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($imageframe)) {
	    $frameIds = array();
	    if ($item->getCanContainChildren()) {
		foreach (array('albumFrame', 'itemFrame') as $key) {
		    if (!empty($params[$key])) {
			$frameIds[] = $layout[$key] = $params[$key];
		    }
		}
	    } else {
		if (!empty($params['photoFrame'])) {
		    $frameIds[] = $layout['photoFrame'] = $params['photoFrame'];
		}
	    }
	    if (!empty($frameIds)) {
		$ret = $imageframe->init($template, $frameIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	if (is_array($bodyFile)) {
	    return array(GalleryStatus::success(), $bodyFile);
	} else {
	    $template->head('layouts/matrix/templates/head.tpl');
	    $template->style('templates/layout.css');
	    $template->style('layouts/matrix/layout.css');
	    return array(GalleryStatus::success(), array('body' => $bodyFile));
	}
    }

    /**
     * Render an album
     *
     * @param array object GalleryTemplate the template instance
     * @param object GalleryItem the item to render.  Can be any subclass of GalleryItem
     * @param array the layout parameters
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     */
    function _loadAlbumTemplate(&$template, $item, $params) {
	$rows = $params['rows'];
	$columns = $params['columns'];
	$perPage = $rows * $columns;

	/* Figure out what page we're on */
	$page = GalleryUtilities::getRequestVariables('page');
	if (empty($page)) {
	    /*
	     * We don't have a page number.  If we have a highlight id, then figure out what
	     * page that id is on and redirect to that page.
	     */
	    $highlightId = GalleryUtilities::getRequestVariables('highlightId');
	    if (!empty($highlightId)) {
		list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$page = 1;
		for ($i = 0; $i < sizeof($childIds); $i++) {
		    if ($childIds[$i] == $highlightId) {
			/* Found it */
			$page = ceil(($i+1) / $perPage);
			break;
		    }
		}

		/* Redirect to the new page */
		$results['redirect'] = array('view' => 'core:ShowItem',
					     'itemId' => $item->getId(),
					     'page' => $page);
		return array(GalleryStatus::success(), $results);
	    } else {
		$page = 1;
	    }
	}

	$start = $perPage * ($page - 1);
	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item, $start, $perPage);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $this->loadLayoutTemplate($template, $item,
	    array('owner', 'viewCount', 'childCount', 'descendentCount', 'parents', 'peers',
		  'systemLinks', 'systemContent', 'itemLinks', 'itemSummaries',
		  'itemDetailFiles', 'thumbnails'),
	    $childIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$layout =& $template->getVariableByReference('layout');
	$totalChildCount = $layout['childCount'];

	/* Redirect to last page if exceeded the max pages */
	$totalPages = ceil($totalChildCount / $perPage);
	if ($page > $totalPages && $totalChildCount > 0) {
	    $results['redirect'] = array('view' => 'core:ShowItem',
					 'itemId' => $item->getId(),
					 'page' => $totalPages);
	    return array(GalleryStatus::success(), $results);
	}

	/* Set up the navigator */
	$navigator = array();
	if ($page > 1) {
	    $navigator['first']['urlParams'] = array('view' => 'core:ShowItem',
						     'itemId' => $item->getId(),
						     'page' => 1);

	    if ($page - 1 != 1) {
		$navigator['back']['urlParams'] = array('view' => 'core:ShowItem',
							'itemId' => $item->getId(),
							'page' => $page-1);
	    }
	}
	if ($page < $totalPages) {
	    if ($page + 1 != $totalPages) {
		$navigator['next']['urlParams'] = array('view' => 'core:ShowItem',
							'itemId' => $item->getId(),
							'page' => $page+1);
	    }

	    $navigator['last']['urlParams'] = array('view' => 'core:ShowItem',
						    'itemId' => $item->getId(),
						    'page' => $totalPages);
	}

	/* Show a window of 11 pages in the page navigator */
	$windowSize = 6;
	$jumprange = array();
	$lowerPage = max($page - (int)($windowSize / 2), 1);
	$upperPage = min($page + (int)($windowSize / 2), $totalPages);
	if ($upperPage == 0) {
	    $upperPage = 1;
	}
	if ($upperPage == $totalPages) {
	    $lowerPage = max($upperPage - $windowSize, 1);
	} else if ($lowerPage == 1) {
	    $upperPage = min($lowerPage + ($windowSize-1), $totalPages);
	}
	for ($i = $lowerPage; $i <= $upperPage; $i++) {
	    $jumprange[] = $i;
	}
	if ($lowerPage > 1) {
	    array_unshift($jumprange, 1);
	}
	if ($upperPage < $totalPages) {
	    $jumprange[] = $totalPages;
	}

	$layout['columnSize'] = $params['columns'];
	$layout['columnWidthPct'] = floor(100 / $params['columns']);
	$layout['currentPage'] = $page;
	$layout['totalPageCount'] = $totalPages;
	$layout['navigator'] = $navigator;
	$layout['jumprange'] = $jumprange;
	$layout['showAlbumOwner'] = $params['showAlbumOwner'];
	$layout['showImageOwner'] = $params['showImageOwner'];
	$layout['showMicroThumbs'] = $params['showMicroThumbs'];

	return array(GalleryStatus::success(), 'layouts/matrix/templates/albumBody.tpl');
    }


    /**
     * Render a single item
     *
     * @param array object GalleryTemplate the template instance
     * @param object GalleryItem the item to render.  Can be any subclass of GalleryItem
     * @param array the layout parameters
     * @return array object GalleryStatus a status code
     *         string the HTML body
     * @access private
     * @todo Maybe display the sizes of an image in increasing order
     */
    function _loadSingleTemplate(&$template, $item, $params) {
	/*
	 * Figure out all possible views of this item that the user can see and
	 * get them into an acceptable format for the template engine.
	 */
	$imageViews = array();
	$can = array();
	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Can we see this item at all? */
	if (!isset($permissions['core.view'])) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__), null);
	}

	/* If the user can see resized versions, add those to the list */
	if (isset($permissions['core.viewResizes'])) {
	    /* Load the resizes */
	    list ($ret, $resizes) =
		GalleryCoreApi::fetchResizesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($resizes)) {
		foreach ($resizes[$item->getId()] as $resize) {
		    /* Rebuild the derivative if we don't have its dimensions */
		    if ($resize->getWidth() == 0 || $resize->getHeight() == 0) {
			list ($ret, $resize) =
			    GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($resize->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		    $imageViews[] = $resize->getMemberData();
		    $can['viewInline'][] = 1;
		}
	    }
	}

	/* If the user can see the full version, add it to the list */
	$sourceImage = null;
	if (isset($permissions['core.viewSource'])) {
	    /* Add the full version */
	    list ($ret, $preferred) =
		GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Show the preferred item, if it's there */
	    if (empty($preferred)) {
		$sourceImage = $item->getMemberData();
		if ($item->canBeViewedInline()) {
		    $can['viewInline'][] = 1;
		} else {
		    $can['viewInline'][] = 0;
		}
	    } else {
		$sourceImage = $preferred[$item->getId()]->getMemberData();
		$can['viewInline'][] = 1;
	    }
	    $sourceImage['itemTypeName'] = $item->itemTypeName();
	    $sourceImage['isSource'] = true;
	    $imageViews[] = $sourceImage;
	    $sourceImageViewIndex = sizeof($imageViews)-1;
	}

	/*
	 * If all else fails, just show the thumbnail.
	 */
	if (empty($imageViews)) {

	    /* Load the thumbnail */
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($thumbnails)) {
		$imageViews[] = $thumbnails[$item->getId()]->getMemberData();
		$can['viewInline'][] = 1;
	    }
	}

	$imageViewsIndex = GalleryUtilities::getRequestVariables('imageViewsIndex');
	if (empty($imageViewsIndex)) {
	    $imageViewsIndex = 0;
	}

	/* Don't let the index overflow the images array */
	$imageViewsIndex = min($imageViewsIndex, count($imageViews) - 1);
	$dataTypes = array('owner', 'parents', 'peers', 'systemLinks', 'systemContent',
			   'itemLinks', 'itemDetailFiles');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'peerThumbnails';
	}
	$ret = $this->loadLayoutTemplate($template, $item, $dataTypes);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$layout =& $template->getVariableByReference('layout');

	$navigator = array();
	$itemIndex = $layout['peerItemIndex'];
	if ($itemIndex > 0) {
	    $navigator['first']['urlParams'] = array('view' => 'core:ShowItem',
						     'itemId' => $layout['peers'][0]['id']);
	    $navigator['first']['item'] = $layout['peers'][0];
	}

	if ($itemIndex > 1) {
	    $navigator['back']['urlParams'] =
		array('view' => 'core:ShowItem',
		      'itemId' => $layout['peers'][$itemIndex - 1]['id']);
	    $navigator['back']['item'] = $layout['peers'][$itemIndex - 1];
	}

	if ($itemIndex < count($layout['peers']) - 2) {
	    $navigator['next']['urlParams'] =
		array('view' => 'core:ShowItem',
		      'itemId' => $layout['peers'][$itemIndex + 1]['id']);
	    $navigator['next']['item'] = $layout['peers'][$itemIndex + 1];
	}

	if ($itemIndex < count($layout['peers']) - 1) {
	    $navigator['last']['urlParams'] =
		array('view' => 'core:ShowItem',
		      'itemId' => $layout['peers'][count($layout['peers']) - 1]['id']);
	    $navigator['last']['item'] = $layout['peers'][count($layout['peers']) - 1];
	}

	/* Tell Smarty about everything we've learned */
	$layout['can'] = $can;
	if (isset($sourceImageViewIndex)) {
	    $layout['sourceImageViewIndex'] = $sourceImageViewIndex;
	}

	$layout['baseUrl'] = GalleryUtilities::convertPathToUrl(dirname(__FILE__));
	$layout['imageViews'] = $imageViews;
	$layout['sourceImage'] = $sourceImage;
	$layout['imageViewsIndex'] = $imageViewsIndex;
	$layout['navigator'] = $navigator;
	$layout['showImageOwner'] = $params['showImageOwner'];

	return array(GalleryStatus::success(), 'layouts/matrix/templates/singleBody.tpl');
    }
}
?>

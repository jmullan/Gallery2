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
 * @package ImageBlock
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * @package ImageBlock
 * @subpackage UserInterface
 */
class ImageBlockSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	if (isset($form['action']['save'])) {
	    $param = array();
	    foreach (array('randomImage', 'recentImage', 'viewedImage',
			   'randomAlbum', 'recentAlbum', 'viewedAlbum',
			   'dailyImage', 'weeklyImage', 'monthlyImage',
			   'dailyAlbum', 'weeklyAlbum', 'monthlyAlbum')
			as $key) {
		if (isset($form[$key]) && $form[$key]) {
		    $param[] = $key;
		}
	    }
	    $ret = GalleryCoreApi::setPluginParameter('module', 'imageblock',
						      'blocks', implode('|', $param));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $param = array();
	    foreach (array('title', 'date', 'views', 'owner') as $key) {
		if (isset($form[$key]) && $form[$key]) {
		    $param[] = $key;
		}
	    }
	    $ret = GalleryCoreApi::setPluginParameter('module', 'imageblock',
						      'show', implode('|', $param));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach (array('albumFrame', 'itemFrame') as $key) {
		if (isset($form[$key])) {
		    $ret = GalleryCoreApi::setPluginParameter('module', 'imageblock',
							      $key, $form[$key]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    $status['saved'] = 1;
	} /* else $form['action']['reset'] */

	/* Figure out where to redirect upon success */
	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'imageblock:ImageBlockSiteAdmin';
	$results['status'] = $status;
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package ImageBlock
 * @subpackage UserInterface
 */
class ImageBlockSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	if ($form['formName'] != 'ImageBlockSiteAdmin') {
	    $form['formName'] = 'ImageBlockSiteAdmin';
	    foreach (array('randomImage', 'recentImage', 'viewedImage',
			   'randomAlbum', 'recentAlbum', 'viewedAlbum',
			   'dailyImage', 'weeklyImage', 'monthlyImage',
			   'dailyAlbum', 'weeklyAlbum', 'monthlyAlbum',
			   'title', 'date', 'views', 'owner') as $tmp) {
		$form[$tmp] = 0;
	    }
	    list ($ret, $param) =
		GalleryCoreApi::fetchAllPluginParameters('module', 'imageblock');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach (explode('|', $param['blocks']) as $tmp) {
		$form[$tmp] = 1;
	    }
	    foreach (explode('|', $param['show']) as $tmp) {
		$form[$tmp] = 1;
	    }
	    $form['albumFrame'] = $param['albumFrame'];
	    $form['itemFrame'] = $param['itemFrame'];
	}
	$ImageBlockSiteAdmin = array('prefix' => GALLERY_FORM_VARIABLE_PREFIX);

	/* ImageFrame settings, if available */
	list ($ret, $imageframe) = GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($imageframe)) {
	    list ($ret, $ImageBlockSiteAdmin['list']) = $imageframe->getImageFrameList();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $ImageBlockSiteAdmin['sampleUrl']) = $imageframe->getSampleUrl();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$template->setVariable('ImageBlockSiteAdmin', $ImageBlockSiteAdmin);
	$template->setVariable('controller', 'imageblock:ImageBlockSiteAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/imageblock/templates/SiteAdmin.tpl'));
    }
}
?>

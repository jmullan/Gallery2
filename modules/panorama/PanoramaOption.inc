<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package Panorama
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This ItemEditOption will handle switching between Photo and Panorama types
 *
 * @package Panorama
 * @subpackage UserInterface
 *
 */
class PanoramaOption extends ItemEditOption {

    /**
     * @see ItemEditOption::isAppropriate
     */
    function isAppropriate($item, $thumbnail) {
	if (!GalleryUtilities::isExactlyA($item, 'GalleryPhotoItem') &&
		!GalleryUtilities::isExactlyA($item, 'PanoramaPhotoItem')) {
	    return array(GalleryStatus::success(), false);
	}
	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'panorama');
	if ($ret->isError() || !$param['itemType']) {
	    return array(GalleryStatus::success(), false);
	}
	list ($ret, $preferred) = GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array(GalleryStatus::success(), false);
	}
	$width = empty($preferred)
	    ? $item->getWidth() : $preferred[$item->getId()]->getWidth();
	$mimeType = empty($preferred)
	    ? $item->getMimeType() : $preferred[$item->getId()]->getMimeType();
	return array(GalleryStatus::success(), $width > $param['width'] &&
		     ($mimeType == 'image/jpeg' || $mimeType == 'image/gif'));
    }

    /**
     * @see ItemEditOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	list ($ret, $preferred) = GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$form['PanoramaOption']['isPanorama'] = empty($preferred)
	    ? GalleryUtilities::isA($item, 'PanoramaPhotoItem')
	    : GalleryUtilities::isA($preferred[$item->getId()], 'PanoramaDerivativeImage');
	return array(GalleryStatus::success(),
		     'modules/panorama/templates/PanoramaOption.tpl',
		     'modules_panorama');
    }

    /**
     * @see ItemEditOption::handleRequestAfterEdit
     */
    function handleRequestAfterEdit($form, &$item, &$preferred) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/PanoramaHelper.class');

	$isPanorama = isset($form['PanoramaOption']['isPanorama']) &&
	    $form['PanoramaOption']['isPanorama'];
	$ret = PanoramaHelper::assignEntityType($item, $isPanorama);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if (isset($preferred) && GalleryUtilities::isA($preferred, 'GalleryDerivativeImage')) {
	    $ret = PanoramaHelper::assignEntityType($preferred, $isPanorama);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	}

	return array(GalleryStatus::success(), array(), array());
    }
}
?>

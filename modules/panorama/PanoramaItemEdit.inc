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
 * This controller will handle switching between Photo and Panorama types
 *
 * @package Panorama
 * @subpackage UserInterface
 *
 */
class PanoramaItemEdit extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	$status = null;
	$error = array();

	if (isset($form['action']['save'])) {
	    require_once(dirname(__FILE__) . '/classes/PanoramaHelper.class');

	    $isPanorama = isset($form['isPanorama']) && $form['isPanorama'];
	    $ret = PanoramaHelper::assignEntityType($item, $isPanorama);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    if (isset($preferred) &&
		    GalleryUtilities::isA($preferred, 'GalleryDerivativeImage')) {
		$ret = PanoramaHelper::assignEntityType($preferred, $isPanorama);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'panorama');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    $status = $module->translate('Changes saved successfully');
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	if ($form['formName'] != 'PanoramaItemEdit') {
	    $form['formName'] = 'PanoramaItemEdit';
	    list ($ret, $preferred) =
		GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $form['isPanorama'] = empty($preferred)
		? GalleryUtilities::isA($item, 'PanoramaPhotoItem')
		: GalleryUtilities::isA($preferred[$item->getId()], 'PanoramaDerivativeImage');
	}
	$template->setVariable('controller', 'panorama:PanoramaItemEdit');
	return array(GalleryStatus::success(), 'modules/panorama/templates/ItemEdit.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	if (strcasecmp(get_class($item), 'GalleryPhotoItem') &&
		strcasecmp(get_class($item), 'PanoramaPhotoItem')) {
	    return false;
	}
	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'panorama');
	if ($ret->isError() || !$param['itemType']) {
	    return false;
	}
	list ($ret, $preferred) =
	    GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return false;
	}
	$width = empty($preferred)
	    ? $item->getWidth() : $preferred[$item->getId()]->getWidth();
	$mimeType = empty($preferred)
	    ? $item->getMimeType() : $preferred[$item->getId()]->getDerivativeMimeType();
	return ($width > $param['width'] &&
	    ($mimeType == 'image/jpeg' || $mimeType == 'image/gif'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'panorama');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $module->translate('Panorama'));
    }
}
?>

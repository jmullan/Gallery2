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
 * @package RandomHighlight
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This controller handles switching between DerivativeImage and RandomHighlight types
 *
 * @package RandomHighlight
 * @subpackage UserInterface
 *
 */
class ItemEditRandomHighlight extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	$status = null;
	$error = array();

	if (isset($form['action']['save'])) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/RandomHighlightHelper.class');

	    list ($ret, $thumbnail) = GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    $thumbnail = array_shift($thumbnail);

	    $isRandomHighlight = isset($form['isRandomHighlight']) && $form['isRandomHighlight'];
	    $ret = RandomHighlightHelper::assignEntityType($thumbnail, $isRandomHighlight);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'randomhighlight');
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
	if ($form['formName'] != 'ItemEditRandomHighlight') {
	    $form['formName'] = 'ItemEditRandomHighlight';
	    $form['isRandomHighlight'] =
		GalleryUtilities::isA($thumbnail, 'RandomHighlightDerivativeImage');
	}
	$template->setVariable('controller', 'randomhighlight:ItemEditRandomHighlight');
	return array(GalleryStatus::success(), 'modules/randomhighlight/templates/ItemEdit.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return GalleryUtilities::isA($item, 'GalleryAlbumItem') &&
		(GalleryUtilities::isExactlyA($thumbnail, 'GalleryDerivativeImage') ||
		 GalleryUtilities::isExactlyA($thumbnail, 'RandomHighlightDerivativeImage'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'randomhighlight');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $module->translate('Random Highlight'));
    }
}
?>

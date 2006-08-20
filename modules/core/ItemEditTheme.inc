<?php
/*
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
 * This controller will handle the changes users make to theme settings for an album.
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 * @version $Revision$ $Date$
 */
class ItemEditTheme extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	list ($ret, $themeId) = GalleryCoreApi::fetchThemeId($item);
	if ($ret) {
	    return array($ret, null, null, null);
	}

	list ($ret, $error, $status) = GalleryCoreApi::handleThemeSettingsRequest(
		$themeId, $item->getId(), $form);
	if ($ret) {
	    return array($ret, null, null, null);
	}

	return array(null, $error, $status, false);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	list ($ret, $themeId) = GalleryCoreApi::fetchThemeId($item);
	if ($ret) {
	    return array($ret, null, null);
	}

	$ret = GalleryCoreApi::loadThemeSettingsForm($themeId, $item->getId(), $template, $form);
	if ($ret) {
	    return array($ret, null, null);
	}

	if ($form['formName'] != 'ItemEditTheme') {
	    $form['formName'] = 'ItemEditTheme';
	}

	$template->setVariable('controller', 'core.ItemEditTheme');
	return array(null, 'modules/core/templates/ItemEditTheme.tpl', 'modules_core');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return (GalleryUtilities::isA($item, 'GalleryAlbumItem'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, $module->translate('Theme'));
    }
}
?>

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
 * @package CustomField
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This controller will handle assigning values to custom fields
 *
 * @package CustomField
 * @subpackage UserInterface
 *
 */
class CustomFieldItemEdit extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	$status = null;
	$error = array();

	if (isset($form['action']['save'])) {
	    require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	    $ret = CustomFieldHelper::saveFieldValues($item->getId(), $form['fields']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'customfield');
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
	require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	if ($form['formName'] != 'CustomFieldItemEdit') {
	    $form['formName'] = 'CustomFieldItemEdit';
	    $set = GalleryUtilities::isA($item, 'GalleryAlbumItem') ? 'album'
		 : (GalleryUtilities::isA($item, 'GalleryPhotoItem') ? 'photo' : 'common');
	    list ($ret, $form['fields'], $param) =
		CustomFieldHelper::fetchFieldValues($item->getId(), null, $set);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach (array('common' => 1, $set => 1) as $s => $tmp) {
		foreach ($param[$s] as $item) {
		    if (!empty($item['choices'])) {
			$form['choices'][$item['field']] = $item['choices'];
		    }
		}
	    }
	}
	$template->setVariable('controller', 'customfield:CustomFieldItemEdit');
	return array(GalleryStatus::success(), 'modules/customfield/templates/ItemEdit.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	list ($ret, $param) = CustomFieldHelper::loadParameters();
	if ($ret->isError()) {
	    return false;
	}
	if (!empty($param['common']) ||
	    (GalleryUtilities::isA($item, 'GalleryAlbumItem') && !empty($param['album'])) ||
	    (GalleryUtilities::isA($item, 'GalleryPhotoItem') && !empty($param['photo']))) {
	    return true;
	}
	return false;
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'customfield');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $module->translate('Custom Fields'));
    }
}
?>

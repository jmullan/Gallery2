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
 * @package CustomField
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Custom fields
 *
 * This module provides custom fields for Gallery items.
 *
 * @package CustomField
 */
class CustomFieldModule extends GalleryModule {

    function CustomFieldModule() {
	global $gallery;

	$this->setId('customfield');
	$this->setName($gallery->i18n('Custom Fields'));
	$this->setDescription($gallery->i18n('Create custom data fields for Gallery items'));
	$this->setVersion('0.8.6');
	$this->setGroup('data', $this->translate('Extra Data'));
	$this->setCallbacks('registerEventListeners|' .
			    'getSiteAdminViews|getItemSummaries|loadItemDetails');
	$this->setRequiredCoreApi(array(3, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	GalleryCoreApi::registerEventListener('GalleryEntity::delete', new CustomFieldHelper());
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Custom Fields'),
				 'view' => 'customfield:CustomFieldSiteAdmin')));
    }

    /**
     * @see GalleryModule::getItemSummaries()
     */
    function getItemSummaries($items) {
	require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	$summaries = array();
	foreach ($items as $item) {
	    list ($ret, $fields) = CustomFieldHelper::fetchFieldValues($item, 'summary');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $list = array();
	    foreach ($fields as $field => $value) {
		$list[] = "$field: $value";
	    }
	    $summaries[$item->getId()] = implode("<br/>\n", $list);
	}
	return array(GalleryStatus::success(), $summaries);
    }

    /**
     * @see GalleryModule::loadItemDetails()
     */
    function loadItemDetails(&$template, $item) {
	require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');
	list ($ret, $fields) = CustomFieldHelper::fetchFieldValues($item, 'detail');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$CustomFieldItemDetails = array('fields' => $fields);
	$template->setVariable('CustomFieldItemDetails', $CustomFieldItemDetails);
	return array(GalleryStatus::success(),
		     'modules/customfield/templates/ItemDetails.tpl');
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	/* Register our item edit plugin */
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemEditPlugin', 'CustomFieldItemEdit', 'CustomFieldItemEdit',
            'modules/customfield/CustomFieldItemEdit.inc', 'customfield', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Register interface implementation */
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'CustomFieldInterface_1_0', 'CustomFieldHelper', 'CustomField',
            'modules/customfield/classes/CustomFieldHelper.class', 'customfield', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Register search implementation */
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GallerySearchInterface_1_0', 'CustomFieldSearch', 'CustomField',
            'modules/customfield/classes/CustomFieldSearch.class', 'customfield', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }
    
}
?>

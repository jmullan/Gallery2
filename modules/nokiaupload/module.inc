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
 * @package NokiaUpload
 * @author Jerome Rannikko <jeromer@hotpop.com>
 */

/**
 * This module implements the Nokia Image Upload Server API v1.1.
 * With this module users can upload pictures straight from their
 * mobile phone (e.g. Nokia 3650 and 6600) to their Gallery account.
 * See README file in this directory for more information and instructions.
 *
 * @package NokiaUpload
 */
class NokiaUploadModule extends GalleryModule {

    function NokiaUploadModule() {
	global $gallery;

	$this->setId('nokiaupload');
	$this->setName('Nokia Image Upload');
	$this->setDescription($gallery->i18n('Implementation of Nokia Image Upload Server API v1.1'));
	$this->setVersion('0.8.2');
	$this->setGroup('import', $this->translate('Import'));
	$this->setCallbacks('');
	$this->setRequiredCoreApi(array(1, 0));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::needsConfiguration
     */
    function needsConfiguration() {
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'nokiaupload');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	foreach (array('id.mobileGroup', 'id.uploadAlbum') as $key) {
	    if (empty($params[$key])) {
		return array(GalleryStatus::success(), true);
	    }
	}
	return array(GalleryStatus::success(), false);
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	return 'nokiaupload:Configure';
    }
}
?>

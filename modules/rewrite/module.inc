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
 * @package Rewrite
 * @version $Revision$ $Date$
 * @author Douglas Cau <douglas@cau.se>
 */

/**
 * URL Rewrite Module
 *
 * This module provides mod_rewrite support
 *
 * @package Rewrite
 */
class RewriteModule extends GalleryModule {

    function RewriteModule() {
	$this->setId('rewrite');
	$this->setName('URL Rewrite');
	$this->setDescription($this->i18n('Enables short URLs using mod_rewrite.'));
	$this->setVersion('0.9.0');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('getSiteAdminViews');
	$this->setRequiredCoreApi(array(4, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/RewriteModuleExtras.inc');
	$ret = RewriteModuleExtras::upgrade($this, $currentVersion);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

    	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
		'GalleryUrlGenerator', 'RewriteUrlGenerator', 'RewriteUrlGenerator',
        	'modules/rewrite/classes/RewriteUrlGenerator.class', 'rewrite', null, 2);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::needsConfiguration
     */
    function needsConfiguration() {
	GalleryCoreApi::relativeRequireOnce('modules/rewrite/classes/RewriteHelper.class');

	foreach (array('galleryLocation') as $key) {
	    list ($ret, $value) = $this->getParameter($key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (empty($value)) {
		return array(GalleryStatus::success(), true);
	    }
	}

	list ($ret, $status) = RewriteHelper::checkFile();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $status != REWRITE_STATUS_OK);
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	return 'rewrite:SetupRewrite';
    }
}
?>

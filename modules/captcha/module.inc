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
 * @package Captcha
 * @author Stefan Ioachim <stefanioachim@gmail.com>
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * The implementation of the Captcha module
 *
 * @package Captcha
 */

class CaptchaModule extends GalleryModule {

    function CaptchaModule() {
	global $gallery;
	$this->setId('captcha');
	$this->setName('Captcha');
	$this->setDescription($gallery->i18n('Captcha'));
	$this->setVersion('0.9.0');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('getSiteAdminViews');
	$this->setRequiredCoreApi(array(5, 1));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'UserLoginPlugin', 'CaptchaLoginPlugin', 'CaptchaLoginPlugin',
	    'modules/captcha/CaptchaLoginPlugin.inc', 'captcha', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    } 

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We need to perform a test before activating */  	
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::needsConfiguration()
     */
    function needsConfiguration() {
	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryPhpVm.class');
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/CaptchaHelper.class');
	$gdReport = CaptchaHelper::testRequiredGdFunctions(new GalleryPhpVm());
	    
	if (count($gdReport['fail']) > 0) {
	    return array(GalleryStatus::success(), true);
	} else {
	    return array(GalleryStatus::success(), false);
	}
    }
	 
    /**
     * @see GalleryModule::activate()
     */
    function activate() {
	/* Set some reasonable defaults */
	$ret = $this->setParameter('failedAttemptThreshold', 3);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), false);
	}

	list ($ret, $redirect) = parent::activate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Captcha'),
				 'view' => 'captcha:CaptchaSiteAdmin')));
    }
    
    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	return 'captcha:CaptchaConfigAdmin';
    }
}
?>

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
 * @package WebCam
 * @author Alan Harder <alan.harder@sun.com>
 */
class WebCamModule extends GalleryModule {

    function WebCamModule() {
	global $gallery;
	$this->setId('webcam');
	$this->setName('WebCam');
	$this->setDescription($gallery->i18n('Support periodically updated images like a webcam'));
	$this->setVersion('0.8.1');
	$this->setGroup('import', $gallery->i18n('Import'));
	$this->setCallbacks('performFactoryRegistrations|getSiteAdminViews');
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryLiveImage', 'GalleryLiveImage',
						      $classDir . 'GalleryLiveImage.class');

	GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
						      'ItemAddLiveImage', 'ItemAddLiveImage',
						      dirname(__FILE__) . '/ItemAddLiveImage.inc');
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    $ret = $this->setModuleParameter('duration', 10 * 60 * 60); /* 10 minutes */
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
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
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::deactivate()
     */
    function deactivate() {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryLiveImageHelper.class');
	list ($ret, $count) = GalleryLiveImageHelper::fetchItemCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($count > 0) {
	    // Can't deactivate if liveimage items exist..
	    return array(GalleryStatus::success(),
			 array('view' => 'core:SiteAdmin',
			       'subView' => 'webcam:WebCamSiteAdmin'));
	}

	list ($ret, $redirect) = parent::deactivate();
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
		     array(array('name' => $this->translate('WebCam'),
				 'view' => 'webcam:WebCamSiteAdmin')));
    }
}
?>

<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
 * Metamorphose applet Copyright (C) 2000 Rüdiger Appel
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
 * @author Alan Harder <alan.harder@sun.com>
 * Java applet: @author Rüdiger Appel
 *              http://www.3quarks.com/Applets/Metamorphose/
 */

/**
 * The implementation of the Panorama module
 *
 * @package Panorama
 */
class PanoramaModule extends GalleryModule {

    function PanoramaModule() {
	global $gallery;
	$this->setId('panorama');
	$this->setName('Panorama');
	$this->setDescription($gallery->i18n('View wide jpeg/gif images in a java applet viewer'));
	$this->setVersion('0.8.2');
	$this->setGroup('display', $gallery->i18n('Display'));
	$this->setCallbacks('performFactoryRegistrations|getSiteAdminViews|' .
			    'getItemLinks');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'PanoramaDerivativeImage',
						      'PanoramaDerivativeImage',
						      dirname(__FILE__) . '/classes/PanoramaDerivativeImage.class');
	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'PanoramaPhotoItem',
						      'PanoramaPhotoItem',
						      dirname(__FILE__) . '/classes/PanoramaPhotoItem.class');
	GalleryCoreApi::registerFactoryImplementation('GalleryDerivative',
						      'PanoramaDerivativeImage',
						      'PanoramaDerivativeImage',
						      dirname(__FILE__) . '/classes/PanoramaDerivativeImage.class',
						      array('PanoramaPhotoItem'));
	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
						      'PanoramaItemEdit',
						      'PanoramaItemEdit',
						      dirname(__FILE__) . '/PanoramaItemEdit.inc');
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    /* Initial install */
	    foreach (array('itemType' => 1,
			   'itemLink' => 1,
			   'width' => 800) as $key => $value) {
		$ret = $this->setModuleParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
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
	require_once(dirname(__FILE__) . '/classes/PanoramaHelper.class');
	list ($ret, $count) = PanoramaHelper::fetchItemCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($count > 0) {
	    // Can't deactivate if panorama entities exist..
	    return array(GalleryStatus::success(),
			 array('view' => 'core:SiteAdmin',
			       'subView' => 'panorama:PanoramaSiteAdmin'));
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
		     array(array('name' => $this->translate('Panorama'),
				 'view' => 'panorama:PanoramaSiteAdmin')));
    }

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	$links = array();
	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'panorama');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($param['itemLink']) {
	    require_once(dirname(__FILE__) . '/classes/PanoramaHelper.class');
	    list ($ret, $images) = PanoramaHelper::fetchViewableImages($items);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($items as $item) {
		if (!isset($images[$item->getId()])) {
		    continue;
		}
		$image = $images[$item->getId()];
		$mimeType = $item->getMimeType();
		$width = $image->getWidth();
		// Applet supports jpeg and gif images
		if (GalleryUtilities::isA($item, 'GalleryPhotoItem') &&
		        !GalleryUtilities::isA($item, 'PanoramaPhotoItem') &&
		        preg_match(':^image/(gif|p?jpeg)$:', $mimeType) &&
			$width > $param['width'] &&
			($image->getHeight() / $width < 0.6)) {
		    $links[$item->getId()][] =
			array('text' => $this->translate('view panorama'),
			      'params' => array('view' => 'panorama:Panorama',
						'itemId' => $item->getId()));
		}
	    }
	}
	return array(GalleryStatus::success(), $links);
    }
}
?>

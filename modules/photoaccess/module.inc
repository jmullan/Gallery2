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
 * @package PhotoAccess
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * The implementation of the core-module
 *
 * @package PhotoAccess
 */
class PhotoAccessModule extends GalleryModule {

    function PhotoAccessModule() {
	global $gallery;
	
	$this->setId('photoaccess');
	$this->setName('PhotoAccess');
	$this->setDescription($gallery->i18n('PhotoAccess Photo Printing Module'));
	$this->setVersion('0.8');
	$this->setGroup('commerce', $gallery->i18n('Commerce'));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Register our cart plugin */
	GalleryCoreApi::registerFactoryImplementation('CartPluginInterface_1_0',
						      'PhotoAccessCartPlugin',
						      'photoaccess',
						      dirname(__FILE__) . '/classes/PhotoAccessCartPlugin.class');
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
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	global $gallery;

	$urlGenerator = $gallery->getUrlGenerator();
	$links = array();
	foreach ($items as $item) {
	    if (GalleryUtilities::isA($item, 'GalleryPhotoItem')) {
		$params['controller'] = 'photoaccess:PrintPhoto';
		$params['itemId'] = $item->getId();
		$params['returnUrl'] = urlencode($urlGenerator->getCurrentUrl());
		$links[$item->getId()][] =
		    array('text' => $this->translate('print on photoaccess.com'),
			  'params' => $params);
	    }
	}

	return array(GalleryStatus::success(), $links);
    }
}
?>

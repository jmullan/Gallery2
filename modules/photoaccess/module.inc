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
 * @package PhotoAccess
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Photo printing at photoaccess.com
 *
 * @package PhotoAccess
 */
class PhotoAccessModule extends GalleryModule {

    function PhotoAccessModule() {
	global $gallery;

	$this->setId('photoaccess');
	$this->setName($gallery->i18n('PhotoAccess'));
	$this->setDescription($gallery->i18n('PhotoAccess Photo Printing Module'));
	$this->setVersion('0.9.1');
	$this->setGroup('commerce', $this->translate('Commerce'));
	$this->setCallbacks('getItemLinks');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'CartPluginInterface_1_0', 'PhotoAccessCartPlugin', 'photoaccess',
	    'modules/photoaccess/classes/PhotoAccessCartPlugin.class', 'photoaccess', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
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

	$urlGenerator =& $gallery->getUrlGenerator();
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

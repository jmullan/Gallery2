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
 * @package Debug
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * Debug Module
 *
 * This module provides some debug information on Gallery
 *
 * @package Debug
 */
class DebugModule extends GalleryModule {

    function DebugModule() {
	global $gallery;

	$this->setId('debug');
	$this->setName('Debugging');
	$this->setDescription($gallery->i18n('Debugging and Developer Tools'));
	$this->setVersion('0.8.3');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('performFactoryRegistrations|getItemLinks');
	$this->setRequiredCoreApi(array(1, 0));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
        /* We don't require any special configuration */
        return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';
	GalleryCoreApi::registerFactoryImplementation('GalleryStatusFormatter',
						      'DebugStatusFormatter',
						      'DebugStatusFormatter',
						      $classDir . 'DebugStatusFormatter.class',
						      array('text/html'));
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items) {
	global $gallery;

	$links = array();
	foreach ($items as $item) {
	    /* Permissions for this item */
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['core.all'])) {
		$links[$item->getId()][] =
		    array('text' => $this->translate('show debug tree'),
			  'params' => array('view' => 'debug:ShowTree',
					    'itemId' => $item->getId()));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }
}
?>

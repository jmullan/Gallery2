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
 * @package Search
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Search Module
 *
 * This module provides support for searching the Gallery
 *
 * @package Search
 */
class SearchModule extends GalleryModule {

    function SearchModule() {
	global $gallery;

	$this->setId('search');
	$this->setName('Search');
	$this->setDescription($gallery->i18n('Search your Gallery'));
	$this->setVersion('0.8.6');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('loadSystemContent');
	$this->setRequiredCoreApi(array(4, 0));
	$this->setRequiredModuleApi(array(0, 9));
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
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	global $gallery;

	$view = GalleryUtilities::getRequestVariables('view');
	if ($view == 'search:SearchScan' || $view == 'search:SearchShowAll') {
	    $content = null;
	} else {
	    $SearchSystemContent['subView'] = 'search:SearchScan';
	    $template->setVariable('SearchSystemContent', $SearchSystemContent);
	    $content = 'modules/search/templates/SearchSystemContent.tpl';
	}

	return array(GalleryStatus::success(), array('searchBox' => $content));
    }
}
?>

<?php
/*
 * $RCSfile
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
class SearchModule extends GalleryTemplateModule {

    function SearchModule() {
	$this->setName('search');
	$this->setDescription('Search');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;

	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$classDir = dirname(__FILE__) . '/classes/';
	require_once($classDir . 'GallerySearchInterface_1_0.class');

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($version != $this->getVersion()) {
	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* XXX: Register permissions here */
	}
	
	return GalleryStatus::success();
    }
	
    /**
     * @see GalleryModule::getSystemContent
     */
    function getSystemContent($returnUrlParams) {
	global $gallery;

	foreach ($returnUrlParams as $param => $value) {
	    $return[$param] = $value;
	}
	
	$template = $this->getTemplate();
	$template->setVariable('view', 'search:SearchScan');
	$template->setVariable('return', $return);
	$html = $template->render('SystemContent.tpl');
	return array(GalleryStatus::success(), array('content' => $html));
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Search'),
				 'view' => 'search:AdminSearch')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	global $gallery;

	return array(GalleryStatus::success(), 'search:AdminSearch');
    }
}
?>

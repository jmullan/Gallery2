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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This ItemAddOption allows the user to choose to create thumbnails
 * when the image is uploaded.
 *
 * @package Core
 * @subpackage UserInterface
 */
class CreateThumbnailOption extends ItemAddOption {

    /**
     * @see ItemAddOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	return array(GalleryStatus::success(),
		     'modules/core/templates/CreateThumbnailOption.tpl',
		     'modules_core');
    }
    
    /**
     * @see ItemAddOption::isAppropriate
     */
    function isAppropriate() {
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see ItemAddOption::handleRequestAfterAdd
     */
    function handleRequestAfterAdd($form, &$item) {
	$error = array();
	$warning = array();

	list ($ret, $thumbTable) = GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if (!empty($thumbTable[$item->getId()])) {
	    $thumbnail = $thumbTable[$item->getId()];
	    list ($ret, $isCurrent) = $thumbnail->isCacheCurrent();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    
	    if (!$isCurrent) {
		$ret = $thumbnail->rebuildCache();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
	    }
	}

	return array(GalleryStatus::success(), $error, $warning);
    }
}
?>
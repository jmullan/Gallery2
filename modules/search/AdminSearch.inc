<?php
/*
 * $RCSfile$
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
 * @package Search
 * @subpackage UserInterface
 */
class AdminSearchController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* ... take some action here ... */

	/* Figure out where to redirect upon success */
	$results['return'] = 1;
	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'search:AdminSearch';
	$results['status'] = array();
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Search
 * @subpackage UserInterface
 */
class AdminSearchView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$form['formName'] = 'AdminSearch';
	$template->setVariable('controller', 'comment:AdminSearch');
	return array(GalleryStatus::success(),
		     '',
		     'modules/search/templates/AdminSearch.tpl');
    }
}
?>

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
 * @package Migrate
 * @subpackage UserInterface
 * @author Jesse Mullan <jmullan@visi.com>
 */

/**
 * @package Migrate
 * @subpackage UserInterface
 */
class ImportResultsView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	if ($form['formName'] != 'ImportResults') {
	    $form['formName'] = 'ImportResults';
	}

	$status = $template->getVariable('status');
	$counts = array();
	foreach (array('userImportFailure', 'userImportSuccess',
		       'albumImportFailure', 'albumImportSuccess')
		 as $key) {

	    if (isset($status[$key])) {
		$counts[$key] = sizeof($status[$key]);
	    } else {
		$counts[$key] = 0;
	    }
	}

	$ImportResults = array();
	$ImportResults['counts'] = $counts;
	$ImportResults['status'] = $status;

	$urlGenerator =& $gallery->getUrlGenerator();
	$urlComponents = parse_url($urlGenerator->getCurrentUrl());
	$ImportResults['uriBase'] = $urlComponents['path'];

	$template->setVariable('ImportResults', $ImportResults);
	$template->setVariable('controller', 'migrate:ImportResults');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/migrate/templates/ImportResults.tpl'));
    }
}
?>

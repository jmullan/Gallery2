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
 * @package Migrate
 * @subpackage UserInterface
 */

class SelectGalleryController extends GalleryController {
    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
        global $gallery;

        // Verify that active user is an admin
        $ret = GalleryUserHelper::assertSiteAdministrator();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

	$error = array();
	$status = array();

	if (isset($form['action']['select'])) {
	    if (empty($form['albumsPath'])) {
		$error[] = 'form.error.albumsPath.missing';
	    } else {
		$platform = $gallery->getPlatform();
		$slash = $platform->getDirectorySeparator();
		$tmp = trim($form['albumsPath']);
		if ($tmp[strlen($tmp)-1] != $slash) {
		    $tmp .= $slash;
		}
		$form['albumsPath'] = trim($tmp);
	    
		if (!Gallery1DataParser::isValidAlbumsPath($form['albumsPath'])) {
		    $error[] = 'form.error.albumsPath.invalid';
		}
	    }
	}

	if (empty($error)) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'migrate:ChooseObjects';
	    $redirect['albumsPath'] = $form['albumsPath'];
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'migrate:SelectGallery';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}	    

class SelectGalleryView extends GalleryView {
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;

	if ($form['formName'] != 'SelectGallery') {
	    $form['formName'] = 'SelectGallery';
	    $form['albumsPath'] = '';
	}

        $template->setVariable('controller', 'migrate:SelectGallery');
        return array(GalleryStatus::success(), '', 'modules/migrate/templates/SelectGallery.tpl');
    }
}
?>
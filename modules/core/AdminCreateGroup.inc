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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the creation of a group
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminCreateGroupController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();

	if (isset($form['action']['cancel'])) {

	    /* Go back to the AdminGroups view */
	    $results['view'] = 'core:SiteAdmin';
	    GalleryUtilities::putRequestVariable('subView', 'core:AdminGroups');
	    
	} else if (isset($form['action']['create'])) {
	    /*
	     * If all the right fields are in place then go ahead and
	     * create the group.
	     */
	    if (!empty($form['groupName'])) {
		list ($ret, $group) = GalleryFactory::newInstance('GalleryEntity', 'GalleryGroup');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if (!isset($group)) {
		    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				 null);
		}

		$ret = $group->create($form['groupName']);
		if ($ret->isError()) {
		    if (!($ret->getErrorCode() & ERROR_COLLISION)) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    // Set our error status and fall back to the view.
		    GalleryUtilities::putRequestVariable('form.error.groupName.exists', 1);
		} else {
		    $ret = $group->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Request a redirect to the confirmation screen */
		    $redirectParams['view'] = 'core:SiteAdmin';
		    $redirectParams['subView'] = 'core:AdminGroups';
		    $redirectParams['form.status.createdGroup'] = $group->getGroupName();
		}
	    } else {
		// Set our error status and fall back to the view.
		GalleryUtilities::putRequestVariable('form.error.groupName.missing', 1);
	    }
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateGroup');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for data to create a new group
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCreateGroupView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    

	if ($form['formName'] != 'AdminCreateGroup') {
	    // Set the form defaults
	    $form['groupName'] = '';
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('controller', 'core:AdminCreateGroup');
	$html = $template->render('AdminCreateGroup.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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

class AdminCreateGroupController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$redirectParams = array();
	$form = GalleryUtilities::getFormVariables('form.');

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

		$ret = $group->create($form['groupName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_COLLISION) {
			/*
			 * Fall through -- the view will let the group know about
			 * the duplication.
			 */
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    $ret = $group->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Request a redirect to the confirmation screen */
		    $redirectParams['view'] = 'core:SiteAdmin';
		    $redirectParams['subView'] = 'core:AdminCreateGroupConfirmation';
		    $redirectParams['groupName'] = $form['groupName'];
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:AdminCreateGroup');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class AdminCreateGroupView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	$formName = GalleryUtilities::getRequestVariables('formName');
	$form = GalleryUtilities::getFormVariables('form.');

	if ($formName == 'AdminCreateGroup') {
	    if (empty($form['groupName'])) {
		$form['error']['groupName']['missing'] = 1;
	    }
	    
	    if (!empty($form['groupName'])) {
		list ($ret, $group) = GalleryGroupHelper::fetchGroupByGroupname($form['groupName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			/* We're good -- no use by that name */
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    /* A group exists by that name */
		    $form['error']['groupName']['exists'] = 1;
		}
	    }
	} else {
	    /*
	     * Otherwise we just arrived at this page the first time so set
	     * defaults
	     */
	    $form['groupName'] = '';
	}

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('controller', 'core:AdminCreateGroup');
	$html = $this->_renderTemplate('core', 'AdminCreateGroup.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

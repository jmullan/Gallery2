<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class AdminCommentsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	/* Make sure we have adequate permissions */
	list ($ret, $inGroup) =
	    GalleryUserGroupMap::isUserInAdminGroup($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!$inGroup) {
	    return array(GalleryStatus::error(ERROR_PERMISSION_DENIED, __FILE__, __LINE__),
			 null);
	}

	list($ret, $module) = $gallery->loadModule('comment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $needsConfiguration) = $module->needsConfiguration();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * If we need configuration, then let the GalleryStorage configure
	 * itself, then update our version in the map accordingly.
	 */
	if ($needsConfiguration) {
	    list ($ret, $storage) = $gallery->getStorage();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = $storage->configureStore($module->getName());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /*
	     * XXX: at some later date we need to make sure that all the
	     * various module parameters are set correctly for this module
	     * here.
	     */

	    /* Update our version */
	    $ret = $gallery->setModuleParameter($module->getName(),
						'version', $module->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out where to redirect upon success */
	$stateVariables['view'] = 'core:SiteAdmin';
	$stateVariables['subView'] = 'comment:AdminComments';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($stateVariables);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminCommentsView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	return array(GalleryStatus::success(), false);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list($ret, $module) = $gallery->loadModule('comment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $needsConfiguration) = $module->needsConfiguration();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('needsConfiguration', $needsConfiguration);
	$smarty->assign('controller', 'comment:AdminComments');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminComments.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

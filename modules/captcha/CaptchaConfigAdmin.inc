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
 * @package Captcha
 * @author Stefan Ioachim <stefanioachim@gmail.com>
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * @package Captcha
 * @subpackage UserInterface
 */

class CaptchaConfigAdminController extends GalleryController {
    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results['status'] = array();
	$results['error'] = array();
	$results['redirect'] = array('view' => 'core:SiteAdmin', 'subView' => 'core:AdminModules');
	return array(GalleryStatus::success(), $results);
    }
}
	

/**
 * Show the user which required GD functions are missing.  They can't install the module, and
 * there's nothing we can do about it.
 */
class CaptchaConfigAdminView extends GalleryView {
	
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	if ($form['formName'] != 'CaptchaConfigAdmin') {
	    $form['formName'] = 'CaptchaConfigAdmin';
	}

	GalleryCoreApi::relativeRequireOnce('modules/core/classes/GalleryPhpVm.class');
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/CaptchaHelper.class');
	$gdReport = CaptchaHelper::testRequiredGdFunctions(new GalleryPhpVm());	

	$CaptchaConfigAdmin = array();
	$CaptchaConfigAdmin['gdReport'] = $gdReport; 
	$template->setVariable('CaptchaConfigAdmin', $CaptchaConfigAdmin);
	$template->setVariable('controller', 'captcha:CaptchaConfigAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/captcha/templates/CaptchaConfigAdmin.tpl'));
    }
}
?>
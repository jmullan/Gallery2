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
 * @package Watermark
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class UserWatermarkEditController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$status = array();
	$error = array();
	$itemId = GalleryUtilities::getRequestVariables('itemId');

	if (empty($itemId)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}

	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['save'])) {
	    if (empty($form['name'])) {
		$error[] = 'form[error][name][missing]';
	    }

	    if (empty($form['whichDerivative'])) {
		$error[] = 'form[error][whichDerivative][missing]';
	    }

	    // Clip our percentages
	    if (empty($error)) {
		$form['xPercentage'] = empty($form['xPercentage']) ? 0 : $form['xPercentage'];
		$form['yPercentage'] = empty($form['yPercentage']) ? 0 : $form['yPercentage'];
		$form['xPercentage'] = max(0, $form['xPercentage']);
		$form['yPercentage'] = max(0, $form['yPercentage']);
		$form['xPercentage'] = min(100, $form['xPercentage']);
		$form['yPercentage'] = min(100, $form['yPercentage']);

		list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$item->setApplyToPreferred(isset($form['whichDerivative']['preferred']));
		$item->setApplyToResizes(isset($form['whichDerivative']['resizes']));
		$item->setApplyToThumbnail(isset($form['whichDerivative']['thumbnail']));
		$item->setName($form['name']);
		$item->setXPercentage(sprintf('%2.3f', $form['xPercentage']));
		$item->setYPercentage(sprintf('%2.3f', $form['yPercentage']));

		$ret = $item->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = GalleryCoreApi::releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$status['saved'] = 1;
		$results['redirect']['view'] = 'core:UserAdmin';
		$results['redirect']['subView'] = 'watermark:UserWatermarks';
	    } else {
		$results['delegate']['view'] = 'core:UserAdmin';
		$results['delegate']['subView'] = 'watermark:UserWatermarkEdit';
	    }
	} else if (isset($form['action']['cancel'])) {
	    $results['redirect']['view'] = 'core:UserAdmin';
	    $results['redirect']['subView'] = 'watermark:UserWatermarks';
	}

	$results['status'] = $status;
	$results['error'] = $error;
	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Watermark
 * @subpackage UserInterface
 */
class UserWatermarkEditView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	$ret = GalleryCoreApi::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $watermark) = GalleryCoreApi::loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	if ($form['formName'] != 'UserWatermarkEdit') {
	    $form['formName'] = 'UserWatermarkEdit';

	    $form['name'] = $watermark->getName();
	    $form['xPercentage'] = $watermark->getXPercentage();
	    $form['yPercentage'] = $watermark->getYPercentage();
	    $form['whichDerivative']['preferred'] = $watermark->getApplyToPreferred() ? 1 : null;
	    $form['whichDerivative']['thumbnail'] = $watermark->getApplyToThumbnail() ? 1 : null;
	    $form['whichDerivative']['resizes'] = $watermark->getApplyToResizes() ? 1 : null;
	}

	/* Set the form's encoding type since we're uploading binary files */
	if ($template->hasVariable('UserAdmin')) {
	    $UserAdmin =& $template->getVariableByReference('UserAdmin');
	    $UserAdmin['enctype'] = 'multipart/form-data';
	} else {
	    $UserAdmin['enctype'] = 'multipart/form-data';
	    $template->setVariable('UserAdmin', $UserAdmin);
	}

	$UserWatermarkEdit = array();
	$UserWatermarkEdit['watermark'] = $watermark->getMemberData();
	$template->setVariable('UserWatermarkEdit', $UserWatermarkEdit);
	$template->setVariable('controller', 'watermark:UserWatermarkEdit');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/watermark/templates/UserWatermarkEdit.tpl'));
    }
}
?>

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
 * @package NetPBM
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Required class
 */
require_once(dirname(__FILE__) . '/classes/NetPbmToolkitHelper.class');

/**
 * @package NetPBM
 * @subpackage UserInterface
 */
class AdminNetPbmController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$return = GalleryUtilities::getFormVariables('return.');

	if (isset($form['action']['save'])) {

	    /* Set the path.  Guarantee that it's got a trailing slash. */
	    $platform = $gallery->getPlatform();
	    $slash = $platform->getDirectorySeparator();
	    $form['path'] = trim($form['path']);
	    if (!empty($form['path'])) {
		if ($form['path']{strlen($form['path'])-1} != $slash) {
		    $form['path'] .= $slash;
		}
	    }
	    

	    $saveSuccess = false;
	    $success = true;
	    list ($ret, $testResults) =
		NetPbmToolkitHelper::testBinaries($form['path'], array('pnmtojpeg' => $form['pnmtojpeg']));
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_BAD_PATH) {
		    GalleryUtilities::putRequestVariable('form.error.path.badPath', 1);
		    $success = false;
		} else {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    } else {
	        $success = false;
		foreach ($testResults as $testResult) {
		    /* At least one test should work, else this path is not a valid one */
		    if ($testResult['success']) {
		        $success = true;
		    }
		    
		    if (!$success) {
			GalleryUtilities::putRequestVariable('form.error.path.testError', 1);
		    }
		}
	    }
	    
	    if ($success) {
		$saveSuccess = true;
		$ret = $gallery->setModuleParameter('netpbm', 'path', $form['path']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/*
		 * Set the image quality
		 */
		$ret = $gallery->setModuleParameter('netpbm', 'jpegQuality', $form['jpegQuality']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/*
		 * Set the pnmtojpeg binary name
		 */
		$ret = $gallery->setModuleParameter('netpbm', 'pnmtojpeg', $form['pnmtojpeg']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Figure out where to redirect upon success/cancel */
	if ((isset($form['action']['save']) && $saveSuccess)
	    || isset($form['action']['cancel'])) {
	    if (!empty($return)) {
		$redirectParams = $return;
	    } else {
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'netpbm:AdminNetPbm';
	    }
	}

	if (!empty($redirectParams)) {
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'netpbm:AdminNetPbm');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package NetPBM
 * @subpackage UserInterface
 */
class AdminNetPbmView extends GalleryView {

    /**
     * @see GalleryView::renderBody()
     */
    function renderBody($form) {
	global $gallery;

	$return = GalleryUtilities::getFormVariables('return.');

	/* Load our default values if we didn't just come from this form. */
	if ($form['formName'] != 'AdminNetPbm') {
	    foreach (array('path', 'jpegQuality', 'pnmtojpeg') as $key) {
		list ($ret, $form[$key]) =
		    $gallery->getModuleParameter('netpbm', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Guarantee that the path has a trailing slash. */
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();
	$form['path'] = trim($form['path']);
	if (!empty($form['path'])) {
	    if ($form['path']{strlen($form['path'])-1} != $slash) {
		$form['path'] .= $slash;
	    }
	}
	
	/* Set up our jpeg quality selection list */
	for ($i = 95; $i >= 50; $i -= 5) {
	    $jpegQualityList[] = $i;
	}

	/* Set up our pnmtojpeg selection list */
	$pnmToJpegList = array('pnmtojpeg', 'ppmtojpeg');

	$platform = $gallery->getPlatform();
	$tests = array();
	$mimeTypes = array();

	if (isset($form['action']['test'])) {
	    if (empty($form['path'])) {
		$form['error']['path']['missing'] = 1;
	    } else {
		list ($ret, $tests, $mimeTypes) =
		    NetPbmToolkitHelper::testBinaries($form['path'],
						      array('pnmtojpeg' => $form['pnmtojpeg']));
	    }
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$template->setVariable('tests', $tests);
	$template->setVariable('mimeTypes', $mimeTypes);
	$template->setVariable('pnmToJpegList', $pnmToJpegList);
	$template->setVariable('jpegQualityList', $jpegQualityList);
	$template->setVariable('controller', 'netpbm:AdminNetPbm');
	list($ret, $html) = $template->render('AdminNetPbm.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), $html);
	}

	return array(GalleryStatus::success(), $html);
    }
}
?>

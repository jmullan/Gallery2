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
/**
 * @version $Revision$ $Date$
 * @package ImageMagick
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Required class
 */
require_once(dirname(__FILE__) . '/classes/ImageMagickToolkitHelper.class');

/**
 * @package ImageMagick
 * @subpackage UserInterface
 */
class AdminImageMagickController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');

	/* Set the path.  Guarantee that it's got a trailing slash. */
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();
	$form['path'] = trim($form['path']);
	if (!empty($form['path'])) {
	    if ($form['path']{strlen($form['path'])-1} != $slash) {
		$form['path'] .= $slash;
	    }
	}

	if (isset($form['action']['save'])) {
	    $saveSuccess = false;
	    $success = true;
	    list ($ret, $testResults) = ImageMagickToolkitHelper::testBinaries($form['path']);
	    if ($ret->isError()) {
		if ($ret->getErrorCode() & ERROR_BAD_PATH) {
		    GalleryUtilities::putRequestVariable('form.error.path.badPath', 1);
		    $success = false;
		} else {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    } else {
		foreach ($testResults as $testResult) {
		    /* All tests should work, else this path is not a valid one */
		    if (! $testResult['success']) {
			$success = false;
			GalleryUtilities::putRequestVariable('form.error.path.testError', 1);
			break;
		    }
		}
	    }
	    if ($success) {
		$saveSuccess = true;
		$ret = $gallery->setModuleParameter('imagemagick', 'path', $form['path']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $ret = $gallery->setModuleParameter('imagemagick', 'jpegQuality', $form['jpegQuality']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out where to redirect upon success */
	if (( isset($form['action']['save']) && $saveSuccess )
	    || isset($form['action']['cancel']) ) {
	    if (!empty($return)) {
		$redirectParams = $return;
	    } else {
		$redirectParams['view'] = 'core:SiteAdmin';
		$redirectParams['subView'] = 'imagemagick:AdminImageMagick';
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:SiteAdmin';
		GalleryUtilities::putRequestVariable('subView', 'imagemagick:AdminImageMagick');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package ImageMagick
 * @subpackage UserInterface
 */
class AdminImageMagickView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');
	$formName = GalleryUtilities::getRequestVariables('formName');
	
	/* Load our default values if we didn't just come from this form. */
	if ($formName != 'AdminImageMagick') {
	    foreach (array('path', 'jpegQuality') as $key) {
		list ($ret, $form[$key]) =
		    $gallery->getModuleParameter('imagemagick', $key);
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

	$platform = $gallery->getPlatform();
	$tests = array();
	$mimeTypes = array();
	if (isset($form['action']['test'])) {
	    if (!empty($form['path'])) {
		list($ret, $testResults) =
		    ImageMagickToolkitHelper::testBinaries($form['path']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$success = true;
		foreach ($testResults as $testResult) {
		    if (! $testResult['success']) {
			$success = false;
		    }
		    $tests[] = $testResult;
		}
		if ($success) {
		    list($ret, $mimeTypes) =
			ImageMagickToolkitHelper::discoverMimeTypes($form['path']);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    } else {
		$form['error']['path']['missing'] = 1;
	    }
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$template->setVariable('tests', $tests);
	$template->setVariable('mimeTypes', $mimeTypes);
	$template->setVariable('jpegQualityList', $jpegQualityList);
	$template->setVariable('controller', 'imagemagick:AdminImageMagick');
	$html = $template->render('AdminImageMagick.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * @package ImageMagick
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Required classes
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
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$error = array();
	$status = array();
	if (isset($form['action']['save'])) {

	    if (empty($form['path'])) {
		$error[] = 'form[error][path][missing]';
	    } else {
		/* Set the path.  Guarantee that it's got a trailing slash. */
		$platform = $gallery->getPlatform();
		$slash = $platform->getDirectorySeparator();
		$form['path'] = trim($form['path']);
		if (!empty($form['path'])) {
		    if ($form['path']{strlen($form['path'])-1} != $slash) {
			$form['path'] .= $slash;
		    }
		}
	    
		list ($ret, $testResults) = ImageMagickToolkitHelper::testBinaries($form['path']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_BAD_PATH) {
			$error[] = 'form[error][path][badPath]';
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    $failCount = 0;
		    foreach ($testResults as $testResult) {
			/* All tests should work, else this path is not a valid one */
			if (!$testResult['success']) {
			    $failCount++;
			}
		    }

		    if ($failCount > 0) {
			$error[] = 'form[error][path][testError]';
		    }
		}
	    }
	    
	    if (empty($error)) {
		$ret = GalleryCoreApi::setPluginParameter(
		    'module', 'imagemagick', 'path', $form['path']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Save some platform specific ImageMagick parameters */
		$ret = ImageMagickToolkitHelper::savePlatformParameters();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = GalleryCoreApi::setPluginParameter(
		    'module', 'imagemagick', 'jpegQuality', $form['jpegQuality']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'imagemagick:AdminImageMagick';
		$status['saved'] = 1;
	    }
	} else if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'imagemagick:AdminImageMagick';
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'imagemagick:AdminImageMagick';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package ImageMagick
 * @subpackage UserInterface
 */
class AdminImageMagickView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Load our default values if we didn't just come from this form. */
	if ($form['formName'] != 'AdminImageMagick') {
	    foreach (array('path', 'jpegQuality') as $key) {
		list ($ret, $form[$key]) =
		    GalleryCoreApi::getPluginParameter('module', 'imagemagick', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	    $form['formName'] = 'AdminImageMagick';
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
	for ($i = 100; $i >= 50; $i -= 5) {
	    $jpegQualityList[] = $i;
	}

	$platform = $gallery->getPlatform();
	$tests = array();
	$mimeTypes = array();
	$version = array();
	$debugSnippet = '';
	$failCount = 0;
	if (isset($form['action']['test'])) {
	    if (!empty($form['path'])) {
		$gallery->startRecordingDebugSnippet();
		list($ret, $testResults) = ImageMagickToolkitHelper::testBinaries($form['path']);
		$debugSnippet = $gallery->stopRecordingDebugSnippet();

		$success = true;
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_BAD_PATH) {
			$testResults = array();
			$form['error']['path']['bad'] = 1;
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    $success = true;
		    foreach ($testResults as $testResult) {
			if (!$testResult['success']) {
			    $success = false;
			    $failCount++;
			}
		        $tests[] = $testResult;
		    }
		    if ($success) {
			list($ret, $mimeTypes) =
			    ImageMagickToolkitHelper::discoverMimeTypes($form['path']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			list($ret, $version) =
			    ImageMagickToolkitHelper::discoverVersion($form['path']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}
	    } else {
		$form['error']['path']['missing'] = 1;
	    }
	}

	$AdminImageMagick = array();
	$AdminImageMagick['tests'] = $tests;
	$AdminImageMagick['version'] = $version;
	$AdminImageMagick['mimeTypes'] = $mimeTypes;
	$AdminImageMagick['jpegQualityList'] = $jpegQualityList;
	$AdminImageMagick['debugSnippet'] = $debugSnippet;
	$AdminImageMagick['failCount'] = $failCount;

	if ($failCount > 0) {
	    $urlGenerator =& $gallery->getUrlGenerator();
	    $jsUrl = $urlGenerator->generateUrl(array('href' => 'lib/javascript/BlockToggle.js'));
	    $template->javascript($jsUrl);
	}

	$template->setVariable('AdminImageMagick', $AdminImageMagick);
	$template->setVariable('controller', 'imagemagick:AdminImageMagick');
	
	return array(GalleryStatus::success(),
		     array('body' => 'modules/imagemagick/templates/AdminImageMagick.tpl'));
    }
}
?>

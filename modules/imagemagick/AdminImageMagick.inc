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

	/* Set the path.  Guarantee that it's got a trailing slash. */
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();
	$form['path'] = trim($form['path']);
	if ($form['path']{strlen($form['path'])-1} != $slash) {
	    $form['path'] .= $slash;
	}

	foreach (array('path', 'jpegQuality') as $parameter) {
	    $ret = $gallery->setModuleParameter('imagemagick', $parameter, $form[$parameter]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out where to redirect upon success */
	$redirectParams['view'] = 'core:SiteAdmin';
	$redirectParams['subView'] = 'imagemagick:AdminImageMagick';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($redirectParams);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminImageMagickView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	foreach (array('path', 'jpegQuality') as $key) {
	    list ($ret, $form[$key]) =
		$gallery->getModuleParameter('imagemagick', $key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Set up our jpeg quality selection list */
	for ($i = 95; $i >= 50; $i -= 5) {
	    $jpegQualityList[] = $i;
	}

	$platform = $gallery->getPlatform();
	GalleryProfiler::start('AdminImageMagickView::renderBody().test-binaries');
	$tests = array();
	if (!empty($form['path'])) {
	    foreach (array('identify',
			   'convert') as $binary) {

		$cmd = array($form['path'] . $binary, '-help');
		list ($success, $results) = $platform->exec(array($cmd));
		$tests[] = array('name' => $binary,
				 'success' => $success,
				 'results' => $results);
	    }
	}

	GalleryProfiler::stop('AdminImageMagickView::renderBody().test-binaries');

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('tests', $tests);
	$this->_setTemplateVariable('jpegQualityList', $jpegQualityList);
	$this->_setTemplateVariable('controller', 'imagemagick:AdminImageMagick');
	$html = $this->_renderTemplate('imagemagick', 'AdminImageMagick.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

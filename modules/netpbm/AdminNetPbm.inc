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

class AdminNetPbmController extends GalleryController {

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

	/*
	 * Set the path.  Normalize it and guarantee that it's got a trailing slash.
	 */
	list ($ret, $platform) = $gallery->getPlatform();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$form['path'] = $platform->exportPath($form['path']);
	
	/* Guarantee a trailing slash */
	if ($form['path']{strlen($form['path'])-1} != '/') {
	    $form['path'] .= '/';
	}
	    
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

	/*
	 * If our graphics type is not NetPBM, set it now.
	 */
	list($ret, $graphicsType) = $gallery->getModuleParameter('core', 'graphics.type');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($graphicsType != 'netpbm') {
	    $ret = $gallery->setModuleParameter('core', 'graphics.type', 'netpbm');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out where to redirect upon success */
	$redirectParams['view'] = 'core:SiteAdmin';
	$redirectParams['subView'] = 'netpbm:AdminNetPbm';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($redirectParams);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminNetPbmView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	foreach (array('path', 'jpegQuality', 'pnmtojpeg') as $key) {
	    list ($ret, $form[$key]) =
		$gallery->getModuleParameter('netpbm', $key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Set up our jpeg quality selection list */
	for ($i = 95; $i >= 50; $i -= 5) {
	    $jpegQualityList[] = $i;
	}

	/* Set up our pnmtojpeg selection list */
	$pnmToJpegList = array('pnmtojpeg', 'ppmtojpeg');

	GalleryProfiler::start('AdminNetPbmView::renderBody().test-binaries');
	$tests = array();
	if (!empty($form['path'])) {
	    foreach (array('jpegtopnm',
			   'giftopnm',
			   $form['pnmtojpeg'],
			   'ppmtogif',
			   'pnmtopng',
			   'pnmscale',
			   'pnmfile',
			   'ppmquant',
			   'pnmcut',
			   'pnmrotate',
			   'pnmflip') as $binary) {

		$cmd = array($form['path'] . $binary, '--version');
		list ($ret, $results) = GalleryUtilities::exec(array($cmd));
		$tests[] = array('name' => $binary,
				 'status' => $ret,
				 'results' => $results);
	    }
	}
	GalleryProfiler::stop('AdminNetPbmView::renderBody().test-binaries');

	/* Specify our translation module */
	$ret = $this->_setTranslationModule('netpbm');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('form', $form);
	$smarty->assign('tests', $tests);
	$smarty->assign('pnmToJpegList', $pnmToJpegList);
	$smarty->assign('jpegQualityList', $jpegQualityList);
	$smarty->assign('controller', 'netpbm:AdminNetPbm');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminNetPbm.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

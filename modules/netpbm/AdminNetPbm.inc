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

	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Set the form values */
	foreach (array('path', 'jpegQuality') as $key) {
	    $value = GalleryUtilities::getRequestVariables($key);

	    /* Normalize the path */
	    if ($key == 'path') {
		list ($ret, $platform) = $gallery->getPlatform();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$value = $platform->exportPath($value);

		/* Guarantee a trailing slash */
		if ($value{strlen($value)-1} != '/') {
		    $value .= '/';
		}
	    }
	    
	    $ret = $gallery->setModuleParameter('netpbm', $key, $value);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list ($ret, $path) = $gallery->getModuleParameter('netpbm', 'path');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $platform) = $gallery->getPlatform();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Scan for the appropriate version of p?mtojpeg */
	foreach (array('pnmtojpeg', 'ppmtojpeg') as $name) {
	    $executable = $platform->executablePath($name);
	    if ($platform->file_exists($path . '/' . $name)) {
		$ret = $gallery->setModuleParameter('netpbm', 'pnmtojpeg', $name);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		break;
	    }
	}

	list($ret, $module) = $gallery->loadModule('netpbm');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $needsConfiguration) = $module->needsConfiguration();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($needsConfiguration) {
	    /*
	     * If we get this far successfully, assume that the user has made
	     * at least a token effort to configure the module correctly.  The
	     * test code in AdminNetPbmView should indicate whether or not they
	     * got it right.  So, update our version in the map accordingly.
	     */
	    $ret = $gallery->setModuleParameter($module->getName(),
						'version', $module->getVersion());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	

	/* Figure out where to redirect upon success */
	$stateVariables['view'] = 'core:SiteAdmin';
	$stateVariables['subView'] = 'netpbm:AdminNetPbm';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->generateUrl($stateVariables);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminNetPbmView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	foreach (array('path', 'jpegQuality') as $key) {

	    list ($ret, $value) =
		$gallery->getModuleParameter('netpbm', $key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $form[$key] = $value;
	}

	/* Set up our jpeg quality selection list */
	for ($i = 95; $i >= 50; $i -= 5) {
	    $jpegQualityList[] = $i;
	}

	/* If we have a NetPBM path, then try to test the binaries */
	list ($ret, $path) = $gallery->getModuleParameter('netpbm', 'path');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $pnmtojpeg) = $gallery->getModuleParameter('netpbm', 'pnmtojpeg');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	foreach (array('jpegtopnm',
		       'giftopnm',
		       $pnmtojpeg,
		       'ppmtogif',
		       'pnmtopng',
		       'pnmscale',
		       'pnmfile',
		       'ppmquant',
		       'pnmcut',
		       'pnmrotate',
		       'pnmflip') as $binary) {

	    $cmd = array($path . $binary, '--version');
	    list ($ret, $results) = GalleryUtilities::exec(array($cmd));
	    $tests[] = array('name' => $binary,
			     'status' => $ret,
			     'results' => $results);
	}

	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('form', $form);
	$smarty->assign('tests', $tests);
	$smarty->assign('jpegQualityList', $jpegQualityList);
	$smarty->assign('controller', 'netpbm:AdminNetPbm');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminNetPbm.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

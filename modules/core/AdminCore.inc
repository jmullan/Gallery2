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

class AdminCoreController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	foreach (array('permissions.directory',
		       'permissions.file',
		       'exec.expectedStatus',
		       'default.orderBy',
		       'default.orderDirection',
		       'default.layout',
		       'default.theme',
		       'graphics.type') as $key) {
	    $value = GalleryUtilities::getRequestVariables($key);

	    if (isset($value)) {
		$ret = $gallery->setModuleParameter('core', $key, $value);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/* Figure out where to redirect upon success */
	$urlParams['view'] = 'core:SiteAdmin';
	$urlParams['subView'] = 'core:AdminCore';

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($urlParams);

	return array(GalleryStatus::success(), $results);
    }
}

class AdminCoreView extends GalleryView {

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
	
	$ret = $this->_assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/* Load up our form data */
	foreach (array('permissions.directory',
		       'permissions.file',
		       'exec.expectedStatus',
		       'default.orderBy',
		       'default.orderDirection',
		       'default.layout',
		       'default.theme',
		       'graphics.type') as $key) {

	    list ($ret, $value) =
		$gallery->getModuleParameter('core', $key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($outer, $inner) = split('\.', $key);
	    $form[$outer][$inner] = $value;
	}

	/* Set up our sort order selection list */
	$orderByList = array();
	$orderByList['title'] = $gallery->translate('Title');
	$orderByList['creationTimestamp'] = $gallery->translate('Creation Date');
	$orderByList['modificationTimestamp'] = $gallery->translate('Last Changed Date');
	$orderByList['description'] = $gallery->translate('Description');
	$orderByList['keywords'] = $gallery->translate('Keywords');

	/* Set up our sort direction selection list */
	$orderDirectionList = array();
	$orderDirectionList['asc'] = $gallery->translate("Ascending");
	$orderDirectionList['desc'] = $gallery->translate("Descending");

	/* Set up our layout selection list */
	$layoutList = array();
	list ($ret, $platform) = $gallery->getPlatform();
	$layoutDir = $gallery->getConfig('code.gallery.layouts');
	if ($dir = $platform->opendir($layoutDir)) {
	    while (($file = readdir($dir)) !== false) {
		if ($file{0} == '.' || $file == 'CVS') {
		    continue;
		}
		$layoutInc = "$layoutDir$file/layout.inc";
		if ($platform->file_exists($layoutInc)) {
		    $layoutList[] = $file;
		}
	    }
	    closedir($dir);
	}
	
	/* Set up our theme selection list */
	$themeList = array();
	list ($ret, $platform) = $gallery->getPlatform();
	$themeDir = $gallery->getConfig('code.gallery.themes');
	if ($dir = $platform->opendir($themeDir)) {
	    while (($subdir = readdir($dir)) !== false) {
		if ($subdir{0} == '.' || $subdir == 'CVS') {
		    continue;
		}

		if ($platform->is_dir("$themeDir$subdir")) {
		    $file = "$themeDir$subdir/theme.inc";
		    if ($platform->file_exists($file)) {
			$themeList[] = $subdir;
		    }
		}
	    }
	    closedir($dir);
	}

	/* Set up our permission selection lists */
	$permissionsDirectoryList = array('700', '750', '755', '770', '775', '777');
	$permissionsFileList = array('600', '640', '644', '660', '664', '666');

	/* Set up our graphics selection list */
	$graphicsTypeList = GalleryGraphicsFactory::getAllImplementationIds();

	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->assign('form', $form);
	$smarty->assign('layoutList', $layoutList);
	$smarty->assign('themeList', $themeList);
	$smarty->assign('orderByList', $orderByList);
	$smarty->assign('orderDirectionList', $orderDirectionList);
	$smarty->assign('permissionsDirectoryList', $permissionsDirectoryList);
	$smarty->assign('permissionsFileList', $permissionsFileList);
	$smarty->assign('graphicsTypeList' , $graphicsTypeList);
	$smarty->assign('controller', 'core:AdminCore');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AdminCore.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

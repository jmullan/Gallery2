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

	$ret = GalleryUserHelper::assertSiteAdministrator();
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
		       'default.language',
		       'graphics.type',
		       'session.lifetime',
		       'session.inactivityTimeout') as $key) {
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
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
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
		       'default.language',
		       'graphics.type',
		       'session.lifetime',
		       'session.inactivityTimeout') as $key) {

	    list ($ret, $value) =
		$gallery->getModuleParameter('core', $key);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($outer, $inner) = split('\.', $key);
	    $form[$outer][$inner] = $value;
	}

	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Set up our sort order selection list */
	$orderByList = array();
	$orderByList['title'] = $module->translate('Title');
	$orderByList['creationTimestamp'] = $module->translate('Creation Date');
	$orderByList['modificationTimestamp'] = $module->translate('Last Changed Date');
	$orderByList['description'] = $module->translate('Description');
	$orderByList['keywords'] = $module->translate('Keywords');

	/* Set up our sort direction selection list */
	$orderDirectionList = array();
	$orderDirectionList['asc'] = $module->translate("Ascending");
	$orderDirectionList['desc'] = $module->translate("Descending");

	list ($ret, $platform) = $gallery->getPlatform();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Set up our layout selection list */
	$layoutList = array();
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

	/* Set up our language selection list */
	list ($ret, $translator) = $gallery->getTranslator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$languageList = array();
	$supportedLanguages = $translator->getSupportedLanguages();
	foreach ($supportedLanguages as $language => $countryList) {
	    foreach ($countryList as $country => $languageData) {
		$languageList[$language . '_' . $country] =
		    $languageData['description'];
	    }
	}

	/* Set up our session time lists */
	$sessionTimeLists = array();
	foreach (array(15, 30, 45) as $minutes) {
	    $sessionTimeList[$minutes * 60] =
		$module->translate(array('one' => '%d minute',
					 'many' => '%d minutes',
					 'count' => $minutes,
					 'arg1' => $minutes));
	}
	foreach (array(1, 6, 12) as $hours) {
	    $sessionTimeList[$hours * 3600] =
		$module->translate(array('one' => '%d hour',
					 'many' => '%d hours',
					 'count' => $hours,
					 'arg1' => $hours));
	}
	foreach (array(1, 2, 3, 4, 5, 6) as $days) {
	    $sessionTimeList[$days * 86400] =
		$module->translate(array('one' => '%d day',
					 'many' => '%d days',
					 'count' => $days,
					 'arg1' => $days));
	}
	foreach (array(1, 2, 3) as $weeks) {
	    $sessionTimeList[$days * 7 * 86400] =
		$module->translate(array('one' => '%d week',
					 'many' => '%d weeks',
					 'count' => $weeks,
					 'arg1' => $weeks));
	}
	$sessionTimeList[25 * 365 * 86400] = $module->translate('forever');
	
	/* Set up our theme selection list */
	$themeList = array();
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
	require_once(dirname(__FILE__) . '/classes/GalleryGraphicsFactory.class');
	$graphicsTypeList = GalleryGraphicsFactory::getAllImplementationIds();

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('layoutList', $layoutList);
	$this->_setTemplateVariable('themeList', $themeList);
	$this->_setTemplateVariable('languageList', $languageList);
	$this->_setTemplateVariable('orderByList', $orderByList);
	$this->_setTemplateVariable('orderDirectionList', $orderDirectionList);
	$this->_setTemplateVariable('permissionsDirectoryList', $permissionsDirectoryList);
	$this->_setTemplateVariable('permissionsFileList', $permissionsFileList);
	$this->_setTemplateVariable('sessionTimeList', $sessionTimeList);
	$this->_setTemplateVariable('graphicsTypeList' , $graphicsTypeList);
	$this->_setTemplateVariable('controller', 'core:AdminCore');
	$html = $this->_renderTemplate('core', 'AdminCore.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

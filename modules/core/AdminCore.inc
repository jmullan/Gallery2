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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the setting of several general Gallery options
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCoreController extends GalleryController {
    
    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Get the list of legal local server dirs */
	list ($ret, $localServerDirs) = $gallery->getModuleParameter('core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$localServerDirList = split(',', $localServerDirs);

	if (isset($form['action']['save'])) {
	    foreach (array('permissions.directory',
			   'permissions.file',
			   'exec.expectedStatus',
			   'default.orderBy',
			   'default.orderDirection',
			   'default.layout',
			   'default.theme',
			   'default.language',
			   'session.lifetime',
			   'session.inactivityTimeout') as $key) {
		list ($a, $b) = split('\.', $key);
		if (isset($form[$a][$b])) {
		    $ret = $gallery->setModuleParameter('core', $key, $form[$a][$b]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	} else if (isset($form['action']['addUploadLocalServerDir'])) {
	    $path = $form['uploadLocalServer']['newDir'];
	    if (!empty($path)) {
		if (!in_array($path, $localServerDirList)) {
		    $localServerDirList[] = $path;
		}

		for ($i = 0; $i < sizeof($localServerDirList); $i++) {
		    if (empty($localServerDirList[$i])) {
			unset($localServerDirList[$i]);
		    }
		}
		
		$ret = $gallery->setModuleParameter('core', 'uploadLocalServer.dirs', join(',', $localServerDirList));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	} else if (isset($form['action']['removeUploadLocalServerDir'])) {
	    $path = $form['uploadLocalServer']['selectedDir'];
	    if (!empty($path)) {
		$flip = array_flip($localServerDirList);
		if (isset($flip[$path])) {
		    unset($flip[$path]);
		}
		$localServerDirList = array_flip($flip);

		for ($i = 0; $i < sizeof($localServerDirList); $i++) {
		    if (empty($localServerDirList[$i])) {
			unset($localServerDirList[$i]);
		    }
		}
	    }
	    $ret = $gallery->setModuleParameter('core', 'uploadLocalServer.dirs', join(',', $localServerDirList));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Figure out where to redirect upon success */
	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'core:AdminCore';

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for general Gallery settings
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminCoreView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
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

	/* Get the list of legal local server dirs */
	list ($ret, $localServerDirs) = $gallery->getModuleParameter('core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$localServerDirList = split(',', $localServerDirs);

	/* Set up our sort order selection list */
	$orderByList = array();
	$orderByList[''] = $module->translate('* No Sort Order *');
	$orderByList['title'] = $module->translate('Title');
	$orderByList['summary'] = $module->translate('Summary');
	$orderByList['creationTimestamp'] = $module->translate('Creation Date');
	$orderByList['modificationTimestamp'] = $module->translate('Last Changed Date');
	$orderByList['description'] = $module->translate('Description');
	$orderByList['keywords'] = $module->translate('Keywords');

	/* Set up our sort direction selection list */
	$orderDirectionList = array();
	$orderDirectionList[ORDER_ASCENDING] = $module->translate("Ascending");
	$orderDirectionList[ORDER_DESCENDING] = $module->translate("Descending");

	$platform = $gallery->getPlatform();

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
	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$languageList = array();
	$languageList[''] = $module->translate('<none>');
	
	$translator =& $gallery->getTranslator();
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
	    $sessionTimeList[$weeks * 7 * 86400] =
		$module->translate(array('one' => '%d week',
					 'many' => '%d weeks',
					 'count' => $weeks,
					 'arg1' => $weeks));
	}
	$sessionTimeList[25 * 365 * 86400] = $module->translate('forever');
	
	/* Set up our permission selection lists */
	$permissionsDirectoryList = array('700', '750', '755', '770', '775', '777');
	$permissionsFileList = array('600', '640', '644', '660', '664', '666');

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('layoutList', $layoutList);
	$template->setVariable('themeList', GalleryTheme::getThemes());
	$template->setVariable('localServerDirList', $localServerDirList);
	$template->setVariable('languageList', $languageList);
	$template->setVariable('orderByList', $orderByList);
	$template->setVariable('orderDirectionList', $orderDirectionList);
	$template->setVariable('permissionsDirectoryList', $permissionsDirectoryList);
	$template->setVariable('permissionsFileList', $permissionsFileList);
	$template->setVariable('sessionTimeList', $sessionTimeList);
	$template->setVariable('controller', 'core:AdminCore');
	$html = $template->render('AdminCore.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>

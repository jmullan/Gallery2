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

	$error = array();
	$status = array();
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
			   'session.inactivityTimeout',
			   'misc.useShortUrls') as $key) {
		list ($a, $b) = split('\.', $key);
		if (isset($form[$a][$b])) {
		    $ret = $gallery->setModuleParameter('core', $key, $form[$a][$b]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    $status['saved'] = 1;
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminCore';
	} else if (isset($form['action']['addUploadLocalServerDir'])) {
	    $path = $form['uploadLocalServer']['newDir'];

	    $platform = $gallery->getPlatform();
	    if (empty($path)) {
		$error[] = 'form.error.uploadLocalServer.newDir.missing';
	    } else if ($platform->isRestrictedByOpenBasedir($path)) {
		$error[] = 'form.error.uploadLocalServer.newDir.restrictedByOpenBasedir';
	    } else if (!$platform->is_readable($path)) {
		$error[] = 'form.error.uploadLocalServer.newDir.notReadable';
	    } else if (!$platform->is_dir($path)) {
		$error[] = 'form.error.uploadLocalServer.newDir.notADirectory';
	    } 

	    if (empty($error)) {
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
		$status['addedDir'] = 1;
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminCore';
	    } else {
	    }
	} else if (isset($form['action']['removeUploadLocalServerDir'])) {
	    if (!empty($form['uploadLocalServer']['selectedDir'])) {
		$path = $form['uploadLocalServer']['selectedDir'];
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
		$ret = $gallery->setModuleParameter('core', 'uploadLocalServer.dirs', join(',', $localServerDirList));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['removedDir'] = 1;
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'core:AdminCore';
	    } else {
		$error[] = 'form.error.uploadLocalServer.selectedDir.missing';
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'core:AdminCore';
	}
	$results['status'] = $status;
	$results['error'] = $error;

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
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	    
	if ($form['formName'] != 'AdminCore') {
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
			   'session.inactivityTimeout',
			   'misc.useShortUrls') as $key) {

		list ($ret, $value) =
		    $gallery->getModuleParameter('core', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		list ($outer, $inner) = split('\.', $key);
		$form[$outer][$inner] = $value;
	    }
	    $form['formName'] = 'AdminCore';
	    $form['uploadLocalServer']['newDir'] = '';
	}

	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Get the list of legal local server dirs */
	list ($ret, $localServerDirs) = $gallery->getModuleParameter('core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$localServerDirList = split(',', $localServerDirs);
	for ($i = 0; $i < sizeof($localServerDirList); $i++) {
	    if (empty($localServerDirList[$i])) {
		unset($localServerDirList[$i]);
	    }
	}

	/* Set up our sort order selection list */
	$orderByList = array();
	$orderByList[''] = $module->translate('&laquo; No Sort Order &raquo;');
	$orderByList['title'] = $module->translate('Title');
	$orderByList['summary'] = $module->translate('Summary');
	$orderByList['creationTimestamp'] = $module->translate('Creation Date');
	$orderByList['modificationTimestamp'] = $module->translate('Last Changed Date');
	$orderByList['description'] = $module->translate('Description');
	$orderByList['keywords'] = $module->translate('Keywords');

	/* Set up our sort direction selection list */
	$orderDirectionList = array();
	$orderDirectionList[ORDER_ASCENDING] = $module->translate('Ascending');
	$orderDirectionList[ORDER_DESCENDING] = $module->translate('Descending');

	$platform = $gallery->getPlatform();

	/* Set up our language selection list */
	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	$languageList = array();
	$languageList[''] = $module->translate('&laquo; None &raquo;');
	
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

	/* Miscellaneous lists */
	$useShortUrlsList = array('true' => $module->translate('yes'),
				  'false' => $module->translate('no'));

	list ($ret, $rootId) = $gallery->getModuleParameter('core', 'id.rootAlbum');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$AdminCore = array();
	$AdminCore['layoutList'] = GalleryLayout::getLayoutList();
	$AdminCore['themeList'] = GalleryTheme::getThemeList();
	$AdminCore['localServerDirList'] = $localServerDirList;
	$AdminCore['languageList'] = $languageList;
	$AdminCore['orderByList'] = $orderByList;
	$AdminCore['orderDirectionList'] = $orderDirectionList;
	$AdminCore['permissionsDirectoryList'] = $permissionsDirectoryList;
	$AdminCore['permissionsFileList'] = $permissionsFileList;
	$AdminCore['sessionTimeList'] = $sessionTimeList;
	$AdminCore['useShortUrlsList'] = $useShortUrlsList;
	$AdminCore['shortUrlTestItemId'] = $rootId;
	
	$template->setVariable('controller', 'core:AdminCore');
	$template->setVariable('AdminCore', $AdminCore);

	return array(GalleryStatus::success(), '', 'modules/core/templates/AdminCore.tpl');
    }
}
?>

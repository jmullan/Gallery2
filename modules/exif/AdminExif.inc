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
 * @package Exif
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the setting of Exif module options
 *
 * @package Exif
 * @subpackage UserInterface
 */
class AdminExifController extends GalleryController {
    
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
		if (isset($form[$key])) {
		    $ret = $gallery->setModuleParameter('core', $key, $form[$key]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
	    }
	    $status['saved'] = 1;
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'core:AdminExif';
	} else if (isset($form['action']['addUploadLocalServerDir'])) {
	    $path = $form['uploadLocalServer']['newDir'];

	    $platform = $gallery->getPlatform();
	    if (empty($path)) {
		$error[] = 'form[error][uploadLocalServer][newDir][missing]';
	    } else if ($platform->isRestrictedByOpenBasedir($path)) {
		$error[] = 'form[error][uploadLocalServer][newDir][restrictedByOpenBasedir]';
	    } else if (!$platform->is_readable($path)) {
		$error[] = 'form[error][uploadLocalServer][newDir][notReadable]';
	    } else if (!$platform->is_dir($path)) {
		$error[] = 'form[error][uploadLocalServer][newDir][notADirectory]';
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
		$redirect['subView'] = 'core:AdminExif';
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
		$redirect['subView'] = 'core:AdminExif';
	    } else {
		$error[] = 'form[error][uploadLocalServer][selectedDir][missing]';
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'core:AdminExif';
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
class AdminExifView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	$mode = GalleryUtilities::getRequestVariables('mode');
	
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	if ($form['formName'] != 'AdminExif') {
	    /* Load up our form data */
	    $form['formName'] = 'AdminExif';
	}

	/*
	 * If the mode is empty get it from the session.  If it's empty there,
	 * default to uploading from the browser.  Either way, save the user's
	 * preference in the session.
	 */
	$session =& $gallery->getSession();
	if (empty($mode)) {
	    $mode = $session->get('exif.view.AdminExif.mode');
	    if (empty($mode)) {
		$mode = 'general';
	    }
	}
	$session->put('exif.view.AdminExif.mode', $mode);

	list ($ret, $module) = $gallery->loadModule('exif');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	list ($ret, $params) = GalleryPluginParameterMap::fetchAllParameters('module', 'exif', null);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$exifKeys = array();
	foreach (ExifHelper::getExifKeys() as $key => $data) {
	    $exifKeys[$key] = array('title' => $module->translate($data[1]));
	    if (isset($params[$key])) {
		switch($params[$key]) {
		case EXIF_SIMPLE:
		    $exifKeys[$key]['status'] = 'simple';
		    break;

		case EXIF_ADVANCED:
		    $exifKeys[$key]['status'] = 'advanced';
		    break;
		}
	    } else {
		$exifKeys[$key]['status'] = 'hidden';
	    }
	}

	uasort($exifKeys, array($this, 'titleComparator'));

	$AdminExif = array();
	$AdminExif['mode'] = $mode;
	$AdminExif['keys'] = $exifKeys;
	
	$template->setVariable('controller', 'core:AdminExif');
	$template->setVariable('AdminExif', $AdminExif);

	return array(GalleryStatus::success(),
		     array('body' => 'modules/exif/templates/AdminExif.tpl'));
    }

    function titleComparator($a, $b) {
	return strcmp($a['title'], $b['title']);
    }
}
?>

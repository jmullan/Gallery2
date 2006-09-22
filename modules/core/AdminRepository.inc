<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

GalleryCoreApi::requireOnce('modules/core/classes/GalleryRepository.class');

/**
 * This controller will handle an administration request for a module
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Jozef Selesi <selesi at gmail dot com>
 * @version $Revision$ $Date$
 */
class AdminRepositoryController extends GalleryController {

    /**
     * Repository.
     * @var object GalleryRepository
     * @access private
     */
    var $_repository;

    function _getRepository() {
	if (!isset($this->_repository)) {
	    $this->_repository = new GalleryRepository();
	}
	return $this->_repository;
    }

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret, null);
	}

	/* Init repository. */
	$repository = $this->_getRepository();
	$ret = $repository->init();
	if ($ret) {
	    return array($ret, null);
	}

	$status = $error = array();

	if (isset($form['action']['update'])) {
	    foreach (array('module', 'theme') as $pluginType) {
		list ($ret, $pluginStatus[$pluginType]) =
		    GalleryCoreApi::fetchPluginStatus($pluginType, true);
		if ($ret) {
		    return array($ret, null);
		}
	    }

	    $templateAdapter =& $gallery->getTemplateAdapter();
	    $templateAdapter->registerTrailerCallback(
		array($this, 'updatePluginStatus'), array($repository, $pluginStatus));
	    $delegate['view'] = 'core.ProgressBar';
	} else if (isset($form['action']['upgradeAll'])) {
	    /* Get list of upgradeable packages. */
	    list ($ret, $packages) = $repository->getAllUpgradeablePackages();
	    if ($ret) {
		return array($ret, null);
	    }

	    if (empty($packages)) {
		$status['noUpgradeAvailable'] = 1;
	    } else {
		/*
		 * Start upgrade process and show progress bar.
		 *
		 * performDownloadAndInstallation used to live in this controller, so we'd just
		 * call it directly.  But it got refactored into AdminRepositoryDownloadController
		 * so for now, just call it there.
		 *
		 * @todo: refactor it into a common base class
		 */
		GalleryCoreApi::requireOnce('modules/core/AdminRepositoryDownload.inc');
		$controller = new AdminRepositoryDownloadController();
		$templateAdapter =& $gallery->getTemplateAdapter();
		$templateAdapter->registerTrailerCallback(
		    array($controller, 'performDownloadAndInstallation'),
		    array($packages, 'commonTasks'));
		$delegate['view'] = 'core.ProgressBar';
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    if (empty($delegate)) {
		$results['delegate']['view'] = 'core.SiteAdmin';
		$results['delegate']['subView'] = 'core.AdminRepository';
	    } else {
		$results['delegate'] = $delegate;
	    }
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(null, $results);
    }

    /**
     * Update the repository index, and scan all installed plugins and update
     * GalleryPluginPackageMap with a complete listing of everything that's installed.
     *
     * @todo Show a summary page (or at least a link to it) which contains details about
     * the exact tasks that were performed and any errors that were encountered.
     */
    function updatePluginStatus($repository, $pluginStatus) {
	global $gallery;
	$templateAdapter =& $gallery->getTemplateAdapter();

	$status = array();
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret) {
	    return $ret;
	}

	/* Update the index. */
	$templateAdapter->updateProgressBar(
	    $module->translate('Updating repository index'),
	    '', 0);
	$ret = $repository->downloadIndex();
	if ($ret) {
	    $status['error'] = $ret->getErrorMessage();
	} else {
	    $status['indexUpdated'] = 1;
	}
	$currentProgress = 10 / 100;

	$total = count($pluginStatus['module']) + count($pluginStatus['theme']);
	$increment = (1 - $currentProgress) / $total;
	$message = $module->translate('Scanning plugins');
	foreach (array('module', 'theme') as $pluginType) {
	    foreach (array_keys($pluginStatus[$pluginType]) as $pluginId) {
		$gallery->guaranteeTimeLimit(30);

		$templateAdapter->updateProgressBar($message, $pluginId, $currentProgress);
		$ret = $repository->scanPlugin($pluginType, $pluginId);
		if ($ret) {
		    return $ret;
		}
		$currentProgress += $increment;
	    }
	}

	$ret = $templateAdapter->updateProgressBar(
	    'Update Plugin List', $module->translate('Done.'), 1);
	if ($ret) {
	    $templateAdapter->errorProgressBar($ret);
	    return $ret;
	}

	$redirect['view'] = 'core.SiteAdmin';
	$redirect['subView'] = 'core.AdminRepository';

	$session =& $gallery->getSession();
	$redirect['statusId'] = $session->putStatus($status);

	$urlGenerator =& $gallery->getUrlGenerator();
	$templateAdapter->completeProgressBar($urlGenerator->generateUrl($redirect));

	return null;
    }
}

/**
 * This view will show all repository-related features.
 */
class AdminRepositoryView extends GalleryView {

    /**
     * Repository.
     * @var object GalleryRepository
     * @access private
     */
    var $_repository;

    function _getRepository() {
	if (!isset($this->_repository)) {
	    $this->_repository = new GalleryRepository();
	}
	return $this->_repository;
    }

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	$platform =& $gallery->getPlatform();

	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret) {
	    return array($ret, null);
	}

	/* Init repository. */
	$repository = $this->_getRepository();
	$ret = $repository->init();
	if ($ret) {
	    return array($ret, null);
	}

	$AdminRepository = array();
	$localIndexExists = $repository->localIndexExists();
	if (!$localIndexExists) {
	    /* Make sure the plugins directory is properly set up. */
	    list ($isSetUp, $errorMessage) = GalleryRepository::createPluginsDirectory();
	    if (!$isSetUp) {
		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminRepositorySetup';
		$AdminRepository['galleryBaseDirectory'] =
		    $platform->realpath(dirname(__FILE__) . '/../..');
		$AdminRepository['errorMessage'] = $errorMessage;

		return array(null,
			     array('body' => 'modules/core/templates/AdminRepositorySetup.tpl'));
	    }
	}

	/* Check if incompatible plugins should be shown. */
	$coreApis = array();
	$showIncompatible = GalleryUtilities::getRequestVariables('showIncompatible');
	if ($showIncompatible == 'true') {
	    list ($coreApiVersion, $themeApiVersion, $moduleApiVersion) =
		GalleryUtilities::getRequestVariables('coreApi', 'themeApi', 'moduleApi');
	    if (empty($coreApiVersion) || empty($themeApiVersion) || empty($moduleApiVersion)) {
		return array(GalleryCoreApi::error(
				 ERROR_BAD_PARAMETER, __FILE__, __LINE__,
				 "[$coreApiVersion] [$themeApiVersion] [$moduleApiVersion]"),
			     null);
	    }
	    $coreApis['core'] = explode('.', $coreApiVersion);
	    $coreApis['module'] = explode('.', $moduleApiVersion);
	    $coreApis['theme'] = explode('.', $themeApiVersion);
	    $AdminRepository['showIncompatible'] = 1;
	}

	if ($localIndexExists) {
	    foreach (array('module', 'theme') as $pluginType) {
		/* Get list of plugins to show in the repository browser. */
		list ($ret, $browseData[$pluginType]) = $repository->getRepositoryPluginList(
		    $pluginType, $showIncompatible, $coreApis);
		if ($ret) {
		    return array($ret, null);
		}
	    }

	    /* TODO: merge these group-wise instead of just appending themes to groups */
	    $browseData = array_merge($browseData['module'], $browseData['theme']);
	    $AdminRepository['browseData'] = $browseData;

	    /* Get local index meta data. */
	    list ($ret, $indexMetaData) = $repository->getIndexMetaData();
	    if ($ret) {
		return array($ret, null);
	    }
	    $AdminRepository['indexMetaData'] = $indexMetaData;

	    /* Get core upgrade info. */
	    list ($ret, $isCoreUpgradeAvailable, $apiVersions) =
		$repository->isCoreUpgradeAvailable();
	    if ($ret) {
		return array($ret, null);
	    }
	    if ($isCoreUpgradeAvailable) {
		$AdminRepository['latestCoreApiVersion'] = $apiVersions['core'];
		$AdminRepository['latestThemeApiVersion'] = $apiVersions['theme'];
		$AdminRepository['latestModuleApiVersion'] = $apiVersions['module'];
	    }
	    $AdminRepository['coreUpgradeAvailable'] = $isCoreUpgradeAvailable;
	}

	$baseName = dirname(dirname(dirname(__FILE__)));
	$AdminRepository['writeable'] = array(
	    'modules' => $platform->is_writeable("$baseName/modules"),
	    'themes' => $platform->is_writeable("$baseName/themes"));

	/* Render the HTML body */
	$template->setVariable('AdminRepository', $AdminRepository);
	$template->setVariable('controller', 'core.AdminRepository');

	return array(null, array('body' => 'modules/core/templates/AdminRepository.tpl'));
    }
}
?>

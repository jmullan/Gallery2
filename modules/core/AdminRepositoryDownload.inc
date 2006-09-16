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
/**
 * @version $Revision$ $Date$
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Jozef Selesi <selesi at gmail dot com>
 */

GalleryCoreApi::requireOnce('modules/core/classes/GalleryRepository.class');

/**
 * This controller will handle an administration request for a module
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminRepositoryDownloadController extends GalleryController {

    /**
     * Repository.
     *
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

	$status = $error = array();

	if (!isset($form['pluginType']) || !isset($form['pluginId'])) {
	    return array(GalleryCoreApi::error(
			     ERROR_BAD_PARAMETER, __FILE__, __LINE__,
			     "Plugin type or ID not set [$pluginType] [$pluginId]"),
			 null);
	}
	$pluginType = $form['pluginType'];
	$pluginId = $form['pluginId'];

	if (!preg_match('/theme|module/', $pluginType)) {
	    return array(GalleryCoreApi::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
					       "Invalid plugin type [$pluginType]"),
			 null);
	}

	/* Handle cancel action. */
	if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core.SiteAdmin';
	    $redirect['subView'] = 'core.AdminRepository';
	} else if (isset($form['action']['download'])) {
	    /* Create package list. */
	    $packages = array();
	    if (isset($form['upgradeBaseFiles'])) {
		$packages['base'] = 'upgrade';
	    } else if (isset($form['downloadBaseFiles'])) {
		$packages['base'] = 'download';
	    }

	    if (isset($form['languages'])) {
		foreach ($form['languages'] as $language) {
		    $packages['lang-' . $language] = 1;
		}
	    }

	    /* Show error message if no packages have been selected for download. */
	    if (empty($packages)) {
		$delegate['view'] = 'core.SiteAdmin';
		$delegate['subView'] = 'core.AdminRepository';
		$error[] = 'form[packages][empty]';

		/* TODO: Do we need to put these vars back into the request? */
		GalleryUtilities::putRequestVariable('pluginId', $pluginId);
		GalleryUtilities::putRequestVariable('pluginType', $pluginType);
	    } else {
		$templateAdapter =& $gallery->getTemplateAdapter();
		$templateAdapter->registerTrailerCallback(
		    array($this, 'performDownloadAndInstallation'),
		    array(array($pluginType => array($pluginId => $packages))));
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
     * Download specified packages to the local repository cache and perform installation.
     *
     * TODO: Show a summary page (or at least a link to it) which contains details about
     * the exact tasks that were performed and any errors that were encountered.
     *
     * @param array $pluginData packages
     * @return object GalleryStatus a status code
     */
    function performDownloadAndInstallation($pluginData) {
	global $gallery;
	$templateAdapter =& $gallery->getTemplateAdapter();

	$repository = $this->_getRepository();
	$ret = $repository->init();
	if ($ret) {
	    return $ret;
	}

	/* Create download file list. */
	list ($ret, $files) = $repository->getDownloadFileList($pluginData);
	if ($ret) {
	    $templateAdapter->errorProgressBar($ret);
	    return $ret;
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret) {
	    return $ret;
	}

	/* Download files. */
	$titleText = $module->translate('Downloading Files');
	foreach ($files as $pluginType => $plugins) {
	    foreach ($plugins as $pluginId => $pluginDownloadData) {
		$packageUrls = $pluginDownloadData['files'];
		$pluginName = $pluginDownloadData['name'];

		/* Set up progress bar variables. */
		$currentUrlIndex = 1;
		$totalUrls = count($packageUrls);

		foreach ($packageUrls as $packageName => $relativePackageUrl) {
		    $ret = $templateAdapter->updateProgressBar($titleText,
			sprintf($module->translate('Downloading %s'), $pluginName),
			$currentUrlIndex / $totalUrls);
		    if ($ret) {
			$templateAdapter->errorProgressBar($ret);
			return $ret;
		    }
		    $currentUrlIndex++;

		    /* Download and unpack package. */
		    list ($ret, $pluginDescriptor) = $repository->downloadAndUnpack(
			$pluginType, $pluginId, $packageName, $relativePackageUrl);
		    if ($ret) {
			$templateAdapter->errorProgressBar($ret);
			return $ret;
		    }

		    if (!empty($pluginDescriptor)) {
			/* Save current package's descriptor. */
			$descriptor = $pluginDescriptor;
		    } else {
			/* Sanity check. */
			if (empty($descriptor)) {
			    $ret = GalleryCoreApi::error(ERROR_STORAGE_FAILURE, __FILE__, __LINE__,
							'Descriptor must not be empty.');
			    $templateAdapter->errorProgressBar($ret);
			    return $ret;
			}

			/* Check the unpacked files' integrity. */
			$ret = $repository->verifyPackageIntegrity($packageName, $descriptor);
			if ($ret) {
			    $templateAdapter->errorProgressBar($ret);
			    return $ret;
			}

			/* Update plugin package map. */
			list ($ret, $version, $build) = $repository->getPackageVersionAndBuild(
			    $pluginType, $pluginId, $packageName);
			if ($ret) {
			    $templateAdapter->errorProgressBar($ret);
			    return $ret;
			}
			$ret = $repository->updatePackageMetaData(
			    $pluginType, $pluginId, $packageName, $version, $build);
			if ($ret) {
			    $templateAdapter->errorProgressBar($ret);
			    return $ret;
			}
		    }
		}

		/*
		 * Our plugin status caches are no longer valid because we've just installed some
		 * new code.  Load the status and ignore the cache which forces a cache update.
		 * @todo: add a real cache flushing method in the api instead
		 */
		list ($ret, $status) = GalleryCoreApi::fetchPluginStatus($pluginType, true);
		if ($ret) {
		    $templateAdapter->errorProgressBar($ret);
		    return $ret;
		}

		/*
		 * This next block is duplicated in PluginCallback.
		 * @todo: Refactor this code duplication away
		 */

		$ret = $templateAdapter->updateProgressBar(
		    $titleText, sprintf($module->translate('Activating %s'), $pluginName),
		    $currentUrlIndex / $totalUrls);

		list ($ret, $plugin) = GalleryCoreApi::loadPlugin($pluginType, $pluginId, true);
		if ($ret) {
		    $templateAdapter->errorProgressBar($ret);
		    return $ret;
		}

		$ret = $plugin->installOrUpgrade();
		if ($ret) {
		    $templateAdapter->errorProgressBar($ret);
		    return $ret;
		}

		if ($pluginType == 'module') {
		    list ($ret, $autoConfigured) = $plugin->autoConfigure();
		    if ($ret) {
			$templateAdapter->errorProgressBar($ret);
			return $ret;
		    }
		} else {
		    /* Themes don't need this step */
		    $autoConfigured = true;
		}

		if ($autoConfigured) {
		    list ($ret, $redirect) = $plugin->activate();
		    if ($ret) {
			$templateAdapter->errorProgressBar($ret);
			return $ret;
		    }
		    /* Ignore the redirect */
		}

		/*********************************************************/
	    }
	}

	/* Update progress bar. */
	$ret = $templateAdapter->updateProgressBar($titleText, $module->translate('Done.'), 1);
	if ($ret) {
	    $templateAdapter->errorProgressBar($ret);
	    return $ret;
	}

	/* Show link to return to the previously selected tab. */
	$redirect['view'] = 'core.SiteAdmin';
	$redirect['subView'] = 'core.AdminRepository';
	$urlGenerator =& $gallery->getUrlGenerator();
	$templateAdapter->completeProgressBar($urlGenerator->generateUrl($redirect));

	return null;
    }
}

/**
 * This view will show all repository-related features.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminRepositoryDownloadView extends GalleryView {

    /**
     * Repository.
     *
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

	$localIndexExists = $repository->localIndexExists();
	if (!$localIndexExists) {
	    /* Make sure the plugins directory is properly set up. */
	    list ($isSetUp, $errorMessage) = GalleryRepository::createPluginsDirectory();
	    if (!$isSetUp) {
		$platform =& $gallery->getPlatform();

		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminRepositorySetup';
		$template->setVariable('galleryBaseDirectory',
		    $platform->realpath(dirname(__FILE__) . '/../..'));
		$template->setVariable('errorMessage', $errorMessage);

		return array(null,
			     array('body' => 'modules/core/templates/AdminRepositorySetup.tpl'));
	    }
	}

	list ($pluginType, $pluginId) =
	    GalleryUtilities::getRequestVariables('pluginType', 'pluginId');

	/* Plugin download options. */
	if (!$repository->pluginExistsInIndex($pluginType, $pluginId)) {
	    return array(
		GalleryCoreApi::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
				      "Plugin not found in index [$pluginId] [$pluginType]"),
			 null);
	}

	/*
	 * Downloading and upgrading plugins are functionally equivalent,
	 * we just adapt the UI a little.
	 */
	list ($ret, $upgradeData) = $repository->getPluginUpgradeInfo($pluginType, $pluginId);
	if ($ret) {
	    return array($ret, null);
	}

	list ($ret, $pluginName) = $repository->getPluginName($pluginType, $pluginId);
	if ($ret) {
	    return array($ret, null);
	}

	$AdminRepositoryDownload = array(
	    'pluginName' => $pluginName,
	    'upgradeData' => $upgradeData,
	    'pluginId' => $pluginId,
	    'pluginType' => $pluginType);

	$template->setVariable('AdminRepositoryDownload', $AdminRepositoryDownload);
	$template->setVariable('controller', 'core.AdminRepositoryDownload');

	return array(null, array('body' => 'modules/core/templates/AdminRepositoryDownload.tpl'));
    }
}
?>

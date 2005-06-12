<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package Rewrite
 * @version $Revision$ $Date$
 * @author Douglas Cau <douglas@cau.se>
 */

/**
 * URL Rewrite Module
 *
 * This module provides mod_rewrite support
 *
 * @package Rewrite
 */
class RewriteModule extends GalleryModule {

    function RewriteModule() {
	global $gallery;
	$this->setId('rewrite');
	$this->setName($gallery->i18n('URL Rewrite'));
	$this->setDescription($gallery->i18n('Enables short URLs using mod_rewrite.'));
	$this->setVersion('0.9.11'); /* Update RewriteModuleExtras::upgrade also! */
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('getSiteAdminViews');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredModuleApi(array(1, 0));
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/RewriteModuleExtras.inc');
	$ret = RewriteModuleExtras::upgrade($this, $currentVersion);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
		'GalleryUrlGenerator', 'RewriteUrlGenerator', 'RewriteUrlGenerator',
		'modules/rewrite/classes/RewriteUrlGenerator.class', 'rewrite', null, 2);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
		'MaintenanceTask', 'RewriteCheckConflictTask', 'RewriteCheckConflictTask',
		'modules/rewrite/classes/RewriteCheckConflictTask.class', 'rewrite', null, 2);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();
	GalleryCoreApi::relativeRequireOnce('modules/rewrite/classes/RewriteHelper.class');

	if (strpos($urlGenerator->getCurrentUrlDir(true), 'install/index.php') !== false &&
		$gallery->getConfig('galleryBaseUrl')) {
	    /*
	     * We can't autoconfigure from installer in a multisite install because
	     * the current url is for the primary site, not the site being installed.
	     */
	    return array(GalleryStatus::success(), false);
	}
	$baseUrlComponents = parse_url(preg_replace('{(install|upgrade)/index\.php.*}', '',
						    $urlGenerator->getCurrentUrlDir(true)));
	$ret = $this->setParameter('galleryLocation', $baseUrlComponents['path']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $rewriteStatus) = RewriteHelper::checkModRewrite();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $fileStatus) = RewriteHelper::checkFile();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $rewriteStatus == REWRITE_STATUS_OK &&
		$fileStatus == REWRITE_STATUS_HTACCESS_READY);
    }

    /**
     * @see GalleryModule::needsConfiguration
     */
    function needsConfiguration() {
	/* Just try to autoConfigure; if it succeeds then we don't need configuration */
	list ($ret, $configured) = $this->autoConfigure();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), !$configured);
    }

    /**
     * @see GalleryModule::activate
     */
    function activate() {
	list ($ret, $redirect) = parent::activate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($redirect)) {
	    return array(GalleryStatus::success(), $redirect);
	}

	GalleryCoreApi::relativeRequireOnce('modules/rewrite/classes/RewriteHelper.class');
	GalleryCoreApi::relativeRequireOnce('modules/rewrite/classes/RewriteMap.class');

	list ($ret, $activeRules) = RewriteMap::getActiveRules();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($activeRules)) {
	    $activeRules = array('rewrite' => array(
				  array('pattern' => 'v/%path%',
					'match' => 'core.ShowItem'),
				  array('pattern' => 'd/%itemId%-%serialNumber%/%fileName%',
					'match' => 'core.DownloadItem')));

	    $ret = RewriteMap::setActiveRules($activeRules);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	list($ret, $code, $rewriteRules) = RewriteHelper::parseActiveRules($activeRules, $this);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($code != REWRITE_STATUS_OK) {
	    return array(GalleryStatus::error(ERROR_UNKNOWN, __FILE__, __LINE__), null);
	}

	list($ret, $code) = RewriteHelper::writeFile($rewriteRules);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($code != REWRITE_STATUS_OK) {
	    return array(GalleryStatus::error(ERROR_CONFIGURATION_REQUIRED, __FILE__, __LINE__),
		    null);
	}

	return array(GalleryStatus::success(), array());
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		    array(array('name' => $this->translate('URL Rewrite'),
			    'view' => 'rewrite.AdminRewrite')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	return 'rewrite.SetupRewrite';
    }

    /**
     * @see GalleryModule::getRewriteRules
     */
    function getRewriteRules() {
	$rules = array();

	$rule = array();
	$rule['comment'] = $this->translate('Show Item');
	$rule['match'] = array('view' => 'core.ShowItem');
	$rule['pattern'] = 'v/%path%';
	$rule['keywords'] = array(
	    'path' => array(
		'pattern' => '([^?]+)',
		'help' => $this->translate('Path to an item (eg, /album/image.jpg.html)')));
	$rules[] = $rule;

	$rule = array();
	$rule['comment'] = $this->translate('Download Item');
	$rule['match'] = array('view' => 'core.DownloadItem');
	$rule['pattern'] = 'd/%itemId%-%serialNumber%/%fileName%';
	$rule['keywords'] = array(
	    'serialNumber' => array(
		'pattern' => '([0-9]+)',
		'help' => $this->translate('Item version to download (original/sized/thumb)')),
	    'fileName' => array(
		'pattern' => '([^\/]+)',
		'help' => $this->translate('Item file name (eg, image.jpg)'),
		'ignore' => 1));
	$rules[] = $rule;

	$rule = array();
	$rule['comment'] = $this->translate('404 File Not Found');
	$rule['pattern'] = '%path%';
	$rule['queryString'] = array('view' => 'rewrite.FileNotFound');
	$rule['keywords'] = array(
	    'path' => array(
		'pattern' => '([^?]+)'));
	$rule['locked'] = 1;
	$rules[] = $rule;

	$rule = array();
	$rule['comment'] = $this->translate('Block hotlinked items');
	$rule['pattern'] = '.';
	$rule['locked'] = 1;
	$rule['flags'] = array('F');
	$rule['restrict'] = array('view' => 'core.DownloadItem');
	$rules[] = $rule;

	return $rules;
    }
}
?>

<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Perform all necessary initialization of the Gallery framework
 */
function GalleryInitFirstPass($params=array()) {
    global $gallery;

    ini_set('magic_quotes_runtime', 0);
    ini_set('magic_quotes_sybase', 0);

    /* Specify that when an assertion fails, we terminate right away. */
    assert_options(ASSERT_WARNING, 1);
    assert_options(ASSERT_BAIL, 1);

    /* Figure out the Gallery base directory here, from our filename. */
    $galleryBase = dirname(__FILE__) . '/';

    /* Load all the core Gallery classes */
    $classDir = dirname(__FILE__) . '/modules/core/classes/';
    require_once($classDir . 'GalleryCoreApi.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryConstants.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryStatus.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryUtilities.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryCapabilities.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryView.class');
    GalleryCoreApi::requireOnce($classDir . 'GalleryModule.class');

    if (strtolower(PHP_OS) == 'winnt') {
	GalleryCoreApi::requireOnce($classDir . 'GalleryPlatform/WinNtPlatform.class');
	$platform = new WinNtPlatform();
    } else {
	GalleryCoreApi::requireOnce($classDir . 'GalleryPlatform/UnixPlatform.class');
	$platform = new UnixPlatform();
    }

    $gallery->setPlatform($platform);
    $slash = $platform->getDirectorySeparator();

    if (isset($params['debug'])) {
	$gallery->setDebug($params['debug']);
    }

    /* Sanitize the data path */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if ($dataBase{strlen($dataBase)-1} != $slash) {
	$dataBase .= $slash;
	$gallery->setConfig('data.gallery.base', $dataBase);
    }

    /* Set our various data paths */
    $gallery->setConfig('data.gallery.cache', $dataBase . 'cache' . $slash);
    $gallery->setConfig('data.gallery.albums', $dataBase . 'albums' . $slash);
    $gallery->setConfig('data.gallery.locks', $dataBase . 'locks'. $slash);
    $gallery->setConfig('data.gallery.sessions', $dataBase . 'sessions' . $slash);
    $gallery->setConfig('data.gallery.tmp', $dataBase . 'tmp' . $slash);
    $gallery->setConfig('data.smarty.base', $dataBase . 'smarty' . $slash);
    $gallery->setConfig('data.smarty.templates_c',
	$dataBase . 'smarty' . $slash . 'templates_c' . $slash);
    $gallery->setConfig('data.gallery.plugins', $dataBase . 'plugins' . $slash);
    $gallery->setConfig('data.gallery.plugins_data', $dataBase . 'plugins_data' . $slash);
    $platform->_getUmask(); /* Init platform umask */

    /* Configure our url Generator */
    if (!isset($params['noDatabase'])) {
	list ($ret, $urlGenerator) = GalleryCoreApi::newFactoryInstance('GalleryUrlGenerator');
	/* Swallow ERROR_STORAGE_FAILURE, or automatic upgrading fails */
	if ($ret->isError() && !($ret->getErrorCode() & ERROR_STORAGE_FAILURE)) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    }
    if (!isset($urlGenerator)) {
	GalleryCoreApi::requireOnce($classDir . 'GalleryUrlGenerator.class');
	$urlGenerator = new GalleryUrlGenerator();
    }
    $urlGenerator->init(
	isset($params['embedUri']) ? $params['embedUri'] : null,
	isset($params['embedPath']) ? $params['embedPath'] : null,
	isset($params['relativeG2Path']) ? $params['relativeG2Path'] : null,
	isset($params['embedSessionString']) ? $params['embedSessionString'] : null);
    $gallery->setUrlGenerator($urlGenerator);

    /* Initialize our session */
    if (!isset($params['noDatabase'])) {
	if (isset($params['gallerySessionId'])) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/GallerySession.class');
	    GalleryUtilities::putRequestVariable(SESSION_ID_PARAMETER, $params['gallerySessionId']);
	}
	$ret = $gallery->initSession();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    }

    /* Initialize our translator */
    if (isset($params['activeLanguage'])) {
	GalleryCoreApi::requireOnce($classDir . 'GalleryTranslator.class');
	list ($language) = GalleryTranslator::getSupportedLanguageCode($params['activeLanguage']);
	$gallery->setActiveLanguageCode($language);
    }
    $ret = $gallery->initTranslator(isset($params['noDatabase']));
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return GalleryStatus::success();
}

function GalleryInitSecondPass() {
    global $gallery;

    $session =& $gallery->getSession();
    /*
     * Set our active user id.  Check to see if we have one in our session.  If
     * not, make us the anonymous user.  If we don't have a session, this will
     * initiate one for us.
     */
    $activeUserId = $session->get('core.id.activeUser');
    if (empty($activeUserId)) {
	/* No active user -- be anonymous */
	list ($ret, $activeUserId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    }

    list ($ret, $activeUser) = GalleryCoreApi::loadEntitiesById($activeUserId);
    if ($ret->isError()) {
	if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
	    /* Missing user -- be anonymous */
	    list ($ret, $activeUserId) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    list ($ret, $activeUser) = GalleryCoreApi::loadEntitiesById($activeUserId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	} else {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    }

    $gallery->setActiveUser($activeUser);

    return GalleryStatus::success();
}
?>

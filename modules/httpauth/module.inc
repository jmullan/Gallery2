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
 * HTTP Auth Module.  Get active user using HTTP authentication.
 * @package HttpAuth
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$ $Date$
 */
class HttpAuthModule extends GalleryModule {

    function HttpAuthModule() {
	global $gallery;

	$this->setId('httpauth');
	$this->setName($gallery->i18n('HTTP Auth'));
	$this->setVersion('0.3.0');
	$this->setDescription($gallery->i18n('Get active user using HTTP authentication'));
	$this->setGroup('authentication', $gallery->i18n('Authentication'));
	$this->setCallbacks('getSiteAdminViews|registerEventListeners');
	$this->setRequiredCoreApi(array(7, 10));
	$this->setRequiredModuleApi(array(3, 0));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	list ($ret, $params) = $this->fetchParameters();
	if ($ret) {
	    return $ret;
	}

	if (!empty($params['httpAuthPlugin'])) {
	    $ret = GalleryCoreApi::registerFactoryImplementation('GalleryAuthPlugin',
		'HttpAuthPlugin', 'HttpAuthPlugin',
		'modules/httpauth/classes/HttpAuthPlugin.class', $this->getId(), null);
	    if ($ret) {
		return $ret;
	    }
	}

	if (!empty($params['serverAuthPlugin'])) {
	    $ret = GalleryCoreApi::registerFactoryImplementation('GalleryAuthPlugin',
		'ServerAuthPlugin', 'ServerAuthPlugin',
		'modules/httpauth/classes/ServerAuthPlugin.class', $this->getId(), null);
	    if ($ret) {
		return $ret;
	    }
	}
    }

    /**
     * @see GalleryModule::registerEventListeners
     */
    function registerEventListeners() {
	if (is_callable(array('GalleryCoreApi', 'registerEventListener_NEW'))) {
	    return GalleryCoreApi::registerEventListener_NEW('Gallery::Error',
		'HttpAuthErrorEventListener', 'HttpAuthErrorEventListener',
		'modules/httpauth/classes/HttpAuthErrorEventListener.class', $this->getId());
	}

	GalleryCoreApi::requireOnce('modules/httpauth/classes/HttpAuthErrorEventListener.class');

	return GalleryCoreApi::registerEventListener('Gallery::Error',
	    new HttpAuthErrorEventListener());
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	switch ($currentVersion) {
	case null:
	    /* Initial install */

	    foreach (array('httpAuthPlugin' => true,
		    'authName' => 'Gallery',
		    'authtypePattern' => '//',
		    'usernamePattern' => '/^(.+\\\\)?([^\\\\@]+)(@.+)?$/',
		    'usernameReplace' => '$2') as $key => $value) {
		$ret = $this->setParameter($key, $value);
		if ($ret) {
		    return $ret;
		}
	    }

	case '0.1.0':
	    /* Added AuthFilterPlugin and RegexAuthFilterPlugin */

	case '0.1.1':
	    /* Updated to lighter event subsystem */

	case '0.2.0':
	    /* Introduced auth plugins */

	    list ($ret, $params) = $this->fetchParameters();
	    if ($ret) {
		return $ret;
	    }

	    if (isset($params['serverAuth'])) {
		$ret = $this->setParameter('serverAuthPlugin', $params['serverAuth']);
		if ($ret) {
		    return $ret;
		}

		$ret = $this->removeParameter('serverAuth');
		if ($ret) {
		    return $ret;
		}
	    }

	    if (isset($params['regexFilter'])) {
		$ret = $this->setParameter('regexAuthPlugin', $params['regexFilter']);
		if ($ret) {
		    return $ret;
		}

		$ret = $this->removeParameter('regexFilter');
		if ($ret) {
		    return $ret;
		}
	    }

	    if (isset($params['usernameReplacement'])) {
		$ret = $this->setParameter('usernameReplace', $params['usernameReplacement']);
		if ($ret) {
		    return $ret;
		}

		$ret = $this->removeParameter('usernameReplacement');
		if ($ret) {
		    return $ret;
		}
	    }

	case '0.2.1':
	    /* Some 2.2 API changes */

	case '0.3.0':
	    /* Simplified auth plugin system */

	case 'end of upgrade path':
	    break;

	default:
	    return GalleryStatus::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
		sprintf('Unknown module version %s', $currentVersion));
	}
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(null, array(array('name' => $this->getName(),
	    'view' => 'httpauth.HttpAuthSiteAdmin')));
    }
}
?>

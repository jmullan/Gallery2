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
 * WebDAV Module.  Mount Gallery on your desktop.
 * @package WebDav
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$
 */
class WebDavModule extends GalleryModule /* and GalleryEventListener */ {

    function WebDavModule() {
	global $gallery;

	$this->setId('webdav');
	$this->setName($gallery->i18n('WebDAV'));
	$this->setVersion('0.6.1'); /* Update upgrade() too */
	$this->setDescription($gallery->i18n('Mount Gallery on your desktop'));
	$this->setGroup('interfaces', $gallery->i18n('Remote Interfaces'));
	$this->setCallbacks('getItemLinks|registerEventListeners');
	$this->setRequiredCoreApi(array(7, 10));
	$this->setRequiredModuleApi(array(3, 3));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation('ItemAddPlugin',
	    'ItemAddWebDav', 'ItemAddWebDav',
	    'modules/webdav/ItemAddWebDav.inc', 'webdav', null);
	if ($ret) {
	    return $ret;
	}
    }

    /**
     * @see GalleryModule::registerEventListeners
     */
    function registerEventListeners() {
	$listener = new WebDavModule();
	return GalleryCoreApi::registerEventListener('Gallery::ActivatePlugin', $listener);
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	global $gallery;

	switch ($currentVersion) {
	case null:
	    /* Initial install */

	    /* Activate essential rewrite rules */
	    $ret = $this->_activateRewriteRules();
	    if ($ret) {
		return $ret;
	    }

	    break;

	case '0.0.3':
	    /* Add WebDavSiteAdmin and WebDavLockMap */

	case '0.0.4':
	    /* Add modules/webdav/webdav.php and WebDavUrlGenerator */

	case '0.0.5':
	    /* Add WebDavInitEventListener */

	case '0.0.6':
	    /* Add item link */

	case '0.2.0':
	    /*
	     * Activate essential short URL rules automatically
	     * Set HTTP response status on all errors
	     */

	case '0.3.0':
	    /*
	     * Eliminate WebDavUrlGenerator, WebDavInitEventListener and WebDavSiteAdmin
	     * Register WebDavActivatePluginEventListener
	     */

	case '0.4.0':
	    /*
	     * Move parsePath from WebDavHelper to WebDavRewriteHelper, to avoid loading
	     * WebDavHelper just to generate URLs
	     */

	case '0.4.1':
	    /* Add GalleryView::isControllerLike to WebDAV view */

	case '0.4.2':
	    /* Add support for the PHP CGI server API */

	case '0.6.0':
	    /* Remove view with WebDAV permission */
	    $ret = GalleryCoreApi::unregisterModulePermissions($this->getId());
	    if ($ret) {
		return $ret;
	    }

	case 'end of upgrade path':
	    break;

	default:
	    return GalleryCoreApi::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
		sprintf('Unknown module version %s', $currentVersion));
	}
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items, $wantsDetailedLinks, $permissions, $userId) {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();

	$links = array();
	$userAgent = GalleryUtilities::getServerVar('HTTP_USER_AGENT');
	foreach ($items as $item) {
	    if (!$item->getCanContainChildren() || empty($wantsDetailedLinks[$item->getId()])) {
		continue;
	    }

	    $url = $urlGenerator->generateUrl(
		array('controller' => 'webdav.WebDav', 'itemId' => $item->getId()),
		array('forceFullUrl' => true));
	    $link = array(
		'text' => $this->translate(array('text' => 'Mount with WebDAV')),
		'params' => array('view' => 'webdav.WebDavMount', 'itemId' => $item->getId()),
		'attrs' => 'style="behavior: url(#default#anchorClick)" folder="'. $url . '"');
	    if (strpos($userAgent, 'MSIE') !== false) {
		/*
		 * Mount with JavaScript only if using MSIE.  By default, dropdowns link to davmount
		 * resources.
		 */
		$link['script'] =
		    "this.style.behavior = 'url(#default#httpFolder)'; this.navigate('$url')";
	    }
	    if (strpos($userAgent, 'Konqueror') !== false) {
		/* Konqueror supports webdav:// URLs */
		$link['params'] =
		    array('controller' => 'webdav.WebDav', 'itemId' => $item->getId());
		$link['options'] =
		    array('protocol' => 'webdav');
	    }

	    $links[$item->getId()][] = $link;
	}

	return array(null, $links);
    }

    /**
     * @see GalleryModule::getRewriteRules
     */
    function getRewriteRules() {
	$rules = array();

	/* Rule 0: Use short URL because most WebDAV clients don't support query strings */
	$rules[0] = array(
	    'comment' => $this->translate('Access WebDAV'),
	    'help' => $this->translate(
		'Use short URL because most WebDAV clients don\'t support query strings.'
		. '  The Windows WebDAV client requires that you don\'t add a slash before the'
		. ' %path% variable.'),
	    'match' => array('controller' => 'webdav.WebDav'),
	    'pattern' => 'w%path%',
	    'keywords' => array(
		'path' => array(
		    'pattern' => '([^?]*)',
		    'function' => array('webdav', 'WebDavRewriteHelper', 'parsePath'),
		    'help' => $this->translate('Path to an item (eg. /album/image.jpg.html)'))));

	/* Rule 1: Give davmount resources correct extension */
	$rules[1] = array(
	    'comment' => $this->translate('Mount WebDAV'),
	    'help' => $this->translate(
		'Give davmount resources correct extension'),
	    'match' => array('view' => 'webdav.WebDavMount'),

	    /* TODO: How to work with the root album? */
	    'pattern' => 'v/%path%.davmount',
	    'keywords' => array(
		'path' => array(
		    'pattern' => '([^?]+)',
		    'function' => array('rewrite', 'RewriteSimpleHelper', 'parsePath'),
		    'help' => $this->translate('Path to an item (eg. /album/image.jpg.html)'))),
	    'onLoad' => array('rewrite', 'RewriteSimpleHelper', 'loadItemIdFromPath'));

	if (strstr(php_sapi_name(), 'cgi')) {
	    /* Rule 2: Redirect HTTP OPTIONS requests so DAV HTTP header can be set */
	    $rules[2] = array(
		'comment' => $this->translate('OPTIONS Requests'),
		'help' => $this->translate(
		    'Redirect HTTP OPTIONS requests so DAV HTTP header can be set'),

		/* Use trailing '/' to avoid 301 Moved Permanently */
		'match' => array('href' => 'modules/webdav/data/options/'),
		'conditions' => array(array('test' => 'REQUEST_METHOD',
					    'pattern' => 'OPTIONS')));
	}

	return $rules;
    }

    /**
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	$data = $event->getData();
	if ($data['pluginType'] != 'module' || $data['pluginId'] != 'rewrite') {
	    return array(null, null);
	}

	$ret = $this->_activateRewriteRules();
	if ($ret) {
	    return array($ret, null);
	}
    }

    function _activateRewriteRules() {
	list ($ret, $rewriteApi) = GalleryCoreApi::newFactoryInstance('RewriteApi');
	if ($ret) {
	    return $ret;
	}

	if (!empty($rewriteApi)) {
	    list ($ret, $success) = $rewriteApi->activateRewriteRulesForModule($this->getId());
	    if ($ret) {
		return $ret;
	    }
	}

	if (empty($rewriteApi) || empty($success)) {
	    /* TODO: Show configuration required or something like that */
	}

	return null;
    }
}
?>

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
 * WebDAV Module.  Mount Gallery with HTTP filesystem interface.
 * @package WebDav
 * @author Jack Bates <ms419@freezone.co.uk>
 * @version $Revision$ $Date$
 */
class WebDavModule extends GalleryModule {

    function WebDavModule() {
	global $gallery;

	$this->setId('webdav');
	$this->setName($gallery->i18n('WebDAV'));
	$this->setVersion('0.4.0');
	$this->setDescription($gallery->i18n('Mount Gallery with HTTP filesystem interface'));
	$this->setGroup('interfaces', $gallery->i18n('Remote Interfaces'));
	$this->setCallbacks('getItemLinks|registerEventListeners');
	$this->setRequiredCoreApi(array(7, 10));
	$this->setRequiredModuleApi(array(3, 0));
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
	GalleryCoreApi::requireOnce(
	    'modules/webdav/classes/WebDavActivatePluginEventListener.class');
	return GalleryCoreApi::registerEventListener(
	    'Gallery::ActivatePlugin', new WebDavActivatePluginEventListener());
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	switch ($currentVersion) {
	case null:
	    /* Initial install */

	    /* Activate essential short URL rules */
	    $ret = $this->activateRewriteRules();
	    if ($ret) {
		return $ret;
	    }

	case '0.0.3':
	    /* Added WebDavSiteAdmin and WebDavLockMap */

	case '0.0.4':
	    /* Added modules/webdav/webdav.php and WebDavUrlGenerator */

	case '0.0.5':
	    /* Added WebDavInitEventListener */

	case '0.0.6':
	    /* Added item link */

	case '0.2.0':
	    /*
	     * Activate essential short URL rules automatically
	     * Set HTTP response status on all errors
	     */

	case '0.3.0':
	    /*
	     * Eliminated WebDavUrlGenerator, WebDavInitEventListener and WebDavSiteAdmin
	     * Registered WebDavActivatePluginEventListener
	     */

	case '0.4.0':
	    /*
	     * Moved parsePath from WebDavHelper to WebDavRewriteHelper, to avoid loading
	     * WebDavHelper just to generate URLs
	     */
	    GalleryCoreApi::requireOnce('modules/rewrite/classes/RewriteHelper.class');
	    list ($ret, $rewriteParser) = RewriteHelper::getRewriteParser();
	    if ($ret) {
		return $ret;
	    }

	    list ($ret, $code, $errorId) = $rewriteParser->saveActiveRules(null, $this);
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

	$userAgent = GalleryUtilities::getServerVar('HTTP_USER_AGENT');
	if (strpos($userAgent, 'Konqueror') !== false) {

	    /* Copy URL generator to set protocol webdav:// */
	    $urlGenerator = $gallery->getUrlGenerator();
	    foreach (array(false, true) as $forceDirect) {
		$urlGenerator->_currentBaseHost[$forceDirect] = sprintf('%s://%s', 'webdav',
		    $urlGenerator->_host[$forceDirect]);
	    }
	}

	$links = array();
	foreach ($items as $item) {
	    if (!GalleryUtilities::isA($item, 'GalleryAlbumItem')) {
		continue;
	    }

	    $params = array('view' => 'webdav.WebDavMount', 'itemId' => $item->getId());
	    $url = $urlGenerator->generateUrl(
		array('controller' => 'webdav.WebDav', 'itemId' => $item->getId()),
		array('forceFullUrl' => true));
	    if (strpos($userAgent, 'Konqueror') !== false) {
		$params = array('href' => $url);
	    }

	    $link = array(
		'text' => $this->translate(
		    array('text' => 'Mount with WebDAV')),
		'params' => $params,
		'attrs' => 'style="behavior: url(#default#anchorClick)" folder="'. $url . '"');
	    if (strpos($userAgent, 'MSIE') !== false) {
		/*
		 * Mount with JavaScript only if using MSIE.  By default, dropdowns link to davmount
		 * resources.
		 */
		$link['script'] =
		    "this.style.behavior = 'url(#default#httpFolder)'; this.navigate('$url')";
	    }
	    $links[$item->getId()][] = $link;
	}

	return array(null, $links);
    }

    /**
     * @see GalleryModule::getRewriteRules
     */
    function getRewriteRules() {
	return array(
	    array(
		'comment' => $this->translate('Access WebDAV'),
		'help' => $this->translate(
		    'Use short URL because most WebDAV clients don\'t support query strings.  '
		    . 'The Windows WebDAV client requires that you don\'t add a slash before the '
		    . '%path% variable.'),
		'match' => array('controller' => 'webdav.WebDav'),
		'pattern' => 'w%path%',
		'keywords' => array(
		    'path' => array(
			'pattern' => '([^?]*)',
			'function' => array('webdav', 'WebDavRewriteHelper', 'parsePath'),
			'help' => $this->translate(
			    'Path to an item (eg. /album/image.jpg.html)')))),
	    array(
		'comment' => $this->translate('Mount WebDAV'),
		'help' => $this->translate('Give davmount resources correct extension'),
		'match' => array('view' => 'webdav.WebDavMount'),

		/* TODO How to work with the root album? */
		'pattern' => 'v/%path%\.davmount',
		'keywords' => array(
		    'path' => array(
			'pattern' => '([^?]+)',
			'function' => array('rewrite', 'RewriteSimpleHelper', 'parsePath'),
			'help' => $this->translate('Path to an item (eg. /album/image.jpg.html)'))),
		'onLoad' => array('rewrite', 'RewriteSimpleHelper', 'loadItemIdFromPath')));
    }

    /**
     * Activate essential short URL rules
     */
    function activateRewriteRules() {
	GalleryCoreApi::requireOnce('modules/rewrite/classes/RewriteHelper.class');
	list ($ret, $activeRules) =
	    GalleryCoreApi::getPluginParameter('module', 'rewrite', 'activeRules');
	if ($ret) {
	    return $ret;
	}

	$activeRules = unserialize($activeRules);
	$rules = $this->getRewriteRules();

	/* Most WebDAV clients don't support query strings */
	if (!isset($activeRules['webdav'][0])) {
	    $activeRules['webdav'][0] = $rules[0]['pattern'];
	}

	/* Give davmount resources correct extension */
	if (!isset($activeRules['webdav'][1])) {
	    $activeRules['webdav'][1] = $rules[1]['pattern'];
	}

	list ($ret, $rewriteParser) = RewriteHelper::getRewriteParser();
	if ($ret) {
	    return $ret;
	}

	list ($ret, $code, $errorId) = $rewriteParser->saveActiveRules($activeRules);
	if ($ret) {
	    return $ret;
	}
    }
}
?>

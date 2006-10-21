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
 * Dynamic album based on keyword search
 *
 * @package KeyAlbum
 * @author Alan Harder <alan.harder@sun.com>
 * @version $Revision$ $Date$
 */
class KeyAlbumModule extends GalleryModule {

    function KeyAlbumModule() {
	global $gallery;
	$this->setId('keyalbum');
	$this->setName($gallery->i18n('Keyword Albums'));
	$this->setDescription($gallery->i18n('Dynamic albums based on keyword search'));
	$this->setVersion('0.9.3');
	$this->setGroup('display', $gallery->i18n('Display'));
	$this->setCallbacks('getSiteAdminViews|getItemSummaries');
	$this->setRequiredCoreApi(array(7, 10));
	$this->setRequiredModuleApi(array(3, 2));
    }

    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'keyalbum');
	if ($ret) {
	    return $ret;
	}
	foreach (array('themeId' => '', 'orderBy' => '', 'orderDirection' => '',
		       'summaryLinks' => 'all', 'description' => '', 'split' => ';,')
		as $key => $value) {
	    if (!isset($params[$key])) {
		$this->setParameter($key, $value);
		if ($ret) {
		    return $ret;
		}
	    }
	}
	if (!isset($params['themeSettingsId'])) {
	    list ($ret, $entity) =
		GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryEntity');
	    $entity->create();
	    $ret = $entity->save(false);
	    if ($ret) {
		return $ret;
	    }
	    $ret = $this->setParameter('themeSettingsId', $entity->getId());
	    if ($ret) {
		return $ret;
	    }
	}
	if (!empty($currentVersion) && version_compare($currentVersion, '0.9.2', '<')) {
	    /* Format for keyword data changed; force refresh */
	    foreach (array('allKeywords.time', 'allKeywords.public.time') as $key) {
		$ret = $this->removeParameter($key);
		if ($ret) {
		    return $ret;
		}
	    }
	}

	return null;
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(null, array(array('name' => $this->translate('Keyword Albums'),
				       'view' => 'keyalbum.KeywordAlbumSiteAdmin')));
    }

    /**
     * @see GalleryModule::getItemSummaries
     */
    function getItemSummaries($items, $permissions, &$template) {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();

	list ($ret, $params) = $this->fetchParameters();
	if ($ret) {
	    return array($ret, null);
	}
	$mode = $params['summaryLinks'];
	if ($mode != 'all') {
	    $view = GalleryUtilities::getRequestVariables('view');
	    if ($mode == 'none' || ($mode == 'key' && $view != 'keyalbum.KeywordAlbum')
		    || ($mode == 'album' && $view != 'core.ShowItem')) {
		return array(null, array());
	    }
	}

	$summaries = array();
	$split = '/[' . $params['split'] . ']+/';
	$label = $this->translate('Keywords:');
	foreach ($items as $item) {
	    if ($item->getKeywords()) {
		$itemId = $item->getId();
		$summaries[$itemId] = $label;
		foreach (preg_split($split, $item->getKeywords()) as $keyword) {
		    $keyword = trim($keyword);
		    $summaries[$itemId] .= ' <a href="' . $urlGenerator->generateUrl(
			array('view' => 'keyalbum.KeywordAlbum', 'keyword' => $keyword,
			      'highlightId' => $itemId)) . '">' . $keyword . '</a>';
		}
	    }
	}
	return array(null, $summaries);
    }

    /**
     * @see GalleryModule::getRewriteRules
     */
    function getRewriteRules() {
	return array(
		array('comment' => $this->translate('Keyword Album'),
		      'match' => array('view' => 'keyalbum.KeywordAlbum'),
		      'pattern' => 'key/%keyword%',
		      'help' => $this->translate('Short URL for Keyword Albums'),
		      'keywords' => array(
			  'keyword' => array('pattern' => '([^?/]+)',
			      'help' => $this->translate('Keyword to use for dynamic album')))
		    ));
    }
}
?>

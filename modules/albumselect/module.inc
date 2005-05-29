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
 * @package AlbumSelect
 * @author Alan Harder <alan.harder@sun.com>
 * @author Jonas Forsberg <jonas@gargamel.nu> (Initial dTree integration)
 */

/**
 * The implementation of the AlbumSelect module
 *
 * @package AlbumSelect
 */
class AlbumSelectModule extends GalleryModule {

    function AlbumSelectModule() {
	global $gallery;
	$this->setId('albumselect');
	$this->setName($gallery->i18n('Album Select'));
	$this->setDescription(
	    $gallery->i18n('Jump directly to any album using a select box or tree view'));
	$this->setVersion('0.9.6');
	$this->setGroup('blocks', $this->translate('Blocks'));
	$this->setCallbacks('getSiteAdminViews|loadSystemContent|registerEventListeners');
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredModuleApi(array(0, 12));
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return false;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	$listener = new AlbumSelectModule();
	GalleryCoreApi::registerEventListener('Gallery::ViewableTreeChange', $listener);
	GalleryCoreApi::registerEventListener('GalleryEntity::save', $listener);
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'albumselect');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	foreach (array('show' => 1, 'type' => 'select', 'sort' => 'manual',
		       'treeLines' => 1, 'treeIcons' => 0, 'treeCookies' => 0,
		       'treeExpandCollapse' => 0, 'treeCloseSameLevel' => 0) as $key => $value) {
	    if (!isset($params[$key])) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    } else if ($key == 'sort' && ($params[$key] == 0 || $params[$key] == 1)) {
		/* v0.9.4 changed 'sort' param from 0/1 to manual/title */
		$value = ($params[$key] == 1) ? 'title' : 'manual';
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Album Select'),
				 'view' => 'albumselect.AlbumSelectSiteAdmin')));
    }

    /**
     * @see GalleryModule::loadSystemContent
     *
     * We always load the template data, but only show in systemContent if
     * the 'show' module param is set.  Otherwise, we assume that the user still
     * wants the tree, but has chosen to manually put it somewhere else on the
     * page (by editing the templates).
     */
    function loadSystemContent(&$template) {
	global $gallery;

	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'albumselect');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Try to load it from the cache */
	$cachePathInfo = array('type' => 'module-data',
			       'module' => 'albumselect',
			       'itemId' => $gallery->getActiveUserId());
	list ($treeList, $titles) = GalleryDataCache::getFromDisk($cachePathInfo);

	if (!isset($titles) || !isset($treeList)) {
	    list ($ret, $rootAlbumId) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $rootAlbum) = GalleryCoreApi::loadEntitiesById($rootAlbumId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $titles = array('root' => preg_replace('/\r\n/', ' ', $rootAlbum->getTitle()));
	    $treeList = array();

	    if ($params['sort'] != 'album') {
		list ($ret, $tree) = GalleryCoreApi::fetchAlbumTree();
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_PERMISSION_DENIED) {
			$tree = null;
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		if (empty($tree)) {
		    return array(GalleryStatus::success(), null);
		}

		list ($ret, $items) =
		    GalleryCoreApi::loadEntitiesById(GalleryUtilities::arrayKeysRecursive($tree));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		foreach ($items as $item) {
		    $title = $item->getTitle() ? $item->getTitle() : $item->getPathComponent();
		    $titles[$item->getId()] = preg_replace('/\r\n/', ' ', $title);
		}

		$sorter = ($params['sort'] == 'title') ? new AlbumSelectTreeSorter($titles) : null;
		$nodeId = 0;
		$this->_parseTree($tree, $treeList, $sorter, $nodeId);

	    } else {
		list ($ret, $canView) =
		    GalleryCoreApi::hasItemPermission($rootAlbumId, 'core.view');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if ($canView) {
		    $ret = $this->_buildTree($rootAlbum, $treeList, $titles, $nodeId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}
		if (empty($treeList)) {
		    return array(GalleryStatus::success(), null);
		}
	    }
	    GalleryDataCache::putToDisk($cachePathInfo,
					$dataToCache = array($treeList, $titles));
	}

	if ($params['type'] == 'tree') {
	    $template->style('modules/albumselect/dtree.css');
	    $template->javascript('modules/albumselect/dtree.js');
	}

	$tpl = ($params['type'] == 'tree') ? 'modules/albumselect/templates/AlbumTree.tpl'
					   : 'modules/albumselect/templates/AlbumSelect.tpl';
	$template->setVariable('AlbumSelectSystemContent',
	    array('tree' => $treeList,
		  'titles' => $titles,
		  'params' => $params,
		  'template' => $tpl));

	return array(GalleryStatus::success(), $params['show'] ? $tpl : null);
    }

    /**
     * Event handler for Gallery::ViewableTreeChange
     *
     * @see GalleryEventListener::handleEvent
     */
    function handleEvent($event) {
	if ($event->getEventName() == 'Gallery::ViewableTreeChange') {
	    GalleryDataCache::removeFromDisk(
		array('type' => 'module-data', 'module' => 'albumselect'));
	} else if ($event->getEventName() == 'GalleryEntity::save') {
	    $entity = $event->getEntity();
	    if ($entity->getEntityType() == 'GalleryAlbumItem'
		    && ($entity->getModifiedFlag('orderBy') & MEMBER_MODIFIED
			|| $entity->getModifiedFlag('orderDirection') & MEMBER_MODIFIED)) {
		list ($ret, $sort) = $this->getParameter('sort');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if ($sort == 'album') {
		    GalleryDataCache::removeFromDisk(
			array('type' => 'module-data', 'module' => 'albumselect'));
		}
	    }
	}

	return array(GalleryStatus::success(), null);
    }

    /**
     * Build template data for subalbum tree (manual and title sorting)
     * @private
     */
    function _parseTree($tree, &$treeList, &$sorter, &$nodeId, $parentNode=0, $depth=0) {
	if (isset($sorter)) {
	    uksort($tree, array($sorter, 'sort'));
	}
	foreach ($tree as $id => $list) {
	    $treeList[] = array('id' => $id, 'nodeId' => ++$nodeId,
				'parentNode' => $parentNode, 'depth' => $depth);
	    if (!empty($list)) {
		$this->_parseTree($list, $treeList, $sorter, $nodeId, $nodeId, $depth + 1);
	    }
	}
    }

    /**
     * Build template data for subalbum tree (apply sort preference of each album)
     * @return object GalleryStatus a status code
     * @private
     */
    function _buildTree($album, &$treeList, &$titles, &$nodeId, $parentNode=0, $depth=0) {
	list ($ret, $subAlbumIds) = GalleryCoreApi::fetchChildAlbumItemIds($album);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (!empty($subAlbumIds)) {
	    list ($ret, $subAlbums) = GalleryCoreApi::loadEntitiesById($subAlbumIds);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    foreach ($subAlbums as $subAlbum) {
		$treeList[] = array('id' => $subAlbum->getId(), 'nodeId' => ++$nodeId,
				    'parentNode' => $parentNode, 'depth' => $depth);
		$title = $subAlbum->getTitle() ? $subAlbum->getTitle()
					       : $subAlbum->getPathComponent();
		$titles[$subAlbum->getId()] = preg_replace('/\r\n/', ' ', $title);
		$ret = $this->_buildTree($subAlbum, $treeList, $titles,
					 $nodeId, $nodeId, $depth + 1);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}
	return GalleryStatus::success();
    }
}

/**
 * Sort albums on a specific field
 */
class AlbumSelectTreeSorter {
    var $_titles;
    function AlbumSelectTreeSorter(&$titles) {
	$this->_titles =& $titles;
    }
    function sort($a, $b) {
	return strcmp($this->_titles[$a], $this->_titles[$b]);
    }
}
?>

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
 * @version $Revision$ $Date$
 * @package ImageBlock
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * The implementation of the Image Block module
 *
 * @package ImageBlock
 */
class ImageBlockModule extends GalleryModule {

    function ImageBlockModule() {
	global $gallery;
	$this->setId('imageblock');
	$this->setName('ImageBlock');
	$this->setDescription($gallery->i18n('Random, Most Recent or Most Viewed Photo or Album'));
	$this->setVersion('0.8.2');
	$this->setGroup('blocks', $gallery->i18n('Blocks'));
	$this->setCallbacks('registerEventListeners|getSiteAdminViews|loadSystemContent');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::registerEventListeners()
     */
    function registerEventListeners() {
	require_once(dirname(__FILE__) . '/classes/ImageBlockHelper.class');
	GalleryCoreApi::registerEventListener('Gallery::ViewableTreeChange', new ImageBlockHelper());
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    foreach (array('blocks' => 'randomImage',
			   'show' => 'title|date|views' )
		     as $key => $value) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Random/Popular'),
				 'view' => 'imageblock:ImageBlockSiteAdmin')));
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	list ($ret, $block) = $this->_loadImageBlocks($template);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$tpl = array();
	if (strlen($block) > 0) {
	    $tpl = array('imageblock' => $block);
	}
	return array(GalleryStatus::success(), $tpl);
    }

    function _loadImageBlocks(&$template, $params = array('heading' => 1)) {
	global $gallery;
	require_once(dirname(__FILE__) . '/classes/ImageBlockHelper.class');

	list ($ret, $moduleParams) = GalleryCoreApi::fetchAllPluginParameters('module', 'imageblock');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$params = array_merge($moduleParams, $params);
	$param = array();
	foreach (explode('|', $params['blocks']) as $key) {
	    $param[$key] = 1;
	}
	$heading = isset($params['heading']);
	$parentId = isset($params['itemId']) ? $params['itemId'] : null;

	$blocks = array();
	if (isset($param['randomImage'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Random Image') : '',
				    'GalleryPhotoItem', IMAGE_BLOCK_RANDOM, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['recentImage'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Newest Image') : '',
				    'GalleryPhotoItem', IMAGE_BLOCK_RECENT, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['viewedImage'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Most Viewed Image') : '',
				    'GalleryPhotoItem', IMAGE_BLOCK_VIEWED, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['randomAlbum'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Random Album') : '',
				    'GalleryAlbumItem', IMAGE_BLOCK_RANDOM, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['recentAlbum'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Newest Album') : '',
				    'GalleryAlbumItem', IMAGE_BLOCK_RECENT, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['viewedAlbum'])) {
	    $ret = $this->_addBlock($blocks,
				    $heading ? $gallery->i18n('Most Viewed Album') : '',
				    'GalleryAlbumItem', IMAGE_BLOCK_VIEWED, $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['specificItem'])) {
	    $ret = $this->_addBlock($blocks, '', 'SpecificItem', '', $parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$show = array();
	foreach (explode('|', $params['show']) as $key) {
	    $show[$key] = 1;
	}
	$ImageBlockSystemContent['show'] = $show;

	$tpl = null;
	if (!empty($blocks)) {
	    $ImageBlockSystemContent['blocks'] = $blocks;
	    $template->setVariable('ImageBlockSystemContent', $ImageBlockSystemContent);
	    $tpl = 'modules/imageblock/templates/ImageBlock.tpl';
	}
	return array(GalleryStatus::success(), $tpl);
    }

    function _addBlock(&$blocks, $title, $itemType, $order, $parentId=null) {
	if ($itemType != 'SpecificItem' || !isset($parentId)) {

	    list ($ret, $data) = ImageBlockHelper::fetchViewableData($itemType, $order, $parentId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	} else {
	    // Image Block for a specific item..
	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($parentId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $data = array('id' => $item->getId(),
			  'creationTimestamp' => $item->getCreationTimestamp());
	    list ($ret, $data['viewCount']) = GalleryCoreApi::fetchItemViewCount($parentId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	if (isset($data)) {
	    $id = $data['id'];
	    list ($ret, $item) = GalleryCoreApi::loadEntitiesById($id);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $thumbnail) = GalleryCoreApi::fetchThumbnailsByItemIds(array($id));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $owner) = GalleryCoreApi::loadEntitiesById($item->getOwnerId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $data['title'] = $title;
	    $data['item'] = $item->getMemberData();
	    $data['owner'] = $owner->getMemberData();
	    if (isset($thumbnail[$id])) {
		$data['thumb'] = $thumbnail[$id]->getMemberData();
		$blocks[] = $data;
	    }
	}
	return GalleryStatus::success();
    }

}
?>

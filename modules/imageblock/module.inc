<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
	$this->setVersion('0.4');
    }

    /**
     * @see GalleryModule::init()
     */
    function init() {
	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;

	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__,__LINE__), false);
	}

	$installed = false;
	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/* Initial install */
		$installed = true;
	    }

	    foreach (array( 'version' => $this->getVersion(),
			    'blocks' => 'randomImage' )
		     as $key => $value) {
		$ret = $this->setModuleParameter($key, $value);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), false);
		}
	    }
	}

	return array(GalleryStatus::success(), $installed);
    }

    /**
     * @see GalleryModule::canBeAutoInstalled()
     */
    function canBeAutoInstalled() {
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
		     array(array('name' => $this->translate('Image Block'),
				 'view' => 'imageblock:ImageBlockSiteAdmin')));
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	require_once(dirname(__FILE__) . '/classes/ImageBlockHelper.class');

	list ($ret, $tmp) = $this->getModuleParameter('blocks');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$param = array();
	foreach (explode('|', $tmp) as $key) {
	    $param[$key] = 1;
	}

	$blocks = array();
	if (isset($param['randomImage'])) {
	    $ret = $this->_addBlock($blocks, 'Random Image',
				    'GalleryPhotoItem', IMAGE_BLOCK_RANDOM);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['recentImage'])) {
	    $ret = $this->_addBlock($blocks, 'Newest Image',
				    'GalleryPhotoItem', IMAGE_BLOCK_RECENT);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['viewedImage'])) {
	    $ret = $this->_addBlock($blocks, 'Most Viewed Image',
				    'GalleryPhotoItem', IMAGE_BLOCK_VIEWED);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['randomAlbum'])) {
	    $ret = $this->_addBlock($blocks, 'Random Album',
				    'GalleryAlbumItem', IMAGE_BLOCK_RANDOM);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['recentAlbum'])) {
	    $ret = $this->_addBlock($blocks, 'Newest Album',
				    'GalleryAlbumItem', IMAGE_BLOCK_RECENT);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}
	if (isset($param['viewedAlbum'])) {
	    $ret = $this->_addBlock($blocks, 'Most Viewed Album',
				    'GalleryAlbumItem', IMAGE_BLOCK_VIEWED);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$tpl = null;
	if (!empty($blocks)) {
	    $ImageBlockSystemContent['blocks'] = $blocks;
	    $template->setVariable('ImageBlockSystemContent', $ImageBlockSystemContent);
	    $tpl = 'modules/imageblock/templates/ImageBlock.tpl';
	}
	return array(GalleryStatus::success(), $tpl);
    }

    function _addBlock(&$blocks, $title, $itemType, $order) {
	list ($ret, $data) = ImageBlockHelper::fetchViewableData($itemType, $order);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
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

	    $data['title'] = $title;
	    $data['item'] = $item->getMemberData();
	    if (isset($thumbnail[$id])) {
		$data['thumb'] = $thumbnail[$id]->getMemberData();
		$blocks[] = $data;
	    }
	}
	return GalleryStatus::success();
    }

}
?>

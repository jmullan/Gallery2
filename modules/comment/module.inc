<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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
 * Comment Module
 *
 * This module provides support for adding comments to items
 *
 * @version $Id$
 * @package Comments
 * @author Bharat Mediratta <bharat@menalto.com>
 */
class CommentModule extends GalleryModule {

    function CommentModule() {
	$this->setName('comment');
	$this->setDescription('User Comments');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;
	
	$classDir = dirname(__FILE__) . '/classes/';
	$gallery->addRegistry('GalleryEntity.GalleryComment',
			      $classDir . 'GalleryComment.class');

	/* Register all comment permissions */
	$gallery->addRegistry('GalleryPermissionMap',
			      array('id' => 'comment.add',
				    'description' => 'Add comment',
				    'admin' => false),
			      array('id' => 'comment.edit',
				    'description' => 'Edit comment',
				    'admin' => false),
			      array('id' => 'comment.delete',
				    'description' => 'Delete comment',
				    'admin' => false),
			      array('id' => 'comment.viewIp',
				    'description' => 'View IP',
				    'admin' => false));
			      
	return parent::init();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($version != $this->getVersion()) {

	    /* The store requires configuration. */
	    list ($ret, $storage) = $gallery->getStorage();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $storage->configureStore('comment');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    if (empty($version)) {
		/*
		 * This is an initial install. Make sure that we have some
		 * reasonable defaults.
		 */
		foreach (array( /* XXX: nothing to set for now */ )
			 as $key => $value) {

		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }
		
	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	
	return GalleryStatus::success();
    }
	
    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items, $returnUrlParams) {
	global $gallery;

	if (!is_array($items)) {
	    $items = array($items);
	}

	/* XXX: Permission check "can the user add a comment to this item?" */
	$gallery->debug("XXX: Comment.getItemLinks should be checking perms");

	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	$links = array();
	foreach ($items as $item) {
	    $params['view'] = 'comment:AddComment';
	    $params['itemId'] = $item->getId();
	    $links[$item->getId()] =
		array('text' => $this->translate('add comment'),
		      'params' => $params);
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * Return module-specific summary content about the item
     *
     * @param object GalleryItem a target item
     * @param array key => value parameters provided by the
     *              parent view -- the module can augment or override these.
     * @return array object GalleryStatus a status code
     *               string HTML content
     */
    function getItemSummaries($items, $returnUrlParams) {
	global $gallery;

	if (!is_array($items)) {
	    $items = array($items);
	}

	/* XXX: Permission check "can the user add a comment to this item?" */
	$gallery->debug("XXX: Comment.getItemSummary should be checking perms");

	$ids = array();
	foreach ($items as $item) {
	    $ids[] = $item->getId();
	}

	list ($ret, $commentCounts) = $this->_fetchCommentCounts($ids);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$summaries = array();
	foreach ($items as $item) {
	    $message = array();
	    if (!empty($commentCounts[$item->getId()])) {
		$message['one'] = '%d comment';
		$message['many'] = '%d comments';
		$message['count'] = $commentCounts[$item->getId()];
		$message['arg1'] = $commentCounts[$item->getId()];
		$summaries[$item->getId()] = $this->translate($message);
	    }
	}

	return array(GalleryStatus::success(), $summaries);
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Comments'),
				 'view' => 'comment:AdminComments')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	global $gallery;

	return array(GalleryStatus::success(), 'comment:AdminComments');
    }

    /**
     * Return the number of comments associated with the given item id
     *
     * XXX: Can't move this into GalleryComment, as that class may not be
     * loaded when we want to use this method!
     *
     * @param array int GalleryItem ids
     * @return array object GalleryStatus a status code
     *               int a count
     * @access private
     */
    function _fetchCommentCounts($itemIds) {
	global $gallery;

	/* Check to see if we have a collision */
	$markers = GalleryUtilities::makeMarkers(sizeof($itemIds));
	list($ret, $searchResults) =
	    $gallery->search(array('select' => '[GalleryChildEntity::parentId], COUNT([GalleryComment::id])',
				   'where' => '[GalleryChildEntity::parentId] IN (' . $markers . ')',
				   'group-by' => '[GalleryChildEntity::parentId]'),
			     $itemIds);

	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$data = array();
	while ($result = $searchResults->nextResult()) {
	    $data[$result[0]] = $result[1];
	}

	return array(GalleryStatus::success(), $data);
    }
}
?>
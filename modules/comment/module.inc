<?php
/*
 * $RCSfile
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
 * Comment Module
 *
 * This module provides support for adding comments to items
 *
 * @version $Revision$ $Date$
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
	require_once($classDir . 'GalleryCommentHelper.class');

	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryComment',
					       'GalleryComment',
					       $classDir . 'GalleryComment.class');

	GalleryPermissionMap::registerPermission('comment.all',
						 $this->translate('[comment] All access'),
						 false);

	GalleryPermissionMap::registerPermission('comment.add',
						 $this->translate('[comment] Add comments'),
						 false);

	GalleryPermissionMap::registerPermission('comment.edit',
						 $this->translate('[comment] Edit comments'),
						 false);

	GalleryPermissionMap::registerPermission('comment.delete',
						 $this->translate('[comment] Delete comments'),
						 false);

	GalleryPermissionMap::registerPermission('comment.view',
						 $this->translate('[comment] View comments'),
						 false);

	GalleryPermissionMap::registerPermission('comment.viewIp',
						 $this->translate('[comment] View commenter\'s IP address'),
						 false);

	
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

	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	$links = array();
	foreach ($items as $item) {

	    list ($ret, $permissions) =
		GalleryItemHelper::getPermissions($item->getId(),
						  $gallery->getActiveUserId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['core.all']) ||
		isset($permissions['comment.all']) ||
		isset($permissions['comment.add'])) {
		$params['view'] = 'comment:AddComment';
		$params['itemId'] = $item->getId();
		$links[$item->getId()][] =
		    array('text' => $this->translate('add comment'),
			  'params' => $params);
	    }
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
     *               array (itemId => string HTML content)
     */
    function getItemSummaries($items, $returnUrlParams) {
	global $gallery;

	if (!is_array($items)) {
	    $items = array($items);
	}

	$ids = array();
	foreach ($items as $item) {
	    $ids[] = $item->getId();
	}

	list ($ret, $commentCounts) = GalleryCommentHelper::fetchCommentCounts($ids);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$summaries = array();
	foreach ($items as $item) {
	    $message = array();

	    list ($ret, $permissions) =
		GalleryItemHelper::getPermissions($item->getId(),
						  $gallery->getActiveUserId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['core.all']) ||
		isset($permissions['comment.all']) ||
		isset($permissions['comment.view'])) {
		if (!empty($commentCounts[$item->getId()])) {
		    $message['one'] = '%d comment';
		    $message['many'] = '%d comments';
		    $message['count'] = $commentCounts[$item->getId()];
		    $message['arg1'] = $commentCounts[$item->getId()];
		    $summaries[$item->getId()] = $this->translate($message);
		}
	    }
	}

	return array(GalleryStatus::success(), $summaries);
    }

    /**
     * Return module-specific summary content about the item
     *
     * @param object GalleryItem a target item
     * @param array key => value parameters provided by the
     *              parent view -- the module can augment or override these.
     * @return array object GalleryStatus a status code
     *               array (itemId => string HTML content)
     */
    function getItemDetails($item, $returnUrlParams) {
	global $gallery;

	list ($ret, $permissions) =
	    GalleryItemHelper::getPermissions($item->getId(),
					      $gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	if (!isset($permissions['core.all']) &&
	        !isset($permissions['comment.all']) &&
	        !isset($permissions['comment.view'])) {
	    return array(GalleryStatus::success(), null);
	}
	
	/* XXX: parameterize this */
	$viewMax = 3;

	list ($ret, $comments) =
	    GalleryCommentHelper::fetchComments($item->getId(), $viewMax, ORDER_DESCENDING);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $counts) =
	    GalleryCommentHelper::fetchCommentCounts(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$html = null;
	if (!empty($counts[$item->getId()])) {
	    $totalComments = $counts[$item->getId()];

	    /* Render the comments */
	    $this->_initTemplate(dirname(__FILE__) . '/templates');

	    $users = array();
	    $commentData = array();
	    foreach ($comments as $comment) {
		/* Extract the member data */
		$memberData = $comment->getMemberData();

		/* Associate the commenter's info */
		$commenterId = $memberData['commenterId'];
		if (empty($users[$commenterId])) {
		    list ($ret, $user) = $gallery->loadEntitiesById($commenterId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $users[$commenterId] = $user->getMemberData();
		}
		$memberData['commenter'] = $users[$commenterId];
		$commentData[] = $memberData;
	    }

	    /* Render the comments */
	    $this->_setTemplateVariable('comments', $commentData);
	    $this->_setTemplateVariable('item', $item->getMemberData());
	    $this->_setTemplateVariable('totalComments', $totalComments);
	    $html = $this->_renderTemplate('comment', 'ItemDetails.tpl');
	}

	return array(GalleryStatus::success(), $html);
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
}
?>
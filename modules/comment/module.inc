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
 * @package Comment
 * @version $Revision$ $Date$
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Comment Module
 *
 * This module provides support for adding comments to items
 *
 * @package Comment
 */
class CommentModule extends GalleryModule {

    function CommentModule() {
	$this->setName('comment');
	$this->setDescription('User Comments');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init()
     */
    function init() {
	global $gallery;

	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$classDir = dirname(__FILE__) . '/classes/';
	require_once($classDir . 'GalleryCommentHelper.class');

	GalleryFactory::registerImplementation('GalleryEntity',
					       'GalleryComment',
					       'GalleryComment',
					       $classDir . 'GalleryComment.class');

	/* Register our search implementation */
	GalleryFactory::registerImplementation('GallerySearchInterface_1_0',
					       'GalleryCommentSearch',
					       'comment',
					       $classDir . 'GalleryCommentSearch.class');
	
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($version != $this->getVersion()) {

	    /* The store requires configuration. */
	    $storage = $gallery->getStorage();
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

	    /* Register our permissions */
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.add',
							       $gallery->i18n('[comment] Add comments')); 
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.edit',
							       $gallery->i18n('[comment] Edit comments')); 
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.delete',
							       $gallery->i18n('[comment] Delete comments')); 
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.view',
							       $gallery->i18n('[comment] View comments'));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.all',
							       $gallery->i18n('[comment] All access'), 
							       GALLERY_PERMISSION_COMPOSITE,
							       array('comment.add',
								     'comment.edit',
								     'comment.delete',
								     'comment.view'));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
		
	    $ret = GalleryPermissionSetMap::registerPermission($this->getName(),
							       'comment.search',
							       $gallery->i18n('[comment] Search comments'),
							       GALLERY_PERMISSION_COMPOSITE,
							       array('core.view',
								     'comment.view'));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	
	return GalleryStatus::success();
    }
	
    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	global $gallery;

	$links = array();
	foreach ($items as $item) {

	    list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['comment.add'])) {
		$params['return'] = 'true';
		$params['view'] = 'core:ItemAdmin';
		$params['subView'] = 'comment:AddComment';
		$params['itemId'] = $item->getId();
		$links[$item->getId()][] =
		    array('text' => $this->translate('add comment'),
			  'params' => $params);
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::loadItemSummaries()
     */
    function getItemSummaries($items) {
	global $gallery;

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

	    list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['comment.view'])) {
		if (!empty($commentCounts[$item->getId()])) {
		    $summaries[$item->getId()] =
			$this->translate(array('one' => '%d comment',
					       'many' => '%d comments',
					       'count' => $commentCounts[$item->getId()],
					       'arg1' => $commentCounts[$item->getId()]));
		}
	    }
	}

	return array(GalleryStatus::success(), $summaries);
    }

    /**
     * @see GalleryModule::loadItemDetails()
     */
    function loadItemDetails(&$template, $item) {
	global $gallery;

	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	if (!isset($permissions['comment.view'])) {
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

	$commenters = array();
	if (isset($counts[$item->getId()])) {
	    $totalComments = $counts[$item->getId()];
	    
	    for ($i = 0; $i < sizeof($comments); $i++) {
		/* Get the commenter ids */
		$commenters[$comments[$i]->getCommenterId()] = 1;
			
		/* Extract the member data */
		$comments[$i] = $comments[$i]->getMemberData();
	    }

	    /* Load all the commenters */
	    if (sizeof($commenters) > 0) {
		list ($ret, $commentersList) = $gallery->loadEntitiesById(array_keys($commenters));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    foreach ($commentersList as $commenter) {
		$commenters[$commenter->getId()] = $commenter->getMemberData();
	    }
	} else {
	    $totalComments = 0;
	}

	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	foreach (array('delete' => 'comment.delete',
		       'edit' => 'comment.edit')
		 as $canFlag => $permission) {
	    $can[$canFlag] = isset($permissions[$permission]);
	}

	$CommentItemDetails = array();
	$CommentItemDetails['comments'] = $comments;
	$CommentItemDetails['commenters'] = $commenters;
	$CommentItemDetails['can'] = $can;
	$CommentItemDetails['item'] = $item->getMemberData();
	$CommentItemDetails['totalComments'] = $totalComments;
	$template->setVariable('CommentItemDetails', $CommentItemDetails);

	return array(GalleryStatus::success(), 'modules/comment/templates/CommentItemDetails.tpl');
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Comments'),
				 'view' => 'comment:AdminComments')));
    }

    /**
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	$views = array();
	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($permissions['comment.add'])) {
	        $views[] = array('name' => $this->translate('Add Comment'),
				 'view' => 'comment:AddComment');
	}

	if (isset($permissions['comment.edit']) ||
	    isset($permissions['comment.delete'])) {
	        $views[] = array('name' => $this->translate('View Comments'),
				 'view' => 'comment:ShowComments');
	}
	
	return array(GalleryStatus::success(), $views);
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	global $gallery;

	return array(GalleryStatus::success(), 'comment:AdminComments');
    }
}
?>
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
	global $gallery;

	$this->setId('comment');
	$this->setName('Comments');
	$this->setDescription($gallery->i18n('User commenting system'));
	$this->setVersion('0.9.1');
	$this->setGroup('data', $this->translate('Extra Data'));
	$this->setCallbacks('getItemLinks|getItemSummaries|' .
			    'loadItemDetails|getItemAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    /* Initial install.  Register our permissions */
	    $permissions[] = array('add', $gallery->i18n('[comment] Add comments'), 0, array());
	    $permissions[] = array('edit', $gallery->i18n('[comment] Edit comments'), 0, array());
	    $permissions[] = array('delete', $gallery->i18n('[comment] Delete comments'),
				   0, array());
	    $permissions[] = array('view', $gallery->i18n('[comment] View comments'), 0, array());
	    $permissions[] = array('all', $gallery->i18n('[comment] All access'),
		GALLERY_PERMISSION_COMPOSITE,
		array('comment.add', 'comment.edit', 'comment.delete', 'comment.view'));
	    $permissions[] = array('search', $gallery->i18n('[comment] Search comments'),
		GALLERY_PERMISSION_COMPOSITE,
		array('core.view', 'comment.view'));
	    foreach ($permissions as $p) {
		$ret = GalleryCoreApi::registerPermission($this->getId(),
							  'comment.' . $p[0],
							  $p[1], $p[2], $p[3]);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryEntity', 'GalleryComment', 'GalleryComment',
	    'modules/comment/classes/GalleryComment.class', 'comment', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GallerySearchInterface_1_0', 'GalleryCommentSearch', 'comment',
	    'modules/comment/classes/GalleryCommentSearch.class', 'comment', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items) {
	global $gallery;

	$links = array();
	foreach ($items as $item) {
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['comment.add'])) {
		$params['view'] = 'core:ItemAdmin';
		$params['subView'] = 'comment:AddComment';
		$params['itemId'] = $item->getId();
		$params['return'] = 1;
		$links[$item->getId()][] =
		    array('text' => $this->translate('add comment'),
			  'params' => $params);
	    }

	    if (isset($permissions['comment.view'])) {
		$params['view'] = 'core:ItemAdmin';
		$params['subView'] = 'comment:ShowComments';
		$params['itemId'] = $item->getId();
		$params['return'] = 1;
		$links[$item->getId()][] =
		    array('text' => $this->translate('view comment'),
			  'params' => $params);
	    }
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getItemSummaries()
     */
    function getItemSummaries($items) {
	global $gallery;

	$ids = array();
	foreach ($items as $item) {
	    $ids[] = $item->getId();
	}

	require_once(dirname(__FILE__) . '/classes/GalleryCommentHelper.class');
	list ($ret, $commentCounts) = GalleryCommentHelper::fetchCommentCounts($ids);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$summaries = array();
	foreach ($items as $item) {
	    $message = array();

	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($permissions['comment.view'])) {
		if (!empty($commentCounts[$item->getId()])) {
		    $summaries[$item->getId()] =
			$this->translate(array('text' => 'Comments: %d',
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

	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!isset($permissions['comment.view'])) {
	    return array(GalleryStatus::success(), null);
	}

	/* XXX: parameterize this */
	$viewMax = 3;

	require_once(dirname(__FILE__) . '/classes/GalleryCommentHelper.class');
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
		list ($ret, $commentersList) = GalleryCoreApi::loadEntitiesById(array_keys($commenters));
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

	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach (array('delete' => 'comment.delete',
		       'edit' => 'comment.edit',
		       'view' => 'comment.view')
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
     * @see GalleryModule::getItemAdminViews();
     */
    function getItemAdminViews($item) {
	$views = array();
	list ($ret, $permissions) = GalleryCoreApi::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($permissions['comment.add'])) {
		$views[] = array('name' => $this->translate('Add Comment'),
				 'view' => 'comment:AddComment');
	}

	if (isset($permissions['comment.edit']) ||
	    isset($permissions['comment.delete']) ||
	    isset($permissions['comment.view'])) {
		$views[] = array('name' => $this->translate('View Comments'),
				 'view' => 'comment:ShowComments');
	}

	return array(GalleryStatus::success(), $views);
    }
}
?>

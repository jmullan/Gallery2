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

class ShowCommentsView extends GalleryView {

    /**
     * @see GalleryView::renderHead
     */
    function renderHead() {
	global $gallery;

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Render the HTML head */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('item', $item->getMemberData());
	$html = $this->_renderTemplate('comment', 'ShowCommentsHead.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Find its thumbnail */
	list ($ret, $thumbnailTable) =
		GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($thumbnailTable)) {
	    $thumbnailData = null;
	} else {
	    $thumbnail = $thumbnailTable[$item->getId()];
	}

	list ($ret, $comments) =
	    GalleryCommentHelper::fetchComments($item->getId(), null, ORDER_ASCENDING);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$commentData = array();
	$users = array();
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

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');

	if (!empty($thumbnail)) {
	    $this->_setTemplateVariable('thumbnail', $thumbnail->getMemberData());
	}
	
	$return = GalleryUtilities::getFormVariables('return.');

	list ($ret, $permissions) =
	    GalleryItemHelper::getPermissions($item->getId(),
					      $gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($permissions['core.all']) ||
	        isset($permissions['comment.all'])) {
	    $can['all'] = true;
	} else {
	    $can['all'] = false;
	    foreach (array('add' => 'comment.add',
			   'delete' => 'comment.delete',
			   'edit' => 'comment.edit',
			   'viewIps' => 'comment.viewIps')
		     as $canFlag => $permission) {
		$can[$canFlag] = isset($permissions[$permission]);
	    }
	}

	$this->_setTemplateVariable('comments', $commentData);
	$this->_setTemplateVariable('can', $can);
	$this->_setTemplateVariable('return', $return);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$html = $this->_renderTemplate('comment', 'ShowComments.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

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
 * @package Comment
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This view will show the comments stored for an item
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class ShowCommentsView extends GalleryView {

    /**
     * @see GalleryView::renderHead()
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
	$template = $this->_getTemplate();
	$template->setVariable('item', $item->getMemberData());
	list($ret, $html) = $template->render('ShowCommentsHead.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), $html);
	}
    
	return array(GalleryStatus::success(), $html);
    }
    
    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
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
	$template = $this->_getTemplate();

	if (!empty($thumbnail)) {
	    $template->setVariable('thumbnail', $thumbnail->getMemberData());
	}
	
	$return = GalleryUtilities::getFormVariables('return.');

	list ($ret, $permissions) = GalleryItemHelper::getPermissions($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach (array('add' => 'comment.add',
		       'delete' => 'comment.delete',
		       'edit' => 'comment.edit',
		       'viewIp' => 'comment.viewIp')
		 as $canFlag => $permission) {
	    $can[$canFlag] = isset($permissions[$permission]);
	}

	$template->setVariable('comments', $commentData);
	$template->setVariable('can', $can);
	$template->setVariable('return', $return);
	$template->setVariable('item', $item->getMemberData());
	list($ret, $html) = $template->render('ShowComments.tpl');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), $html);
	}
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

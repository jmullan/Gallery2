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
 * @version $Revision$ $Date$
 * @package Comment
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the deletion of a comment
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class DeleteCommentController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest() {
	global $gallery;

	list ($itemId, $commentId) =
	    GalleryUtilities::getRequestVariables('itemId', 'commentId');
	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');

	/* Make sure we have permission to delete a comment */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'comment.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['delete'])) {
	    /* Delete the comment */
	    list ($ret, $comment) = $gallery->loadEntitiesById($commentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Make sure that the comment<->parent relationship is right */
	    if ($comment->getParentId() != $itemId) {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__));
	    }

	    $ret = $gallery->deleteEntityById($comment->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} 

	/* Redirect back to the item */
	$urlGenerator = $gallery->getUrlGenerator();
	$results['redirect'] = $urlGenerator->generateUrl($return);

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will ask for a confirmation to delete a comment
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class DeleteCommentView extends GalleryView {

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

	/* Render the HTML head */
	$template = $this->_getTemplate();
	$template->setVariable('item', $item->getMemberData());
	$html = $template->render('DeleteCommentHead.tpl');
	return array(GalleryStatus::success(), $html);
    }
    
    /**
     * @see GalleryView::renderBody()
     */
    function renderBody() {
	global $gallery;

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Make sure we have permission to delete a comment */
	$ret = GalleryUserHelper::assertHasItemPermission($item->getId(), 'comment.delete');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Get its thumbnail */
	list ($ret, $thumbnailTable) = 
		GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the specific comment */
	$commentId = GalleryUtilities::getRequestVariables('commentId');
	list ($ret, $comment) = $gallery->loadEntitiesById($commentId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Associate the commenter's info */
	$commenterId = $comment->getCommenterId();
	list ($ret, $commenter) = $gallery->loadEntitiesById($commenterId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	
	if (!empty($thumbnailTable)) {
	    $thumbnail = $thumbnailTable[$item->getId()];
	    $template->setVariable('thumbnail', $thumbnail->getMemberData());
	}
	
	$return = GalleryUtilities::getFormVariables('return.');

	$template->setVariable('return', $return);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('comment', $comment->getMemberData());
	$template->setVariable('commenter', $commenter->getMemberData());
	$template->setVariable('controller', 'comment:DeleteComment');
	$html = $template->render('DeleteComment.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

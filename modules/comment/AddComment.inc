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

class AddCommentController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;
	global $HTTP_SERVER_VARS;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');

	/* Make sure we have permission to add a comment */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all',
								'comment.all',
								'comment.add'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['add']) && !empty($form['comment'])) {
	    /* Add the comment */
	    list ($ret, $comment) = GalleryFactory::newInstance('GalleryEntity', 'GalleryComment');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $ret = $comment->create($itemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Sanitize the comment */
	    $form['comment'] = strip_tags($form['comment']);

	    $comment->setCommenterId($gallery->getActiveUserId());
	    $comment->setHost($HTTP_SERVER_VARS['REMOTE_ADDR']);
	    $comment->setComment($form['comment']);
	    $comment->setDate(time());

	    $ret = $comment->save();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} 

	/* Redirect back to the item */
	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($return);

	return array(GalleryStatus::success(), $results);
    }
}

class AddCommentView extends GalleryView {

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

	/* Render the HTML head */
	$template = $this->getTemplate();
	$html = $template->render('AddCommentHead.tpl');
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

	/* Make sure we have permission to add a comment */
	$ret = GalleryUserHelper::assertHasItemPermission($item->getId(),
							  $gallery->getActiveUserId(),
							  array('core.all',
								'comment.all',
								'comment.add'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Get its thumbnail */
	list ($ret, $thumbnailTable) = 
		GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Render the HTML body */
	$template = $this->getTemplate();
	
	if (!empty($thumbnailTable)) {
	    $thumbnail = $thumbnailTable[$item->getId()];
	    $template->setVariable('thumbnail', $thumbnail->getMemberData());
	}
	
	$return = GalleryUtilities::getFormVariables('return.');

	$template->setVariable('return', $return);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'comment:AddComment');
	$html = $template->render('AddComment.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

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

class AddCommentController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;
	global $HTTP_SERVER_VARS;

	$gallery->debug('XXX: check to make sure that the user can add this comment');

	list ($text, $itemId) = 
	    GalleryUtilities::getRequestVariables('comment', 'itemId');

	/* Add the comment */
	list ($ret, $comment) = $gallery->newEntity('GalleryComment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$ret = $comment->create($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$comment->setCommenterId($gallery->getActiveUserId());
	$comment->setHost($HTTP_SERVER_VARS['REMOTE_ADDR']);
	$comment->setComment($text);

	$ret = $comment->save();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out where to redirect upon success */
	$urlParams['view'] = 'core:ShowItem';
	$urlParams['itemId'] = $itemId;

	$templateAdapter = $gallery->getTemplateAdapter();
	$results['redirect'] = $templateAdapter->url($urlParams);

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

	/* Activate our theme */
	$this->_activateTheme($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Specify our translation module */
	$ret = $this->_setTranslationModule('comment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Render the HTML head */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AddCommentHead.tpl');
	
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

	/* Get its thumbnail */
	list ($ret, $thumbnailTable) = 
	    GalleryDerivative::loadDerivatives($item->getId(),
					       DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Activate our theme */
	$this->_activateTheme($item);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Specify our translation module */
	$ret = $this->_setTranslationModule('comment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Render the HTML body */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($thumbnailTable)) {
	    $smarty->assign('thumbnail', $thumbnailTable[$item->getId()][0]);
	}

	$smarty->assign('item', $item->getMemberData());
	$smarty->assign('controller', 'comment:AddComment');
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('AddCommentBody.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

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

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	/* Render the HTML head */
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$smarty->assign('item', $item->getMemberData());
	$html = $smarty->fetch('ShowCommentsHead.tpl');
	
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
	    GalleryDerivativeHelper::loadDerivatives($item->getId(),
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
	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($thumbnailTable)) {
	    $smarty->assign('thumbnail', $thumbnailTable[$item->getId()][0]);
	}
	
	$return = GalleryUtilities::getFormVariables('return.');

	$smarty->assign('comments', $commentData);
	$smarty->assign('return', $return);
	$smarty->assign('itemId', $item->getId());
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	$html = $smarty->fetch('ShowComments.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>

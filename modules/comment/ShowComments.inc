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
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/* Load our item */
	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $comments) =
	    GalleryCommentHelper::fetchComments($item->getId(), null, ORDER_ASCENDING);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$commenters = array();
	if (!empty($comments)) {
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

	$ShowComments = array();
	$ShowComments['comments'] = $comments;
	$ShowComments['commenters'] = $commenters;
	$ShowComments['can'] = $can;
	$template->setVariable('ShowComments', $ShowComments);

	/*
	 * We don't have a form, so don't need a controller, but ItemAdmin demands
	 * one so just leave it blank.
	 */
	$template->setVariable('controller', '');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/comment/templates/ShowComments.tpl'));
    }
}
?>

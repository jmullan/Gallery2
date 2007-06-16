<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * This view handles Ajax calls.
 * @package Comment
 * @author  Bharat Mediratta <bharat@menalto.com>
 * @version $Revision$
 */
class CommentCallbackView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::isControllerLike
     */
    function isControllerLike() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	global $gallery;

	$result = array();
	list ($command, $commentId) = GalleryUtilities::getRequestVariables('command', 'commentId');
	switch ($command) {
	case 'delete':
	    $commentId = (int)$commentId;
	    $ret = $this->deleteComment($commentId);
	    if ($ret) {
		$result['status'] = 'error';
		$storage =& $gallery->getStorage();
		$ret->putInSession();
	    } else {
		$result['status'] = 'success';
	    }
	}

	GalleryCoreApi::requireOnce('lib/JSON/JSON.php');
	$json = new Services_JSON();
	print $json->encode($result);
	return null;
    }

    /**
     * Delete the comment with the given id.
     * @param $id int the id
     */
    function deleteComment($commentId) {
	if (empty($commentId)) {
	    return GalleryCoreApi::error(ERROR_BAD_PARAMETER);
	}

	list ($ret, $comment) = GalleryCoreApi::loadEntitiesById($commentId, 'GalleryComment');
	if ($ret) {
	    return $ret;
	}

	$ret = GalleryCoreApi::assertHasItemPermission(
	    $comment->getParentId(), 'comment.delete');
	if ($ret) {
	    return $ret;
	}

	$ret = GalleryCoreApi::deleteEntityById($commentId, 'GalleryComment');
	if ($ret) {
	    return $ret;
	}
    }
}
?>

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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Comment
 * @subpackage UserInterface
 * @author Johannes Schmittat <Johannes@Schmittat.com>
 */

/**
 * This view will show all comments stored in the Gallery
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class ShowAllCommentsView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	GalleryCoreApi::relativeRequireOnce('modules/comment/classes/GalleryCommentHelper.class');

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$ret = GalleryCoreApi::assertHasItemPermission($item->getId(), 'comment.view');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $showCount) =
	    GalleryCoreApi::getPluginParameter('module', 'comment', 'comments.show');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $comments) = GalleryCommentHelper::fetchAllComments(
	    $item->getId(), $showCount, null, ORDER_DESCENDING);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$commenters = $itemIds = $can = $itemData = array();
	for ($i = 0; $i < count($comments); $i++) {
	    /* Get the commenter ids */
	    $commenters[$comments[$i]->getCommenterId()] = 1;
	    $itemIds[$comments[$i]->getParentId()] = 1;

	    /* Extract the member data */
	    $comments[$i] = $comments[$i]->getMemberData();
	}

	if (!empty($commenters)) {
	    list ($ret, $commentersList) =
		GalleryCoreApi::loadEntitiesById(array_keys($commenters));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($commentersList as $commenter) {
		$commenters[$commenter->getId()] = $commenter->getMemberData();
	    }
	}

	if (!empty($itemIds)) {
	    $itemIds = array_keys($itemIds);
	    $ret = GalleryCoreApi::studyPermissions($itemIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $itemList) = GalleryCoreApi::loadEntitiesById($itemIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($itemList as $it) {
		$items[$it->getId()] = $it->getMemberData();
	    }
	    list ($ret, $thumbnails) = GalleryCoreApi::fetchThumbnailsByItemIds($itemIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	foreach ($comments as $comment) {
	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($comment['parentId']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach (array('delete' => 'comment.delete',
			   'edit' => 'comment.edit') as $canFlag => $permission) {
		$can[$comment['id']][$canFlag] = isset($permissions[$permission]);
	    }

	    if (!isset($itemData[$comment['parentId']])) {
		$it = $items[$comment['parentId']];
		if (isset($thumbnails[$comment['parentId']])) {
		    $it['thumb'] = $thumbnails[$comment['parentId']]->getMemberData();
		}
		$itemData[$comment['parentId']] = $it;
	    }
	}

	$template->setVariable('ShowAllComments', array(
	    'comments' => $comments,
	    'commenters' => $commenters,
	    'can' => $can,
	    'item' => $item->getMemberData(),
	    'itemData' => $itemData));

	return array(GalleryStatus::success(),
		     array('body' => 'modules/comment/templates/ShowAllComments.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'comment');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('show comments'));
    }
}
?>

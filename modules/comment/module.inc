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

/**
 * Comment Module
 *
 * This module provides support for adding comments to items
 *
 * @version $Id$
 * @package Comments
 * @author Bharat Mediratta <bharat@menalto.com>
 */
class CommentModule extends GalleryModule {

    function CommentModule() {
	$this->setName('comment');
	$this->setDescription('User Comments');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init
     */
    function init() {
	global $gallery;
	
	$classDir = dirname(__FILE__) . '/classes/';
	$gallery->addRegistry('GalleryEntity.GalleryComment',
			      $classDir . 'GalleryComment.class');

	/* Register all comment permissions */
	$gallery->addRegistry('GalleryPermissionMap',
			      array('id' => 'comment.add', 'description' => 'Add comment'),
			      array('id' => 'comment.edit', 'description' => 'Edit comment'),
			      array('id' => 'comment.delete', 'description' => 'Delete comment'),
			      array('id' => 'comment.viewIp', 'description' => 'View IP'));
			      
	return parent::init();
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($item, $urlParams) {
	global $gallery;

	/* XXX: Permission check "can the user add a comment to this item?" */
	$gallery->debug("XXX: Comment.getItemLinks should be checking perms");

	return array(GalleryStatus::success(),
		     array(array('text' => $gallery->translate('add comment'),
				 'params' => array('view' => 'comment:AddComment',
						   'itemId' => $item->getId()))));
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $gallery->translate('Comments'),
				 'view' => 'comment:AdminComments')));
    }

    /**
     * @see GalleryModule::getConfigurationView
     */
    function getConfigurationView() {
	global $gallery;

	return array(GalleryStatus::success(), 'comment:AdminComments');
    }
    
}
?>
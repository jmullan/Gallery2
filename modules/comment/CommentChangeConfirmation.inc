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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Comment
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Confirm a change to a comment
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class CommentChangeConfirmationView extends GalleryView {

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

	if ($form['formName'] != 'CommentChangeConfirmation') {
	    $form['formName'] = 'CommentChangeConfirmation';
	}
	
	$CommentChangeConfirmation = array();
	
	$template->setVariable('CommentChangeConfirmation', $CommentChangeConfirmation);
	$template->setVariable('controller', 'comment:CommentChangeConfirmation');
	
	return array(GalleryStatus::success(),
		     array('body' => 'modules/comment/templates/CommentChangeConfirmation.tpl'));
    }
}
?>

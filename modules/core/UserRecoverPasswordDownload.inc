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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Jay Rossiter <cryptographite@users.sf.net>
 */

/**
 * This controller will handle the recovery of passwords that have
 * been lost or forgotten by the user.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
 
class UserRecoverPasswordDownloadView extends GalleryView {

    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	global $gallery;

	$session =& $gallery->getSession();

        $authString = $session->get('core.UserRecoverPasswordAdminAuthKey');

	if (empty($authString)) {
	    return GalleryStatus::error(ERROR_MISSING_VALUE, __FILE__, __LINE__, 
					'Authorization String Not Set');
	}

	header('Content-Type: text/plain');
	header('Content-Length: ' . strlen($authString));
	header('Content-Description: Download login.txt to your computer.');
	header('Content-Disposition: attachment; filename="login.txt"');
	print $authString;

	return GalleryStatus::success();
    }
}
?>

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
 * @package NokiaUpload
 * @author Jerome Rannikko <jeromer@hotpop.com>
 */

require_once('constants.inc'); // Error codes
require_once(dirname(__FILE__) . '/classes/LogFile.class');
require_once(dirname(__FILE__) . '/classes/ImageUploadApi.class');

/**
 * This controller implements the Nokia Image Uploader API's 'Retrieve Directory Listing' command.
 *
 * @package NokiaUpload
 */
class NewDirectoryController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest($form) {
	/* 
	 * We set the Content-length header in the view and that is not possible if
	 * anything gets sent before that so we need to buffer all (possible) output.
	 */
	ob_start();

	LogFile::mark('CreateAlbumController');
	LogFile::writeRequest();

	$results['status'] = ImageUploadApi::createNewDirectory();
	$results['delegate'] = array('view' => 'nokiaupload:NewDirectory');
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}


/**
 * This view implements the Nokia Image Uploader API's 'Retrieve Directory Listing' command.
 *
 * @package NokiaUpload
 */
class NewDirectoryView extends GalleryView {

    /**
     * @see GalleryView::renderImmediate()
     */
    function isImmediate() {
        return true;
    }


    /**
     * API defines the output very specifically so we can't allow any global 
     * templating to be used.
     *
     * @see GalleryView::renderImmediate()
     */
    function renderImmediate($status, $error) {
	LogFile::mark('NewDirectoryView');
	LogFile::write('$status = ' . print_r($status, true));

	if ($status['success'] == NOKIAUPLOAD_ERR_NOERR && !isset($status['id'])) {
		$status['success'] = NOKIAUPLOAD_ERR_UNKNOWN;
	}

	$reply = $status['success'] . "\r\n";

	if ($status['success'] == NOKIAUPLOAD_ERR_NOERR) {
	    $reply .= 'Did=' . $status['id'] . "\r\n";
	} else {
	    $reply .= "Album creation failed.\r\n";
	}

	LogFile::write("sending:\n$reply");

	/* stop output buffering. */
	ob_end_clean();

	header('Content-Length: '.strlen($reply));
	echo $reply;

	return GalleryStatus::success();
    }


}

?>

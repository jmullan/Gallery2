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
 * @package ZipCart
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This view sends the zip file and deletes the temp file.
 *
 * @package ZipCart
 */
class DownloadView extends GalleryView {

    /**
     * @see GalleryView::isImmediate()
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate()
     */
    function renderImmediate($status, $error) {
	global $gallery;
	$platform = $gallery->getPlatform();

	$file = GalleryUtilities::getRequestVariables('file');
	if (!empty($file)) {
	    $file = $gallery->getConfig('data.gallery.tmp') . $file;
	}

	if ($platform->is_readable($file)) {
	    $size = $platform->filesize($file);
	    $sendMultipart =
		(strpos(GalleryUtilities::getServerVar('HTTP_USER_AGENT'), 'MSIE ') === false);
	    if ($sendMultipart) {
		/* Send multipart reply: zip + html-to-reload */
		header('Content-Type: multipart/mixed; boundary=G2ZipCart');
		print "--G2ZipCart\nContent-Type: application/zip\n";
		print "Content-Disposition: inline; filename=\"G2cart.zip\"\n";

		if ($size > 0) {
		    print "Content-Length: " . $size . "\n";
		}
		print "\n";
	    } else {
		/* Poor IE6 doesn't know multipart.. just send zip */
		header('Content-Disposition: inline; filename="G2cart.zip"');
		if ($size > 0) {
		    header("Content-Length", $size);
		}
	    }

	    if ($fd = $platform->fopen($file, 'rb')) {
		while (true) {
		    $data = $platform->fread($fd, 65535);
		    if (strlen($data) == 0) {
			break;
		    }
		    print $data;
		    $gallery->guaranteeTimeLimit(30);
		}
		$platform->fclose($fd);
	    }

	    @$platform->unlink($file);
	    @$platform->unlink(substr($file, 0, -4));   /* Remove file created by tempnam() too */

	    if ($sendMultipart) {
		print "\n--G2ZipCart\nContent-type: text/html\nPragma: No-cache\n\n";
		print "<html><body onload=\"location.reload()\"></body></html>\n\n";
		print "--G2ZipCart--\n";
	    }
	} else {
	    /* On reload return to View Cart */
	    $urlGenerator =& $gallery->getUrlGenerator();
	    $url = $urlGenerator->generateUrl(array('view' => 'cart:ViewCart'));
	    header('Location: ' . str_replace('&amp;', '&', $url));
	}

	return GalleryStatus::success();
    }
}
?>

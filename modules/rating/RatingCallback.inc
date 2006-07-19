<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * @package Rating
 * @author  Don Seiler <don@seiler.us>
 */

/**
 * This view handles calls from the javascript (AJAX) side and returns
 * data to the javascript by printing results.
 *
 * @package Rating
 */
class RatingCallbackView extends GalleryView {

    /**
     * @see GalleryView::isImmediate()
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::isImmediate()
     */
    function renderImmediate($status, $error) {
	global $gallery;
	GalleryCoreApi::requireOnce('modules/rating/classes/RatingHelper.class');

	list ($command, $itemId, $rating) =
	    GalleryUtilities::getRequestVariables('command', 'itemId', 'rating');

	if (!headers_sent()) {
	    header("Content-type: text/plain; charset=UTF-8");
	}

	switch($command) {
	case 'rate':
	    list ($ret, $permission) = GalleryCoreApi::hasItemPermission($itemId, 'rating.add');
	    if ($ret) {
		return $ret;
	    }
	    if (!$permission) {
		return null;
	    }

	    list ($ret, $results) =
		RatingHelper::rateItem($itemId, (int)$rating, $gallery->getActiveUserId());
	    if ($ret) {
		return $ret;
	    }
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'rating');
	    if ($ret) {
		return $ret;
	    }
	    $results['votesString'] = 
		$module->translate(array('one' => '%d vote', 
					 'many' => '%d votes', 
					 'count' => $results['votes'], 
					 'arg1' => $results['votes']));

	    print $results['itemId'] . "\n"
		. $results['rating'] . "\n"
		. $results['votesString'] . "\n"
		. $results['userRating'];

	    break;
	}

	return null;
    }
}
?>

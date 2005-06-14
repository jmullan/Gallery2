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
 * @package ImageFrame
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Display CSS needed to render image frames.
 *
 * @package ImageFrame
 * @subpackage UserInterface
 */
class CSSView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	$frameList = GalleryUtilities::getRequestVariables('frames');
	if (empty($frameList)) {
	    return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), null);
	}
	$frameList = explode('|', $frameList);

	list ($ret, $imageframe) = GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!isset($imageframe)) {
	    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	}

	$ret = $imageframe->init($template, $frameList);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	header('Content-type: text/css');
	header('Expires: ' . GalleryUtilities::getHttpDate(time() + 2592000));
	return array(GalleryStatus::success(),
		     array('html' => 'modules/imageframe/templates/ImageFrameStyle.tpl'));
    }
}
?>

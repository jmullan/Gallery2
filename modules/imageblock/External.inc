<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package ImageBlock
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Render image block for use in external pages.
 *
 * @package ImageBlock
 * @subpackage UserInterface
 */
class ExternalView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate()
     */
    function loadTemplate(&$template, &$form) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ImageBlockHelper.class');
	global $gallery;
	$SlideShow = array();
	$startId = null;

	/* Force UrlGenerator to not add session id into urls.. */
	$session =& $gallery->getSession();
	$session->_isUsingCookies = true;

	$params = array();
	foreach (array('blocks', 'show', 'heading', 'itemId') as $key) {
	    $tmp = GalleryUtilities::getRequestVariables($key);
	    if (!empty($tmp)) {
		$params[$key] = $tmp;
	    }
	}

	list ($ret, $tpl) = ImageBlockHelper::loadImageBlocks($template, $params);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), array('html' => $tpl));
    }
}
?>

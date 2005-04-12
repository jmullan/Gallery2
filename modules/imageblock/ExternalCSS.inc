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
 * @package ImageBlock
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Generate CSS required if image frames are used with external image block.
 *
 * @package ImageBlock
 * @subpackage UserInterface
 */
class ExternalCSSView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate()
     */
    function loadTemplate(&$template, &$form) {
	$frameIds = GalleryUtilities::getRequestVariables('frames');
	if (!empty($frameIds)) {
	    $frameIds = explode('|', $frameIds);
	} else {
	    $frameIds = array();
	    foreach (array('albumFrame', 'itemFrame') as $key) {
		list ($ret, $frame) =
		    GalleryCoreApi::getPluginParameter('module', 'imageblock', $key);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if (!empty($frame)) {
		    $frameIds[] = $frame;
		}
	    }
	}

	list ($ret, $imageframe) = GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$tpl = 'modules/imageblock/templates/NoCSS.tpl';
	if (isset($imageframe) && !empty($frameIds)) {
	    $ret = $imageframe->init($template, $frameIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $head = $template->getVariable('head');
	    list ($tpl) = each($head['tpl']);
	}

	/* Force UrlGenerator to not add session id into urls.. */
	global $gallery;
	$session =& $gallery->getSession();
	$session->_isUsingCookies = true;

	return array(GalleryStatus::success(), array('html' => $tpl));
    }

    /**
     * @see GalleryView::getL10Domain()
     */
    function getL10Domain() {
	return 'modules_imageframe';
    }
}
?>

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

class ClassicTheme extends GalleryTheme {

    /**
     * @see GalleryTheme::themeStyle
     */
    function style($params) {
	$stylePath = dirname(__FILE__) . '/styles/style.css';
	$styleUrl = GalleryUtilities::convertPathToRelativeUrl($stylePath);

	return "<link rel=\"stylesheet\" type=\"text/css\" href=\"$styleUrl\">";
    }

    /**
     * Return the given content in a "happy" font color
     *
     * @param array key => value attributes
     * @param string content to go inside the block
     * @return HTML content
     */
    function successFontColor($params, $content) {
	return "<span class=\"gallery-success\">$content</span>";
    }

    /**
     * Return the given content in a "pay attention!" font color
     *
     * @param array key => value attributes
     * @param string content to go inside the block
     * @return HTML content
     */
    function warningFontColor($params, $content) {
	return "<span class=\"gallery-warning\">$content</span>";
    }

    /**
     * Return the given content in a "this is bad!" font color
     *
     * @param array key => value attributes
     * @param string content to go inside the block
     * @return HTML content
     */
    function errorFontColor($params, $content) {
	return "<span class=\"gallery-error\">$content</span>";
    }

    /**
     * @see GalleryTheme::lightFrame
     */
    function lightFrame($params, $content) {
	return "<table border=\"1\"><tr><td>$content</td></tr></table>";
    }

    /**
     * @see GalleryTheme::heavyFrame
     */
    function heavyFrame($params, $content) {
	return "<table border=\"5\"><tr><td>$content</td></tr></table>";
    }

    /**
     * @see GalleryTheme::threeDFrame
     */
    function threeDFrame($params, $content) {
	global $gallery;

	$baseUrl = GalleryUtilities::convertPathToRelativeUrl(dirname(__FILE__));
	$imagesUrl = $baseUrl . '/images';

	list ($ret, $smarty) = $gallery->getSmarty();
	if ($ret->isError()) {
	    return "Error getting smarty";
	}

	$smarty->assign('width', $params['width']);
	$smarty->assign('height', $params['height']);
	$smarty->assign('content', $content);
	$smarty->assign('imagesUrl', $imagesUrl);
	$smarty->template_dir = dirname(__FILE__) . '/templates';
	return $smarty->fetch('threeDFrame.tpl');
    }
    
}
?>

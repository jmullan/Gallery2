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
 * @package MatrixTheme
 * @author Bharat Mediratta <bharat@menalto.com>
 * @author Ross Reyman 
 */

/**
 * This theme (code named "Matrix") is based on the UI designed by Ross Reyman.  
 *
 * @package MatrixTheme
 */
class MatrixTheme extends GalleryTheme {

    function MatrixTheme() {
	$this->GalleryTheme(dirname(__FILE__));
    }
    
    /**
     * style theme method
     * @param array the template context
     * @return string HTML content
     */
    function style($context) {
	$themeCss = $this->getBaseUrl() . 'styles/theme.css';
	return '<style type="text/css" media="all">@import url(' . $themeCss . ');</style>';
    }

    /**
     * image theme method
     * @param array the template context
     * @return string HTML content
     */
    function image($context) {
 	global $gallery;
 	$urlGenerator = $gallery->getUrlGenerator();
 
 	$params = $context['params'];
 	$src = $urlGenerator->generateUrl(array('view' => 'core:DownloadItem',
 						'itemId' => $params['image']['id'],
						'serial' => $params['image']['serialNumber']));

	/* Shrink down images that we display in the sidebar */
 	if (in_array('sidebar', $context['stack'])) {
 	    list ($width, $height) =
 		GalleryUtilities::shrinkDimensionsToFit(140,
 							$params['image']['width'],
 							$params['image']['height']);
 	} else {
 	    list ($width, $height) = array($params['image']['width'],
 					   $params['image']['height']);
 	}
 
 	$title = $params['item']['title'];
 	if (empty($title)) {
 	    $title = $params['item']['pathComponent'];
 	}

	if (isset($params['image']['derivativeType'])) {
	    switch($params['image']['derivativeType']) {
	    case DERIVATIVE_TYPE_IMAGE_RESIZE:
		; // fall through
		
	    case DERIVATIVE_TYPE_IMAGE_PREFERRED:
		$imageClass = "fullsize_image";
		break;
		
	    case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
		$imageClass = "thumbnail_image";
		break;
	    }
	} else {
	    $imageClass = "fullsize_image";
	}

 	$result = sprintf('<img class="%s" src="%s" width="%s" height="%s" alt="%s" longdesc="%s">',
			  $imageClass,
 			  $src,
 			  $width,
 			  $height,
 			  $title,
 			  $params['item']['description']);
 	return $result;
    }

    /**
     * error theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function error($context, $content) {
	return '<p class="error">' . $content . '</p>';
    }

    /**
     * status theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function status($context, $content) {
	return '<span class="status">' . $content . '</span>';
    }

    /**
     * textmodifier theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function textmodifier($context, $content) {
	return '<span class="textmodifier">' . $content . '</span>';
    }

    /**
     * globalheader theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function globalheader($context, $content) {
	return '<table class="globalheader"> <tr> <td> ' . $content . ' </td> </tr> </table>';
    }

    /**
     * main theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => header content)
     * @param array optional ("params" => array, "content" => footer content)
     * @param array optional ("params" => array, "content" => pathbar content)
     * @param array optional (array("params" => array, "content" => sidebar content), ...)
     * @param array optional (array("params" => array, "content" => component content), ...)
     * @return string HTML content
     */
    function main($context, $header, $footer, $pathbar, $sidebar_array, $component_array) {
	$buf = '<table class="main"> ';

	// Header row
	if (!empty($header['content'])) {
	    $buf .= '<tr> <td class="header"> ' . $header['content'] . ' </td> </tr> ';
	}

	// Pathbar row
	if (!empty($pathbar['content'])) {
	    $buf .= '<tr> <td class="pathbar" colspan="2"> ' . $pathbar['content'] . ' </td> </tr> ';
	}

	// Begin center row
	$buf .= '<tr> ';

	// First sidebar (that isn't marked for the right side) goes on the left
	for ($i = 0; $i < sizeof($sidebar_array); $i++) {
	    if ($sidebar_array[$i]['params']['side'] != 'right') {
		$buf .= '<td class="sidebar_left"> ' . $sidebar_array[$i]['content'] . ' </td>';
		array_splice($sidebar_array, $i, 1);
	    }
	}

	// Center body 
	$buf .= '<td class="main_inner"> <table class="main_inner">';
	for ($i = 0; $i < sizeof($component_array); $i++) {
	    $buf .= '<tr> <td class="main_box"> ' . $component_array[$i]['content'] . '</td> </tr>';
	}
	$buf .= '</table> </td>';

	// Remaining sidebars go on the right
	for ($i = 0; $i < sizeof($sidebar_array); $i++) {
	    $buf .= '<td class="sidebar_right"> ' . $sidebar_array[$i]['content'] . ' </td>';
	}

	// End center row
	$buf .= '</tr>';

	// Footer row
	if (!empty($footer['content'])) {
	    $buf .= '<tr> <td class="footer"> ' . $footer['content'] . ' </td> </tr> ';
	}

	$buf .= '</table>';
	return $buf;
    }

    /**
     * globalfooter theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function globalfooter($context, $content) {
	return '<table class="globalfooter"> <tr> <td> <p> ' . $content . ' </p> </td> </tr> </table>';
    }

    /**
     * header theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function header($context, $content) {
	return $content;
    }

    /**
     * footer theme method
     * @param array the template context
     * @param string optional content
     * @return string HTML content
     */
    function footer($context, $content) {
        trigger_error("Undefined theme function: footer", E_USER_ERROR);
    }

    /**
     * pathbar theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => item content), ...)
     * @return string HTML content
     */
    function pathbar($context, $item_array) {
	$buf = '<table class="pathbar_inner"> <tr> ';
	for ($i = 0; $i < sizeof($item_array); $i++) {
	    $buf .= '<td class="pathbar_item">' . $item_array[$i]['content'] . '</td>';
	    if ($i < sizeof($item_array)-1) {
		$buf .= '<td class="pathbar_item"> &raquo; </td>';
	    }
	}
	$buf .= ' </tr> </table>';
	return $buf;
    }

    /**
     * sidebar theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => component content), ...)
     * @return string HTML content
     */
    function sidebar($context, $component_array) {
	$buf = '<table class="sidebar">';
	if ($context['params']['side'] == 'right') {
	    $class="sidebar_box_right";
	} else {
	    $class="sidebar_box_left";
	}
	foreach ($component_array as $component) {
	    $buf .= '<tr> <td class="' . $class . '"> ' . $component['content'] . ' </td> </tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * bannerbox theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array optional ("params" => array, "content" => description content)
     * @param array optional (array("params" => array, "content" => component content), ...)
     * @return string HTML content
     */
    function bannerbox($context, $title, $description, $component_array) {
	$buf = '<table class="bannerbox">';
	if (empty($component_array)) {
	    if (!empty($title['content'])) {
		$buf .= '<tr> <td class="bannerbox_title"> ' . $title['content'] . ' </td> </tr>';
	    }

	    if (!empty($description['content'])) {
		$buf .= '<tr> <td class="bannerbox_description"> ' . $description['content'] . ' </td> </tr>';
	    }
	} else {
	    $buf .= '<tr>';
	    if (!empty($title['content']) || !empty($description['content'])) {
		$buf .= '<td valign="top"> <table class="bannerbox_inner">';
		if (!empty($title['content'])) {
		    $buf .= '<tr> <td class="bannerbox_title"> ' . $title['content'] . ' </td> </tr>';
		}

		if (!empty($description['content'])) {
		    $buf .= '<tr> <td class="bannerbox_description"> ' . $description['content'] . ' </td> </tr>';
		}
		$buf .= '</table> </td>';
	    }

	    foreach ($component_array as $component) {
		$buf .= '<td class="bannerbox_component">' . $component['content'] . '</td>';
	    }
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * linksbox theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => item content), ...)
     * @return string HTML content
     */
    function linksbox($context, $item_array) {
	$buf = '<span class="linksbox"> ';
	for ($i = 0; $i < sizeof($item_array); $i++) {
	    if ($i > 0) {
		$buf .= ' | ';
	    }
	    $buf .= $item_array[$i]['content'];
	}
	$buf .= '</span>';
	return $buf;
    }

    /**
     * infobox theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => item content), ...)
     * @return string HTML content
     */
    function infobox($context, $item_array) {
	$buf .= '<table class="infobox"> ';
	foreach ($item_array as $item) {
	    $buf .= '<tr> <td class="infobox_item"> ' . $item['content'] . '</td> </tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * listingbox theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory (array("params" => array, "content" => item content), ...)
     * @return string HTML content
     */
    function listingbox($context, $title, $item_array) {
	$buf = '<table class="listingbox"> ';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="listingbox_title"> ' . $title['content'] . '</td> </tr>';
	}
	$buf .= '<tr> <td> <ul class="listingbox_list">';
	foreach ($item_array as $item) {
	    if ($item['params']['selected'] == 'true') {
		$buf .= '<li class="listingbox_selecteditem"> ' . $item['content'];
	    } else {
		$buf .= '<li class="listingbox_item"> ' . $item['content'];
	    }
	}
	$buf .= '</ul> </td> </tr> </table>';
	return $buf;
    }

    /**
     * imagebox theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array optional ("params" => array, "content" => description content)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function imagebox($context, $title, $description, $body) {
	$buf = '<table class="imagebox"> ';
	$buf .= '<tr> <td> ' . $body['content'] . '</td> </tr>';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="imagebox_title"> ' . $title['content'] . '</td> </tr> ';
	}

	if (!empty($description['content'])) {
	    $buf .= '<tr> <td class="imagebox_description"> ' . $description['content'] . '</td> </tr> ';
	}

	$buf .= ' </table>';

	return $buf;
    }

    /**
     * detailedbox theme method
     * @param array the template context
     * @param array mandatory ("params" => array, "content" => title content)
     * @param array mandatory ("params" => array, "content" => description content)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function detailedbox($context, $title, $description, $body) {
	$buf = '<table class="detailedbox"> ';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="detailedbox_title"> ' . $title['content'] . '</td> </tr> ';
	}

	if (!empty($description['content'])) {
	    $buf .= '<tr> <td class="detailedbox_description"> ' . $description['content'] . '</td> </tr> ';
	}

	$buf .= '<tr> <td> ' . $body['content'] . '</td> </tr> </table>';
	return $buf;
    }

    /**
     * tabbedbox theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory (array("params" => array, "content" => item content), ...)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function tabbedbox($context, $title, $item_array, $body) {
	$buf = '<table class="tabbedbox">';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="tabbedbox_title"> ' . $title['content'] . '</td> </tr> ';
	}

	$buf .= '<tr> <td class="tabbedbox_tabset"> <table class="tabbedbox_tabset_inner"> <tr>';
	foreach ($item_array as $item) {
	    if ($item['params']['selected'] == 'true') {
		$buf .= '<td class="tabbedbox_tab">' . $item['content'] . '</td>';
	    } else {
		$buf .= '<td class="tabbedbox_selectedtab">' . $item['content'] . '</td>';
	    }
	}
	$buf .= '</tr> </table> </td> </tr>';

	$buf .= '<tr> <td class="tabbedbox_body"> ' . $body['content'] . '</td> </tr> ';
	$buf .= '</table>';
	return $buf;
    }

    /**
     * simplebox theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function simplebox($context, $title, $body) {
	$buf = '<table class="simplebox">';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="simplebox_title"> ' . $title['content'] . '</td> </tr> ';
	}

	$buf .= '<tr> <td class="simplebox_body"> ' . $body['content'] . '</td> </tr> ';
	$buf .= '</table>';
	return $buf;
    }

    /**
     * widget1box theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory (array("params" => array, "content" => widget1 content), ...)
     * @return string HTML content
     */
    function widget1box($context, $title, $widget1_array) {
	$buf = '<table class="widget1box"> ';

	if (!empty($title['content'])) {
	    $buf .= '<tr> <td> ' . $title['content'] . ' </td> </tr> ';
	}
	
	for ($i = 0; $i < sizeof($widget1_array); $i++) {
	    $buf .= $widget1_array[$i]['content'];
	}
	$buf .= ' </table>';
	return $buf;
    }

    /**
     * widget2box theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory (array("params" => array, "content" => widget2 content), ...)
     * @return string HTML content
     */
    function widget2box($context, $title, $widget2_array) {
	$buf = '<table class="widget2box"> <tr> <td> ' . $title['content'] . ' </td> </tr> ';
	for ($i = 0; $i < sizeof($widget2_array); $i++) {
	    $buf .= $widget2_array[$i]['content'];
	}
	$buf .= ' </table>';
	return $buf;
    }

    /**
     * widget1 theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function widget1($context, $title, $body) {
	return '<tr> <td class="widget1_title"> ' . $title['content'] . '</td> ' .
	    '<td class="widget1_body"> ' . $body['content'] . '</td> </tr>';
    }

    /**
     * widget2 theme method
     * @param array the template context
     * @param array optional ("params" => array, "content" => title content)
     * @param array optional ("params" => array, "content" => description content)
     * @param array mandatory ("params" => array, "content" => body content)
     * @return string HTML content
     */
    function widget2($context, $title, $description, $body) {
	$buf = '';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="widget2_title"> ' . $title['content'] . ' </td> </tr> ';
	}
	
	if (!empty($description['content'])) {
	    $buf .= '<tr> <td class="widget2_description"> ' . $description['content'] . ' </td> </tr> ';
	}

	$buf .= '<tr> <td class="widget2_body"> ' . $body['content'] . ' </td> </tr>';
	return $buf;
    }

    /**
     * table theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => row content), ...)
     * @return string HTML content
     */
    function table($context, $row_array) {
	$buf = '<table class="table">';
	for ($i = 0; $i < sizeof($row_array); $i++) {
	    $buf .= $row_array[$i]['content'];
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * row theme method
     * @param array the template context
     * @param array mandatory (array("params" => array, "content" => column content), ...)
     * @return string HTML content
     */
    function row($context, $column_array) {
	$buf = '<tr>';
	for ($i = 0; $i < sizeof($column_array); $i++) {
	    $attrs = "";
	    foreach (array('width', 'colspan', 'rowspan', 'valign') as $attrName) {
		if ($column_array[$i]['params'][$attrName]) {
		    $attrs .= ' ' . $attrName . ' ="' . $column_array[$i]['params'][$attrName] . '"';
		}
	    }
	    
	    if ($column_array[$i]['params']['header'] == 'true') {
		$buf .= '<td class="columnheader" ' . $attrs . '>' . $column_array[$i]['content'] . '</td>';
	    } else {
		$buf .= '<td class="column" ' . $attrs . '>';
		$buf .= $column_array[$i]['content'] . '</td>';
	    }
	}
	$buf .= '</tr>';
	return $buf;
    }
}
?>

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
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param string HTML content 
     * @return string HTML content
     */
    function style($context) {
	$themeCss = $this->getBaseUrl() . 'styles/theme.css';
	return '<style type="text/css" media="all">@import url(' . $themeCss . ');</style>';
    }

    /**
     * success theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param string HTML content 
     * @return string HTML content
     */
    function success($context, $content) {
	return '<span class="success">' . $content . '</span>';
    }

    /**
     * warning theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param string HTML content 
     * @return string HTML content
     */
    function warning($context, $content) {
	return '<span class="warning">' . $content . '</span>';
    }

    /**
     * error theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param string HTML content 
     * @return string HTML content
     */
    function error($context, $content) {
	return '<p class="error">' . $content . '</p>';
    }

    /**
     * image theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @return string HTML content
     */
    function image($context) {
	$class = "image";
	
	/* Shrink down images that we display in the sidebar */
	if (in_array('sidebar', $context['stack'])) {
	    return parent::image($context, $class, 140);
	} else {
	    /* Else just display them normally */
	    return parent::image($context, $class);
	}
    }

    /**
     * listing theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => item HTML content)
     * @return string HTML content
     */
    function listing($context, $item_array) {
	$buf = '<table class="listing"> ';
	$buf .= '<tr> <td> <ul class="listing_list">';
	foreach ($item_array as $item) {
	    if ($item['params']['selected'] == 'true') {
		$buf .= '<li class="listing_selecteditem"> ' . $item['content'];
	    } else {
		$buf .= '<li class="listing_item"> ' . $item['content'];
	    }
	}
	$buf .= '</ul> </td> </tr> </table>';
	return $buf;
    }

    /**
     * breadcrumb theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => item HTML content)
     * @return string HTML content
     */
    function breadcrumb($context, $item_array) {
	$buf = '<table class="breadcrumb_inner"> <tr> ';
	for ($i = 0; $i < sizeof($item_array); $i++) {
	    $buf .= '<td class="breadcrumb_item">' . $item_array[$i]['content'] . '</td>';
	    if ($i < sizeof($item_array)-1) {
		$buf .= '<td class="breadcrumb_item"> &raquo; </td>';
	    }
	}
	$buf .= ' </tr> </table>';
	return $buf;
    }

    /**
     * linkset theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => item HTML content)
     * @return string HTML content
     */
    function linkset($context, $title, $item_array) {
	$buf = '<span class="linksbox"> ';
	if (!empty($title['content'])) {
	    $buf .= $title['content'];
	    $buf .= '&nbsp;';
	}
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
     * actionset theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => actionitem HTML content)
     * @return string HTML content
     */
    function actionset($context, $title, $actionitem_array) {
	$buf = '';
	if (!empty($title['content'])) {
	    $buf .= '<span class="actionset_title">' . $title['content'] . '</span>';
	}

	// TODO: How about having this call GalleryTheme::select, instead?
	$buf .= '<select onChange="if (this.value) javascript:location.href=this.value">';
	foreach ($actionitem_array as $actionitem) {
	    $buf .= $actionitem['content'];
	}
	$buf .= '</select>';
	return $buf;
    }

    /**
     * infoset theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => item HTML content)
     * @return string HTML content
     */
    function infoset($context, $item_array) {
	$buf = '<table class="infoset"> ';
	foreach ($item_array as $item) {
	    $buf .= '<tr> <td class="infoset_item"> ' . $item['content'] . '</td> </tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * tabset theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => item HTML content)
     * @return string HTML content
     */
    function tabset($context, $item_array) {
	$imageUrl = $this->getBaseUrl() . 'images/';
	$buf = '<table class="tabset"> <tr>';

	$lastActive = true;
	$firstTab = true;
	$piece = array();
	foreach ($item_array as $item) {
	    $active = ($item['params']['selected'] == 'true');

	    if ($active) {
		if ($firstTab) {
		    $left = array($imageUrl . 'tab-left-act.gif', 8, 28);
		} else {
		    $left = array($imageUrl . 'tab-tween-inact-act.gif', 16, 28);
		}
		$mid = array('tabset_activetab', $imageUrl . 'tab-mid-act.gif');
	    } else {
		if ($firstTab) {
		    $left = array($imageUrl . 'tab-left-inact.gif', 8, 28);
		} else {
		    if ($lastActive) {
			$left = array($imageUrl . 'tab-tween-act-inact.gif', 16, 28);
		    } else {
			$left = array($imageUrl . 'tab-tween-inact-inact.gif', 16, 28);
		    }
		}
		$mid = array('tabset_inactivetab', $imageUrl . 'tab-mid-inact.gif');
	    }

	    $buf .= sprintf('<td class="tabset_tab_tween"><img src="%s" width="%s" height="%s" alt=""/></td>',
			    $left[0], $left[1], $left[2]);
	    $buf .= sprintf('<td class="%s" style="background-image: url(%s);">%s</td>',
			    $mid[0],
			    $mid[1],
			    $item['content']);
	    $lastActive = $active;
	    $firstTab = false;
	}

	if ($active) {
	    $right = array($imageUrl . 'tab-right-act.gif', 8, 28);
	} else {
	    $right = array($imageUrl . 'tab-right-inact.gif', 8, 28);
	}
	$buf .= sprintf('<td class="tabset_tab_tween"><img src="%s" width="%s" height="%s" alt=""/></td>',
			$right[0], $right[1], $right[2]);
	$buf .= '</tr> </table>';
	return $buf;
    }

    /**
     * table theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => row HTML content)
     * @return string HTML content
     */
    function table($context, $row_array) {
	switch($context['params']['style']) {
	case 'canvas':
	case 'admin_listing':
	case 'admin_widgets':
	case 'listing':
	    $table_class = 'table_' . $context['params']['style'];
	    break;

	default:
	    $table_class = 'table';
	}
	     
	$buf = '<table class="' . $table_class . '">';
	for ($i = 0; $i < sizeof($row_array); $i++) {
	    $row_class = 'row';
	    if ($context['params']['evenodd'] == 'true') {
		$row_class = ($i % 2) ? 'row_even' : 'row_odd';
	    }

	    $buf .= '<tr class="' . $row_class . '">' . $row_array[$i]['content'] . '</tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * row theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => column HTML content)
     * @return string HTML content
     */
    function row($context, $column_array) {
	$buf = '';
	for ($i = 0; $i < sizeof($column_array); $i++) {
	    $attrs = "";
	    foreach (array('align', 'width', 'colspan', 'rowspan', 'valign') as $attrName) {
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
	return $buf;
    }

    /**
     * main theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => breadcrumb HTML content)
     * @param array ("params" => array, "content" => sidebar HTML content)
     * @param array ("params" => array, "content" => pagebox HTML content)
     * @return string HTML content
     */
    function main($context, $breadcrumb, $sidebar_array, $pagebox) {
	$buf = '<table class="main"> ';

	// Breadcrumb row
	if (!empty($breadcrumb['content'])) {
	    $buf .= '<tr> <td class="breadcrumb" colspan="2"> ' . $breadcrumb['content'] . ' </td> </tr> ';
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

	// Page box
	$buf .= '<td class="main_inner"> ' . $pagebox['content'] . '</td>';

	// Remaining sidebars go on the right
	for ($i = 0; $i < sizeof($sidebar_array); $i++) {
	    $buf .= '<td class="sidebar_right"> ' . $sidebar_array[$i]['content'] . ' </td>';
	}

	// End center row
	$buf .= '</tr>';

	$buf .= '</table>';
	return $buf;
    }

    /**
     * sidebar theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => element HTML content)
     * @return string HTML content
     */
    function sidebar($context, $element_array) {
	$buf = '<table class="sidebar">';
	if ($context['params']['side'] == 'right') {
	    $class="sidebar_box_right";
	} else {
	    $class="sidebar_box_left";
	}
	foreach ($element_array as $element) {
	    $buf .= '<tr> <td class="' . $class . '"> ' . $element['content'] . ' </td> </tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * itemthumbnail theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => description HTML content)
     * @param array ("params" => array, "content" => media HTML content)
     * @param array ("params" => array, "content" => infoset HTML content)
     * @param array ("params" => array, "content" => actionset HTML content)
     * @return string HTML content
     */
    function itemthumbnail($context, $title, $description, $media, $infoset, $actionset) {
	switch ($context['params']['style']) {
	case 'album':
	    $buf = '<table class="albumthumbnail">';
	    $buf .= '<tr>';
	    $buf .= '<td class="albumthumbnail_media">' . $media['content'] . '</td>';
	    $buf .= '<td class="albumthumbnail_data"> <table class="albumthumbnail_inner"> ';
	    $buf .= '<tr> <td class="albumthumbnail_title">' . $title['content'] . '<td>';
	    $buf .= '<tr> <td class="albumthumbnail_description">' . $description['content'] . '<td> </tr>';
	    $buf .= '<tr> <td class="albumthumbnail_infoset">' . $infoset['content'] . '<td> </tr>';
	    $buf .= '</table> </td>';
	    $buf .= '</tr>';
	    $buf .= '<tr> <td colspan="2" class="albumthumbnail_actionset">' . $actionset['content'] . '<td> </tr>';
	    $buf .= '</table>';
	    break;

	case 'item':
	default:
	    $buf = '<table class="itemthumbnail">';
	    $buf .= '<tr> <td class="itemthumbnail_media">' . $media['content'] . '</td> </tr>';
	    $buf .= '<tr> <td class="itemthumbnail_title">' . $title['content'] . '</td> </tr>';
	    $buf .= '<tr> <td class="itemthumbnail_actionset">' . $actionset['content'] . '</td> </tr>';
	    $buf .= '</table>';
	    break;
	}
	return $buf;
    }

    /**
     * itemview theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => description HTML content)
     * @param array ("params" => array, "content" => media HTML content)
     * @param array ("params" => array, "content" => footer HTML content)
     * @return string HTML content
     */
    function itemview($context, $title, $description, $media, $footer) {
	// This theme doesn't return anything but the image for the item view
	return $media['content'];
    }

    /**
     * tabbedbox theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => tabset HTML content)
     * @param array ("params" => array, "content" => footer HTML content)
     * @param array ("params" => array, "content" => element HTML content)
     * @return string HTML content
     */
    function tabbedbox($context, $tabset, $footer, $element_array) {
	$buf = '<table class="tabbedbox">';
	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="tabbedbox_title"> ' . $title['content'] . '</td> </tr> ';
	}

	$buf .= '<tr> <td class="tabbedbox_tabset"> ' . $tabset['content'] . ' </td> </tr>';
	$buf .= '<tr> <td class="tabbedbox_tabset_divider"> </td> </tr>';
	foreach ($element_array as $element) {
	    $buf .= '<tr> <td class="tabbedbox_element"> ' . $element['content'] . ' </td> </tr>';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * box theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => subtitle HTML content)
     * @param array ("params" => array, "content" => description HTML content)
     * @param array ("params" => array, "content" => footer HTML content)
     * @param array ("params" => array, "content" => element HTML content)
     * @return string HTML content
     */
    function box($context, $title, $subtitle, $description, $footer, $element_array) {
	$subTitleOnSeparateRow = false;
	switch($context['params']['style']) {
	case 'sidebar':
	    $subTitleOnSeparateRow = true;
	     
	case 'admin':
	case 'debug':
	case 'comment':
	case 'exif':
	    $class = 'box_' . $context['params']['style'];
	    break;

	default:
	    $class = 'box';
	}
	 
	$buf = '<table class="' . $class . '"> ';

	if (!empty($title['content'])) {
	    $buf .= '<tr> <td class="' . $class . '_title"> ' . $title['content'];
	    if (!empty($subtitle['content'])) {
		if ($subTitleOnSeparateRow) {
		    $buf .= '</td></tr><tr><td class="' . $class. '_title">';
		}
		$buf .= '<span class="' . $class . '_subtitle"> ' . $subtitle['content'] . '</span>';
	    }
	    $buf .= '</td> </tr> ';
	}

	if (!empty($description['content'])) {
	    $buf .= '<tr> <td class="' . $class . '_description"> ' . $description['content'] . '</td> </tr> ';
	}

	foreach ($element_array as $element) {
	    switch($element['params']['style']) {
	    case 'emphasized':
		$elementClass = $class . '_element_' . $element['params']['style'];
		break;
		
	    default:
		$elementClass = $class . '_element';
		break;
	    }
	    
	    $buf .= '<tr> <td class="' . $elementClass . '"> ' . $element['content'] . '</td> </tr>';
	}

	if (!empty($footer['content'])) {
	    $buf .= '<tr> <td class="' . $class . '_footer"> ' . $footer['content'] . '</td> </tr> ';
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * pagebox theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => element HTML content)
     * @return string HTML content
     */
    function pagebox($context, $element_array) {
	$buf = '<table class="pagebox">';
	if (!empty($banner['content'])) {
	    $buf .= '<tr> <td> ' . $banner['content'] . '</td> </tr>';
	}

	if (!empty($description['content'])) {
	    $buf .= '<tr> <td class="pagebox_description"> ' . $banner['content'] . '</td> </tr>';
	}

	foreach ($element_array as $element) {
	    switch($element['name']) {
	    case 'success':
	    case 'error':
		$class = 'pagebox_element_' . $element['name'];
		break;

	    default:
		$class = 'pagebox_element';
	    }
	    $buf .= '<tr> <td class="' . $class . '"> ' . $element['content'] . '</td> </tr>';
	}
	 
	if (!empty($footer['content'])) {
	    $buf .= '<tr> <td class="pagebox_footer"> ' . $footer['content'] . '</td> </tr>';
	}
	$buf .= '</table>';

	return $buf;
    }

    /**
     * banner theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => description HTML content)
     * @param array ("params" => array, "content" => element HTML content)
     * @return string HTML content
     */
    function banner($context, $title, $description, $element_array) {
	$buf = '<table class="bannerbox">';
	if (empty($element_array)) {
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

	    foreach ($element_array as $element) {
		$buf .= '<td class="bannerbox_element">' . $element['content'] . '</td>';
	    }
	}
	$buf .= '</table>';
	return $buf;
    }

    /**
     * item theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => subtitle HTML content)
     * @return string HTML content
     */
    function item($context, $title, $subtitle) {
	switch($context['stack'][0]) {
	case 'breadcrumb':
	case 'listing':
	case 'linkset':
	case 'infoset':
	case 'tabset':
	    $buf = '<span class="title">' . $title['content'] . '</span>';
	     
	    if (!empty($subtitle)) {
		$buf .= '<span class="subtitle">' . $subtitle['content'] . '</span>';
	    }
	    return $buf;
	    break;

	default:
	    trigger_error(sprintf('Unexpected item parent: %s', $context['stack'][0]), E_USER_ERROR);
	}
    }

    /**
     * actionitem theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
     * @param array ("params" => array, "content" => title HTML content)
     * @param array ("params" => array, "content" => value HTML content)
     * @return string HTML content
     */
    function actionitem($context, $title, $value) {
	$buf = '<option label="' . $title['content'] . '" value="' . $value['content'] . '"';
	if ($context['params']['selected'] == 'true') {
	    $buf .= 'SELECTED';
	}
	$buf .= '>' . $title['content'] . '</option>';
	return $buf;
    }
}
?>

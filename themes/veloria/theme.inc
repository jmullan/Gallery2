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
 * @package VeloriaTheme
 * @author Chris Smith <chris@jacko.com>
 * @author Bharat Mediratta <bharat@menalto.com>
 * @author Ross Reyman 
 */

/**
 * This theme (code named "Veloria") is derived from the theme codenamed "Matrix" done
 * by Bharat Mediratta based on the UI designed by Ross Reyman.  
 *
 * @package VeloriaTheme
 */
class VeloriaTheme extends GalleryTheme {

    function VeloriaTheme() {
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
	$buf = "\n".'<div class="breadcrumb_inner">';
        $buf .= "\n".'  <span class="breadcrumb_item">&raquo;</span>';
	for ($i = 0; $i < sizeof($item_array); $i++) {
	    $buf .= "\n".'  <span class="breadcrumb_item">' . $item_array[$i]['content'] . '</span>';
	    if ($i < sizeof($item_array)-1) {
		$buf .= "\n".'  <span class="breadcrumb_item">&raquo;</span>';
	    }
	}
	$buf .= "\n".'</div>';
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
	$buf = '<div class="infoset"> ';
	foreach ($item_array as $item) {
	    $buf .= '<div class="infoset_item"> ' . $item['content'] . '</div>';
	}
	$buf .= '</div>';
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
	    $table_class = 'table_' . $context['params']['style'];
	    break;

	default:
	    $table_class = 'table';
	}
	     
	$buf = "\n".'<table class="' . $table_class . '">';
	for ($i = 0; $i < sizeof($row_array); $i++) {
	    $row_class = 'row';
	    if ($context['params']['evenodd'] == 'true') {
		$row_class = ($i % 2) ? 'row_even' : 'row_odd';
	    }

	    $buf .= "\n".'  <tr class="' . $row_class . '">' . $row_array[$i]['content'] . '</tr>';
	}
	$buf .= "\n".'</table>';
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
	$buf = "\n".'';
	for ($i = 0; $i < sizeof($column_array); $i++) {
	    $attrs = "";
	    foreach (array('align', 'width', 'colspan', 'rowspan', 'valign') as $attrName) {
		if ($column_array[$i]['params'][$attrName]) {
		    $attrs .= ' ' . $attrName . ' ="' . $column_array[$i]['params'][$attrName] . '"';
		}
	    }
	    
	    if ($column_array[$i]['params']['header'] == 'true') {
		$buf .= "\n".'    <td class="columnheader" ' . $attrs . '>' . $column_array[$i]['content'] . '</td>';
	    } else {
		$buf .= "\n".'    <td class="column" ' . $attrs . '>';
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
	$buf = "\n".'<table class="main"> ';

	// image banner 
        $imageUrl = $this->getBaseUrl() . 'images/';
	$buf .= "\n".'  <tr> <td class="banner" colspan="2"><img width="600" height="50" src="' 
	      . $imageUrl . 'banner.gif">  </td> </tr> ';

	// Breadcrumb row
	if (!empty($breadcrumb['content'])) {
	    $buf .= "\n".'  <tr> <td class="breadcrumb" colspan="2"> ' . $breadcrumb['content'] . ' </td> </tr> ';
	}

	// Begin center row
	$buf .= "\n".'  <tr> ';

	// First sidebar (that isn't marked for the right side) goes on the left
	for ($i = 0; $i < sizeof($sidebar_array); $i++) {
	    if ($sidebar_array[$i]['params']['side'] != 'right') {
		$buf .= "\n".'    <td class="sidebar_left"> ' . $sidebar_array[$i]['content'] . ' </td>';
		array_splice($sidebar_array, $i, 1);
	    }
	}

	// Page box
	$buf .= "\n".'    <td class="main_inner"> ' . $pagebox['content'] . '</td>';

	// Remaining sidebars go on the right
	for ($i = 0; $i < sizeof($sidebar_array); $i++) {
	    $buf .= "\n".'    <td class="sidebar_right"> ' . $sidebar_array[$i]['content'] . ' </td>';
	}

	// End center row
	$buf .= "\n".'  </tr>';

	$buf .= "\n".'</table>';
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
	$buf = "\n".'<div class="sidebar">';
	if ($context['params']['side'] == 'right') {
	    $class="sidebar_box_right";
	} else {
	    $class="sidebar_box_left";
	}
	foreach ($element_array as $element) {
	    $buf .= "\n".'<div class="' . $class . '"> ' . $element['content'] . ' </div>';
	}
	$buf .= "\n".'</div>';
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
	    $buf =  "\n".'<div class="albumthumbnail">';
	    $buf .= "\n".'<table border="0" cellpadding="0" cellspacing="0" >';
	    $buf .= "\n".'  <tr>';
	    $buf .= "\n".'    <td class="albumthumbnail_media">' . $media['content'] . '</td>';
	    $buf .= "\n".'    <td class="albumthumbnail_data"> ';
	    $buf .= "\n".'      <div class="albumthumbnail_title">' . $title['content'] . '</div>';
	    $buf .= "\n".'      <div class="albumthumbnail_description">' . $description['content'] . '</div>';
	    $buf .= "\n".'      <div class="albumthumbnail_infoset">' . $infoset['content'] . '</div>';
	    $buf .= "\n".'    </td>';
	    $buf .= "\n".'  </tr>';
	    $buf .= "\n".'  <tr><td colspan="2" class="albumthumbnail_actionset">' . $actionset['content'] . '</td></tr>';
	    $buf .= "\n".'</table>';
	    $buf .= "\n".'</div>';
	    break;

	case 'item':
	default:
	    $buf =  "\n".'<div class="itemthumbnail">';
	    $buf .= "\n".'  <div class="itemthumbnail_media">' . $media['content'] . '</div>';
	    $buf .= "\n".'  <div class="itemthumbnail_title">' . $title['content'] . '</div>';
	    $buf .= "\n".'  <div class="itemthumbnail_actionset">' . $actionset['content'] . '</div>';
	    $buf .= "\n".'</div>';
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
	$buf = '<div class="tabbedbox">';
	if (!empty($title['content'])) {
	    $buf .= '<div class="tabbedbox_title"> ' . $title['content'] . '</div> ';
	}

	$buf .= '<div class="tabbedbox_tabset"> ' . $tabset['content'] . ' </div>';
	$buf .= '<div class="tabbedbox_tabset_divider"> </div>';
	foreach ($element_array as $element) {
	    $buf .= '<div class="tabbedbox_element"> ' . $element['content'] . ' </div>';
	}
	$buf .= '</div>';
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
	    $class = 'box_' . $context['params']['style'];
	    break;

	default:
	    $class = 'box';
	}
	 
	$buf = '<div class="' . $class . '"> ';

	if (!empty($title['content'])) {
	    $buf .= '<div class="' . $class . '_title"> ' . $title['content'];
	    if (!empty($subtitle['content'])) {
		if ($subTitleOnSeparateRow) {
		    $buf .= '</div><div class="' . $class. '_title">';
		}
		$buf .= '<span class="' . $class . '_subtitle"> ' . $subtitle['content'] . '</span>';
	    }
	    $buf .= '</div> ';
	}

	if (!empty($description['content'])) {
	    $buf .= '<div class="' . $class . '_description"> ' . $description['content'] . '</div> ';
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
	    
	    $buf .= '<div class="' . $elementClass . '"> ' . $element['content'] . '</div>';
	}

	if (!empty($footer['content'])) {
	    $buf .= '<div class="' . $class . '_footer"> ' . $footer['content'] . '</div> ';
	}
	$buf .= '</div>';
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
	$buf = '<div class="pagebox">';
	if (!empty($banner['content'])) {
	    $buf .= '<div class="pagebox_banner"> ' . $banner['content'] . '</div>';
	}

	if (!empty($description['content'])) {
	    $buf .= '<div class="pagebox_description"> ' . $description['content'] . '</div>';
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
	    $buf .= '<div class="' . $class . '"> ' . $element['content'] . '</div>';
	}
	 
	if (!empty($footer['content'])) {
	    $buf .= '<div class="pagebox_footer"> ' . $footer['content'] . '</div>';
	}
	$buf .= '</div>';

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

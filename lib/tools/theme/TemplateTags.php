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

$contracted_tag['style'] = 1;
$contracted_tag['image'] = 1;

/*
 * Not all attribute tags are trimmed -- we don't want to trim "column" for example because it makes the HTML
 * very hard to read.
 */
$trimmed_tag['value'] = 1;
$trimmed_tag['title'] = 1;

$attribute_tag['title'] = 1;
$attribute_tag['subtitle'] = 1;
$attribute_tag['description'] = 1;
$attribute_tag['footer'] = 1;
$attribute_tag['media'] = 1;
$attribute_tag['column'] = 1;
$attribute_tag['element'] = 1;
$attribute_tag['value'] = 1;

$builtin_tag['input'] = 1;
$builtin_tag['form'] = 1;
$builtin_tag['select'] = 1;
$builtin_tag['textarea'] = 1;
$builtin_tag['link'] = 1;
$builtin_tag['image'] = 1;

$tags['style'] = array('children' => 'content');
$tags['input'] = array('children' => 'content');
$tags['form'] = array('children' => 'content');
$tags['select'] = array('children' => 'content');
$tags['textarea'] = array('children' => 'content');
$tags['link'] = array('children' => 'content');
$tags['success'] = array('children' => 'content');
$tags['warning'] = array('children' => 'content');
$tags['error'] = array('children' => 'content');
$tags['image'] = array('attributes' => 'item=array(),image=array(),fallback=null');
$tags['listing'] = array('children' => 'item[]');
$tags['breadcrumb'] = array('children' => 'item[]');
$tags['linkset'] = array('attributes' => 'style=null', 'children' => 'title,item[]');
$tags['actionset'] = array('attributes' => 'style=null', 'children' => 'title,actionitem[]');
$tags['infoset'] = array('children' => 'item[]');
$tags['tabset'] = array('children' => 'item[]');
$tags['table'] = array('attributes' => 'style=null,evenodd=false', 'children' => 'row[]');
$tags['row'] = array('attributes' => 'rowspan=1,colspan=1', 'children' => 'column[]');
$tags['column'] = array('attributes' => 'align=null,valign=null,width=null,header=false,colspan=1,rowspan=1', 'children' => 'content');
$tags['element'] = array('attributes' => 'style=null', 'children' => 'content');

/* Attributes */
$tags['title'] = array('children' => 'content');
$tags['subtitle'] = array('children' => 'content');
$tags['description'] = array('children' => 'content');
$tags['footer'] = array('children' => 'content');
$tags['media'] = array('children' => 'content');
$tags['value'] = array('children' => 'content');

$tags['main'] = array('children' => 'breadcrumb,sidebar[],pagebox');
$tags['sidebar'] = array('attributes' => 'style=null,side=null', 'children' => 'element[]');
$tags['itemthumbnail'] = array('attributes' => 'style=null', 'children' => 'title,description,media,infoset,actionset');
$tags['itemview'] = array('attributes' => 'style=null', 'children' => 'title,description,media,footer');
$tags['tabbedbox'] = array('children' => 'tabset,footer,element[]');
$tags['box'] = array('attributes' => 'style=null', 'children' => 'title,subtitle,description,footer,element[]');
$tags['pagebox'] = array('attributes' => 'style=null', 'children' => 'element[]');
$tags['banner'] = array('children' => 'title,description,element[]');
$tags['item'] = array('attributes' => 'selected=false', 'children' => 'title,subtitle');
$tags['actionitem'] = array('attributes' => 'selected=false', 'children' => 'title,value');

foreach ($tags as $tagName => $tagInfo) {
    /* Process children */
    if (!empty($tags[$tagName]['children'])) {
	$tmp = array();
	foreach (split(',', $tags[$tagName]['children']) as $child) {
	    if (strstr($child, '[]')) {
		$child = str_replace('[]', '', $child);
		$tmp[$child]['isArray'] = 1;
	    } else {
		$tmp[$child]['isArray'] = 0;
	    }
	}
	$tags[$tagName]['children'] = $tmp;
    } else {
	$tags[$tagName]['children'] = array();
    }

    /* Process attributes */
    if (!empty($tags[$tagName]['attributes'])) {
	$tmp = array();
	foreach (split(',', $tags[$tagName]['attributes']) as $attribute) {
	    list ($key, $value) = split('=', $attribute);
	    $tmp[$key] = $value;
	}
	$tags[$tagName]['attributes'] = $tmp;
    } else {
	$tags[$tagName]['attributes'] = array();
    }
}

require_once(dirname(__FILE__) . '/../../smarty/Smarty.class.php');

$smarty = new Smarty();
$smarty->compile_dir = dirname(__FILE__) . '/templates_c';
$smarty->template_dir = dirname(__FILE__) . '/templates';
$smarty->assign('tags', $tags);
$smarty->assign('contracted_tag', $contracted_tag);
$smarty->assign('attribute_tag', $attribute_tag);
$smarty->assign('trimmed_tag', $trimmed_tag);
$smarty->assign('builtin_tag', $builtin_tag);

$fd = fopen("GalleryTemplateAdapter.inc", "w");
fwrite($fd, $smarty->fetch('GalleryTemplateAdapter.tpl'));
fclose($fd);
       
$fd = fopen("GalleryTheme.inc", "w");
fwrite($fd, $smarty->fetch('GalleryTheme.tpl'));
fclose($fd);

<?php
/*
 * $RCSfile
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

require_once(dirname(__FILE__) . '/../bbcode/bbcode.class');

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * Type:     modifier
 * Name:     bbcode
 * Purpose:  Format the embedded BBCode tags in the given string
 * -------------------------------------------------------------
 */
function smarty_modifier_bbcode($text) {
    static $bbcode;
    if (!isset($bbcode)) {
	$bbcode = new BBCode ();

	// Convert line breaks everywhere
	$bbcode->addParser('galleryBbcodeConvertLineBreaks', array('block', 'inline', 'link', 'listitem', 'list'));

	// Escape all characters everywhere
	$bbcode->addParser('htmlspecialchars', array('block', 'inline', 'link', 'listitem'));
	
	// Convert line endings
	$bbcode->addParser('nl2br', array('block', 'inline', 'link', 'listitem'));

	// Strip last line break in list items
	$bbcode->addParser('galleryBbcodeStripLastLineBreak', array ('listitem'));

	// Strip contents in list elements
	$bbcode->addParser('galleryBbcodeStripContents', array('list'));

	// [b], [i]
	$bbcode->addCode('b', 'simple_replace', null, array ('<b>', '</b>'),
			 'inline', array ('listitem', 'block', 'inline', 'link'), array ());
	$bbcode->addCode('i', 'simple_replace', null, array ('<i>', '</i>'),
			 'inline', array ('listitem', 'block', 'inline', 'link'), array ());
	
	// [url]http://...[/url], [url=http://...]Text[/url]
	$bbcode->addCode('url', 'usecontent?', 'galleryDoBbcodeUrl', array ('default'),
			 'link', array ('listitem', 'block', 'inline'), array ('link'));
	
	// [img]http://...[/img]
	$bbcode->addCode('img', 'usecontent', 'galleryDoBbcodeImg', array (),
			 'image', array ('listitem', 'block', 'inline', 'link'), array ());

	// [list]
	//   [*]Element
	// [/list]
	$bbcode->addCode('list', 'simple_replace', null, array ('<ul>', '</ul>'),
			 'list', array ('block', 'listitem'), array ());
	$bbcode->addCode('*', 'simple_replace', null, array ('<li>', "</li>\n"),
			 'listitem', array ('list'), array ());
	$bbcode->setCodeFlag('*', 'no_close_tag', true);
    }

    return $bbcode->parse($text);
}

function galleryDoBbcodeUrl($tag_name, $attrs, $elementContents, $funcParam, $openClose) {
    if ($openClose == 'all') {
	return sprintf('<a href="%s">%s</a>',
		       htmlspecialchars($elementContents), htmlspecialchars($elementContents));
    } else if ($openClose == 'open') {
	return sprintf('<a href="%s">%s</a>', htmlspecialchars($attrs['default']));
    } else if ($openClose == 'close') {
        return '</a>';
    } else {
        return false;
    }
}

function galleryDoBbcodeImg($tagName, $attrs, $elementContents, $funcParam, $openClose) {
    if ($openClose == 'all') {
	return sprintf('<img src="%s" alt="">', htmlspecialchars($elementContents));
    } else {
	return false;
    }
}

function galleryBbcodeConvertLineBreaks ($text) {
    return preg_replace("/\015\012|\015|\012/", "\n", $text);
}

function galleryBbcodeStripContents ($text) {
    return preg_replace("/[^\n]/", '', $text);
}

function galleryBbcodeStripLastLineBreak ($text) {
    return preg_replace("/\n( +)?$/", '$1', $text);
}

?>

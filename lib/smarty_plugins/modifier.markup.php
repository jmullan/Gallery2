<?php
/*
 * $RCSfile
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

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * Type:     modifier
 * Name:     markup
 * Purpose:  Format embedded markup in the given string according
 *           to settings specified in site admin (no markup, bbcode or
 *           raw html)
 * -------------------------------------------------------------
 */
function smarty_modifier_markup($text, $overrideMarkupType=null) {
    global $gallery;
    static $defaultMarkupType;
    static $parsers;

    if (isset($overrideMarkupType)) {
	$markupType = $overrideMarkupType;
    } else {
	if (!isset($defaultMarkupType)) {
	    list ($ret, $defaultMarkupType) = GalleryCoreApi::getPluginParameter('module', 'core', 'misc.markup');
	    if ($ret->isError()) {
		/* This code is used by the UI -- we can't return an error.  Choose something safe */
		$defaultMarkupType = 'stripBbcodeAndHtml';
	    }
	}

	$markupType = $defaultMarkupType;
    }

    if (!isset($parsers[$markupType])) {
	switch($markupType) {
	case 'stripBbcodeAndHtml':
	    $parsers[$markupType] = new GalleryStripBbcodeAndHtmlParser();
	    break;
	    
	case 'bbcode':
	    $parsers[$markupType] = new GalleryBbcodeMarkupParser();
	    break;

	case 'none':
	    $parsers[$markupType] = new GalleryNoMarkupParser();
	    break;

	case 'html':
	    $parsers[$markupType] = new GalleryHtmlMarkupParser();
	    break;
	}
    }
    
    return $parsers[$markupType]->parse($text);
}

class GalleryBbcodeMarkupParser {
    var $_bbcode;

    function GalleryBbcodeMarkupParser() {
	require_once(dirname(__FILE__) . '/../bbcode/bbcode.class');

	$this->_bbcode = new BBCode();

	// Convert line breaks everywhere
	$this->_bbcode->addParser(array($this, 'convertLineBreaks'),
			   array('block', 'inline', 'link', 'listitem', 'list'));

	// Escape all characters everywhere
	// We don't need to do this 'cause G2 doesn't allow raw entities into the database
	// $this->_bbcode->addParser('htmlspecialchars', array('block', 'inline', 'link', 'listitem'));
	
	// Convert line endings
	$this->_bbcode->addParser('nl2br', array('block', 'inline', 'link', 'listitem'));

	// Strip last line break in list items
	$this->_bbcode->addParser(array($this, 'stripLastLineBreak'), array ('listitem'));

	// Strip contents in list elements
	$this->_bbcode->addParser(array($this, 'stripContents'), array('list'));

	// [b], [i]
	$this->_bbcode->addCode('b', 'simple_replace', null, array ('<b>', '</b>'),
			 'inline', array ('listitem', 'block', 'inline', 'link'), array ());
	$this->_bbcode->addCode('i', 'simple_replace', null, array ('<i>', '</i>'),
			 'inline', array ('listitem', 'block', 'inline', 'link'), array ());
	
	// [url]http://...[/url], [url=http://...]Text[/url]
	$this->_bbcode->addCode('url', 'usecontent?', array($this, 'url'), array ('default'),
			 'link', array ('listitem', 'block', 'inline'), array ('link'));
	
	// [img]http://...[/img]
	$this->_bbcode->addCode('img', 'usecontent', array($this, 'image'), array (),
			 'image', array ('listitem', 'block', 'inline', 'link'), array ());

	// [list]
	//   [*]Element
	// [/list]
	$this->_bbcode->addCode('list', 'simple_replace', null, array ('<ul>', '</ul>'),
			 'list', array ('block', 'listitem'), array ());
	$this->_bbcode->addCode('*', 'simple_replace', null, array ('<li>', "</li>\n"),
			 'listitem', array ('list'), array ());
	$this->_bbcode->setCodeFlag('*', 'no_close_tag', true);
    }

    function parse($text) {
	return $this->_bbcode->parse($text);
    }

    function url($tagName, $attrs, $elementContents, $funcParam, $openClose) {
	static $lastOpenSuccess;
	
	if ($openClose == 'all') {
	    if (preg_match('/^(http|ftp|mailto|https):/', $elementContents)) {
		return sprintf('<a href="%s">%s</a>', $elementContents, $elementContents);
	    } else {
		return sprintf('[url=%s]', $elementContents, $elementContents);
	    }
	} else if ($openClose == 'open') {
	    if (preg_match('/^(http|ftp|mailto|https):/', $attrs['default'])) {
		$lastOpenSuccess = true;
		return sprintf('<a href="%s">', $attrs['default']);
	    } else {
		$lastOpenSuccess = false;
		return sprintf('[url=%s]', $attrs['default']);
	    }
	} else if ($openClose == 'close') {
	    if (isset($lastOpenSuccess) && $lastOpenSuccess) {
		return '</a>';
	    } else {
		return '[/url]';
	    }
	} else {
	    return false;
	}
    }

    function image($tagName, $attrs, $elementContents, $funcParam, $openClose) {
	if (!preg_match('/^(http|ftp|mailto|https):/', $elementContents)) {
	    return sprintf('[img]%s[/img]', $elementContents);
	}
	
	if ($openClose == 'all') {
	    return sprintf('<img src="%s" alt="">', htmlspecialchars($elementContents));
	} else {
	    return false;
	}
    }

    function convertLineBreaks($text) {
	return preg_replace("/\015\012|\015|\012/", "\n", $text);
    }

    function stripContents($text) {
	return preg_replace("/[^\n]/", '', $text);
    }

    function stripLastLineBreak ($text) {
	return preg_replace("/\n( +)?$/", '$1', $text);
    }
}    

class GalleryNoMarkupParser {
    function parse($text) {
	return $text;
    }
}

class GalleryHtmlMarkupParser {
    function parse($text) {
	return GalleryUtilities::htmlEntityDecode($text);
    }
}

class GalleryStripBbcodeAndHtmlParser {
    function parse($text) {
	static $bbcode;
	if (!isset($bbcode)) {
	    $bbcode = new GalleryBbcodeMarkupParser();
	}

	$text = $bbcode->parse($text);
	$text = strip_tags($text);
	return $text;
    }
}
?>

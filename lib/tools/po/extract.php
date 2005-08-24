#!/usr/bin/php -f
<?php
/*
 * $RCSfile$
 *
 * PHP script to extract strings from all the files and print
 * to stdout for use with xgettext.
 *
 * This script is based on the perl script provided with the Horde project
 * http://www.horde.org/.  As such, it inherits the license from the
 * original version.  You can find that license here:
 *
 * http://cvs.horde.org/co.php/horde/COPYING?r=2.1
 *
 * I'm not exactly sure what the license restrictions are in this case,
 * but I want to give full credit to the original authors:
 *
 * Copyright 2000-2002 Joris Braakman <jbraakman@yahoo.com>
 * Copyright 2001-2002 Chuck Hagenbuch <chuck@horde.org>
 * Copyright 2001-2002 Jan Schneider <jan@horde.org>
 *
 * We've modified the script somewhat to make it work cleanly with the
 * way that Gallery embeds internationalized text, so let's tack on our
 * own copyrights.
 *
 * Copyright 2002-2005 Bharat Mediratta <bharat@menalto.com>
 *
 * $Id$
 */

if (!empty($_SERVER['SERVER_NAME'])) {
    print "You must run this from the command line\n";
    exit(1);
}

$exts = '(class|php|inc|tpl|css|html)';

foreach ($_SERVER['argv'] as $moduleDir) {
    find($moduleDir);
}
$strings = array_keys($strings);
print '# $Id$';
print "\n\n" . implode("\n", $strings) . "\n";

/**
 * Recursive go through subdirectories
 */
function find($dir) {
    if (is_dir($dir) && $dh = opendir($dir)) {
	$listing = array();
	while (($file = readdir($dh)) !== false) {
	    if ($file == '.' || $file == '..') {
		continue;
	    }
	    $listing[] = $file;
	}
	closedir($dh);
	sort($listing);
	global $exts;
	foreach ($listing as $file) {
	    $filename = $dir . '/' . $file;
	    $type = filetype($filename);
	    if ($type == 'dir') {
		find($filename);
	    }
	    if (preg_match("/\." . $exts . "$/", $file)) {
		extractStrings($filename);
	    }
	}
    }
}

/**
 * Grab all translatable strings in a file into $strings array
 */
function extractStrings($filename) {
    global $strings;
    $fd = fopen($filename, 'r');
    $data = '';
    while (! feof($fd)) {
	$data .= fgets($fd, 4096);
    }
    fclose($fd);
    #echo "$data\n";

    # grab phrases for translate( or i18n( or _( calls; capture string parameter enclosed
    # in single or double quotes including concatenated strings like 'one' . "two"
    if (preg_match_all("/(translate|i18n|_)\(\s*(((\s*\.\s*)?('((\\')?[^']*?)*[^\\\]'|\"((\")?[^\"]*?)*[^\\\]\"))+)\s*\)/s",
		       $data, $matches, PREG_SET_ORDER)) {
	foreach ($matches as $match) {
	    $text = $match[2];
	    $cmd = sprintf('return %s;', $text);
	    $text = eval($cmd);
	    $text = str_replace('"', '\\"', $text);    # escape double-quotes
	    $string = sprintf('gettext("%s")', $text);
	    $strings[$string] = TRUE;
	}
    }

    # grab phrases of this format: translate(array('one' => '...', 'many' => '...'))
    if (preg_match_all("/translate\(.*?array\('one'\s*=>\s*'(.*?)'.*?'many'\s*=>\s*'(.*?)'.*?\).*?\)/s",
		       $data, $matches, PREG_SET_ORDER)) {
	foreach ($matches as $match) {
	    $one = $match[1];
	    $many = $match[2];
	    $one = str_replace('"', '\\"', $one);      # escape double-quotes
	    $many = str_replace('"', '\\"', $many);    # escape double-quotes
	    $string = sprintf('ngettext("%s", "%s")', $one, $many);
	    $strings[$string] = TRUE;
	}
    }

    # grab phrases of this format: translate(array('text' => '...', ...))
    if (preg_match_all("/translate\(\s*array\('text'\s*=>\s+'(.*?[^\\\])'/s",
		       $data, $matches, PREG_SET_ORDER)) {
	foreach ($matches as $match) {
	    $text = $match[1];
	    $text = str_replace('"', '\\"', $text);    # escape double-quotes
	    $string = sprintf('gettext("%s")', $text);
	    $strings[$string] = TRUE;
	}
    }

    # grab phrases of this format: {g->text ..... }
    if (preg_match_all("/(\{\s*g->text\s+.*?[^\\\]\})/s",
		       $data, $matches, PREG_SET_ORDER)) {
	foreach ($matches as $match) {
	    $string = $match[1];
	    $text = null;
	    $one = null;
	    $many = null;

	    # Ignore translations of the form:
	    #   text=$foo
	    # as we expect those to be variables containing values that
	    # have been marked elsewhere with the i18n() function
	    if (preg_match("/text=\\$/", $string)) {
		continue;
	    }

	    # text=.....
	    if (preg_match("/text=\"(.*?[^\\\])\"/s", $string, $matches)) {
		$text = $matches[1];
	    } elseif (preg_match("/text='(.*?)'/s", $string, $matches)) {
		$text = $matches[1];
		$text = str_replace('"', '\\"', $text);    # escape double-quotes
	    }

	    # one = .....
	    if (preg_match("/\s+one=\"(.*?[^\\\])\"/s", $string, $matches)) {
		$one = $matches[1];
	    } elseif (preg_match("/\s+one='(.*?)'/s", $string, $matches)) {
		$one = $matches[1];
		$one = str_replace('"', '\\"', $one);    # escape double-quotes
	    }

	    # many = .....
	    if (preg_match("/\s+many=\"(.*?[^\\\])\"/s", $string, $matches)) {
		$many = $matches[1];
	    } elseif (preg_match("/\s+many='(.*?)'/s", $string, $matches)) {
		$many = $matches[1];
		$many = str_replace('"', '\\"', $many);    # escape double-quotes
	    }

	    # pick gettext() or ngettext()
	    if ($text != null) {
		$string = sprintf('gettext("%s")', $text);
	    } elseif ($one != null && $many != null) {
		$string = sprintf('ngettext("%s", "%s")', $one, $many);
	    } else {
		# parse error
		$stderr = fopen('php://stderr', 'w');
		$text = preg_replace("/\n/s", '\n>', $text);
		fwrite($stderr, "extract.pl parse error: $file:\n");
		fwrite($stderr, "> $text\n");
		exit(1);
	    }

	    $string = str_replace('\\}', '}', $string);    # unescape right-curly-braces
	    $strings[$string] = TRUE;
	}
    }
}
?>

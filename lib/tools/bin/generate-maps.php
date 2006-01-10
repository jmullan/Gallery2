<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
ini_set('error_reporting', 2047);
if (!empty($_SERVER['SERVER_NAME'])) {
    print "You must run this from the command line\n";
    exit(1);
}

require_once(dirname(__FILE__) . '/XmlParser.inc');
require_once(dirname(__FILE__) . '/../../smarty/Smarty.class.php');

if (!empty($_ENV['TMP'])) {
    $tmpdir = $_ENV['TMP'];
} else {
    $tmpdir = '/tmp';
}
$tmpdir .= "/g2_" . rand(1, 30000);
if (file_exists($tmpdir)) {
    print "Tmp dir already exists: $tmpdir\n";
    exit(1);
}

if (!mkdir($tmpdir)) {
    print "Unable to make tmp dir: $tmpdir\n";
    exit(1);
}

$smarty = new Smarty();
$smarty->compile_dir = $tmpdir;
$smarty->error_reporting = error_reporting();
$smarty->debugging = true;
$smarty->use_sub_dirs = false;
$smarty->template_dir = dirname(__FILE__);

$xmlFile = 'Maps.xml';
if (!file_exists($xmlFile)) {
    return;
}

$p =& new XmlParser();
$root = $p->parse($xmlFile);

$maps = array();
foreach ($root[0]['child'] as $map) {
    $mapName = $map['child'][0]['content'];

    for ($j = 2; $j < count($map['child']); $j++) {
	$child = $map['child'][$j];
	if ($child['name'] == 'MEMBER') {
	    $member = array(
		'name' => $child['child'][0]['content'],
		'type' => 'STORAGE_TYPE_' . $child['child'][1]['content']);

	    if (!empty($child['child'][2]['name']) &&
		    $child['child'][2]['name'] == 'MEMBER-SIZE') {
		$member['size'] = 'STORAGE_SIZE_' . $child['child'][2]['content'];
	    } else {
		$member['size'] = 'STORAGE_SIZE_MEDIUM';
	    }

	    $maps[$mapName][] = $member;
	}
    }
}

$smarty->assign('maps', $maps);
$smarty->assign('mapName', $mapName);
$new = $smarty->fetch('maps.tpl');

$fd = fopen('Maps.inc', 'w');
fwrite($fd, $new);
fclose($fd);

/* Clean up the cheap and easy way */
if (file_exists($tmpdir)) {
    system("rm -rf $tmpdir");
}
?>
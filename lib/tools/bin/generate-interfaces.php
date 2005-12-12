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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
ini_set('error_reporting', 2047);
if (!empty($_SERVER['SERVER_NAME'])) {
    print "You must run this from the command line\n";
    exit(1);
}

require_once(dirname(__FILE__) . '/XmlParser.inc');
require_once('../../../../lib/smarty/Smarty.class.php');

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

if (!ini_get('register_argc_argv')) {
    print "You must enable the 'register_argc_argv' php variable for this script to work\n";
    exit(1);
}

if (count($argv) < 2) {
    print "Usage: generate-interfaces.php <PackageName>\n";
    exit(1);
}
$package = $argv[1];

$smarty = new Smarty();
$smarty->compile_dir = $tmpdir;
$smarty->error_reporting = error_reporting();
$smarty->debugging = true;
$smarty->use_sub_dirs = false;
$smarty->template_dir = dirname(__FILE__);

$modifiedCount = 0;
$checkedCount = 0;
foreach (glob('tmp/*.xml') as $xmlFile) {
    $checkedCount++;
    $p =& new XmlParser();
    $root = $p->parse($xmlFile);
    $base = basename($xmlFile);
    $base = preg_replace('/\.[^\.]*$/', '', $base);
    $tmpFile = "$base.inc.tmp";
    $origFile = "$base.inc";

    if ($root[0]['child'][2]['name'] == 'MAP') {
	$isMap = true;
	$membersBase = $root[0]['child'][2]['child'];
	$schema = array($root[0]['child'][1]['child'][1]['content'],
			$root[0]['child'][1]['child'][2]['content']);
    } else {
	$isMap = false;
	$membersBase = $root[0]['child'];
	$schema = array($root[0]['child'][2]['child'][1]['content'],
			$root[0]['child'][2]['child'][2]['content']);
    }
    if (empty($schema[1])) {
	$schema[1] = 0;
    }

    $members = array();
    foreach ($membersBase as $child) {
	if ($child['name'] == 'MEMBER') {
	    $member = array('name' => $child['child'][0]['content'],
			    'type' => $child['child'][1]['content'],
			    'ucName' => ucfirst($child['child'][0]['content']),
			    'lcType' => strtolower($child['child'][1]['content']));
	    for ($i = 2; $i < count($child['child']); $i++) {
		switch($child['child'][$i]['name']) {
		case 'MEMBER-SIZE':
		    $member['size'] = $child['child'][$i]['content'];
		    break;

		case 'INDEXED':
		case 'REQUIRED':
		case 'UNIQUE':
		case 'ID':
		case 'PRIMARY':
		case 'LINKED':
		    $member[strtolower($child['child'][$i]['name'])] = 1;
		    break;

		default:
		    print 'Unknown member type: ' . $child['child'][$i]['name'] . '\n';
		}
	    }

	    $members[] = $member;
	}
    }

    $smarty->assign('root', $root);
    $smarty->assign('package', $package);
    $smarty->assign('schema', $schema);
    $smarty->assign('className', $root[0]['child'][0]['content']);
    $smarty->assign('members', $members);
    $smarty->assign('isMap', $isMap);

    $new = $smarty->fetch('interface.tpl');
    $new = explode("\n", $new);

    /*
     * Move any RCS tags over.  We know exactly where they are in the template so
     * do this the quick and dirty way.
     */
    if (file_exists($origFile)) {
	$orig = str_replace("\n", "", file($origFile));
	if (count($orig) > 25) {
	    $new[2] = $orig[2];
	    $new[24] = $orig[24];
	}
    }

    $fd = fopen($tmpFile, "w");
    fwrite($fd, join("\n", $new));
    fclose($fd);

    if (file_exists($origFile)) {
	if (md5_file($tmpFile) != md5_file($origFile)) {
	    unlink($origFile);
	    rename($tmpFile, $origFile);
	    $modifiedCount++;
	} else {
	    unlink($tmpFile);
	}
    } else {
	rename($tmpFile, $origFile);
	$modifiedCount++;
    }
}

/* Clean up the cheap and easy way */
if (file_exists($tmpdir)) {
    system("rm -rf $tmpdir");
}
?>

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
if (!empty($_SERVER['SERVER_NAME'])) {
    print "You must run this from the command line\n";
    exit(1);
}

require_once(dirname(__FILE__) . '/XmlParser.inc');
require_once('../../../../../../../lib/smarty/Smarty.class.php');

$tmpdir = "$_ENV[TMP]/g2_" . rand(1, 30000);
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

$modifiedCount = 0;
$checkedCount = 0;
foreach (glob('tmp/*.xml') as $xmlFile) {
    $checkedCount++;
    $p =& new XmlParser();
    $root = $p->parse($xmlFile);
    $base = basename($xmlFile);
    $base = preg_replace('/\.[^\.]*$/', '', $base);
    $tmpFile = "../xml-out/$base.xml";
    $origFile = "$base.xml";

    if ($root[0]['child'][2]['name'] == 'MAP') {
	$isMap = true;
	$membersBase = $root[0]['child'][2]['child'];
	$schema = array(
	    'name' => $root[0]['child'][1]['child'][0]['content'],
	    'major' => $root[0]['child'][1]['child'][1]['content'],
	    'minor' => $root[0]['child'][1]['child'][2]['content']);
    } else {
	$isMap = false;
	$membersBase = $root[0]['child'];
	$schema = array(
	    'name' => $root[0]['child'][2]['child'][0]['content'],
	    'major' => $root[0]['child'][2]['child'][1]['content'],
	    'minor' => $root[0]['child'][2]['child'][2]['content']);
    }
    if (empty($schema['minor'])) {
	$schema['minor'] = 0;
    }

    $className = $root[0]['child'][0]['content'];

    $members = array();
    $keys = array();
    $indexes = array();
    $requiresId = false;
    foreach ($membersBase as $child) {
	switch($child['name']) {
	case 'MEMBER':
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
		    $indexes[] = array('columns' => array($member['name']));
		    $member[strtolower($child['child'][$i]['name'])] = 1;
		    break;

		case 'UNIQUE':
		    $keys[] = array('columns' => array($member['name']));
		    $member[strtolower($child['child'][$i]['name'])] = 1;
		    break;

		case 'PRIMARY':
		    $keys[] = array('columns' => array($member['name']), 'primary' => 1);
		    $member['primary'] = 1;
		    break;
		case 'ID':
		case 'LINKED':
		    $member[strtolower($child['child'][$i]['name'])] = 1;
		    break;

		case 'REQUIRED':
		    $member['required'] = array();
		    if (isset($child['child'][$i]['attrs']['EMPTY'])) {
			$member['required']['empty'] = $child['child'][$i]['attrs']['EMPTY'];
		    } else {
			$member['required']['empty'] = 'disallowed';
		    }
		    break;


		default:
		    print 'Unknown member type: ' . $child['child'][$i]['name'] . '\n';
		}
	    }

	    if (empty($member['size'])) {
		$member['size'] = 'MEDIUM';
	    }

	    $members[] = $member;
	    break;

	case 'KEY':
	    $key = array();
	    foreach ($child['child'] as $column) {
		$key['columns'][] = $column['content'];
	    }
	    $key['primary'] =
		isset($child['attrs']['PRIMARY']) && $child['attrs']['PRIMARY'] == 'true';
	    $keys[] = $key;
	    break;

	case 'INDEX':
	    $index = array();
	    foreach ($child['child'] as $column) {
		$index['columns'][] = $column['content'];
	    }
	    $index['primary'] =
		isset($child['attrs']['PRIMARY']) && $child['attrs']['PRIMARY'] == 'true';

	    $indexes[] = $index;
	    break;

	case 'REQUIRES-ID':
	    $requiresId = true;
	    $keys[] = array('columns' => array('id'), 'primary' => 1);
	    break;
	}
    }

    $smarty->assign('root', $root);
    $smarty->assign('package', $package);
    $smarty->assign('schema', $schema);
    $smarty->assign('className', $className);
    $smarty->assign('members', $members);
    $smarty->assign('keys', $keys);
    $smarty->assign('indexes', $indexes);
    $smarty->assign('isMap', $isMap);
    $smarty->assign('requiresId', $requiresId);
    $new = $smarty->fetch('dbxml.tpl');

    $fd = fopen($tmpFile, "w");
    fwrite($fd, $new);
    fclose($fd);
}

/* Clean up the cheap and easy way */
if (file_exists($tmpdir)) {
    system("rm -rf $tmpdir");
}
?>
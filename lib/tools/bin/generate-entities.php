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

/* Grab all G2 XML from entity class files */

$xml = "<!DOCTYPE classes SYSTEM \"" . dirname(__FILE__) .
    "/../../../lib/tools/dtd/GalleryClass2.1.dtd\">\n";
$xml .= "<classes>\n";
if (!$dh = opendir('.')) {
    print "Unable to opendir(.)\n";
    exit(1);
}

$classXml = '';
while (($file = readdir($dh)) !== false) {
    if (preg_match('/\.class$/', $file)) {
	$snippet = getXml($file);
	if ($snippet) {
	    $classXml .= "<class>\n" . join("\n", $snippet) . "\n</class>\n";
	}
    }
}
closedir($dh);

if (empty($classXml)) {
    /* Nothing to do */
    exit(0);
}

$xml .= $classXml;
$xml .= "</classes>\n";

$entitiesXml = "$tmpdir/Entities.xml";
if (!$fp = fopen($entitiesXml, 'wb')) {
    print "Unable to write to $entitiesXml\n";
    exit(1);
}
fwrite($fp, $xml);
fclose($fp);

if (system("xmllint --valid --noout $entitiesXml", $retval)) {
    print "System error: $retval\n";
    exit;
}

$p =& new XmlParser();
$root = $p->parse($entitiesXml);

$entities = array();
foreach ($root[0]['child'] as $entity) {
    $entityName = $entity['child'][0]['content'];
    $parentEntityName = $entity['child'][1]['content'];

    $j = 3;
    if ($entity['child'][$j]['name'] == 'REQUIRES-ID') {
	$j++;
    }

    $entities[$entityName]['members'] = array();
    $entities[$entityName]['linked'] = array();
    for (; $j < count($entity['child']); $j++) {
	$member = $entity['child'][$j];
	$name = $member['child'][0]['content'];

	$entities[$entityName]['members'][$name]['type'] =
	    'STORAGE_TYPE_' . $member['child'][1]['content'];
	$entities[$entityName]['members'][$name]['type'] =
	    'STORAGE_TYPE_' . $member['child'][1]['content'];

	for ($k = 2; $k < count($member['child']); $k++) {
	    if (!empty($member['child'][$k]['name'])) {
		switch($member['child'][$k]['name']) {
		case 'MEMBER-SIZE':
		    $entities[$entityName]['members'][$name]['size'] =
			$size = 'STORAGE_SIZE_' . $member['child'][$k]['content'];
		    break;

		case 'ID':
		    $entities[$entityName]['members'][$name]['type'] .= '| STORAGE_TYPE_ID';
		    break;

		case 'LINKED':
		    $entities[$entityName]['linked'][] = $name;
		    break;
		}
	    }
	}
    }

    $entities[$entityName]['parent'] = $parentEntityName;
    $entities[$entityName]['module'] = basename(dirname(realpath('.')));
}

$smarty->assign('entities', $entities);
$new = $smarty->fetch('entities.tpl');

$fd = fopen('Entities.inc', 'w');
fwrite($fd, $new);
fclose($fd);

/* Clean up the cheap and easy way */
if (file_exists($tmpdir)) {
    system("rm -rf $tmpdir");
}

/* Done */
exit(0);

function getXml($filename) {
    $results = array();
    if ($fp = fopen($filename, 'rb')) {
	while (!feof($fp)) {
	    $line = fgets($fp, 4096);
	    if (preg_match('/@g2(.*)/', $line, $matches)) {
		$results[] = $line = $matches[1];

		/*
		 * NOTE!  Keep this in sync with the similar block in extractClassXml.pl
		 * and generate-dbxml.php
		 */
		if (preg_match('{<class-name>(.*)</class-name>}', $line, $matches)) {
		    $schemaName = $matches[1];
		    $schemaName = preg_replace('/^Gallery/', '', $schemaName);
		    /* Shorten some table names to fit Oracle's 30 char name limit.. */
		    $schemaName = preg_replace('/Preferences/', 'Prefs', $schemaName);
		    $schemaName = preg_replace('/Toolkit/', 'Tk', $schemaName);
		    $schemaName = preg_replace('/TkOperation/', 'TkOperatn', $schemaName);
		}

		if (preg_match('{<schema>}', $line)) {
		    $results[] = "   <schema-name>$schemaName</schema-name>";
		}
	    }
	}
	fclose($fp);
    }
    return $results;
}
?>

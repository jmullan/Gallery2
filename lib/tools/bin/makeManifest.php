#!php -q
<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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
    die("You must run this from the command line\n");
}

if (!function_exists('file_put_contents')) {
    /* Define file_put_contents if running PHP 4.x */
    function file_put_contents($path, $data) {
	if (false === ($file = fopen($path, 'w')) || false === fwrite($file, $data)) {
	    return false;
	}
	fclose($file);
	return true;
    }
}

$startTime = time();
$quiet = false;
$path = null;
array_shift($argv);

for ($i = 0; $i < count($argv); $i++) {
    if ($argv[$i] === '-q') {
	$quiet = true;
    } else if ($argv[$i] === '-p') {
	$path = $argv[++$i];
    }
}

/* Just so we are consistent lets standardize on Unix path sepearators */
$baseDir = dirname(dirname(dirname(dirname(__file__)))) . '/';
$baseDir = str_replace("\\", '/', $baseDir);
chdir($baseDir);

if (empty($path)) {
    $path = $baseDir;
} else if (!file_exists($path)) {
    die("The directory '$path' does not exist");
} else if (!is_dir($path)) {
    die("The specified path ('$path') is not a directory");
} else if (!preg_match('#^(modules|themes)(/\w+)?/?$#', $path)) {
    die("The path '$path' must be a relative path to a plugin (e.g. modules/core)");
}

quietprint("Finding all files...\n");
$entries = listSvn($path);
quietprint("\n");

/* sort */
quietprint("Sorting...");
sort($entries);
quietprint("\n");

/* Split into sections */
$sections = array();
quietprint("Separating into sections...");
foreach ($entries as $file) {
    $matches = array();
    if (preg_match('#(^.*)((modules|layouts|themes)[\\/].*?)[\\/]#', $file, $matches) !== 0) {
    	$sections["{$matches[2]}/MANIFEST"][] = $file;
    } else {
    	$sections['MANIFEST'][] = $file;
    }
}
quietprint("\n");

/* Now generate the checksum files */
quietprint("Generating checksums...\n");
$changed = 0;
$total = 0;

foreach ($sections as $manifest => $entries) {
    $oldLines = file($manifest);
    $oldContent = implode('', $oldLines);
    $nl = preg_match('/\r\n/', $oldContent) ? "\r\n" : "\n";
    $matches = array();
    preg_match('/Revision: (\d+\s*)\$/', $oldLines[0], $matches);
    $oldRevision = $matches[1];

    $newContent = "# \$Revision$oldRevision\$$nl";
    $newContent .= "# File crc32 crc32(crlf) size size(crlf)  or  R File$nl";

    $deleted = array();
    $seen = array();
    foreach ($entries as $entry) {
	list ($file, $isBinary) = preg_split('/\@\@/', $entry);
	
	if (preg_match('/deleted:(.*)/', $file, $matches)) {
	    $deleted[$matches[1]] = true;
	} else {
	    $seen[$file] = true;
	    $fileHandle = fopen($file, 'rb');
	    $fileSize = filesize($file);
	    $data = fread($fileHandle, $fileSize);
	    fclose($fileHandle);

	    $data_crlf = $data;
	    if ($isBinary) {
		$size = $size_crlf = filesize($file);
	    } else {
		if (preg_match("/\r\n/", $data)) {
		    $data = str_replace("\r\n", "\n", $data);
		} else {
		    $data_crlf = str_replace("\n", "\r\n", $data_crlf);
		}
		$size = strlen($data);
		$size_crlf = strlen($data_crlf);
	    }
	    
	    $cksum = crc32($data);
	    $cksum_crlf = crc32($data_crlf);
	    $file = substr($file, strlen($baseDir));
	    $newContent .= 
		sprintf("$file\t%u\t%u\t%d\t%d$nl", $cksum, $cksum_crlf, $size, $size_crlf);
	}
    }

    if (!empty($oldLines)) {
	foreach ($oldLines as $line) {
	    if ($line[0] == '#') {
		continue;
	    }
	    if (preg_match('/^R\t(.*)$/', $line, $matches)) {
		$file = $baseDir . trim($matches[1]);
		if (empty($seen[$file])) {
		    $deleted[$file] = true;
		}
	    } else {
		preg_match('/^(.+?)\t/', $line, $matches);
		$file = $baseDir . trim($matches[1]);
		if (empty($seen[$file])) {
		    $deleted[$file] = true;
		}
	    }
	}

	$deletedFiles = array_keys($deleted);
	foreach ($deletedFiles as $file) {
	    $file = substr($file, strlen($baseDir));
	    $newContent .= "R\t$file$nl";
	}
    }

    if ($oldContent != $newContent) {
	file_put_contents($manifest, $newContent);
	$changed++;
    }
    $total++;

    quietprint(".");
}

quietprint("\n");
quietprint(sprintf("Completed in %d seconds\n", time() - $startTime));
quietprint(sprintf("Manifests changed: $changed (total: $total)\n"));

/**
 * If quiet mode is not enabled, display the message on standard out.
 * @param string $message Message to display.
 */
function quietPrint($message) {
    global $quiet;
    if (!$quiet) {
	print "$message";
    }
}

/**
 * Retrieve the SVN Entries
 * @param string $path Path to create retrieve the SVN entries for.
 * @return array List of SVN entries
 */
function listSvn($path) {
    $entries = array();

    $binaryList = array();
    exec("svn propget --non-interactive -R svn:mime-type $path", $output);
    foreach ($output as $line) {
	$parts = preg_split('/\s-\s/', $line);
	$file = str_replace("\\", '/', $parts[0]);
	$binaryList[$file] = 1;
    }

    $output = array();
    exec("svn status --non-interactive -v -q $path", $output);
    foreach ($output as $line) {
	$matches = array();
	if (preg_match('/^(.).....\s*\d+\s+[\d|\?]+\s+\S+\s+(.*)$/', $line, $matches) == 0) {
	    die("Unexpected SVN status format:\n$line\n");
	}
	if (!file_exists($matches[2])) {
	    die("The file '$matches[2]' does not exist");
	}

	if (is_dir($matches[2])) {
	    continue;
	}

	if (preg_match('#[\\/]MANIFEST#', $matches[2]) > 0) {
	    continue;
	}

	if ($matches[1] == 'M') {
	    quietprint("Warning: $matches[2] is locally modified\n");
	} else if (!in_array($matches[1], array(' ', 'D', 'M'))) {
	    die("Check {$matches[1]} status for {$matches[2]}");
	}

	$status = $matches[1] === 'D' ? 'deleted:' : '';

	$file = str_replace("\\", '/', $matches[2]);
	$entries[] = sprintf("%s%s@@%d", $status, $file, isset($binaryList[$file]));
    }
    return $entries;
}

?>

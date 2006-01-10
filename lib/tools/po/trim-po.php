<?php
/**
 * Usage: php trim-po.php xx_YY.po
 * Prints a copy of xx_YY.po, omitting all translations that match xx.po.
 * Simply prints the given file if not of the form xx_YY.po or xx.po does not exist.
 */
$path = $argv[1];
$langpath = preg_replace('{(..)_..\.po$}', '$1.po', $path);
if ($langpath == $path || !file_exists($langpath)) {
    readfile($path);
    if ($langpath != $path) {
	fwrite(STDERR, "\nWarning: $path without $langpath\n");
    }
    exit;
}

list ($po, $header) = readPo($path);
list ($langpo) = readPo($langpath);

print $header;
foreach ($po as $id => $str) {
    if (!isset($langpo[$id]) || $langpo[$id] != $str) {
	print $id . $str . "\n";
    }
}

function readPo($path) {
    $header = $data = array();
    $lines = file($path);
    for ($line = 'a'; $lines && trim($line); $header[] = $line) {
	$line = array_shift($lines);
    }
    $id = $str = false;
    $key = $value = '';
    while ($lines) {
	$line = array_shift($lines);
	if (!$id && substr($line, 0, 5) == 'msgid') {
	    $id = true;
	} else if ($id && substr($line, 0, 6) == 'msgstr') {
	    $str = true;
	} else if ($id && $str && !trim($line)) {
	    $data[$key] = $value;
	    $id = $str = false;
	    $key = $value = '';
	    continue;
	}
	if ($str) {
	    $value .= $line;
	} else if ($id) {
	    $key .= $line;
	}
    }
    if ($key && $value) {
	$data[$key] = $value;
    }
    return array($data, implode('', $header));
}
?>

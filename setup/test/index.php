<?php
require('init.php');
require('TestCase.class');

$testDir = 'TestCase';
if ($dir = opendir($testDir)) {
    while (($file = readdir($dir)) != false) {
	if (preg_match('/.class$/', $file)) {
	    require_once($testDir . '/' . $file);

	    $name = str_replace('.class', '', $file);
	    $className = $name . 'TestCase';
	    $class = new $className();
	    $testTable[$name] = $class;
	}
    }
    closedir($dir);
} else {
    print "Unable to open test dir";
}

print '<center>';
print '<h1> Test Harness </h1>';
print '<table border=1 cellspacing=0 cellpadding=5>';
print '<tr>';
print '<th bgcolor=#9999CC> Name';
print '<th bgcolor=#9999CC> Description';
print '</tr>';

ksort($testTable);
$evenOdd = 0;
foreach ($testTable as $name => $class) {
    print '<tr>';
    if ($evenOdd++ % 2) {
	$bgColor = '#EEEEEE';
    } else {
	$bgColor = '#CCCCCC';
    }
    print '<td bgColor=' . $bgColor . '>';
    print '<a href=index.php?runTest=' . $name . '>';
    print $name;
    print '</a>';
    print '</td>';
    print '<td bgColor=' . $bgColor . '>';
    print $class->getDescription();
    print '</td>';
    print '</tr>';
}

print '</table>';
print '</center>';

print '<br>';
print '<hr>';

if (!empty($HTTP_GET_VARS['runTest'])) {
    $runTest = $HTTP_GET_VARS['runTest'];

    $class = $testTable[$runTest];

    if ($class->useDefaultDatabase()) {
	include('connectToDbDefault.php');
    } else {
	include('connectToDbNoDefault.php');
    }


    print '<b>Test: ' . $runTest . '</b>';
    print '<br>';
    
    print '<b>Start</b><br>';
    set_time_limit(30);
    $ret = $class->start();
    if ($ret->isSuccess()) {
	print 'Status: Success<br>';
    } else {
	print 'Status: ' . $ret->getAsString();
    }

    print '<br>';
    
    print '<b>Cleanup</b><br>';
    $ret = $class->cleanup();
    if ($ret->isSuccess()) {
	print 'Status: Success<br>';
    } else {
	print 'Status: ' . $ret->getAsString();
    }

    print '<hr>';
    print '<b>Debug Output</b>';
    print '<pre>';
    foreach ($class->getDebugOutput() as $line) {
	print $line;
    }
    print '</pre>';
}
?>

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
print '<h1> <a href=index.php>Test Harness</a> </h1>';
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
    print '<a href=index.php?testName=' . $name . '>';
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

if (!empty($HTTP_GET_VARS['testName'])) {
    ob_start();
    $ret = runTest($HTTP_GET_VARS['testName']);
    $buf = ob_get_contents();
    ob_end_clean();

    if ($ret->isError()) {
	print 'Overall Status: ' . $ret->getAsString() . '<br>';
    } else {
	print 'Overall Status: Success<br>';
    }

    print '<hr>';

    print $buf;
}

function runTest($testName) {
    global $testTable;
    global $gallery;
    
    $class = $testTable[$testName];

    $dependencies = $class->getDependencies();
    foreach ($dependencies as $test) {
	$ret = runTest($test);
	if ($ret->isError()) {
	    return $ret;
	}
    }

    if ($class->requireDatabaseConnection()) {
	/* Set up our storage */
	$storage = new DatabaseStorage();
	$config = $gallery->getConfig();
	$storage->setType($config->get('storage.database.type'));
	$storage->setHostname($config->get('storage.database.hostname'));
	$storage->setUsername($config->get('storage.database.username'));
	$storage->setPassword($config->get('storage.database.password'));
	if ($class->useDefaultDatabase()) {
	    $storage->setDatabase($config->get('storage.database.database'));
	}
	$ret = $storage->connect();
	if ($ret->isError()) {
	    print "Error: ";
	    print $ret->getAsString();
	    exit;
	}
    
	$gallery->setStorage($storage);
    }

    print '<b>Test: ' . $testName . '</b>';
    print '<br>';
    
    print '<b>Start</b><br>';
    set_time_limit(30);
    $ret1 = $class->start();
    if ($ret1->isSuccess()) {
	print 'Status: Success<br>';
    } else {
	print 'Status: ' . $ret->getAsString();
    }

    print '<br>';
    
    print '<b>Cleanup</b><br>';
    $ret2 = $class->cleanup();
    if ($ret2->isSuccess()) {
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

    if ($ret1->isError()) {
	return $ret1;
    }

    return $ret2;
}
?>

<?php
require_once('../../init.php');
require_once('TestCase.class');
require_once('TestCase/ActivateModule.class');
require_once('TestCase/DeactivateModule.class');
$tests = array();

$ret = main();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();

    if ($gallery->getDebug() == 'buffered') {
	print '<pre>';
	print $gallery->getDebugBuffer();
	print '</pre>';
    }
}

function main() {

    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Init our storage */
    $ret = GalleryInitStorage();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    global $gallery;
    $ret = $gallery->beginTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryTestHarness();
    if ($ret->isError()) {
	$gallery->rollbackTransaction();
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = $gallery->commitTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return GalleryStatus::success();
}

function GalleryTestHarness() {
    global $gallery;
    global $tests;
    global $HTTP_GET_VARS;

    /*
     * Pretend to be the admin
     */
    $gallery->setActiveUserId(4);

    $modulesDir = $gallery->getConfig('code.gallery.modules');

    $platform = $gallery->getPlatform();

    /*
     * Load the test cases for every module (active or not).
     */
    list ($ret, $moduleNames) = $gallery->getAllModuleNames();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    foreach ($moduleNames as $moduleName) {
	$testDir = $modulesDir . $moduleName . '/test/TestCase';

	/* Add our implicit tests */
	foreach (array('ActivateModule', 'DeactivateModule') as $implicitTestName) {
	    $className = $implicitTestName . 'TestCase';
	    $testCase = new $className($moduleName);
	    $test = array('moduleName' => $moduleName,
			  'testName' => $implicitTestName,
			  'class' => $testCase,
			  'description' => $testCase->getDescription());
	    $tests[$moduleName][$implicitTestName] = $test;
	}

	$files = array();
	if ($platform->file_exists($testDir) && $platform->is_dir($testDir) && $dir = $platform->opendir($testDir)) {
	    while (($file = readdir($dir)) != false) {
		if (preg_match('/.class$/', $file)) {
		    $files[] = $file;
		    require_once($testDir . '/' . $file);
		}
	    }
	    closedir($dir);

	    /* Add our explicit tests */
	    foreach ($files as $file) {
		$testName = str_replace('.class', '', $file);
		$className = $testName . 'TestCase';
		$testCase = new $className();
		$test = array('moduleName' => $moduleName,
			      'testName' => $testName,
			      'class' => $testCase,
			      'description' => $testCase->getDescription());
		foreach ($testCase->getIterations() as $iter) {
		    $test['iterations'][$iter] = array('count' => $iter,
						       'title' => shorten($iter));
		}
		$tests[$moduleName][$testName] = $test;
	    }
	}
    }

    /*
     * Alphabetize the module names and test names
     */
    ksort($tests);
    foreach ($tests as $moduleName => $testArray) {
	ksort($tests[$moduleName]);
    }

    /* Suppress preliminary debug output */
    if (0) {
	print '<pre>';
	print_r($gallery->getDebugBuffer());
	print '</pre>';
    }
    $gallery->clearDebugBuffer();

    $results = array();
    if (!empty($HTTP_GET_VARS['testName']) &&
	!empty($HTTP_GET_VARS['moduleName'])) {
    
	$testName = $HTTP_GET_VARS['testName'];
	$moduleName = $HTTP_GET_VARS['moduleName'];
    
	$iterations = 1;
	$disableDebug = false;
	if (!empty($HTTP_GET_VARS['iterations'])) {
	    $iterations = $HTTP_GET_VARS['iterations'];
	    $disableDebug = true;
	}

	if ($disableDebug) {
	    /* Temporarily turn off debug mode */
	    global $gallery;
	    $debug = $gallery->getDebug();
	    $gallery->setDebug(false);
	}
	
	$results = $results + runTest($moduleName, $testName, $iterations);
	if ($disableDebug) {
	    $gallery->setDebug($debug);
	}
    }

    $rollup = array();
    if (sizeof($results) > 1) {
	$rollup['elapsed'] = 0.0;
	foreach ($results as $result) {
	    if (!empty($result['error']) && empty($rollup['error'])) {
		$rollup['error'] = $result['error'];
	    }
	    $rollup['elapsed'] += $result['timing']['elapsed'];
	}
    }

    /* Get the Smarty instance. */
    $template = new GalleryTemplate(null, null, 
				    dirname(__FILE__) . '/templates');
    $template->setVariable('tests', $tests);
    $template->setVariable('results', $results);
    $template->setVariable('rollup', $rollup);
    print $template->render('index.tpl');

    return GalleryStatus::success();
}

function shorten($number) {
    $number = str_replace('000000', 'M', $number);
    $number = str_replace('00000', '00K', $number);
    $number = str_replace('0000', '0K', $number);
    $number = str_replace('000', 'K', $number);
    return $number;
}

function runTest($moduleName, $testName, $iterations) {
    global $gallery;
    global $tests;

    $results = array();
    $class = $tests[$moduleName][$testName]['class'];

    /* Satisfy all dependencies first */
    $dependencies = $class->getDependencies();
    foreach ($dependencies as $dependency) {
	$results = array_merge($results,
			       runTest($dependency['moduleName'],
				       $dependency['testName'],
				       $iterations));
    }

    /* Run the test */
    ob_start();

    $gallery->setTimeLimit(30);
    list ($timing, $ret1) = $class->start($iterations);
    $ret2 = $class->cleanup();

    $result = array();
    $result['moduleName'] = $moduleName;
    $result['testName'] = $testName;
    $result['iterations'] = $iterations;
    $result['timing'] = $timing;
    $result['debug'] = $gallery->getDebugBuffer();
    $gallery->clearDebugBuffer();
    
    $result['output'] = ob_get_contents();
    ob_end_clean();

    if ($ret1->isError() || $ret2->isError()) {
	if ($ret1->isError()) {
	    $ret1 = $ret1->wrap(__FILE__, __LINE__);
	    $result['error'] = $ret1->getAsHtml();
	} else {
	    $ret2 = $ret2->wrap(__FILE__, __LINE__);
	    $result['error'] = $ret2->getAsHtml();
	}
    } else {
	$result['error'] = null;
    }
    $results[] = $result;

    return $results;
}
?>

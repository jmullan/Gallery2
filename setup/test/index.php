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

    /* Configure our url Generator for the test harness */
    $urlGenerator = new GalleryUrlGenerator('../../main.php');
    $gallery->setUrlGenerator($urlGenerator);

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
    list ($ret, $moduleIds) = $gallery->getAllModuleIds();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    foreach ($moduleIds as $moduleId) {
	$testDir = $modulesDir . $moduleId . '/test/TestCase';

	/* Add our implicit tests */
	foreach (array('ActivateModule', 'DeactivateModule') as $implicitTestName) {
	    $className = $implicitTestName . 'TestCase';
	    $testCase = new $className($moduleId);
	    $test = array('moduleId' => $moduleId,
			  'testName' => $implicitTestName,
			  'class' => $testCase,
			  'description' => $testCase->getDescription());
	    $tests[$moduleId][$implicitTestName] = $test;
	}

	$files = array();
	if ($platform->file_exists($testDir) &&
	        $platform->is_dir($testDir) &&
	        $dir = $platform->opendir($testDir)) {
	    while (($file = $platform->readdir($dir)) != false) {
		if (preg_match('/.class$/', $file)) {
		    $files[] = $file;
		    require_once($testDir . '/' . $file);
		}
	    }
	    $platform->closedir($dir);

	    /* Add our explicit tests */
	    foreach ($files as $file) {
		$testName = str_replace('.class', '', $file);
		$className = $testName . 'TestCase';
		$testCase = new $className();
		$test = array('moduleId' => $moduleId,
			      'testName' => $testName,
			      'class' => $testCase,
			      'description' => $testCase->getDescription());
		foreach ($testCase->getIterations() as $iter) {
		    $test['iterations'][$iter] = array('count' => $iter,
						       'title' => shorten($iter));
		}
		$tests[$moduleId][$testName] = $test;
	    }
	}
    }

    /*
     * Alphabetize the module names and test names
     */
    ksort($tests);
    foreach ($tests as $moduleId => $testArray) {
	ksort($tests[$moduleId]);
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
	!empty($HTTP_GET_VARS['moduleId'])) {
    
	$testName = $HTTP_GET_VARS['testName'];
	$moduleId = $HTTP_GET_VARS['moduleId'];
    
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
	
	$results = $results + runTest($moduleId, $testName, $iterations);
	if ($disableDebug) {
	    $gallery->setDebug($debug);
	}
    }

    $rollup = array();
    $rollup['elapsed'] = 0.0;
    foreach ($results as $result) {
	if (!empty($result['error']) && empty($rollup['error'])) {
	    $rollup['error'] = $result['error'];
	}
	$rollup['elapsed'] += $result['timing']['elapsed'];
    }

    /* Get the Smarty instance. */
    $template = new GalleryTemplate(dirname(__FILE__) . '/templates');
    $template->setVariable('tests', $tests);
    $template->setVariable('results', $results);
    $template->setVariable('rollup', $rollup);
    list($ret, $html) = $template->render('index.tpl');
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    print $html;

    /* If we had any errors, pass them back now */
    if (isset($rollup['error'])) {
	return $rollup['error']['object']->wrap(__FILE__, __LINE__);
    }
    
    return GalleryStatus::success();
}

function shorten($number) {
    $number = str_replace('000000', 'M', $number);
    $number = str_replace('00000', '00K', $number);
    $number = str_replace('0000', '0K', $number);
    $number = str_replace('000', 'K', $number);
    return $number;
}

function runTest($moduleId, $testName, $iterations) {
    global $gallery;
    global $tests;

    $results = array();
    $class = $tests[$moduleId][$testName]['class'];

    /* Satisfy all dependencies first */
    $dependencies = $class->getDependencies();
    foreach ($dependencies as $dependency) {
	$results = array_merge($results,
			       runTest($dependency['moduleId'],
				       $dependency['testName'],
				       $iterations));
    }

    /* Run the test */
    ob_start();

    $gallery->setTimeLimit(30);
    list ($timing, $ret1) = $class->start($iterations);
    $ret2 = $class->cleanup();

    $result = array();
    $result['moduleId'] = $moduleId;
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
	    $result['error']['html'] = $ret1->getAsHtml();
	    $result['error']['object'] = $ret1;
	} else {
	    $ret2 = $ret2->wrap(__FILE__, __LINE__);
	    $result['error']['html'] = $ret2->getAsHtml();
	    $result['error']['object'] = $ret2;
	}
    } else {
	$result['error'] = null;
    }
    $results[] = $result;

    return $results;
}
?>

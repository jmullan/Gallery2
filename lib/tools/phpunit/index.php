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
/**
 * @package Gallery
 * @subpackage PHPUnit
 */
include('../../support/security.inc');
include('../../../bootstrap.inc');
require_once('../../../init.inc');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');
require_once('GalleryControllerTestCase.class');
require_once('ItemAddPluginTestCase.class');
require_once('ItemEditPluginTestCase.class');
require_once('CodeAuditTestCase.class');
require_once('UnitTestPlatform.class');
require_once('MockTemplateAdapter.class');

function PhpUnitGalleryMain(&$testSuite, $filter) {
    $ret = GalleryInitFirstPass();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryInitSecondPass();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    global $gallery;

    /* Configure our url Generator, find the correct base URL */
    $urlGenerator = new GalleryUrlGenerator();
    $ret = $urlGenerator->init('index.php');
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    $urlDir = str_replace('lib/tools/phpunit/', '', $urlGenerator->getCurrentUrlDir());
    $path = substr($urlDir, strlen($urlGenerator->makeUrl('/')) - 1);
    $urlGenerator = new GalleryUrlGenerator();
    $ret = $urlGenerator->init($path . GALLERY_MAIN_PHP);
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    $gallery->setUrlGenerator($urlGenerator);

    /*
     * Commit our transaction here because we're going to have a new
     * transaction for every test.
     */
    $storage =& $gallery->getStorage();
    $ret = $storage->commitTransaction();
    if ($ret) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
    if ($ret) {
	print $ret->getAsHtml();
	return;
    }

    if ($isSiteAdmin) {

	/*
	 * Load the test cases for every active module.
	 */
	list ($ret, $moduleStatusList) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$suiteArray = array();
	foreach ($moduleStatusList as $moduleId => $moduleStatus) {
	    $modulesDir = GalleryCoreApi::getPluginBaseDir('module', $moduleId) . 'modules/';
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    $testDir = $modulesDir . $moduleId . '/test/phpunit';
	    $suiteArray += loadTests($moduleId, $testDir, $filter);
	}

	/* Add repository tools tests. */
	$suiteArray += loadTests(
	    'repositorytools', dirname(__FILE__) . '/../repository/test/phpunit', $filter);

	$keys = array_keys($suiteArray);
	natcasesort($keys);

	foreach ($keys as $className) {
	    $testSuite->addTest($suiteArray[$className]);
	}
    }

    $counter =& GalleryTestCase::getEntityCounter();
    GalleryCoreApi::registerEventListener('GalleryEntity::save', $counter);
    GalleryCoreApi::registerEventListener('GalleryEntity::delete', $counter);

    return null;
}

function loadTests($moduleId, $testDir, $filter) {
    global $gallery;
    $moduleArray = array();

    $platform =& $gallery->getPlatform();
    if ($platform->file_exists($testDir) &&
	$platform->is_dir($testDir) &&
	$dir = $platform->opendir($testDir)) {

	if (empty($filter)) {
	    $filterRegexp = '.*';
	} else {
	    $filterRegexp = $filter;
	}

	while (($file = $platform->readdir($dir)) != false) {
	    if (preg_match('/(.*Test).class$/', $file, $matches)) {
		require_once($testDir . '/' . $file);
			$className = $matches[1];
		if (class_exists($className) &&
			GalleryUtilities::isA(new $className(null), 'GalleryTestCase')) {
		    $moduleArray[$className] = new TestSuite($className, $moduleId, $filterRegexp);
		}
	    }
	}
	$platform->closedir($dir);
    }

    return $moduleArray;
}

class GalleryTestResult extends TestResult {
    var $_totalElapsed = 0;
    var $_testsFailed = 0;

    function GalleryTestResult() {
	$this->TestResult();
    }

    function report() {
	/* report result of test run */
	global $compactView;
	$nRun = $this->countTests();
	$nFailures = $this->failureCount();

	if ($nFailures) print("</ol>\n");
	if (!isset($compactView)) {
	    print '<script type="text/javascript">';
	    print 'function setTxt(i,t) { document.getElementById(i).firstChild.nodeValue=t; }';
	    printf("setTxt('testTime','%2.4f');", $this->_totalElapsed);
	    printf("setTxt('testCount','%s test%s');", $nRun, ($nRun == 1) ? '' : 's');
	    printf("setTxt('testFailCount','%s test%s');",
		    $this->_testsFailed, ($this->_testsFailed == 1) ? '' : 's');
	    printf("setTxt('testErrorCount','%s error%s');",
		    $nFailures, ($nFailures == 1) ? '' : 's');
	    print "document.getElementById('testSummary').style.display='block';</script>\n";
	}
	if ($nFailures == 0)
	    return;

	$failures = $this->getFailures();
	$newFilter = array();
	foreach ($failures as $failure) {
	    $newFilter[$failure->getClassName() . '.' . $failure->getTestName()] = 1;
	}
	printf('<script type="text/javascript">var failedTestFilter="(%s)$";%s</script>',
		implode('|', array_keys($newFilter)),
		"document.getElementById('runBrokenButton').style.display='block';");
    }

    function _endTest($test) {
	$failure = $extra = '';
	if ($test->wasSkipped()) {
	    global $compactView;
	    if (isset($compactView)) return;
	    $class = 'Skipped';
	    $text = 'r.cells[4].lastChild.nodeValue="SKIP";';
	    $extra = 'r.className="skip";';
	    $elapsed = '0.0000';
	} else {
	    $elapsed = sprintf("%2.4f", $test->elapsed());
	    $this->_totalElapsed += $elapsed;
	    if ($test->failed()) {
		$class = 'Failure';
		$text = 'r.cells[4].firstChild.style.display="inline";';
		$failure = $this->_testsFailed++ ? '' : '<h2>Failure Details</h2><ol>';
		$failure .= '<li><a href="?filter=' .
		    urlencode('^' . $test->getModuleId() . '.' . $test->classname() . '.' .
			      $test->name() . '$') .
		    '" name="fail' . $this->fRunTests . '">' . $test->classname() . '.' .
		    $test->name() . "</a></li><ul>\n";
		foreach ($test->getExceptions() as $exception) {
		    $failure .= '<li>' . $exception->getMessage() . "</li>\n";
		}
		$failure .= "</ul>\n";
	    } else {
		$class = 'Pass';
		$text = 'r.cells[4].lastChild.nodeValue="OK";';
		global $testOneByOne;
		if (isset($testOneByOne)) {
		    $i = $testOneByOne + 1;
		    $x = substr($_GET['filter'], 0, strrpos($_GET['filter'], ':') + 1);
		    print '<meta http-equiv="refresh" content="0; index.php?filter=' .
			"$x$i-$i" . '&amp;onebyone=true"/>';
		}
	    }
	}
	print '<script type="text/javascript">r=document.getElementById(\'testRow'
		. $this->fRunTests . "');$extra";
	print "r.cells[4].className='$class';$text";
	print "r.cells[5].firstChild.nodeValue='$elapsed';</script>\n$failure";
	flush();
    }
}

define('FILTER_MAX', 1000000);
if (isset($_GET['filter'])) {
    $filter = trim($_GET['filter']);
    if (substr($filter, -5) == ':1by1') {
	$testOneByOne = $compactView = 1;
	$_GET['filter'] = $filter = substr($filter, 0, -3) . '-1';
    } else if (!empty($_GET['onebyone'])) {
	$testOneByOne = $compactView = (int)substr($filter, strrpos($filter, '-') + 1);
    }
    $range = array();
    $skip = explode(',', $filter);
    foreach ($skip as $tempSkip) {
	if (preg_match('/(\d+)-(\d+)/', $tempSkip, $matches)) {
	    if ($matches[1] >= 1 && $matches[1] <= FILTER_MAX &&
		$matches[2] >= 1 && $matches[2] <= FILTER_MAX) {
		$range[] = array($matches[1], $matches[2]);
		$filter = trim(preg_replace('/:?\d+-\d+,?/', '', $filter, 1));
	    }
	} else if (preg_match('/(\d+)-/', $filter, $matches)) {
	    if ($matches[1] >= 1 && $matches[1] <= FILTER_MAX) {
		$range[] = array($matches[1], FILTER_MAX);
		$filter = trim(preg_replace('/:?\d+-,?/', '', $filter, 1));
	    }
	} else if (preg_match('/-(\d+)/', $filter, $matches)) {
	    if ($matches[1] >= 1 && $matches[1] <= FILTER_MAX) {
		$range[] = array(1, $matches[1]);
		$filter = preg_replace('/:?-\d+,?/', '', $filter, 1);
	    }
	}
    }
    $displayFilter = $filter;
    if (count($range) == 0) {
	$range[] = array(1, FILTER_MAX);
    }
    for ($j=0; $j < count($range); $j++) {
	if ($j == 0 && $j == (count($range)-1)) {
	    if ($range[$j][0] != 1 || $range[$j][1] != FILTER_MAX) {
		$displayFilter .= sprintf(':%d-%d', $range[$j][0], $range[$j][1]);
	    }
	} else if ($j == 0) {
	    $displayFilter .= sprintf(':%d-%d,', $range[$j][0], $range[$j][1]);
	} else if ($j == (count($range)-1)) {
	    $displayFilter .= sprintf('%d-%d', $range[$j][0], $range[$j][1]);
	} else {
	    $displayFilter .= sprintf('%d-%d,', $range[$j][0], $range[$j][1]);
	}
    }
} else {
    $filter = 'match_nothing';
    $displayFilter = null;
    $range = array(array(1, FILTER_MAX));
}
$testSuite = new TestSuite();
$ret = PhpUnitGalleryMain($testSuite, $filter);
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    print $gallery->getDebugBuffer();
    return;
}

list ($ret, $moduleStatusList) = GalleryCoreApi::fetchPluginStatus('module');
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

$session = $gallery->getSession();
if (!$session->isUsingCookies()) {
    $sessionKey = GALLERY_FORM_VARIABLE_PREFIX . $session->getKey();
    $sessionId = $session->getId();
}

list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

/* Check that our dev environment is correct */
$incorrectDevEnv = array();
foreach (array('error_reporting' => array(2047),
	       'short_open_tag' => array('off', 0),
	       'magic_quotes_gpc' => array('on', 1),
	       'allow_call_time_pass_reference' => array('off', 0),
	       'register_globals' => array('off', 0),
	       'display_errors' => array('on', 1),
	       'allow_url_fopen' => array('off', 0),
	       'include_path' => array('/bogus')) as $key => $expected) {
    $actual = ini_get($key);
    if (!in_array($actual, $expected)) {
	$incorrectDevEnv[$key] = array($expected, $actual);
    }
}

/*
 * Uncomment this to see debug output before tests run
print "<pre>";
print $gallery->getDebugBuffer();
print "</pre>";
 */
include(dirname(__FILE__) . '/index.tpl');

/* Compact any ACLs that were created during this test run */
$ret = GalleryCoreApi::compactAccessLists();
if ($ret) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

$storage =& $gallery->getStorage();
$ret = $storage->commitTransaction();
if ($ret) {
    return $ret->wrap(__FILE__, __LINE__);
}
?>

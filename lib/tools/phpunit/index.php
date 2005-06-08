<?php
/**
 * @package Gallery
 * @subpackage PHPUnit
 */
include('../security.inc');
include('../../../bootstrap.inc');
require_once('../../../init.inc');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');
require_once('GalleryControllerTestCase.class');
require_once('ItemAddPluginTestCase.class');
require_once('ItemEditPluginTestCase.class');
require_once('CodeAuditTestCase.class');
require_once('UnitTestPlatform.class');

function PhpUnitGalleryMain(&$testSuite, $filter) {
    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    global $gallery;

    /* Configure out url Generator for phpunit mode. */
    $urlGenerator = new GalleryUrlGenerator();
    $urlGenerator->init('lib/tools/phpunit/');
    $gallery->setUrlGenerator($urlGenerator);

    /*
     * Commit our transaction here because we're going to have a new
     * transaction for every test.
     */
    $storage =& $gallery->getStorage();
    $ret = $storage->commitTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
    if ($ret->isError()) {
	print $ret->getAsHtml();
	return;
    }

    if ($isSiteAdmin) {

	/*
	 * Load the test cases for every active module.
	 */
	list ($ret, $moduleStatusList) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$platform = $gallery->getPlatform();
	$modulesDir = dirname(__FILE__) . '/../../../modules/';
	$suiteArray = array();
	foreach ($moduleStatusList as $moduleId => $moduleStatus) {
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    $testDir = $modulesDir . $moduleId . '/test/phpunit';

	    if ($platform->file_exists($testDir) &&
		$platform->is_dir($testDir) &&
		$dir = $platform->opendir($testDir)) {

		if (empty($filter)) {
		    $filterRegexp = '.*';
		} else {
		    $filterRegexp = $filter;
		}

		while (($file = $platform->readdir($dir)) != false) {
		    if (preg_match('/(.*).class$/', $file, $matches)) {
			require_once($testDir . '/' . $file);

			$className = $matches[1];
			if (class_exists($className) &&
			        GalleryUtilities::isA(new $className(null), 'GalleryTestCase')) {
			    $suiteArray[$className] = new TestSuite($className, $moduleId, $filterRegexp);
			}
		    }
		}
		$platform->closedir($dir);
	    }
	}

	$keys = array_keys($suiteArray);
	natcasesort($keys);

	foreach ($keys as $className) {
	    $testSuite->addTest($suiteArray[$className]);
	}
    }

    $counter =& GalleryTestCase::getEntityCounter();
    GalleryCoreApi::registerEventListener('GalleryEntity::save', $counter);
    GalleryCoreApi::registerEventListener('GalleryEntity::delete', $counter);

    return GalleryStatus::success();
}

define('FILTER_MAX', 1000000);
if (isset($_GET['filter'])) {
    $filter = trim($_GET['filter']);
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
    $filter = null;
    $displayFilter = null;
    $range = array(array(1, FILTER_MAX));
}
$testSuite = new TestSuite();
$ret = PhpUnitGalleryMain($testSuite, $filter);
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    print $gallery->getDebugBuffer();
    return;
}

list ($ret, $moduleStatusList) = GalleryCoreApi::fetchPluginStatus('module');
if ($ret->isError()) {
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
if ($ret->isError()) {
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
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

$storage =& $gallery->getStorage();
$ret = $storage->commitTransaction();
if ($ret->isError()) {
    return $ret->wrap(__FILE__, __LINE__);
}
?>

<?php
/**
 * @package Gallery
 * @subpackage PHPUnit
 */   
include('../security.inc');
require_once('../../../init.inc');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');
require_once('GalleryControllerTestCase.class');
require_once('ItemAddPluginTestCase.class');
require_once('ItemEditPluginTestCase.class');
require_once('CodeAuditTestCase.class');

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
    $urlGenerator->init('lib/tools/phpunit/index.php');
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
$range = array(1, FILTER_MAX);
if (isset($_GET['filter'])) {
    $filter = trim($_GET['filter']);

    if (preg_match('/:(\d+)-(\d+)/', $filter, $matches)) {
	$range = array($matches[1], $matches[2]);
	$filter = preg_replace('/:\d+-\d+/', '', $filter);
    }

    if (preg_match('/:(\d+)-/', $filter, $matches)) {
	$range[0] = $matches[1];
	$filter = preg_replace('/:\d+-/', '', $filter);
    }

    if (preg_match('/:-(\d+)/', $filter, $matches)) {
	$range[1] = $matches[1];
	$filter = preg_replace('/:-\d+/', '', $filter);
    }
} else {
    $filter = null;
}

$displayFilter = $filter;
if ($range[0] != 1 || $range[1] != FILTER_MAX) {
    $displayFilter .= sprintf(' :%d-%d', $range[0], $range[1]);
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

/* Uncomment this to see debug output before tests run
print "<pre>";
print $gallery->getDebugBuffer();
print "</pre>";
*/
include(dirname(__FILE__) . '/index.tpl');
?>

<?php
require_once('../../init.php');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');

function GalleryMain(&$testSuite) {
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

    /*
     * Commit our transaction here because we're going to have a new
     * transaction for every test.
     */
    $ret = $gallery->commitTransaction();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Load the test cases for every module (active or not).
     */
    list ($ret, $moduleNames) = $gallery->getAllModuleNames();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $platform = $gallery->getPlatform();
    $modulesDir = $gallery->getConfig('code.gallery.modules');
    foreach ($moduleNames as $moduleName) {
	$testDir = $modulesDir . $moduleName . '/test/phpunit';

	if ($platform->file_exists($testDir) &&
	    $platform->is_dir($testDir) &&
	    $dir = $platform->opendir($testDir)) {

	    while (($file = readdir($dir)) != false) {
		if (preg_match('/(.*).class$/', $file, $matches)) {
		    require_once($testDir . '/' . $file);

		    $className = $matches[1];
		    if (class_exists($className) &&
			GalleryUtilities::isA(new $className(null), 'GalleryTestCase')) {
			
			$testSuite->addTest(new TestSuite($className));
		    }
		}
	    }
	    closedir($dir);
	}
    }

    return GalleryStatus::success();
}

$testSuite = new TestSuite();
$ret = GalleryMain($testSuite);
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

/* Uncomment this to see debug output before tests run
print "<pre>";
print $gallery->getDebugBuffer();
print "</pre>";
*/

?>
<html>
  <head>
    <title>Gallery Unit Tests</title>
    <STYLE TYPE="text/css">
      <?php include ("stylesheet.css"); ?>
    </STYLE>
  </head>
  <body>
    <h1>Gallery Unit Tests</h1>
    <h2>Test Results</h2>
    <?php
    $result = new PrettyTestResult();
    $testSuite->run($result);
    $result->report();
    ?>
  </body>
</html>


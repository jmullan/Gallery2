<?php
require_once('../../init.php');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');

function GalleryMain(&$testSuite, $filter) {
    global $HTTP_GET_VARS;
    
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
		    if (!$filter || stristr($className, $filter)) {
			if (class_exists($className) &&
			    GalleryUtilities::isA(new $className(null), 'GalleryTestCase')) {

			    $suiteArray[$className] = new TestSuite($className);
			}
		    }
		}
	    }
	    closedir($dir);
	}
    }

    $keys = array_keys($suiteArray);
    natcasesort($keys);
    
    foreach ($keys as $className) {
	$testSuite->addTest($suiteArray[$className]);
    }

    return GalleryStatus::success();
}

if (isset($HTTP_GET_VARS['filter'])) {
    $filter = $HTTP_GET_VARS['filter'];
} else {
    $filter = null;
}

$testSuite = new TestSuite();
$ret = GalleryMain($testSuite, $filter);
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

$session = $gallery->getSession();
if (!$session->isUsingCookies()) {
    list ($sessionKey, $sessionId) = $session->getSessionDescriptor();
    $sessionKey = GALLERY_FORM_VARIABLE_PREFIX . $sessionKey;
}

list ($ret, $isSiteAdmin) = GalleryUserGroupMap::isUserInSiteAdminGroup();
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
    <center>
    <h1>Gallery Unit Tests</h1>
    </center>
    <br>
    This is the Gallery test framework.  We'll use this to verify that
    the Gallery code is functioning properly.  It'll help us identify
    bugs in the code when we add new features, port to new systems, or
    add support for new database back ends.  Some of these tests will
    not pass unless you are logged in as a Gallery site administrator.
    When logged on, all the tests below should pass (each line will
    have a green box that says <b>OK</b> in it).

    <?php if (!$isSiteAdmin) { ?>
    <br><br><br>
    <font color="red">
    <b>
    <h2>ERROR!</h2>
    You are not logged in as a Gallery site administrator so some
    some of the tests <i>will</i> fail.  In order to properly use
    these tests, you should log in as a site administrator.  If you
    have cookies disabled, then you must go back to the page where you
    logged in and copy the part of your URL that looks like this:
    <i>g2_GALLERYSID=51c0ca5a9ce1296ccfd5307fa77fd998</i>, get rid of
    the <i>g2_GALLERYSID</i> part and paste it into this text box then
    click the Reload Page button.  That will transfer your session from
    the page where you logged in over to this page.
    <form>
      <input type="text" size=33 name="<?php echo $sessionKey?>">
      <input type="submit" value="Reload page">
    </form>
    </b>
    </font>
    <?php } ?>
    
    <br>
    <br>
    
    <form>
    <?php if (isset($sessionKey)) { ?>
    <input type="hidden" name="<?php echo $sessionKey?>" value="<?php echo $sessionId ?>">
    <?php } ?>
    <h2>Filtering</h2>
    Enter a filter string in the box below to restrict testing to classes containing 
    that text in their name.
    <br>
    Filter: <input type="text" name="filter" value="<?php echo $filter ?>">
    </form>
    
    <?php
    $result = new PrettyTestResult();
    $testSuite->run($result);
    $result->report();
    ?>
  </body>
</html>


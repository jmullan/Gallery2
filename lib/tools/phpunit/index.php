<?php
/**
 * @package Gallery
 * @subpackage PHPUnit
 */   
include('../security.inc');
require_once('../../../init.php');
require_once('phpunit.inc');
require_once('GalleryTestCase.class');
require_once('GalleryControllerTestCase.class');
require_once('ItemAddPluginTestCase.class');
require_once('ItemEditPluginTestCase.class');

function GalleryMain(&$testSuite, $filter) {
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

    /* Configure out url Generator for phpunit mode. */
    $urlGenerator = new GalleryUrlGenerator('../../../main.php');
    $gallery->setUrlGenerator($urlGenerator);
    
    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Specify the base URL to the Gallery.  In standalone mode this will be the
     * empty string (since everything is relative to main.php).  But when we're
     * embedded, we need to put in the relative path from the outer app to the
     * Gallery directory (eg for PostNuke it might be 'modules/gallery')
     */
    $gallery->setConfig('url.gallery.base', '');

    /*
     * Commit our transaction here because we're going to have a new
     * transaction for every test.
     */
    $ret = $gallery->commitTransaction();
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
	list ($ret, $moduleStatusList) = GalleryCoreApi::getPluginStatus('module');
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

    return GalleryStatus::success();
}

if (isset($_GET['filter'])) {
    $filter = $_GET['filter'];
} else {
    $filter = null;
}

$testSuite = new TestSuite();
$ret = GalleryMain($testSuite, $filter);
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    print $gallery->getDebugBuffer();
    return;
}

list ($ret, $moduleStatusList) = GalleryCoreApi::getPluginStatus('module');
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

$session = $gallery->getSession();
if (!$session->isUsingCookies()) {
    list ($sessionKey, $sessionId) = $session->getSessionDescriptor();
    $sessionKey = GALLERY_FORM_VARIABLE_PREFIX . $sessionKey;
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

?>
<html>
  <head>
    <title>Gallery Unit Tests</title>
    <STYLE TYPE="text/css">
      <?php include ("stylesheet.css"); ?>
    </STYLE>
  </head>
  <body>
    <script type="text/javascript" language="javascript">
    function setFilter(value) {
        document.forms[0].filter.value=value;
    }
    function reRun(value) {
	setFilter(value);
	document.forms[0].submit();
    }
    </script>
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
    You are not logged in as a Gallery site administrator so you are
    not allowed to run the unit tests.  If you have cookies disabled, then you
    must go back to the page where you logged in and copy the part of your URL
    that looks like this: <i>g2_GALLERYSID=51c0ca5a9ce1296ccfd5307fa77fd998</i>,
    get rid of the <i>g2_GALLERYSID</i> part and paste it into this text box then
    click the Reload Page button.  That will transfer your session from
    the page where you logged in over to this page.
    <br>
    <a href="../../../main.php?g2_view=core:UserAdmin&g2_subView=core:UserLogin&g2_return=<?php echo $_SERVER['REQUEST_URI']?>">[ login ]</a>
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
    that text in their test class name and test method.
    <br>
    Examples:
    <a href="javascript:setFilter('AddCommentControllerTest.testAddComment')">AddCommentControllerTest.testAddComment</a>, <a href="javascript:setFilter('AddCommentControllerTest.testAdd')">AddCommentControllerTest.testAdd</a>, <a href="javascript:setFilter('AddCommentControllerTest')">AddCommentControllerTest</a>, <a href="javascript:setFilter('comment')">comment</a> </i>
    <p>
    Filter: <input type="text" name="filter" size="60" value="<?php echo $filter ?>"> <i>(regular expressions are ok)</i>
    
    </form>

    <h2>Modules</h2>
    <table cellspacing="1" cellpadding="1" border="0" width="90%" align="center" class="details">
    <tr>
    <th> Module Id </th>
    <th> Active </th>
    <th> Installed </th>
    </tr>
    <?php foreach ($moduleStatusList as $moduleId => $moduleStatus) { ?>
    <tr>
    <td>
    <?php print $moduleId ?>
    </td>
    <td>
    <?php print !empty($moduleStatus['active']) ? "active" : "not active" ?>
    </td>
    <td>
    <?php print !empty($moduleStatus['installed']) ? "installed" : "not installed" ?>
    </td>
    </tr>
    <?php } ?>									   
    </table>
    
    <?php
    $result = new PrettyTestResult();
    $testSuite->run($result);
    $result->report();
    ?>
  </body>
</html>


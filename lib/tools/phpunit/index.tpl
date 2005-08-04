<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
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
    <h1>Gallery Unit Tests</h1>
    <div class="section">
      This is the Gallery test framework.  We'll use this to verify
      that the Gallery code is functioning properly.  It'll help us
      identify bugs in the code when we add new features, port to new
      systems, or add support for new database back ends.  All the
      tests should pass with a green box that says <b>OK</b> in it).
    </div>

    <?php if (!$isSiteAdmin): ?>
    <h2> <span class="error">ERROR!</span> </h2>
    <div class="section">
      You are not logged in as a Gallery site administrator so you are
      not allowed to run the unit tests.  If you have cookies disabled, then you
      must go back to the page where you logged in and copy the part of your URL
      that looks like this:
      <p>
	<code>g2_GALLERYSID=51c0ca5a9ce1296ccfd5307fa77fd998</code>
      </p>
      get rid of the <i>g2_GALLERYSID</i> part and paste it into this text box then
      click the Reload Page button.  That will transfer your session from
      the page where you logged in over to this page.

      <a href="../../../main.php?g2_view=core.UserAdmin&g2_subView=core.UserLogin&g2_return=<?php echo $_SERVER['REQUEST_URI']?>">[ login ]</a>
      <form>
	<input type="text" size=33 name="<?php echo isset($sessionKey) ? $sessionKey : '' ?>">
	  <input type="submit" value="Reload page">
      </form>
    </div>
    <?php endif; ?>

    <script type="text/javascript">
      examplesVisible = false;
      function toggleFilterExamples() {
        myList = document.getElementById('help_and_examples');
        myIndicator = document.getElementById('filter_examples_toggle_indicator');
        if (examplesVisible) {
	  myList.style.display = 'none';
	  myIndicator.innerHTML = '+';
	} else {
	  myList.style.display = 'inline';
	  myIndicator.innerHTML = '-';
	}
	examplesVisible = !examplesVisible;
      }

      modulesListingVisible = false;
      function toggleModulesListing() {
        myList = document.getElementById('modules_listing');
        myIndicator = document.getElementById('modules_listing_toggle_indicator');
        if (modulesListingVisible) {
          myList.style.display = 'none';
          myIndicator.innerHTML = '+';
        } else {
          myList.style.display = 'inline';
          myIndicator.innerHTML = '-';
        }
        modulesListingVisible = !modulesListingVisible;
      }
    </script>

    <?php if (sizeof($incorrectDevEnv) > 0): ?>
    <div style="float: right; width: 500px; border: 2px solid red; padding: 3px">
      <h2 style="margin: 0px"> Development Environment Warning </h2>
      <div style="margin-left: 5px">
        The following settings in your development environment are not correct.  See the <a href="http://gallery.menalto.com/modules.php?op=modload&name=phpWiki&file=index&pagename=Development%20Environment">G2 Development Environment</a> page for more information
      </div>
      <br/>
      <table border="0" class="details">
        <tr>
          <th> PHP Setting </th>
          <th> Actual Value </th>
          <th> Expected Value(s) </th>
        </tr>
        <?php foreach (array_keys($incorrectDevEnv) as $key): ?>
        <tr>
          <td> <?php print $key ?> </td>
          <td> <?php print $incorrectDevEnv[$key][1] ?> </td>
          <td> <?php print join(' <b>or</b> ', $incorrectDevEnv[$key][0]) ?> </td>
        </tr>
        <?php endforeach; ?>
      </table>
    </div>
    <?php endif; ?>

    <h2>Filter</h2>
    <div class="section">
      <form>
	<?php if (isset($sessionKey)): ?>
	<input type="hidden" name="<?php echo $sessionKey?>" value="<?php echo $sessionId ?>"/>
	<?php endif; ?>

	<input style="margin-top: 0.3em; margin-bottom: 0.3em" type="text" name="filter" size="60" value="<?php echo $displayFilter ?>" />

	<br/>
        <span id="filter_examples_toggle"
          href="#"
          onclick="toggleFilterExamples()">
          Help/Examples
          <span id="filter_examples_toggle_indicator"
            style="padding-left: .3em; padding-right: 0.3em; border: solid #a6caf0; border-width: 1px; background: #eee">
            +
          </span>
        </span>

        <div id="help_and_examples" style="display: none">
         <br/>
	  Enter a regular expression string to restrict testing to classes containing
          that text in their class name or test method.  If you use an exclamation before a
          module/class/test name(s) encapsulated in parenthesis and separated with bars, this will
          exclude the matching tests. Use ":#-#" to restrict which matching tests are actually run.
          You can also specify multiple spans with ":#-#,#-#,#-#".

          <ul id="filter_examples_list">
            <li>
              <a href="javascript:setFilter('AddCommentControllerTest.testAddComment')">AddCommentControllerTest.testAddComment</a>
            </li>
            <li>
              <a href="javascript:setFilter('AddCommentControllerTest.testAdd')">AddCommentControllerTest.testAdd</a>
            </li>
            <li>
              <a href="javascript:setFilter('AddCommentControllerTest')">AddCommentControllerTest</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment')">comment</a>
            </li>
            <li>
              <a href="javascript:setFilter('!(comment)')">!(comment)</a>
            </li>
            <li>
              <a href="javascript:setFilter('!(comment|core)')">!(comment|core)</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment:1-3')">comment:1-3</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment:3-')">comment:3-</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment:-5')">comment:-5</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment:1-3,6-8,10-12')">comment:1-3,6-8,10-12</a>
            </li>
            <li>
              <a href="javascript:setFilter('comment:-3,4-')">comment:-3,4-</a>
            </li>
          </ul>
        </div>
      </form>
    </div>

    <h2>
      Modules
    </h2>

    <div class="section" style="width: 100%">
      <?php
      $activeCount = 0;
      foreach ($moduleStatusList as $moduleId => $moduleStatus) {
        if (!empty($moduleStatus['active'])) {
          $activeCount++;
        }
      }
      ?>
      <?php printf("%d active, %d total", $activeCount, sizeof($moduleStatusList)); ?>
      <span onclick="toggleModulesListing()" id="modules_listing_toggle_indicator" style="border: solid #a6caf0; border-width: 1px; background: #eee">
	+
      </span>
      <br/>
      <table cellspacing="1" cellpadding="1" border="0"
        width="800" align="center" class="details"
        id="modules_listing"
        style="display: none">
        <tr>
          <th> Module Id </th>
          <th> Active </th>
          <th> Installed </th>
        </tr>
        <?php foreach ($moduleStatusList as $moduleId => $moduleStatus): ?>
        <tr>
          <td style="width: 100px">
            <?php print $moduleId ?>
          </td>
          <td style="width: 100px">
            <?php print !empty($moduleStatus['active']) ? "active" : "not active" ?>
          </td>
          <td style="width: 100px">
            <?php print !empty($moduleStatus['available']) ? "installed" : "not available" ?>
          </td>
        </tr>
        <?php endforeach; ?>
      </table>
    </div>

    <?php
    $result = new PrettyTestResult();
    $testSuite->run($result, $range);
    $result->report();
    ?>
  </body>
</html>

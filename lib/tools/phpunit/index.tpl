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
      This is the Gallery test framework.  We'll use this to verify that
      the Gallery code is functioning properly.  It'll help us identify
      bugs in the code when we add new features, port to new systems, or
      add support for new database back ends.  Some of these tests will
      not pass unless you are logged in as a Gallery site administrator.
      When logged on, all the tests below should pass (each line will
      have a green box that says <b>OK</b> in it).
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

      <a href="../../../main.php?g2_view=core:UserAdmin&g2_subView=core:UserLogin&g2_return=<?php echo $_SERVER['REQUEST_URI']?>">[ login ]</a>
      <form>
	<input type="text" size=33 name="<?php echo isset($sessionKey) : $sessionKey : '' ?>">
	  <input type="submit" value="Reload page">
      </form>
    </div>
    <?php endif; ?>
    
    <script type="text/javascript">
      examplesVisible = false;
      function toggleFilterExamples() {
        myList = document.getElementById('filter_examples_list');
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
	
    <h2>Filter</h2>
    <div class="section">
      Enter a regular expression string to restrict testing to classes containing 
      that text in their class name or test method.

      <form>
	<?php if (isset($sessionKey)): ?>
	<input type="hidden" name="<?php echo $sessionKey?>" value="<?php echo $sessionId ?>"/>
	<?php endif; ?>

	<input style="margin-top: 0.3em; margin-bottom: 0.3em" type="text" name="filter" size="60" value="<?php echo $filter ?>" />

	<br/>
        <span id="filter_examples_toggle" 
          href="#" 
          onclick="toggleFilterExamples()">
          Examples
          <span id="filter_examples_toggle_indicator" 
            style="padding-left: .3em; padding-right: 0.3em; border: solid #a6caf0; border-width: 1px; background: #eee">
            +
          </span>
        </span>
		  
        <ul id="filter_examples_list" style="display: none">
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
          </i>
        </ul>
      </form>
    </div>

    <h2 onclick="toggleModulesListing()"> 
      Modules
      <span id="modules_listing_toggle_indicator" style="border: solid #a6caf0; border-width: 1px; background: #eee">
	+
      </span>
    </h2>

    <div class="section" style="width: 100%">
      <?php
      $activeCount = 0;
      foreach ($moduleStatusList as $moduleId => $moduleStatus) { 
        if (isset($moduleStatus['active'])) {
          $activeCount++;
        }
      }
      ?>
      <?php printf("%d active, %d total", $activeCount, sizeof($moduleStatusList)); ?>
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
          <td width="100">
            <?php print $moduleId ?>
          </td>
          <td width="100">
            <?php print !empty($moduleStatus['active']) ? "active" : "not active" ?>
          </td>
          <td width="100">
            <?php print !empty($moduleStatus['available']) ? "installed" : "not available" ?>
          </td>
        </tr>
        <?php endforeach; ?> 
      </table>
    </div>
	
    <?php
    $result = new PrettyTestResult();
    $testSuite->run($result);
    $result->report();
    ?>
  </body>
</html>

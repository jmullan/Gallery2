{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Archive Upload Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="This module will enable extraction of individual files from a zip archive to add each item to Gallery.  You must locate or install an unzip binary on your machine, then enter the path to it in the text box below.  If you're on a Unix machine, don't forget to make the binary executable (<i>chmod 755 unzip</i> in the right directory should do it)"}
    </p>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Path to unzip"}
      </h3>

      <input type="text" size="40" name="{g->formVar var="form[unzipPath]"}"
       value="{$form.unzipPath}"/>

      {if isset($form.error.unzipPath.missing)}
      <div class="giError">
	{g->text text="You must enter a path to your unzip binary"}
      </div>
      {/if}

      {if isset($form.error.unzipPath.exec)}
      <div class="giError">
	{g->text text="The path you entered doesn't contain a valid unzip binary."}
      </div>
      {/if}

      {if isset($form.error.unzipPath.badPath)}
      <div class="giError">
	{g->text text="The path you entered isn't a valid path to an unzip binary."}
      </div>
      {/if}

      {if isset($form.error.unzipPath.notExecutable)}
      <div class="giError">
	{g->text text="The unzip binary is not executable.  To fix it, run <b>chmod 755 %s</b>" arg1=$form.unzipPath}
      </div>
      {/if}
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}"
     value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][test]"}"
     value="{g->text text="Test Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}"
     value="{g->text text="Cancel"}"/>
  </div>

  {if !empty($ArchiveUploadSiteAdmin.tests)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="unzip binary test results"}
    </h3>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Binary Name"}
	</th>
	<th>
	  {g->text text="Pass/Fail"}
	</th>
      </tr>

      {foreach from=$ArchiveUploadSiteAdmin.tests item=test}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$test.name}
	</td>
	<td>
	  {if ($test.success)}
	  <div class="giSuccess">
	    {g->text text="Passed"}
	  </div>
	  {else}
	  <div class="giError">
	    {g->text text="Failed"}
	  </div>
	  {if !empty($test.message)}
	  {g->text text="Error messages:"}
	  <pre>{$test.message}</pre>
	  {/if}
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>
  </div>
  {/if}
</div>

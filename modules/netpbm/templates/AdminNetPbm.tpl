{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminNetPbm.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="NetPBM Settings"}
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
      {g->text text="NetPBM is a graphics toolkit that can be used to process images that you upload to Gallery.  You must install the NetPBM binaries on your machine, then enter the path to them in the text box below.  If you're on a Unix machine, don't forget to make the binaries executable (<i>chmod 755 *</i> in the NetPBM directory should do it)"}
    </p>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="NetPBM Path"}
      </h3>
	
      <input type="text" size="40" name="{g->formVar var="form[path]"}" value="{$form.path}"/>
      
      {if isset($form.error.path.missing)}
      <div class="giError">
	{g->text text="You must enter a path to your NetPBM binaries"}
      </div>
      {/if}
      
      {if isset($form.error.path.testError)}
      <div class="giError">
	{g->text text="The path you entered doesn't contain valid NetPBM binaries. Use the 'test' button to check where the error is."}
      </div>
      {/if}
      
      {if isset($form.error.path.badPath)}
      <div class="giError">
	{g->text text="The path you entered isn't a valid path."}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	  {g->text text="PNM to JPEG converter"}
      </h3>

      <select name="{g->formVar var="form[pnmtojpeg]"}">
	  {html_options values=$AdminNetPbm.pnmToJpegList selected=$form.pnmtojpeg output=$AdminNetPbm.pnmToJpegList}
      </select>
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="JPEG Quality"}
      </h3>

      <select name="{g->formVar var="form[jpegQuality]"}">
	  {html_options values=$AdminNetPbm.jpegQualityList selected=$form.jpegQuality output=$AdminNetPbm.jpegQualityList}
      </select>
    </div>
  </div>

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="NetPBM will lose embedded EXIF data if you modify the original image, unless you have the optional <b>jhead</b> binary installed on your system.  If you have jhead installed, enter the path below.  Without it, NetPBM will still perform all of its normal functions, but you should always use the <i>preserve original image</i> option when rotating and scaling images"}
    </p>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Path to jhead"}
      </h3>

      <input type="text" size="40" name="{g->formVar var="form[jheadPath]"}" value="{$form.jheadPath}"/>

      {if isset($form.error.jheadPath.badPath)}
      <div class="giError">
	{g->text text="The path you entered isn't a valid path."}
      </div>
      {/if}

      {if isset($form.error.jheadPath.missing)}
      <div class="giWarning">
	{g->text text="You should enter a path to the optional jhead binary"}
      </div>
      {/if}
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>

  {if !empty($AdminNetPbm.tests)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="NetPBM binary test results"}
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

      {foreach from=$AdminNetPbm.tests item=test}
      <tr>
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

	  {if ! empty($test.message)}
	  {g->text text="Error messages:"}
	  <br />
	  {foreach from=$test.message item=line}
	  <pre>{$line}</pre>
	  {/foreach}
	  {/if}
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>

    {if ($AdminNetPbm.failCount > 0) && !empty($AdminNetPbm.mimeTypes)} 
    <div class="giWarning">
      {g->text text="Although your NetPBM installation is not completely functional, you can still use it for the mime types listed below."}
    </div>
    {/if}
  </div>

  {if $AdminNetPbm.mimeTypes}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Supported MIME Types"}
    </h3>

    <p class="giDescription">
      {g->text text="The NetPBM module can support files with the following MIME types"}
    </p>
    
    {foreach from=$AdminNetPbm.mimeTypes item=mimeType}
    {$mimeType} 
    {/foreach}
  </div>
  {/if}
  {/if}
</div>

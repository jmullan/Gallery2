{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminImageMagick.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="ImageMagick Settings"}
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
    <div class="giDescription">
      {g->text text="ImageMagick is a graphics toolkit that can be used to process images that you upload to Gallery.  You must install the ImageMagick binaries on your machine, then enter the path to them in the text box below.  If you're on a Unix machine, don't forget to make the binaries executable (<i>chmod 755 *</i> in the ImageMagick directory should do it)"}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Directory to ImageMagick/GraphicsMagick binaries"}
      </h3>

      <input type="text" name="{g->formVar var="form[path]"}" value="{$form.path}"/>
	
      {if isset($form.error.path.missing)}
      <div class="giError">
	{g->text text="You must enter a path to your ImageMagick binaries"}
      </div>
      {/if}

      {if isset($form.error.path.bad)}
      <div class="giError">
	{g->text text="The path you entered is not a valid directory or is not accessible."}
      </div>
      {/if}

      {if isset($form.error.path.testError)}
      <div class="giError">
	{g->text text="The path you entered doesn't contain valid ImageMagick binaries. Use the 'test' button to check where the error is."}
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
	{g->text text="JPEG Quality"}
      </h3>

      <select name="{g->formVar var="form[jpegQuality]"}">
	  {html_options values=$AdminImageMagick.jpegQualityList selected=$form.jpegQuality output=$AdminImageMagick.jpegQualityList}
      </select>
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>

  {if !empty($AdminImageMagick.tests)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="ImageMagick binary test results"}
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

      {foreach from=$AdminImageMagick.tests item=test}
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

	  {if ! empty($test.message)}
	  {g->text text="Error messages:"}
	  <br />
	  <div class="giError">
	    {foreach from=$test.message item=line}
	    <pre>{$line}</pre>
	    {/foreach}
	  </div>
	  {/if}
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>
  </div>
    
  {if $AdminImageMagick.mimeTypes}
  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Version"}
    </div>

    <div class="giDescription">
      {$AdminImageMagick.version.0} {$AdminImageMagick.version.1}
    </div>

    <div class="giTitle">
      {g->text text="Supported MIME Types"}
    </div>
    
    <div class="giDescription">
      {g->text text="The ImageMagick module can support files with the following MIME types"}
    </div>
	
    {foreach from=$AdminImageMagick.mimeTypes item=mimeType}
    <span>
      {$mimeType}<br />
    </span>
    {/foreach}
  </div>
  {/if}
  {/if}
</div>

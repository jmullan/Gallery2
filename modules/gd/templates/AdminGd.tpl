{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminGd.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Gd Settings"}
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
      {g->text text="Gd is a graphics toolkit that can be used to process images that you upload to Gallery. The GD-library should be compiled in your PHP (--with-gd)."}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="JPEG Quality"}
      </h3>

      <select name="{g->formVar var="form[jpegQuality]"}">
	  {html_options values=$AdminGd.jpegQualityList selected=$form.jpegQuality output=$AdminGd.jpegQualityList}
      </select>
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="GD library version"}
    </div>
    
  {if $AdminGd.gdVersion}
    <table class="gbDataTable">
      <tr>
        <th>
          {g->text text="GD version"}
        </th>
        <th>
          {g->text text="Required"}
        </th>
        <th>
          {g->text text="Pass/fail"}
        </th>
      </tr>

      <tr class="{cycle values="gbEven,gbOdd"}">
        <td>
          {$AdminGd.gdVersion}
          {if $AdminGd.isGdBundled}
            ({g->text text="bundled"})
          {/if}
        </td>
        <td>
          {$AdminGd.minGdVersion}
        </td>
        <td>
          {if ($AdminGd.gdVersionTooOld)}
          <div class="giError">
            {g->text text="Failed"}
          </div>
          <div class="giError">
          {g->text text="This GD version is too old and is not supported by this module! Please upgrade your PHP installation to include the latest GD version."}
          </div>
          {else}
          <div class="giSuccess">
            {g->text text="Passed"}
          </div>
          {/if}
        </td>
      </tr>
    </table>
  
  {else}
    <div class="giDescription">
      {g->text text="You don't seem to have the GD library available on this PHP installation."}
    </div>
  {/if}
  </div>

  {if $AdminGd.mimeTypes}
  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Supported MIME Types"}
    </div>
    
    <div class="giDescription">
      {g->text text="The Gd module will support files with the following MIME types:"}
    </div>
	
    {foreach from=$AdminGd.mimeTypes item=mimeType}
    <span>
      {$mimeType}<br />
    </span>
    {/foreach}
  </div>
  {/if}

</div>

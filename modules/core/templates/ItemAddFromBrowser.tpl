{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $ItemAddFromBrowser.uploadsPermitted}
<div class="gbAdmin">
  <p class="giDescription">
    {g->text text="Upload files directly from your computer."}
    {g->text text="Enter the full path to the file and an optional caption in the boxes below."}
    <input type="hidden" name="{g->formVar var="form[uploadBoxCount]"}" value="{$form.uploadBoxCount}" />
  </p>

  <p class="giDescription">
    {if $ItemAddFromBrowser.maxFileSize == 0}
    {g->text text="<b>Note:</b> You can upload up to %s at one time.  If you want to upload more than that, you must upload the files separately, use a different upload format, or ask your system administrator to allow larger uploads." arg1=$ItemAddFromBrowser.totalUploadSize}
    {else}
    {g->text text="<b>Note:</b> You can upload up to %s at one time.  No individual file may be larger than %s. If you want to upload more than that, you must upload the files separately, use a different upload format, or ask your system administrator to allow larger uploads." arg1=$ItemAddFromBrowser.totalUploadSize arg2=$ItemAddFromBrowser.maxFileSize}
    {/if}
  </p>
  {section name="uploadBoxes" loop=$form.uploadBoxCount}
  {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
  <div class="gbDataEntry"
       {if $iteration > $form.visibleBoxCount} id="fileDiv_{$iteration}" style="display:none"{/if}>
    <h3 class="giTitle">
      {g->text text="File"}
    </h3>
    <input name="{g->formVar var="form[$iteration]"}" type="file" size="60"/>

    <h3 class="giTitle">
      {g->text text="Caption"}
    </h3>
    <textarea rows="2" cols="60" name="{g->formVar var="form[caption][$iteration]"}"></textarea>
  </div>
  {/section}
  {if $form.uploadBoxCount > $form.visibleBoxCount}
    <script type="text/javascript">
      // <![CDATA[
      document.write('<a id="addOne" href="javascript:addOne()">{g->text text="More.."}</a>');
      var fileIndex = {$form.visibleBoxCount};
      {literal}
      function addOne() {
	var link = document.getElementById('addOne');
	link.blur();
	document.getElementById('fileDiv_' + ++fileIndex).style.display = 'block';
	if (fileIndex >= {/literal}{$form.uploadBoxCount}{literal}) {
	  link.style.display = 'none';
	}
      }
      // ]]>
    {/literal}</script>
  {/if}
</div>
<div class="gbAdmin">
  {g->text text="Set item titles from:"}
  <select name="{g->formVar var="form[set][title]"}">
    {html_options options=$ItemAddFromBrowser.titleList selected=$form.set.title}
  </select>
  &nbsp;
  {g->text text="Assign caption to:"}
  <input type="checkbox" id="captionSummary" name="{g->formVar var="form[set][summary]"}"
   {if !empty($form.set.summary)}checked="checked"{/if}/>
  <label for="captionSummary"> {g->text text="Summary"} </label>
  &nbsp;
  <input type="checkbox" id="captionDescription" name="{g->formVar var="form[set][description]"}"
   {if !empty($form.set.description)}checked="checked"{/if}/>
  <label for="captionDescription"> {g->text text="Description"} </label>
</div>

{* Include our extra ItemAddOptions *}
{foreach from=$ItemAdd.options item=option}
  {if isset($option.file)}
    {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
  {/if}
{/foreach}

<div class="gbBottomFlag">
  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][addFromBrowser]"}"
    value="{g->text text="Add Items"}"/>
  </div>
</div>
{else}
<div class="gbAdmin">
  <div class="giError">
    {g->text text="Your webserver is configured to disallow file uploads from your web browser at this time.  Please contact your system administrator for assistance."}
  </div>
</div>
{/if}


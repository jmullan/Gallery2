{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $ItemAddFromBrowser.uploadsPermitted}
<div class="gbAdmin">
  <p class="giDescription">
    {g->text one="Upload a file directly from your computer."
    many="Upload up to %d files directly from your computer."
    count=$form.uploadBoxCount
    arg1=$form.uploadBoxCount}
    {g->text text="Enter the full path to the file and an optional caption in the boxes below."}
    <input type="hidden" name="{g->formVar var="form[uploadBoxCount]"}" value="{$form.uploadBoxCount}" />
  </p>

  <p class="giDescription">
    {g->text text="<b>Note:</b> You can upload up to %s at one time.  No individual file may be larger than %s.  If you want to upload more than that, you must upload the files separately, use a different upload format, or ask your system administrator to allow larger uploads." arg1=$ItemAddFromBrowser.totalUploadSize arg2=$ItemAddFromBrowser.maxFileSize}
  </p>
  {section name="uploadBoxes" loop=$form.uploadBoxCount}
  {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
  <div class="gbDataEntry">
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


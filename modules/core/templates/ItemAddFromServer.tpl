{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAddFromServer.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if !empty($form.localServerFiles)}
<script type="text/javascript">
  {* Generate indexes of items that we know, which will correspond to checkbox ids, below *}
  {strip}
  var knownTypeCheckboxIds = new Array(
  {assign var="first" value="1"}
  {foreach name=fileIndex from=$form.localServerFiles item=file}
  {if ($file.type == 'file' && !$file.unknown)}
  {if !$first},{/if}
  {$smarty.foreach.fileIndex.iteration}
  {assign var="first" value="0"}
  {/if}
  {/foreach}
  );
  {/strip}

  {literal}
  function toggleSelections() {
    for (i = 0; i < knownTypeCheckboxIds.length; i++) {
      var cb = document.getElementById('cb_' + knownTypeCheckboxIds[i]);
      cb.checked = !cb.checked;
    }
  }
  {/literal}
</script>
{/if}

<script type="text/javascript">
  function selectPath(path) {ldelim}
  document.forms[0].elements['{g->formVar var="form[localServerPath]"}'].value = path;
  {rdelim}
</script>

<div class="gbAdmin">
  <p class="giDescription">
    {g->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anyelement on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
  </p>
  
  {if empty($ItemAddFromServer.localServerDirList)}
  <div class="giWarning">
    {g->text text="For security purposes, you can't use this feature until the Gallery Site Administrator configures a set of legal upload directories."}
    {if $ItemAdd.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminCore"}">
      {g->text text="site admin"}
    </a>
    {/if}
  </div>
  {else}

  {if empty($form.localServerFiles)}
  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Server Path"}
    </h3>
  
    <input type="text" size="80" name="{g->formVar var="form[localServerPath]"}" value="{$form.localServerPath}"/>
  
    {if isset($form.error.localServerPath.missing)}
    <div class="giError">
      {g->text text="You must enter a directory."}
    </div>
    {/if}
  
    {if isset($form.error.localServerPath.invalid)}
    <div class="giError">
      {g->text text="The directory you entered is invalid.  Make sure that the directory is readable by all users."}
    </div>
    {/if}
  
    {if isset($form.error.localServerPath.illegal)}
    <div class="giError">
      {g->text text="The directory you entered is illegal.  It must be a sub directory of one of the directories listed below."}
    </div>
    {/if}
  </div>
  
  {g->text text="Legal Directories"}
    
  {if $ItemAdd.isAdmin}
  <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminCore"}">
    {g->text text="modify"}
  </a>
  {/if}
  
  <ul class="gbAdminList">
    {foreach from=$ItemAddFromServer.localServerDirList item=dir}
    {capture name="escapedDir"}{$dir|replace:"\\":"\\\\"}{/capture}
    <li> 
      <a href="javascript:selectPath('{$smarty.capture.escapedDir}')">
	{$dir}
      </a>
    </li>
    {/foreach}
  </ul>
  
  {if !empty($ItemAddFromServer.recentPaths)}
  {g->text text="Recent Directories"}
  
  <ul class="gbAdminList">
    {foreach from=$ItemAddFromServer.recentPaths item=dir}
      {capture name="escapedDir"}{$dir|replace:"\\":"\\\\"}{/capture}
    <li>
      <a href="javascript:selectPath('{$smarty.capture.escapedDir}')">
	{$dir}
      </a>
    </li>
    {/foreach}
  </ul>
  {/if}

  {capture name="bottomFlagHtml"}
    <input type="submit" name="{g->formVar var="form[action][findFilesFromLocalServer]"}" value="{g->text text="Find Files"}"/>
  {/capture}
  {else} {* {if empty($form.localServerFiles)} *}
  <strong>
    {capture name="path"}
    {strip}
    {foreach name="pathElements" from=$ItemAddFromServer.pathElements key=idx item=element}
    {if $idx>1}{$ItemAddFromServer.pathSeparator}{/if}
    {if ($element.legal && !$smarty.foreach.pathElements.last)}
    <a href="{g->url arg1="controller=core:ItemAdd" arg2="addPlugin=ItemAddFromServer" arg3="form[localServerPath]=`$element.path`" arg4="itemId=`$ItemAdmin.item.id`" arg5="form[action][findFilesFromLocalServer]=1" arg6="form[formName]=ItemAddFromServer"}">{$element.name}</a>
    {else}
    {$element.name}
    {/if}
    {/foreach}
    {/strip}
    {/capture}
    {g->text text="Directory: %s" arg1=$smarty.capture.path}
  </strong>
  
  
  <input type="hidden" name="{g->formVar var="form[localServerPath]"}" 
	 value="{$form.localServerPath}"/>
  
  <br />
  
  <table class="gbDataTable">
    <tr>
      <th>
      </th>

      <th>
	{g->text text="File name"}
      </th>

      <th>
	{g->text text="Type"}
      </th>

      <th>
	{g->text text="Size"}
      </th>
    </tr>
  
    {foreach name=fileIndex from=$form.localServerFiles item=file}
    {assign var=key value=$file.fileKey|urlencode}
    <tr class="{cycle values="gbEven,gbOdd"}">
      {if ($file.type == 'file')}
      <td style="text-align: center">
	<input type="checkbox" id="cb_{$smarty.foreach.fileIndex.iteration}" name="{g->formVar var="form[localServerFiles][$key]"}"/>
      </td>

      <td>
        {$file.fileName}
      </td>

      <td>
	{$file.itemType}
      </td>

      <td>
	{g->text one="%d byte" many="%d bytes" count=$file.stat.size arg1=$file.stat.size}
      </td>
      {else}
      <td>
        &nbsp;
      </td>

      <td>
	{if $file.legal}
	<a href="{g->url arg1="controller=core:ItemAdd" arg2="addPlugin=ItemAddFromServer" arg3="form[localServerPath]=$key" arg4="itemId=`$ItemAdmin.item.id`" arg5="form[action][findFilesFromLocalServer]=1" arg6="form[formName]=ItemAddFromServer"}">{$file.fileName}</a>
	{else}
	<i>{$file.fileName}</i>
	{/if}
      </td>

      <td>
	{g->text text="Directory"}
      </td>

      <td>
	&nbsp;
      </td>
      {/if}
    </tr>
    {/foreach}
    <tr>
      <th>
        <input name="selectionToggle" type="checkbox" onClick="javascript:toggleSelections()"/>
      </th>
      <th colspan="3">
        {g->text text="(Un)check all known types"}
      </th>     
    </tr>
  </table>
  {capture name="bottomFlagHtml"}
    <input type="submit" name="{g->formVar var="form[action][addFromLocalServer]"}" value="{g->text text="Add Files"}"/>
    <input type="submit" name="{g->formVar var="form[action][startOver]"}" value="{g->text text="Start Over"}"
onclick="document.location='{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[localServerPath]=`$form.localServerPath`" arg5="form[formName]=ItemAddFromServer" arg6="addPlugin=ItemAddFromServer"}'"/>
  {/capture}
  {assign var="showOptions" value="true"}
  {/if} {* {if !empty($form.localServerFiles)} *}
  {/if} {* {if empty($ItemAddFromServer.localServerDirList)} *}
</div>

{if isset($showOptions)}
  {* Include our extra ItemAddOptions *}
  {foreach from=$ItemAdd.options item=option}
    {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
  {/foreach}
{/if}
  
<div class="gbBottomFlag">
  <div class="gbButtons">
    {$smarty.capture.bottomFlagHtml}
  </div>
</div>

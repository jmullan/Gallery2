<div class="gbAdmin">
  {if !empty($form.localServerFiles)}
  <script type="text/javascript">
    function toggleSelections() {ldelim}
    form = document.forms[0];
    state = form.elements['selectionToggle'].checked;
    {foreach from=$form.localServerFiles item=file}
    form.elements['{g->elementName name="form[localServerFiles][`$file.fileKey`]"}'].checked = state;
    {/foreach}
    {rdelim}
  </script>
  {/if}

  <script type="text/javascript">
    function selectPath(path) {ldelim}
    document.forms[0].elements['{g->elementName name="form[localServerPath]"}'].value = path;
    {rdelim}
  </script>

  <div class="giDescription">
    {g->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anyelement on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
  </div>

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
    <div class="giTitle">
      {g->text text="Server Path"}
    </div>

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

  <ul>
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

  <ul>
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
  <input type="submit" name="{g->formVar var="form[action][findFilesFromLocalServer]"}" value="{g->text text="Find Files"}"/>

  {else} {* {if empty($form.localServerFiles)} *}
  <b>
    {g->text text="Directory: %s" arg1=$form.localServerPath}
  </b>
  <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[localServerPath]=`$form.localServerPath`" arg5="form[formName]=ItemAddFromServer" arg6="addPlugin=ItemAddFromServer"}">
    {g->text text="change"}
  </a>

  <input type="hidden" name="{g->formVar var="form[localServerPath]"}" value="{$form.localServerPath}"/>

  <br />

  {g->text one="%d file found" many="%d files found" count=$ItemAddFromServer.localServerFileCount arg1=$ItemAddFromServer.localServerFileCount}

  <table class="gbDataTable" width="100%">
    <tr>
      <th>
	<input name="selectionToggle" type="checkbox" onclick="javascript:toggleSelections()"/>
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

    {foreach from=$form.localServerFiles item=file}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
	<input type="checkbox" name="{g->formVar var="form[localServerFiles][`$file.fileKey`]"}"/>
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
    </tr>
    {/foreach}
  </table>

  <input type="submit" name="{g->formVar var="form[action][addFromLocalServer]"}" value="{g->text text="Add Files"}"/>
  {/if} {* {if !empty($form.localServerFiles)} *}
  {/if} {* {if empty($ItemAddFromServer.localServerDirList)} *}
</div>




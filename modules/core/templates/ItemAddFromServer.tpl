{g->element}
  {if !empty($form.localServerFiles)}
    <script type="text/javascript" language="javascript">
      function toggleSelections() {ldelim}
        form = document.forms[0];
        state = form.elements['{g->elementName name="selectionToggle"}'].checked;
        {foreach from=$form.localServerFiles item=file}
        form.elements['{g->elementName name="form[localServerFiles][`$file.fileKey`]"}'].checked = state;
        {/foreach}
      {rdelim}
    </script>
  {/if}

  <script type="text/javascript" language="javascript">
    function selectPath(path) {ldelim}
      document.forms[0].elements['{g->elementName name="form[localServerPath]"}'].value = path;
    {rdelim}
  </script>
{/g->element}

{g->box style="admin"}
  {g->description}
    {g->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anyelement on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
  {/g->description}

  {if empty($ItemAddFromServer.localServerDirList)}
    {g->element}
      {g->text text="For security purposes, you can't use this feature until the Gallery Site Administrator configures a set of legal upload directories."}
      {if $ItemAdd.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminCore"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {else}
    {if empty($form.localServerFiles)}
      {g->element}
	{g->text text="Server Path"}
	{g->input type="text" size="80" name="form[localServerPath]"}{$form.localServerPath}{/g->input}
      {/g->element}

      {if isset($form.error.localServerPath.missing)}
	{g->error}
	  {g->text text="You must enter a directory."}
	{/g->error}
      {/if}

      {if isset($form.error.localServerPath.invalid)}
	{g->error}
	  {g->text text="The directory you entered is invalid.  Make sure that the directory is readable by all users."}
	{/g->error}
      {/if}

      {if isset($form.error.localServerPath.illegal)}
	{g->error}
	  {g->text text="The directory you entered is illegal.  It must be a sub directory of one of the directories listed below."}
	{/g->error}
      {/if}

      {g->element}
	{g->text text="Legal Directories"}
	{if $ItemAdd.isAdmin}
	  {g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminCore"}
	    {g->text text="modify"}
	  {/g->link}
	{/if}
	{g->listing}
	  {foreach from=$ItemAddFromServer.localServerDirList item=dir}
	    {capture name="escapedDir"}{$dir|replace:"\\":"\\\\"}{/capture}
	    {g->item}
	      {g->title}
		{g->link javascript="selectPath('`$smarty.capture.escapedDir`')"}
		  {$dir}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/foreach}
	{/g->listing}
	{if !empty($ItemAddFromServer.recentPaths)}
	  {g->text text="Recent Directories"}
	  {g->listing}
	    {foreach from=$ItemAddFromServer.recentPaths item=dir}
	      {capture name="escapedDir"}{$dir|replace:"\\":"\\\\"}{/capture}
	      {g->item}
		{g->title}
		  {g->link javascript="selectPath('`$smarty.capture.escapedDir`')"}
		    {$dir}
		  {/g->link}
		{/g->title}
	      {/g->item}
	    {/foreach}
	  {/g->listing}
	{/if}
	{g->input type="submit" name="form[action][findFilesFromLocalServer]"}{g->text text="Find Files"}{/g->input}
      {/g->element}
    {else} {* {if empty($form.localServerFiles)} *}

      {g->element style="emphasized"}
	{g->text text="Directory: %s" arg1=$form.localServerPath}
	{g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddFromServer" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[localServerPath]=`$form.localServerPath`" arg5="form[formName]=ItemAddFromServer"}
	  {g->text text="change"}
	{/g->link}
	{g->input type="hidden" name="form[localServerPath]"}{$form.localServerPath}{/g->input}
      {/g->element}
      {g->element}
	{g->text one="%d file found" many="%d files found" count=$ItemAddFromServer.localServerFileCount arg1=$ItemAddFromServer.localServerFileCount}
      {/g->element}

      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
	    {g->input name="selectionToggle" type="checkbox" onClick="javascript:toggleSelections()"}{/g->input}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="File name"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Type"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Size"}
	  {/g->column}
	{/g->row}

	{foreach from=$form.localServerFiles item=file}
	  {g->row}
	    {g->column}
	      {g->input type="checkbox" name="form[localServerFiles][`$file.fileKey`]"}{/g->input}
	    {/g->column}
	    {g->column}
	      {$file.fileName}
	    {/g->column}
	    {g->column}
	      {$file.itemType}
	    {/g->column}
	    {g->column}
	      {g->text one="%d byte" many="%d bytes" count=$file.stat.size arg1=$file.stat.size}
	    {/g->column}
	  {/g->row}
	{/foreach}
      {/g->table}
      {g->input type="submit" name="form[action][addFromLocalServer]"}{g->text text="Add Files"}{/g->input}
    {/if} {* {if !empty($form.localServerFiles)} *}
  {/if} {* {if empty($ItemAddFromServer.localServerDirList)} *}
{/g->box}



{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Add Items to this Album"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery can handle files of any format.  However, it can only create automatic resizes and thumbnails for certain types of files."}
    {/g->description}
  {/g->box}

  {g->tabbedbox}
    {g->tabset}
      {if $ItemAddChildren.mode == 'fromBrowser'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="From Web Browser"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddChildren" arg3="itemId=`$ItemAdmin.item.id`" arg4="mode=fromBrowser"}
	      {g->text text="From Web Browser"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}

      {if $ItemAddChildren.mode == 'fromLocalServer'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="From Local Server"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddChildren" arg3="itemId=`$ItemAdmin.item.id`" arg4="mode=fromLocalServer"}
	      {g->text text="From Local Server"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}

      {if $ItemAddChildren.mode == 'fromWebPage'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="From Web Page"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddChildren" arg3="itemId=`$ItemAdmin.item.id`" arg4="mode=fromWebPage"}
	      {g->text text="From Web Page"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}
    {/g->tabset}
    
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

      {if !empty($form.webPageUrls)}
        <script type="text/javascript" language="javascript">
          function toggleSelections() {ldelim}
            form = document.forms[0];
            state = form.elements['{g->elementName name="selectionToggle"}'].checked;
            {foreach from=$form.webPageUrls item=url}
  	    form.elements['{g->elementName name="form[webPageUrls][`$url.url`]"}'].checked = state;
  	    {/foreach}
  	  {rdelim}
        </script>
      {/if}

      {if ($ItemAddChildren.mode == 'fromLocalServer')}
	<script type="text/javascript" language="javascript">
          function selectPath(path) {ldelim}
            document.forms[0].elements['{g->elementName name="form[localServerPath]"}'].value = path;
          {rdelim}
	</script>
      {/if}

      {if ($ItemAddChildren.mode == 'fromWebPage')}
	<script type="text/javascript" language="javascript">
          function selectPath(path) {ldelim}
            document.forms[0].elements['{g->elementName name="form[webPage]"}'].value = path;
          {rdelim}
	</script>
      {/if}

      {if $ItemAddChildren.mode == 'fromBrowser'}
	{g->box style="admin"}
	  {g->description}
	    {g->text one="Upload a file directly from your computer."
	    many="Upload up to %d files directly from your computer."
	    count=$form.uploadBoxCount
	    arg1=$form.uploadBoxCount}
	    {g->text text="Enter the full path to the file and an optional caption in the boxes below."}
	    {g->input type="hidden" name="form[uploadBoxCount]"}{$form.uploadBoxCount}{/g->input}
	  {/g->description}

	  {g->element}
	    {section name="uploadBoxes" loop=$form.uploadBoxCount}
	      {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
	      {g->box}
		{g->title}
		  {g->text text="File"}
		{/g->title}
		{g->element}
		  {g->input name="form[$iteration]" type="file" size="60"}{/g->input}
		{/g->element}
	      {/g->box}

	      {g->box}
		{g->title}
		  {g->text text="Caption"}
		{/g->title}
		{g->element}
		  {g->textarea rows="2" cols="60" name="form[caption][$iteration]"}{/g->textarea}
		{/g->element}
	      {/g->box}
	    {/section}
	  {/g->element}

	  {g->element}
	    {g->input type="submit" name="form[action][addFromBrowser]"}{g->text text="Add Items"}{/g->input}
	  {/g->element}
	{/g->box}
      {/if}

      {if $ItemAddChildren.mode == 'fromLocalServer'}
	{g->box style="admin"}
	  {g->description}
	    {g->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anyelement on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
	  {/g->description}

	  {if empty($ItemAddChildren.localServerDirList)}
	    {g->element}
	      {g->text text="For security purposes, you can't use this feature until the Gallery Site Administrator configures a set of legal upload directories."}
	      {if $ItemAddChildren.isAdmin} 
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
		{if $ItemAddChildren.isAdmin}
		  {g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminCore"}
		    {g->text text="modify"}
		  {/g->link}
		{/if}
		{g->listing}
		  {foreach from=$ItemAddChildren.localServerDirList item=dir}
		    {g->item}
		      {g->title}
			{g->link javascript="selectPath('$dir')"}
			  {$dir}
			{/g->link}
		      {/g->title}
		    {/g->item}
		  {/foreach}
		{/g->listing}
		{if !empty($ItemAddChildren.recentPaths)}
		  {g->text text="Recent Directories"}
		  {g->listing}
		    {foreach from=$ItemAddChildren.recentPaths item=dir}
		      {g->item}
			{g->title}
			  {g->link javascript="selectPath('$dir')"}
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
		{g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddChildren" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[localServerPath]=`$form.localServerPath`" arg5="form[formName]=ItemAddChildren"}
		  {g->text text="change"}
		{/g->link}
		{g->input type="hidden" name="form[localServerPath]"}{$form.localServerPath}{/g->input}
	      {/g->element}
	      {g->element}
		{g->text one="%d file found" many="%d files found" count=$ItemAddChildren.localServerFileCount arg1=$ItemAddChildren.localServerFileCount}
	      {/g->element}

	      {g->table style="admin_listing" evenodd="true"}
		{g->row}
		  {g->column header="true"}
		    {g->input name="selectionToggle" type="checkbox" onChange="javascript:toggleSelections()"}{/g->input}
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
	  {/if} {* {if empty($ItemAddChildren.localServerDirList)} *}
	{/g->box}
      {/if}
      
      {if $ItemAddChildren.mode == 'fromWebPage'}
	{g->box style="admin"}
	  {g->description}
	    {g->text text="Import files into Gallery from another website.  Enter a URL below to a web page anywhere on the net and Gallery will allow you to upload any media files that it finds on that page.  Note that if you're entering a URL to a directory, you should end the URL with a trailing slash (eg, http://example.com/directory/). "}
	  {/g->description}

	  {if empty($form.webPageUrls)}
	    {g->element}
	      {g->text text="URL"}
	      {g->input type="text" size="80" name="form[webPage]"}{$form.webPage}{/g->input}
	    {/g->element}
	    
	    {if isset($form.error.webPage.missing)}
	      {g->error}
		{g->text text="You must enter a URL to a web page"}
	      {/g->error}
	    {/if}
	    
	    {if isset($form.error.webPage.invalid)}
	      {g->error}
		{g->text text="The URL entered must begin with http://"}
	      {/g->error}
	    {/if}
	    
	    {if isset($form.error.webPage.unavailable)}
	      {g->error}
		{g->text text="The web page you specified is unavailable"}
	      {/g->error}
	    {/if}
	    
	    {g->element}
	      {if !empty($ItemAddChildren.recentPaths)}
		{g->text text="Recent URLs"}
		{g->listing}
		  {foreach from=$ItemAddChildren.recentPaths item=dir}
		    {g->item}
		      {g->title}
			{g->link javascript="selectPath('$dir')"}
			  {$dir}
			{/g->link}
		      {/g->title}
		    {/g->item}
		  {/foreach}
		{/g->listing}
	      {/if}

	      {g->input type="submit" name="form[action][findFilesFromWebPage]"}
		{g->text text="Find Files"}
	      {/g->input}
	    {/g->element}
	  {else} {* {if empty($form.webPageUrls)} *}
	    {g->element style="emphasized"}
	      {g->text text="URL: %s" arg1=$form.webPage}
	      {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddChildren" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[webPage]=`$form.webPage`" arg5="form[formName]=ItemAddChildren"}
		{g->text text="change"}
	      {/g->link}
	      {g->input type="hidden" name="form[webPage]"}{$form.webPage}{/g->input}
	    {/g->element}
	    {g->element}
	      {g->text one="%d url found" 
	               many="%d urls found" 
                       count=$ItemAddChildren.webPageUrlCount 
         	       arg1=$ItemAddChildren.webPageUrlCount}
	    {/g->element}

	    {g->table style="admin_listing" evenodd="true"}
	      {g->row}
		{g->column header="true"}
		  {g->input name="selectionToggle" type="checkbox" onChange="javascript:toggleSelections()"}{/g->input}
		{/g->column}
		{g->column header="true"}
		  {g->text text="URL"}
		{/g->column}
		{g->column header="true"}
		  {g->text text="Type"}
		{/g->column}
	      {/g->row}

	      {foreach from=$form.webPageUrls item=url}
		{g->row}
		  {g->column}
		    {g->input type="checkbox" name="form[webPageUrls][`$url.url`]"}{/g->input}
		  {/g->column}
		  {g->column}
		    {$url.url}
		  {/g->column}
		  {g->column}
		    {$url.itemType}
		  {/g->column}
		{/g->row}
	      {/foreach}
	    {/g->table}
	    {g->input type="submit" name="form[action][addFromWebPage]"}{g->text text="Add URLs"}{/g->input}
	  {/if} {* {if !empty($form.webPageUrls)} *}
	{/g->box}
      {/if}
    {/g->element}
  {/g->tabbedbox}
{/g->pagebox}

... doesn't work because we're inside a component block from itemadmin
... perhaps use some kind of meta-global tag that gets picked up by the global
    file?


{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Add Items to this Album"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="Gallery can handle files of any format.  However, it can only create automatic resizes and thumbnails for certain types of files."}
  {/gallery->description}
{/gallery->detailedbox}

{gallery->tabbedbox}
  {if $ItemAddChildren.mode != 'fromBrowser'}
    {gallery->item}
      {gallery->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id url_mode="fromBrowser"}
	{gallery->text text="From Web Browser"}
      {/gallery->link}
    {/gallery->item}
  {else}
    {gallery->item selected="true"}
      {gallery->text text="From Web Browser"}
    {/gallery->item}
  {/if}

  {if $ItemAddChildren.mode != 'fromLocalServer'}
    {gallery->item}
      {gallery->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id url_mode="fromLocalServer"}
	{gallery->text text="From Local Server"}
      {/gallery->link}
    {/gallery->item}
  {else}
    {gallery->item selected="true"}
      {gallery->text text="From Local Server"}
    {/gallery->item}
  {/if}

  {if $ItemAddChildren.mode != 'fromWebPage'}
    {gallery->item}
      {gallery->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id url_mode="fromWebPage"}
	{gallery->text text="From Web Page"}
      {/gallery->link}
    {/gallery->item}
  {else}
    {gallery->item selected="true"}
      {gallery->text text="From Web Page"}
    {/gallery->item}
  {/if}
  
  {gallery->body}
    {if !empty($form.localServerFiles)}
      <script type="text/javascript" language="javascript">
        function toggleSelections() {ldelim}
          form = document.forms[0];
          state = form.elements['{gallery->elementName name="selectionToggle"}'].checked;
      {foreach from=$form.localServerFiles item=file}
          form.elements['{gallery->elementName name="form.localServerFiles.`$file.fileKey`"}'].checked = state;
      {/foreach}
        {rdelim}
      </script>
    {/if}
  
    {if ($ItemAddChildren.mode == 'fromLocalServer')}
      <script type="text/javascript" language="javascript">
        function selectPath(path) {ldelim}
          document.forms[0].elements['{gallery->elementName name="form.localServerPath"}'].value = path;
        {rdelim}
      </script>
    {/if}

    {if $ItemAddChildren.mode == 'fromBrowser'}
      {gallery->detailedbox}
	{gallery->description}
	  {gallery->text one="Upload a file directly from your computer."
	  many="Upload up to %d files directly from your computer."
	  count=$form.uploadBoxCount
	  arg1=$form.uploadBoxCount}
	  {gallery->text text="Enter the full path to the file and an optional caption in the boxes below."}
	  {gallery->input type="hidden" name="form.uploadBoxCount"}{$form.uploadBoxCount}{/gallery->input}
	{/gallery->description}

	{gallery->body}
	  {gallery->widget2box}
	    {section name="uploadBoxes" loop=$form.uploadBoxCount}
	      {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
	      {gallery->widget2}
		{gallery->title}
		  {gallery->text text="File"}
		{/gallery->title}
		{gallery->body}
		  {gallery->input name=form.fileUpload.$iteration type="file" size="60"}{/gallery->input}
		{/gallery->body}
	      {/gallery->widget2}

	      {gallery->widget2}
		{gallery->title}
		  {gallery->text text="Caption"}
		{/gallery->title}
		{gallery->body}
		  {gallery->textarea rows="2" cols="60" name=form.fileUpload.$iteration.caption}{/gallery->textarea}
		{/gallery->body}
	      {/gallery->widget2}
	    {/section}
	  {/gallery->widget2box}
	{/gallery->body}
      {/gallery->detailedbox}

      {gallery->detailedbox}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.addFromBrowser"}{gallery->text text="Add Items"}{/gallery->input}
	{/gallery->body}
      {/gallery->detailedbox}
    {/if}

    {if $ItemAddChildren.mode == 'fromLocalServer'}
      {gallery->detailedbox}
	{gallery->description}
	  {gallery->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anybody on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
	{/gallery->description}

	{gallery->body}
	  {if empty($ItemAddChildren.localServerDirList)}
	    {gallery->text text="For security purposes, you can't use this feature until the Gallery Site Administrator configures a set of legal upload directories."}
	    {if $ItemAddChildren.isAdmin} 
	      {gallery->link url_view="core:SiteAdmin" url_subView="core:AdminCore"}
		{gallery->text text="site admin"}
	      {/gallery->link}
	    {/if}
	  {else}
	    {if empty($form.localServerFiles)}
	      {gallery->widget2box}
		{gallery->widget2}
		  {gallery->title}
		    {gallery->text text="Server Path"}
		  {/gallery->title}
		  {gallery->body}
		    {gallery->input type=text size=80 name="form.localServerPath"}{$form.localServerPath}{/gallery->input}
		    {if isset($form.error.localServerPath.missing)}
		      {gallery->error}
			{gallery->text text="You must enter a directory."}
		      {/gallery->error}
		    {/if}

		    {if isset($form.error.localServerPath.invalid)}
		      {gallery->error}
			{gallery->text text="The directory you entered is invalid.  Make sure that the directory is readable by all users."}
		      {/gallery->error}
		    {/if}

		    {if isset($form.error.localServerPath.illegal)}
		      {gallery->error}
			{gallery->text text="The directory you entered is illegal.  It must be a sub directory of one of the directories listed below."}
		      {/gallery->error}
		    {/if}

		    <br />
		    {gallery->text text="Legal Directories"}
		    {if $ItemAddChildren.isAdmin}
		      {gallery->link url_view="core:SiteAdmin" url_subView="core:AdminCore"}
			{gallery->text text="modify"}
		      {/gallery->link}
		    {/if}
		    {gallery->listingbox}
		      {foreach from=$ItemAddChildren.localServerDirList item=dir}
			{gallery->item}
			  {gallery->link javascript="selectPath('$dir')"}
			    {$dir}
			  {/gallery->link}
			{/gallery->item}
		      {/foreach}
		    {/gallery->listingbox}
		    {gallery->input type="submit" name="form.action.findFilesFromLocalServer"}{gallery->text text="Find Files"}{/gallery->input}
		  {/gallery->body}
		{/gallery->widget2}
	      {/gallery->widget2box}
	    {else} {* {if empty($form.localServerFiles)} *}
	      {gallery->widget2box}
		{gallery->widget2}
		  {gallery->title}
		    {gallery->text text="Directory"} {$form.localServerPath}
		    {gallery->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id url_form_localServerPath=$form.localServerPath url_form_formName="ItemAddChildren"}
		      {gallery->text text="change"}
		    {/gallery->link}
		    {gallery->input type="hidden" name="form.localServerPath"}{$form.localServerPath}{/gallery->input}
		  {/gallery->title}
		  {gallery->description}
		    {gallery->text one="%d file found" many="%d files found" count=$ItemAddChildren.localServerFileCount arg1=$ItemAddChildren.localServerFileCount}
		  {/gallery->description}
		  {gallery->body}
		    {gallery->table}
		      {gallery->row}
			{gallery->column header="true"}
			  {gallery->input name="selectionToggle" type="checkbox" onChange="javascript:toggleSelections()"}{/gallery->input}
			{/gallery->column}
			{gallery->column header="true"}
			  {gallery->text text="File name"}
			{/gallery->column}
			{gallery->column header="true"}
			  {gallery->text text="Type"}
			{/gallery->column}
			{gallery->column header="true"}
			  {gallery->text text="Size"}
			{/gallery->column}
		      {/gallery->row}

		      {foreach from=$form.localServerFiles item=file}
			{gallery->row}
			  {gallery->column}
			    {gallery->input type="checkbox" name="form.localServerFiles.`$file.fileKey`"}{/gallery->input}
			  {/gallery->column}
			  {gallery->column}
			    {$file.fileName}
			  {/gallery->column}
			  {gallery->column}
			    {$file.itemType}
			  {/gallery->column}
			  {gallery->column}
			    {gallery->text one="%d byte" many="%d bytes" count=$file.stat.size arg1=$file.stat.size}
			  {/gallery->column}
			{/gallery->row}
		      {/foreach}
		    {/gallery->table}
		    {gallery->input type="submit" name="form.action.addFromLocalServer"}{gallery->text text="Add Files"}{/gallery->input}
		  {/gallery->body}
		{/gallery->widget2}
	      {/gallery->widget2box}
	    {/if} {* {if !empty($form.localServerFiles)} *}
	  {/if} {* {if empty($ItemAddChildren.localServerDirList)} *}
	{/gallery->body}
      {/gallery->detailedbox}
    {/if}

    {if $ItemAddChildren.mode == 'fromWebPage'}
      {gallery->detailedbox}
	{gallery->title}
	  {gallery->text text="Not implemented yet"}
	{/gallery->title}
      {/gallery->detailedbox}
    {/if}
  {/gallery->body}
{/gallery->tabbedbox}

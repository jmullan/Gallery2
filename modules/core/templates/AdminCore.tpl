{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="General Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Settings saved successfully"}
      {/if}
      {if isset($status.addedDir)}
	{g->text text="Added local upload dir successfully"}
      {/if}
      {if isset($status.removedDir)}
	{g->text text="Removed local upload dir successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Defaults"}
    {/g->title}

    {g->description}
      {g->text text="These are default values.  They can be overridden in each album."}
    {/g->description}

    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Default sort order"}
	{/g->column}

	{g->column}
	  {g->select name="form.default.orderBy"}
	    {html_options options=$AdminCore.orderByList selected=$form.default.orderBy}
	  {/g->select}
	  {g->select name="form.default.orderDirection"}
	    {html_options options=$AdminCore.orderDirectionList selected=$form.default.orderDirection}
	  {/g->select}
	{/g->column}
      {/g->row}

      {g->row}
	{g->column}
	  {g->text text="Default layout"}
	{/g->column}

	{g->column}
	  {g->select name="form.default.layout"}
	    {html_options options=$AdminCore.layoutList selected=$form.default.layout}
	  {/g->select}
	{/g->column}
      {/g->row}

      {g->row}
	{g->column}
	  {g->text text="Default theme"}
	{/g->column}

	{g->column}
	  {g->select name="form.default.theme"}
	    {html_options options=$AdminCore.themeList selected=$form.default.theme}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Language settings"}
    {/g->title}
    {g->description}
      {g->text text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences."}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Default language"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.default.language"}
	    {html_options options=$AdminCore.languageList selected=$form.default.language}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Filesystem Permissions"}
    {/g->title}
    {g->description}
      {g->text text="Specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="New directories"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.permissions.directory"}
	    {html_options values=$AdminCore.permissionsDirectoryList selected=$form.permissions.directory output=$AdminCore.permissionsDirectoryList}
	  {/g->select}
	{/g->column}
      {/g->row}
      
      {g->row}
	{g->column}
	  {g->text text="New files"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.permissions.file"}
	    {html_options values=$AdminCore.permissionsFileList selected=$form.permissions.file output=$AdminCore.permissionsFileList}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Local Server Upload Paths"}
    {/g->title}
    
    {g->description}
      {g->text text="Specify the legal directories on the local server where a user can store files and then upload them into Gallery using the <i>Upload from Local Server</i> feature.  The paths you enter here and all the files and directories under those paths will be available to any Gallery user who has upload privileges, so you should limit this to directories that won't contain sensitive data (eg. /tmp or /usr/ftp/incoming)"}
    {/g->description}
    
    {g->table style="admin_listing" evenodd="true"}
      {g->row}
	{g->column header="true"}
	  {g->text text="Path"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Action"}
	{/g->column}
      {/g->row}

      {foreach from=$AdminCore.localServerDirList item=dir}
	{g->row}
	  {g->column}
	    {$dir}
	  {/g->column}
	  {g->column}
	    {g->link url_controller="core:AdminCore" url_form_action_removeUploadLocalServerDir=1 url_form_uploadLocalServer_selectedDir=$dir}
	      {g->text text="remove"}
	    {/g->link}
	  {/g->column}
	{/g->row}
      {/foreach}

      {g->row}
	{g->column}
	  {g->input type="text" size="40" name="form.uploadLocalServer.newDir"}{$form.uploadLocalServer.newDir}{/g->input}
	{/g->column}

	{g->column}
	  {g->input type="submit" name="form.action.addUploadLocalServerDir"}
	    {g->text text="add"}
	  {/g->input}
	{/g->column}
      {/g->row}
    {/g->table}

    {if isset($form.error.uploadLocalServer.newDir.missing)}
      {g->error}
	{g->text text="You must enter a directory to add."}
      {/g->error}
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.restrictedByOpenBasedir)}
      {g->error}
	{capture name="open_basedir"}
	  {g->link href="http://php.net/ini_set"}
	    {g->text text="open_basedir documentation"}
	  {/g->link}
	{/capture}
	{g->text text="Your webserver is configured to prevent you from accessing that directory.  Please refer to the %s and consult your webserver administrator." arg1=$smarty.capture.open_basedir}
      {/g->error}
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.notReadable)}
      {g->error}
	{g->text text="The webserver does not have permissions to read that directory."}
      {/g->error}
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.notADirectory)}
      {g->error}
	{g->text text="The path you specified is not a valid directory."}
      {/g->error}
    {/if}

  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Session Settings"}
    {/g->title}
    
    {g->description}
      {g->text text="Specify the lifetime of the session here."}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Lifetime"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.session.lifetime"}
	    {html_options options=$AdminCore.sessionTimeList selected=$form.session.lifetime}
	  {/g->select}
	{/g->column}
      {/g->row}
      
      {g->row}
	{g->column}
	  {g->text text="Inactivity Timeout"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.session.inactivityTimeout"}
	    {html_options options=$AdminCore.sessionTimeList selected=$form.session.inactivityTimeout}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="URL Style"}
    {/g->title}
    
    {g->description}
      {capture name="acceptPathInfoLink"}
	{g->link href="http://httpd.apache.org/docs-2.0/mod/core.html#acceptpathinfo"}
	  {g->text text="AcceptPathInfo Directive."}
	{/g->link}
      {/capture}
      {capture name="shortUrlTestLink"}
	{g->link url_view="core:ShowItem" url_itemId=$AdminCore.shortUrlTestItemId url_forceShortUrls=true}
	  {g->text text="test url"}
	{/g->link}
      {/capture}
      {g->text text="Gallery has the option to use a compact URL format, however this format is not supported by default on all web servers.  It is enabled by default on Apache 1, but not on Apache 2.  If you're using Apache 2 and you want this feature, you must use the %s  Use this %s to find out if short URLs work for you.  If the link returns a webserver error then they don't work for you." arg1=$smarty.capture.acceptPathInfoLink arg2=$smarty.capture.shortUrlTestLink}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Use short URLs?"}
	{/g->column}
	
	{g->column}
	  {g->select name="form.misc.useShortUrls"}
	    {html_options options=$AdminCore.useShortUrlsList selected=$form.misc.useShortUrls}
	  {/g->select}
	{/g->column}
      {/g->row}

    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form.action.save"}
	{g->text text="save"}
      {/g->input}
      {g->input type="submit" name="form.action.reset"}
	{g->text text="reset"}
      {/g->input}
    {/g->element}
  {/g->box}

{/g->pagebox}

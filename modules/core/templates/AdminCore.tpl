{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="General Settings"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Settings saved successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Defaults"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="These are default values.  They can be overridden in each album."}
  {/gallery->description}

  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Default sort order"}
	{/gallery->title}

	{gallery->body}
	  {gallery->select name="form.default.orderBy"}
	    {html_options options=$AdminCore.orderByList selected=$form.default.orderBy}
	  {/gallery->select}

	  {gallery->select name="form.default.orderDirection"}
	    {html_options options=$AdminCore.orderDirectionList selected=$form.default.orderDirection}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}

      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Default layout"}
	{/gallery->title}

	{gallery->body}
	  {gallery->select name="form.default.layout"}
	    {html_options values=$AdminCore.layoutList selected=$form.default.layout output=$AdminCore.layoutList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}

      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Default theme"}
	{/gallery->title}

	{gallery->body}
	  {gallery->select name="form.default.theme"}
	    {html_options values=$AdminCore.themeList selected=$form.default.theme output=$AdminCore.themeList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Language settings"}
  {/gallery->title}
  {gallery->description}
    {gallery->text text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences."}
  {/gallery->description}
  
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Default language"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->select name="form.default.language"}
	    {html_options options=$AdminCore.languageList selected=$form.default.language}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Filesystem Permissions"}
  {/gallery->title}
  {gallery->description}
    {gallery->text text="Specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
  {/gallery->description}
  
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="New directories"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->select name="form.permissions.directory"}
	    {html_options values=$AdminCore.permissionsDirectoryList selected=$form.permissions.directory output=$AdminCore.permissionsDirectoryList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
      
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="New files"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->select name="form.permissions.file"}
	    {html_options values=$AdminCore.permissionsFileList selected=$form.permissions.file output=$AdminCore.permissionsFileList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Local Server Upload Paths"}
  {/gallery->title}
  
  {gallery->description}
    {gallery->text text="Specify the legal directories on the local server where a user can store files and then upload them into Gallery using the <i>Upload from Local Server</i> feature.  The paths you enter here and all the files and directories under those paths will be available to any Gallery user who has upload privileges, so you should limit this to directories that won't contain sensitive data (eg. /tmp or /usr/ftp/incoming)"}
  {/gallery->description}
  
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Legal Paths"}
	{/gallery->title}
	{gallery->body}
	  {gallery->select name="form.uploadLocalServer.selectedDir" size="5"}
	    {html_options values=$AdminCore.localServerDirList selected=$form.uploadFromLocalServer.selectedDir output=$AdminCore.localServerDirList}
	  {/gallery->select}

	  <br/>

	  {gallery->input type="submit" name="form.action.removeUploadLocalServerDir"}
	    {gallery->text text="remove"}
	  {/gallery->input}

	  <br/>

	  {gallery->input type="submit" name="form.action.addUploadLocalServerDir"}
	    {gallery->text text="add"}
	  {/gallery->input}
	  {gallery->input type="text" name="form.uploadLocalServer.newDir"}{/gallery->input}

	  {if isset($form.error.uploadLocalServer.newDir.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a directory to add."}
	    {/gallery->error}
	  {/if}

	  {if isset($form.error.uploadLocalServer.selectedDir.missing)}
	    {gallery->error}
	      {gallery->text text="You must select a directory to remove"}
	    {/gallery->error}
	  {/if}

	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Session Settings"}
  {/gallery->title}
  
  {gallery->description}
    {gallery->text text="Specify the lifetime of the session here."}
  {/gallery->description}
  
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Lifetime"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->select name="session.lifetime"}
	    {html_options options=$AdminCore.sessionTimeList selected=$form.session.lifetime}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
      
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Inactivity Timeout"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->select name="session.inactivityTimeout"}
	    {html_options options=$AdminCore.sessionTimeList selected=$form.session.inactivityTimeout}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.save"}
      {gallery->text text="save"}
    {/gallery->input}
    {gallery->input type="submit" name="form.action.reset"}
      {gallery->text text="reset"}
    {/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

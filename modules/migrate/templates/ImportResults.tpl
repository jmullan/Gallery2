{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Import Complete"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->success}
	{if ($ImportResults.counts.userImportSuccess)}
	  {g->text one="Successfully imported %d user." 
	           many="Successfully imported %d users." 
	           count=$ImportResults.counts.userImportSuccess
                   arg1=$ImportResults.counts.userImportSuccess
	  }
	{else}
	  {g->text text="No users imported."}
	{/if}
      {/g->success}
    {/g->title}
    
    {if sizeof($ImportResults.status.userImportSuccess) > 0}
      {foreach from=$status.userImportSuccess key=username item=junk}
	{g->element}
	  {g->text text="Imported %s" arg1=$username}
	{/g->element}
      {/foreach}
    {/if}
  {/g->box}

  {if sizeof($ImportResults.status.userImportFailure) > 0}
    {g->box style="admin"}
      {g->title}
	{g->error}
	  {if ($ImportResults.counts.userImportFailure)}
	    {g->text one="Error while importing %d user." 
	             many="Errors while importing %d users." 
  	             count=$ImportResults.counts.userImportFailure
                     arg1=$ImportResults.counts.userImportFailure
	    }
	  {/if}
	{/g->error}
      {/g->title}
    
      {foreach from=$ImportResults.status.userImportFailure key=username item=junk}
	{g->element}
	  {g->text text="Error importing %s" arg1=$username}
	{/g->element}
      {/foreach}
    {/g->box}
  {/if}



  {g->box style="admin"}
    {g->title}
      {g->success}
	{if ($ImportResults.counts.albumImportSuccess)}
	  {g->text one="Successfully imported %d album." 
	           many="Successfully imported %d albums." 
	           count=$ImportResults.counts.albumImportSuccess
                   arg1=$ImportResults.counts.albumImportSuccess
	  }
	{else}
	  {g->text text="No users imported."}
	{/if}
      {/g->success}
    {/g->title}
    {if sizeof($ImportResults.status.albumImportSuccess) > 0}
      {foreach from=$status.albumImportSuccess key=albumname item=junk}
	{g->element}
	  {g->text text="Imported %s" arg1=$albumname}
	{/g->element}
      {/foreach}
    {/if}
  {/g->box}

  {if sizeof($ImportResults.status.albumImportFailure) > 0}
    {g->box style="admin"}
      {g->title}
	{g->error}
	  {if ($ImportResults.counts.albumImportFailure)}
	    {g->text one="Error while importing %d album." 
	             many="Errors while importing %d albums." 
  	             count=$ImportResults.counts.albumImportFailure
                     arg1=$ImportResults.counts.albumImportFailure
	    }
	  {/if}
	{/g->error}
      {/g->title}
    
      {foreach from=$ImportResults.status.albumImportFailure key=albumname item=junk}
	{g->element}
	  {g->text text="Error importing %s" arg1=$albumname}
	{/g->element}
      {/foreach}
    {/g->box}
  {/if}

  {g->box style="admin"}
    {g->element}
      {g->link url_view="core:SiteAdmin" url_subView="migrate:SelectGallery"}
	{g->text text="Import more data"}
      {/g->link}
    {/g->element}
  {/g->box}
{/g->pagebox}

<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Import Complete"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      <div class="giSuccess">
	{if ($ImportResults.counts.userImportSuccess)}
	{g->text one="Successfully imported %d user." 
	         many="Successfully imported %d users." 
	         count=$ImportResults.counts.userImportSuccess
                 arg1=$ImportResults.counts.userImportSuccess}
	{else}
	{g->text text="No users imported."}
	{/if}
      </div>
    </div>
    
    {if sizeof($ImportResults.status.userImportSuccess) > 0}
    <ul>
      {foreach from=$status.userImportSuccess key=username item=junk}
      <li>
	{g->text text="Imported %s" arg1=$username}
      </li>
      {/foreach}
    </ul>
    {/if}
  </div>

  {if sizeof($ImportResults.status.userImportFailure) > 0}
  <div class="gbAdmin">
    <div class="giTitle">
      <div class="giError">
	{if ($ImportResults.counts.userImportFailure)}
	{g->text one="Error while importing %d user." 
	         many="Errors while importing %d users." 
  	         count=$ImportResults.counts.userImportFailure
                 arg1=$ImportResults.counts.userImportFailure}
	{/if}
      </div>
    </div>
    
    {foreach from=$ImportResults.status.userImportFailure key=username item=junk}
    <ul>
      <li>
	{g->text text="Error importing %s" arg1=$username}
      </li>
    </ul>
    {/foreach}
  </div>
  {/if}

  <div class="gbAdmin"}
    <div class="giTitle">
      <div class="giSuccess">
	{if ($ImportResults.counts.albumImportSuccess)}
	{g->text one="Successfully imported %d album." 
	         many="Successfully imported %d albums." 
	         count=$ImportResults.counts.albumImportSuccess
                 arg1=$ImportResults.counts.albumImportSuccess}
	{else}
	{g->text text="No albums imported."}
	{/if}
      </div>
    </div>

    {if sizeof($ImportResults.status.albumImportSuccess) > 0}
    <ul>
      {foreach from=$status.albumImportSuccess key=albumname item=junk}
      <li>
	{g->text text="Imported %s" arg1=$albumname}
      </li>
      {/foreach}
    </ul>
    {/if}
  </div>

  {if sizeof($ImportResults.status.albumImportFailure) > 0}
  <div class="gbAdmin"}
    <div class="giTitle">
      <div class="giError">
	{if ($ImportResults.counts.albumImportFailure)}
	{g->text one="Error while importing %d album." 
	         many="Errors while importing %d albums." 
  	         count=$ImportResults.counts.albumImportFailure
                 arg1=$ImportResults.counts.albumImportFailure}
	{/if}
      </div>
    </div>
    
    <ul>
      {foreach from=$ImportResults.status.albumImportFailure key=albumname item=junk}
      <li>
	{g->text text="Error importing %s" arg1=$albumname}
      </li>
      {/foreach}
    </ul>
  </div>
  {/if}

  <div class="gbAdmin"}
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=migrate:SelectGallery"}">
      {g->text text="Import more data"}
    </a>
  </div>
</div>

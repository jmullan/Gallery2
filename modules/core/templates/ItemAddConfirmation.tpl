<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Upload Complete"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {if isset($ItemAddConfirmation.count)}
      {g->text one="Successfully added %d file." 
	       many="Successfully added %d files." 
	       count=$ItemAddConfirmation.count 
	       arg1=$ItemAddConfirmation.count}
      {else}
      {g->text text="No files added."}
      {/if}
    </div>

    {foreach from=$ItemAddConfirmation.status.addedFiles item=entry}
    {capture name="itemLink"}
    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$entry.id`"}">
      {$entry.fileName}
    </a>
    {/capture}
    {g->text text="Added %s" arg1=$smarty.capture.itemLink}
    <br/>
    {/foreach}
  </div>

  <div class="gbAdmin">
    <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`"}">
      {g->text text="Add more files"}
    </a>
  </div>
</div>

{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAddConfirmation.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Upload Complete"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <h3 class="giTitle">
      {if isset($ItemAddConfirmation.count)}
      {g->text one="Successfully added %d file." 
	       many="Successfully added %d files." 
	       count=$ItemAddConfirmation.count 
	       arg1=$ItemAddConfirmation.count}
      {else}
      {g->text text="No files added."}
      {/if}
    </h3>

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

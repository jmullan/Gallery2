{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Delete Watermark"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <p class="giDescription">
      {$ConfirmDelete.item.name} <br/>
      {g->image item=$ConfirmDelete.item image=$ConfirmDelete.item maxSize=150}
    </p>
    <p class="giDescription">
      {g->text one="This watermark is used on one item." count=$ConfirmDelete.count
               many="This watermark is used on %d items." arg1=$ConfirmDelete.count}
      {g->text text="The watermark will be removed from all items if the watermark image is deleted."}
    </p>

    <input type="hidden" name="{g->formVar var="form[itemId]"}" value="{$form.itemId}"/>
    {if !empty($form.fromAdmin)}
      <input type="hidden" name="{g->formVar var="form[fromAdmin]"}" value="{$form.fromAdmin}"/>
    {/if}
    <input type="submit" name="{g->formVar var="form[action][delete]"}" value="{g->text text="Delete"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>

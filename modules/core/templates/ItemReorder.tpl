<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Reorder Album"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
    </div>
  </div>

  {if isset($ItemReorder.show.automaticOrderMessage)}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This album has an automatic sort order specified, so you cannot change the order of items manually.  You must remove the automatic sort order to continue."}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemEditAlbum" arg3="itemId=`$ItemAdmin.item.id`"}" value="{g->text text="[change]"}"/>
    </div>
  </div>
  {else}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Change the order of the items in this album."}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Move this item"}
      </div>

      <select name="{g->formVar var="form[selectedId]"}">
	{foreach from=$ItemReorder.peers item=peer}
	<option value="{$peer.id}"> {$peer.title|default:$peer.pathComponent} </option>
	{/foreach}
      </select>
	
      <select name="{g->formVar var="form[placement]"}">
	<option value="before"> {g->text text="before"} </option>
	<option value="after"> {g->text text="after"} </option>
      </select>

      <select name="{g->formVar var="form[targetId]"}">
	{foreach from=$ItemReorder.peers item=peer}
	<option value="{$peer.id}"> {$peer.title|default:$peer.pathComponent} </option>
	{/foreach}
      </select>
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][reorder]"}" value="{g->text text="Reorder"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
  {/if}
</div>

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Reorder Album"}
    {/g->title}
  {/g->banner}

  {if isset($ItemReorder.show.automaticOrderMessage)}
    {g->box style="admin"}
      {g->description}
	{g->text text="This album has an automatic sort order specified, so you cannot change the order of items manually.  You must remove the automatic sort order to continue."}
	{g->link url_view="core:ItemAdmin" url_subView="core:ItemEditAlbum" url_itemId=$ItemAdmin.item.id}
	  {g->text text="[change]"}
	{/g->link}
      {/g->description}
    {/g->box}
  {else}
    {g->box style="admin"}
      {g->description}
	{g->text text="Change the order of the items in this album."}
      {/g->description}

      {g->box}
	{g->title}
	  {g->text text="Move this item"}
	{/g->title}

	{g->element}
	  {g->select name="form[selectedId]"}
	    {foreach from=$ItemReorder.peers item=peer}
	      <option value="{$peer.id}"> {$peer.title|default:$peer.pathComponent}
	    {/foreach}
	  {/g->select}
	  {g->select name="form[placement]"}
	    <option value="before"> {g->text text="before"}
	    <option value="after"> {g->text text="after"}
	  {/g->select}
	  {g->select name="form[targetId]"}
	    {foreach from=$ItemReorder.peers item=peer}
	      <option value="{$peer.id}"> {$peer.title|default:$peer.pathComponent}
	    {/foreach}
	  {/g->select}
	{/g->element}
      {/g->box}
    {/g->box}

    {g->box}
      {g->element}
	{g->input type="submit" name="form[action][reorder]"}{g->text text="Reorder"}{/g->input}
	{g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
      {/g->element}
    {/g->box}
  {/if}
{/g->pagebox}
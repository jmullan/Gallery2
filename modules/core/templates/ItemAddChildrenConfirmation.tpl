{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Upload Complete"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {if ($ItemAddChildrenConfirmation.count)}
	{g->text one="Successfully added %d file." many="Successfully added %d files." count=$ItemAddChildrenConfirmation.count arg1=$ItemAddChildrenConfirmation.count}
      {else}
	{g->text text="No files added."}
      {/if}
    {/g->title}
    
    {if sizeof($status) > 0}
      {foreach from=$status.addFromLocalServer item=entry}
	{g->element}
	  {g->text text="Added %s" arg1=$entry.fileName}
	{/g->element}
      {/foreach}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id}
	{g->text text="Add more files"}
      {/g->link}
    {/g->element}
  {/g->box}
{/g->pagebox}

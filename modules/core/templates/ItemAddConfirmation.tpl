{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Upload Complete"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {if isset($ItemAddConfirmation.count)}
	{g->text one="Successfully added %d file." 
	         many="Successfully added %d files." 
	         count=$ItemAddConfirmation.count 
	         arg1=$ItemAddConfirmation.count}
      {else}
	{g->text text="No files added."}
      {/if}
    {/g->title}

    {foreach from=$ItemAddConfirmation.status.addedFiles item=entry}
      {g->element}
	{capture name="itemLink"}
	  {g->link arg1="view=core:ShowItem" arg2="itemId=`$entry.id`"}
	    {$entry.fileName}
	  {/g->link}
	{/capture}
	{g->text text="Added %s" arg1=$smarty.capture.itemLink}
      {/g->element}
    {/foreach}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`"}
	{g->text text="Add more files"}
      {/g->link}
    {/g->element}
  {/g->box}
{/g->pagebox}

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Delete Item"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Are you sure?"}
    {/g->title}
    
    {g->description}
      {if ($ItemDelete.itemType == 'album')}
	{if ($ItemDelete.childCount > 0)}
	  {g->text one="This album has %d child." 
	           many="This album has %d children." 
	           count=$ItemDelete.childCount 
	           arg1=$ItemDelete.childCount}
	  {g->text text="Removing this album will remove all of its children also.  There is no undo!"}
	{else}
	  {g->text text="This album is empty.  This will completely remove this album from Gallery.  There is no undo!"}
	{/if}
      {else}
	{g->text text="This will completely remove this item from Gallery. There is no undo!"}
      {/if}
    {/g->description}

    {g->element}
      {g->input type="submit" name="form.action.delete"}{g->text text="Delete"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
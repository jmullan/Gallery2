{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Delete Item"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Are you sure?"}
  {/gallery->title}

  {gallery->description}
    {if ($ItemDelete.itemType == 'album')}
      {if ($ItemDelete.childCount > 0)}
	{gallery->text one="This album has %d child." many="This album has %d children." 
	               count=$ItemDelete.childCount 
	               arg1=$childCount}
	{gallery->text text="Removing this album will remove all of its children also.  There is no undo!"}
      {else}
	{gallery->text text="This album is empty.  This will completely remove this album from Gallery.  There is no undo!"}
      {/if}
    {else}
      {gallery->text text="This will completely remove this item from Gallery. There is no undo!"}
    {/if}
  {/gallery->description}

  {gallery->body}
    {gallery->input type="submit" name="form.action.delete"}{gallery->text text="Delete"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Upload Complete"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->title}
    {if ($ItemAddChildrenConfirmation.count)}
      {gallery->text one="Successfully added %d file." many="Successfully added %d files." count=$ItemAddChildrenConfirmation.count arg1=$ItemAddChildrenConfirmation.count}
    {else}
      {gallery->text text="No files added."}
    {/if}
  {/gallery->title}
  
  {if sizeof($status) > 0}
    {gallery->body}
      {gallery->table}
	{foreach from=$status.addFromLocalServer item=entry}
	  {gallery->row}
	    {gallery->column}
	      {gallery->text text="Added %s" arg1=$entry.fileName}
	    {/gallery->column}
	  {/gallery->row}
	{/foreach}
      {/gallery->table}
    {/gallery->body}
  {/if}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->link url_view="core:ItemAdmin" url_subView="core:ItemAddChildren" url_itemId=$ItemAdmin.item.id}
      {gallery->text text="Add more files"}
    {/gallery->link}
  {/gallery->body}
{/gallery->detailedbox}

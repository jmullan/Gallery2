{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Comment change confirmation"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {if isset($status.added)}
	{gallery->status}
	  {gallery->text text="Commented added successfully"}
	{/gallery->status}
      {/if}
      {if isset($status.deleted)}
	{gallery->status}
	  {gallery->text text="Commented deleted successfully"}
	{/gallery->status}
      {/if}
      {if isset($status.saved)}
	{gallery->status}
	  {gallery->text text="Commented modified successfully"}
	{/gallery->status}
      {/if}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

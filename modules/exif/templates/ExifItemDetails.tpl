{g->box style="comment"}
  {g->title}
    {g->text text="Photo Properties"}
  {/g->title}

  {g->subtitle}
    {g->linkset}
      {g->item}
	{g->title}
	  {if ($ExifItemDetails.mode == 'summary')}
	    {g->text text="summary"}
	  {else}
	    {g->link arg1="return=true" arg2="controller=exif:SwitchDetailMode" arg3="mode=summary"}
	      {g->text text="summary"}
	    {/g->link}
	  {/if}
	{/g->title}
      {/g->item}
      {g->item}
	{g->title}
	  {if ($ExifItemDetails.mode == 'detailed')}
	    {g->text text="details"}
	  {else}
	    {g->link arg1="return=true" arg2="controller=exif:SwitchDetailMode" arg3="mode=detailed"}
	      {g->text text="details"}
	    {/g->link}
	  {/if}
	{/g->title}
      {/g->item}
    {/g->linkset}
  {/g->subtitle}

  {g->table evenodd="true"}
    {section name=outer loop=$ExifItemDetails.exifData step=2}
      {g->row}
	{section name=inner loop=$ExifItemDetails.exifData start=$smarty.section.outer.index max=2}
	  {g->column width="15%"}
	    {g->text text=$ExifItemDetails.exifData[inner].title}
	  {/g->column}
	  {g->column width="35%"}
	    {$ExifItemDetails.exifData[inner].value}
	  {/g->column}
	{/section}
      {/g->row}
    {/section}
  {/g->table}
{/g->box}
{g->box style="comment"}
  {g->title}
    {g->text text="Photo Properties"}
  {/g->title}

  {g->subtitle}
    {g->linkset}
      {g->item}
	{g->title}
	  {if ($ExifItemDetails.mode == 'simple')}
	    {g->text text="summary"}
	  {else}
	    {g->link url_return="true" url_controller="exif:SwitchDetailMode" url_mode="simple"}
	      {g->text text="summary"}
	    {/g->link}
	  {/if}
	{/g->title}
      {/g->item}
      {g->item}
	{g->title}
	  {if ($ExifItemDetails.mode == 'advanced')}
	    {g->text text="details"}
	  {else}
	    {g->link url_return="true" url_controller="exif:SwitchDetailMode" url_mode="advanced"}
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
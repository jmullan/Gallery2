<!-- Profiling output -->
{if !empty($main.profile)}
  {gallery->table width="100%"}
    {gallery->row}
      {gallery->column colspan="8"}
	{gallery->text text="Profiling"}
      {/gallery->column}
    {/gallery->row}

    {gallery->row}
      {gallery->column header="true" rowspan="2"}
	{gallery->text text="Function"}
      {/gallery->column}
      {gallery->column header="true" colspan="2"}
	{gallery->text text="Combined"}
      {/gallery->column}
      {gallery->column header="true" colspan="3"}
	{gallery->text text="Internal"}
      {/gallery->column}
      {gallery->column header="true" colspan="3"}
	{gallery->text text="External"}
      {/gallery->column}
    {/gallery->row}

    {gallery->row}
      {gallery->column header="true"}
	{gallery->text text="Calls"}
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Total"}
      {/gallery->column}
      {gallery->column header="true"}
	&lt;{gallery->text text="Total"}&gt;
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Max"}
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Average"}
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Total"}
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Max"}
      {/gallery->column}
      {gallery->column header="true"}
	{gallery->text text="Average"}
      {/gallery->column}
    {/gallery->row}

    {foreach from=$main.profile item=profileEntry}
      {gallery->row}
	{gallery->column}
	  {$profileEntry.name}
	{/gallery->column}
	{if (isset($profileEntry.error))} 
	  {gallery->column colspan="7"}
	    {gallery->text text="Error: %s" arg1=$profileEntry.error}
	  {/gallery->column}
	{else}
	  {gallery->column}
	    {$profileEntry.count}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.total}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.internal.total}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.internal.max}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.internal.average}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.external.total}

	    {* Embed more data in the comments *}
	    <!-- External call report for {$profileEntry.name} -->
	    {foreach from=$profileEntry.external.calls item=call}
	      <!-- Call: {$call.elapsed} {$call.marker} -->
	    {/foreach}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.external.max}
	  {/gallery->column}
	  {gallery->column}
	    {$profileEntry.external.average}
	  {/gallery->column}
	{/if}
      {/gallery->row}
    {/foreach}
  {/gallery->table}
{/if}

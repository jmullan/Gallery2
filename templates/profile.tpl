<!-- Profiling output -->
{if !empty($main.profile)}
  {g->table width="100%"}
    {g->row}
      {g->column colspan="8"}
	{g->text text="Profiling"}
      {/g->column}
    {/g->row}

    {g->row}
      {g->column header="true" rowspan="2"}
	{g->text text="Function"}
      {/g->column}
      {g->column header="true" colspan="2"}
	{g->text text="Combined"}
      {/g->column}
      {g->column header="true" colspan="3"}
	{g->text text="Internal"}
      {/g->column}
      {g->column header="true" colspan="3"}
	{g->text text="External"}
      {/g->column}
    {/g->row}

    {g->row}
      {g->column header="true"}
	{g->text text="Calls"}
      {/g->column}
      {g->column header="true"}
	{g->text text="Total"}
      {/g->column}
      {g->column header="true"}
	&lt;{g->text text="Total"}&gt;
      {/g->column}
      {g->column header="true"}
	{g->text text="Max"}
      {/g->column}
      {g->column header="true"}
	{g->text text="Average"}
      {/g->column}
      {g->column header="true"}
	{g->text text="Total"}
      {/g->column}
      {g->column header="true"}
	{g->text text="Max"}
      {/g->column}
      {g->column header="true"}
	{g->text text="Average"}
      {/g->column}
    {/g->row}

    {foreach from=$main.profile item=profileEntry}
      {g->row}
	{g->column}
	  {$profileEntry.name}
	{/g->column}
	{if (isset($profileEntry.error))} 
	  {g->column colspan="7"}
	    {g->text text="Error: %s" arg1=$profileEntry.error}
	  {/g->column}
	{else}
	  {g->column}
	    {$profileEntry.count}
	  {/g->column}
	  {g->column}
	    {$profileEntry.total}
	  {/g->column}
	  {g->column}
	    {$profileEntry.internal.total}
	  {/g->column}
	  {g->column}
	    {$profileEntry.internal.max}
	  {/g->column}
	  {g->column}
	    {$profileEntry.internal.average}
	  {/g->column}
	  {g->column}
	    {$profileEntry.external.total}

	    {* Embed more data in the comments *}
	    <!-- External call report for {$profileEntry.name} -->
	    {foreach from=$profileEntry.external.calls item=call}
	      <!-- Call: {$call.elapsed} {$call.marker} -->
	    {/foreach}
	  {/g->column}
	  {g->column}
	    {$profileEntry.external.max}
	  {/g->column}
	  {g->column}
	    {$profileEntry.external.average}
	  {/g->column}
	{/if}
      {/g->row}
    {/foreach}
  {/g->table}
{/if}

{g->breadcrumb}
  {section name=parent loop=$layout.parents}
    {g->item}
      {g->title}
	{if ! $smarty.section.parent.last}
	  {g->link arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`" arg3="highlightId=`$layout.parents[parent.index_next].id`"}
	    {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
	  {/g->link}
	{else}
	  {g->link arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`" arg3="highlightId=`$layout.item.id`"}
	    {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
	  {/g->link}
	{/if}
      {/g->title}
    {/g->item}
  {/section}
  {g->item}
    {g->title}
      {g->link arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`"}
	{$layout.item.title|default:$layout.item.pathComponent|markup}
      {/g->link}
    {/g->title}
  {/g->item}
{/g->breadcrumb}

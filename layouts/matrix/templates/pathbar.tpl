{g->breadcrumb}
  {section name=parent loop=$layout.parents}
    {g->item}
      {g->title}
	{if ! $smarty.section.parent.last}
	  {g->link url_view='core:ShowItem' url_itemId=$layout.parents[parent].id url_highlightId=$layout.parents[parent.index_next].id}
	    {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent}
	  {/g->link}
	{else}
	  {g->link url_view='core:ShowItem' url_itemId=$layout.parents[parent].id url_highlightId=$layout.item.id}
	    {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent}
	  {/g->link}
	{/if}
      {/g->title}
    {/g->item}
  {/section}
  {g->item}
    {g->title}
      {g->link url_view='core:ShowItem' url_itemId=$layout.item.id}
	{$layout.item.title|default:$layout.item.pathComponent}
      {/g->link}
    {/g->title}
  {/g->item}
{/g->breadcrumb}

{g->breadcrumb}
  {foreach from=$layout.parents item=parent}
    {g->item}
      {g->title}
	{g->link url_view='core:ShowItem' url_itemId=$parent.id}
	  {$parent.title|default:$parent.pathComponent}
	{/g->link}
      {/g->title}
    {/g->item}
  {/foreach}
  {g->item}
    {g->title}
      {g->link url_view='core:ShowItem' url_itemId=$layout.item.id}
	{$layout.item.title|default:$layout.item.pathComponent}
      {/g->link}
    {/g->title}
  {/g->item}
{/g->breadcrumb}

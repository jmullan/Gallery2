{gallery->pathbar}
  {foreach from=$layout.parents item=parent}
    {gallery->item}
      {gallery->link url_view='core:ShowItem' url_itemId=$parent.id}
	{$parent.title|default:$parent.pathComponent}
      {/gallery->link}
    {/gallery->item}
  {/foreach}
  {gallery->item}
    {gallery->link url_view='core:ShowItem' url_itemId=$layout.item.id}
      {$layout.item.title|default:$layout.item.pathComponent}
    {/gallery->link}
  {/gallery->item}
{/gallery->pathbar}

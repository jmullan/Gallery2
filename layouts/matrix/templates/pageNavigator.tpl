{gallery->linksbox}
  {gallery->item}
    {gallery->text text="Page"}
  {/gallery->item}

  {foreach from=jumprange item=page}
    {gallery->item}
      {gallery->link url_view="core:ShowItem" url_itemId=$layout.item.id url_page=$page}
    {/gallery->item}
  {/foreach}
{/gallery->linksbox}

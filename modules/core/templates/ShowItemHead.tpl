  <title>
    {if empty($ShowItem.item.title)}
    {$ShowItem.item.pathComponent}
    {else}
    {$ShowItem.item.title}
    {/if}
  </title>
  {gallery->style}

  <title>
    {if empty($item.title)}
    {$item.pathComponent}
    {else}
    {$item.title}
    {/if}
  </title>
  {if !empty($style)}
  <link rel="stylesheet" type="text/css" href="{$style}">
  {/if}
<title>
  {if isset($item.title)}
    {g->text text="Slideshow for %s" arg1=$item.title}
  {else}
    {g->text text="Slideshow"}
  {/if}
</title>
{g->style}

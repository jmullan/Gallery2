<title>
  {if isset($SlideShow.item.title)}
    {g->text text="Slideshow for %s" arg1=$SlideShow.item.title}
  {else}
    {g->text text="Slideshow"}
  {/if}
</title>
{g->style}

{foreach from=$ImageBlockSystemContent.blocks item=block}
{g->box}
{g->title}
  {g->text text="`$block.title`"}
{/g->title}
{g->element}
  {g->link arg1="view=core:ShowItem" arg2="itemId=`$block.id`"}
    {g->image item=$block.item image=$block.thumb}
  {/g->link}
  {g->listing}{g->item}{g->title}
    {if isset($block.item.title)}{$block.item.title}<br>{/if}
    {g->text text="Date: "}{g->date timestamp=$block.item.creationTimestamp format="%D"}<br>
    {g->text one="Viewed: %d time" many="Viewed: %d times"
     count=$block.viewCount arg1=$block.viewCount}
  {/g->title}{/g->item}{/g->listing}
{/g->element}
{/g->box}
{/foreach}

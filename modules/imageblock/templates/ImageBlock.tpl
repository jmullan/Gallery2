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
    {if isset($ImageBlockSystemContent.show.title)}
      {if isset($block.item.title)}{$block.item.title}<br>{/if}
    {/if}
    {if isset($ImageBlockSystemContent.show.date)}
      {g->text text="Date: "}{g->date timestamp=$block.item.creationTimestamp format="%D"}<br>
    {/if}
    {if isset($ImageBlockSystemContent.show.views)}
      {g->text one="Viewed: %d time" many="Viewed: %d times"
       count=$block.viewCount arg1=$block.viewCount}<br>
    {/if}
    {if isset($ImageBlockSystemContent.show.owner)}
      {g->text text="Owner: %s" arg1=$block.owner.fullName|default:$block.owner.userName}<br>
    {/if}
  {/g->title}{/g->item}{/g->listing}
{/g->element}
{/g->box}
{/foreach}

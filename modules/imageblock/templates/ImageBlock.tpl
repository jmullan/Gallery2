    {foreach from=$ImageBlockSystemContent.blocks item=block}
      <div class="gbMenu" style="width:144px">
	{if !empty($block.title)}
	  <div class="giTitle">
	    {g->text text=$block.title}
	  </div>
	{/if}

	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$block.id`"}">
	  {g->image item=$block.item image=$block.thumb class="giThumbImage" maxSize=140}
	</a><p style="clear:both" />

	{if isset($ImageBlockSystemContent.show.title) && isset($block.item.title)}
	<span class="giDescription">
	  {$block.item.title}
	</span>
	{/if}

	{if isset($ImageBlockSystemContent.show.date) ||
	    isset($ImageBlockSystemContent.show.views) ||
	    isset($ImageBlockSystemContent.show.owner)}
	<div class="giInfo">
	  {if isset($ImageBlockSystemContent.show.date)}
	  <span>
	    {g->text text="Date:"} {g->date timestamp=$block.item.creationTimestamp format="%D"}
	  </span>
	  {/if}

	  {if isset($ImageBlockSystemContent.show.views)}
	  <span>
	    {g->text one="Viewed: %d time" 
	             many="Viewed: %d times"
	             count=$block.viewCount arg1=$block.viewCount}
	  </span>
	  {/if}

	  {if isset($ImageBlockSystemContent.show.owner)}
	  <span>
	    {g->text text="Owner: %s" arg1=$block.owner.fullName|default:$block.owner.userName}
	  </span>
	  {/if}
	</div>
	{/if}
      </div>
    {/foreach}

    {foreach from=$ImageBlockSystemContent.blocks item=block}
      <div class="gbMenu">
	<div class="giTitle">
	  {g->text text=$block.title}
	</div>

	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$block.id`"}">
	  {g->image item=$block.item image=$block.thumb class="giThumbImage"}
	</a>

	{if isset($ImageBlockSystemContent.show.title)}
	{if isset($block.item.title)}
	<b>
	  {$block.item.title}
	</b>
	{/if}
	{/if}

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
      </div>
    {/foreach}

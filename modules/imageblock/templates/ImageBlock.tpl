{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
    {foreach from=$ImageBlockSystemContent.blocks item=block}
      <div class="gbMenu" style="width:144px">
	{if !empty($block.title)}
	  <h3 class="giTitle">
	    {g->text text=$block.title}
	  </h3>
	{/if}

	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$block.id`"}">
	  {g->image item=$block.item image=$block.thumb class="giThumbImage" maxSize=140}
	</a>

	{if isset($ImageBlockSystemContent.show.title) && isset($block.item.title)}
	<h4 class="giDescription">
	  {$block.item.title|markup}
	</h4>
	{/if}

	{if isset($ImageBlockSystemContent.show.date) ||
	    isset($ImageBlockSystemContent.show.views) ||
	    isset($ImageBlockSystemContent.show.owner)}
	<ul class="giInfo">
	  {if isset($ImageBlockSystemContent.show.date)}
	  <li>
	    {g->text text="Date:"} {g->date timestamp=$block.item.creationTimestamp format="%D"}
	  </li>
	  {/if}

	  {if isset($ImageBlockSystemContent.show.views)}
	  <li>
	    {g->text text="Views: %d" arg1=$block.viewCount}
	  </li>
	  {/if}

	  {if isset($ImageBlockSystemContent.show.owner)}
	  <li>
	    {g->text text="Owner: %s" arg1=$block.owner.fullName|default:$block.owner.userName}
	  </li>
	  {/if}
	</ul>
	{/if}
      </div>
    {/foreach}

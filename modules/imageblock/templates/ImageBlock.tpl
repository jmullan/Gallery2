{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{foreach from=$ImageBlockSystemContent.blocks item=block}
<div class="gbBlock">
  {if !empty($block.title)}
    <h3> {g->text text=$block.title} </h3>
  {/if}

  {capture name="link"}
  <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$block.id`"}" {strip}
    {if isset($ImageBlockSystemContent.linkTarget)}
      target="{$ImageBlockSystemContent.linkTarget}"
    {/if}{/strip}>
  {/capture}
  {if $block.item.canContainChildren}
    {assign var=frameType value="albumFrame"}
  {else}
    {assign var=frameType value="itemFrame"}
  {/if}
  {if isset($ImageBlockSystemContent.$frameType)}
    {g->block type="imageframe" frame=$ImageBlockSystemContent.$frameType}
      {$smarty.capture.link}
      {g->image item=$block.item image=$block.thumb id="%ID%" class="%CLASS%"
		maxSize=$ImageBlockSystemContent.maxSize|default:null}
      </a>
    {/g->block}
  {else}
    {$smarty.capture.link}
      {g->image item=$block.item image=$block.thumb class="giThumbnail"
		maxSize=$ImageBlockSystemContent.maxSize|default:null}
    </a>
  {/if}

  {if isset($ImageBlockSystemContent.show.title) && isset($block.item.title)}
    <h4 class="giDescription">
      {$block.item.title|markup}
    </h4>
  {/if}

  {if isset($ImageBlockSystemContent.show.date) ||
      isset($ImageBlockSystemContent.show.views) ||
      isset($ImageBlockSystemContent.show.owner)}
    <p class="giInfo">
      {if isset($ImageBlockSystemContent.show.date)}
	{g->text text="Date:"} {g->date timestamp=$block.item.originationTimestamp}
	<br/>
      {/if}

      {if isset($ImageBlockSystemContent.show.views)}
	{g->text text="Views: %d" arg1=$block.viewCount}
	<br/>
      {/if}

      {if isset($ImageBlockSystemContent.show.owner)}
	{g->text text="Owner: %s" arg1=$block.owner.fullName|default:$block.owner.userName}
	<br/>
      {/if}
    </p>
  {/if}
 </div>
{/foreach}

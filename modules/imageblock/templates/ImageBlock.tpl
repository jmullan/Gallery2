{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{foreach from=$ImageBlockData.blocks item=block}
<div class="one-image">
  {if !empty($block.title)}
    <h3> {g->text text=$block.title} </h3>
  {/if}

  {capture name="link"}
  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$block.id`"}" {strip}
    {if isset($ImageBlockData.linkTarget)}
      target="{$ImageBlockData.linkTarget}"
    {/if}{/strip}>
  {/capture}
  {if $block.item.canContainChildren}
    {assign var=frameType value="albumFrame"}
  {else}
    {assign var=frameType value="itemFrame"}
  {/if}
  {if array_key_exists('maxSize', $ImageBlockData)}
    {assign var=maxSize value=$ImageBlockData.maxSize}
  {elseif isset($ImageBlockData.$frameType)
	  && $ImageBlockData.$frameType != 'none'}
    {assign var=maxSize value=120}
  {else}
    {assign var=maxSize value=150}
  {/if}
  {if isset($ImageBlockData.$frameType)}
    {g->container type="imageframe.ImageFrame"
		  frame=$ImageBlockData.$frameType}
      {$smarty.capture.link}
      {g->image item=$block.item image=$block.thumb id="%ID%" class="%CLASS%" maxSize=$maxSize}
      </a>
    {/g->container}
  {else}
    {$smarty.capture.link}
      {g->image item=$block.item image=$block.thumb class="giThumbnail" maxSize=$maxSize}
    </a>
  {/if}

  {if isset($ImageBlockData.show.title) && isset($block.item.title)}
    <h4 class="giDescription">
      {$block.item.title|markup}
    </h4>
  {/if}

  {if isset($ImageBlockData.show.date) ||
      isset($ImageBlockData.show.views) ||
      isset($ImageBlockData.show.owner)}
    <p class="giInfo">
      {if isset($ImageBlockData.show.date)}
	{g->text text="Date:"} {g->date timestamp=$block.item.originationTimestamp}
	<br/>
      {/if}

      {if isset($ImageBlockData.show.views)}
	{g->text text="Views: %d" arg1=$block.viewCount}
	<br/>
      {/if}

      {if isset($ImageBlockData.show.owner)}
	{g->text text="Owner: %s" arg1=$block.owner.fullName|default:$block.owner.userName}
	<br/>
      {/if}
    </p>
  {/if}
 </div>
{/foreach}


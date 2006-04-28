{*
 * $Revision: 1.2 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{g->callback type="rss.FeedList"}
<div class="{$class}">
  <h3> {g->text text="RSS Feeds"} </h3>
  {if empty($block.rss.feeds)}
    <p> {g->text text="No feeds have yet been defined"} </p>
  {else}
    {foreach from=$block.rss.feeds item=feed}
      <a href="{g->url arg1="view=rss.Render" arg2="name=`$feed`"}">
        {$feed}</a><br/>
    {/foreach}
  {/if}
  
  {if $block.rss.showMore}
    <p><a href="{g->url arg1="view=rss.FeedList"}">{g->text text="List all RSS Feeds"}</a></p>
  {/if}
</div>


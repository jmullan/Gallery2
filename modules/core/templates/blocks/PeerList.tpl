{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if empty($peers) && !empty($theme.peers)}{assign var="peers" value=$theme.peers}{/if}
{if empty($item) && !empty($theme.item)}{assign var="item" value=$theme.item}{/if}
{if empty($parent) && !empty($theme.parent)}{assign var="parent" value=$theme.parent}{/if}

{if !empty($peers)}
<div class="{$class}">
  <h3 class="parent"> {$parent.title|default:$parent.pathComponent|markup} </h3>

  {assign var="lastIndex" value=0}
  {foreach from=$peers item=peer}
  {assign var="title" value=$peer.title|default:$peer.pathComponent|markup}
  {if ($peer.peerIndex - $lastIndex > 1)}
  <span class="neck">...</span>
  {/if}

  {if ($peer.id == $item.id)}
  <span class="current">
    {g->text text="%d. %s" arg1=$peer.peerIndex arg2=$title|markup:strip|entitytruncate:14}
  </span>
  {else}
  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$peer.id`"}">
    {g->text text="%d. %s" arg1=$peer.peerIndex arg2=$title|markup:strip|entitytruncate:14}
  </a>
  {/if}
  {assign var="lastIndex" value=$peer.peerIndex}
  {/foreach}
</div>
{/if}

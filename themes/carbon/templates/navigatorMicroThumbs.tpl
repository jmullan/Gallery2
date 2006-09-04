{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{g->callback type="core.LoadPeers" item=$item|default:$theme.item
	     windowSize=$windowSize|default:$theme.params.maxMicroThumbs
	     addEnds=false loadThumbnails=true}

{assign var="data" value=$block.core.LoadPeers}

{if !empty($data.peers)}
<div>
  {assign var="lastIndex" value=0}
  {assign var="columnIndex" value=0}
  <table cellpadding="0" cellspacing="2">
    <tr>
    {foreach from=$data.peers item=peer}
      {assign var="title" value=$peer.title|default:$peer.pathComponent}
      {if ($columnIndex == 4)}
	</tr>
	<tr>
	{assign var="columnIndex" value=0}
      {/if}

      {if ($peer.peerIndex == $data.thisPeerIndex)}
	<td align="center" width="44" height="40">
	  {g->image item=$peer image=$peer.thumbnail maxSize=40 title="$title"}
	</td>
      {else}
	<td align="center" width="44" height="40">
	  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$peer.id`"}">
	    {g->image item=$peer image=$peer.thumbnail maxSize=40 title="$title"}
	  </a>
	</td>
      {/if}

      {assign var="lastIndex" value=$peer.peerIndex}
      {assign var="columnIndex" value=$columnIndex+1}
    {/foreach}
    </tr>
  </table>
</div>
{/if}

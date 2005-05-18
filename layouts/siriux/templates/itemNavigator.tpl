{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if (isset($layout.currentPage) && $layout.totalPages > 1) ||
    (!isset($layout.currentPage) && isset($layout.peerCount) && $layout.peerCount > 1)}
  <div class="prevnext">
    <span class="prev">
      {if isset($layout.navigator.back)}
	<a href="{g->url params=$layout.navigator.back.urlParams}">
	  &laquo; {g->text text="Previous"}
	</a>
      {else}
	<span class="giInfo"> &laquo; {g->text text="Previous"} </span>
      {/if}
      &nbsp;
    </span>

    <span class="current">{strip}
      &nbsp;
      {if isset($layout.currentPage)}
	{g->text text="Page %d of %d" arg1=$layout.currentPage arg2=$layout.totalPages}
      {else}
	{if isset($layout.peerCount)}
	  {g->text text="Picture %d of %d" arg1=$layout.peers[$layout.peerItemIndex].peerIndex
					   arg2=$layout.peerCount}
	{/if}
      {/if}
      &nbsp;
    {/strip}</span>

    <span class="next">
      &nbsp;
      {if isset($layout.navigator.next)}
	<a href="{g->url params=$layout.navigator.next.urlParams}">
	  {g->text text="Next"} &raquo;
	</a>
      {else}
	<span class="giInfo"> {g->text text="Next"} &raquo; </span>
      {/if}
    </span>
  </div>
{/if}

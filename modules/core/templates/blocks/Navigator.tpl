{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="{$class}">
  <div class="next-and-last{if !isset($navigator.first) && !isset($navigator.back)} no-previous{/if}">
    {if isset($navigator.next)}
    <a href="{g->url params=$navigator.next.urlParams}" class="next">
      {g->text text="next"}
      {if isset($navigator.next.item.thumbnail)}
      {g->image item=$navigator.next.item image=$navigator.next.item.thumbnail
		maxSize=40 class="next"}
      {/if}
    </a>
    {/if}

    {if isset($navigator.last)}
    <a href="{g->url params=$navigator.last.urlParams}" class="last">
      {g->text text="last"}
      {if isset($navigator.last.item.thumbnail)}
      {g->image item=$navigator.last.item image=$navigator.last.item.thumbnail
		maxSize=40 class="last"}
      {/if}
    </a>
    {/if}
  </div>

  {if (isset($currentPage) && isset($totalPages)) || (isset($currentItem) && isset($totalItems))}
  <span class="current">
    {if isset($currentPage)}
      {g->text text="Page %d of %d" arg1=$currentPage arg2=$totalPages}
    {else}
      {if isset($currentItem)}
        {g->text text="%d of %d" arg1=$currentItem arg2=$totalItems}
      {/if}
    {/if}
  </span>
  {/if}

  <div class="first-and-previous">
    {if isset($navigator.first)}
    <a href="{g->url params=$navigator.first.urlParams}" class="first">
      {if isset($navigator.first.item.thumbnail)}
      {g->image item=$navigator.first.item image=$navigator.first.item.thumbnail maxSize=40}
      {/if}
      {g->text text="first"}
    </a>
    {/if}

    {if isset($navigator.back)}
    <a href="{g->url params=$navigator.back.urlParams}" class="previous">
      {if isset($navigator.back.item.thumbnail)}
      {g->image item=$navigator.back.item image=$navigator.back.item.thumbnail maxSize=40 border=0}
      {/if}
      {g->text text="previous"}
    </a>
    {/if}
  </div>
</div>

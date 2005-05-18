{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($layout.navigator)}
<div class="gbBlock gcBackground2">

  {if isset($layout.navigator.next) || isset($layout.navigator.last)}
  <div style="{if isset($layout.navigator.first) || isset($layout.navigator.back)}float: right{else}text-align: right{/if}">
    {if isset($layout.navigator.next)}
    <a href="{g->url params=$layout.navigator.next.urlParams}">
      {g->text text="next &gt;"}
      {if isset($layout.navigator.next.item.thumbnail)}
	{g->image item=$layout.navigator.next.item image=$layout.navigator.next.item.thumbnail
		  maxSize=40 class="giThumbnail"}
      {/if}
    </a>
    {/if}
    &nbsp;
    {if isset($layout.navigator.last)}
    <a href="{g->url params=$layout.navigator.last.urlParams}">
      {g->text text="last &gt;&gt;"}
      {if isset($layout.navigator.last.item.thumbnail)}
	{g->image item=$layout.navigator.last.item image=$layout.navigator.last.item.thumbnail
		  maxSize=40 class="giThumbnail"}
      {/if}
    </a>
    {/if}
  </div>
  {/if}

  {if isset($layout.navigator.first) || isset($layout.navigator.back)}
  <div>
    {if isset($layout.navigator.first)}
    <a href="{g->url params=$layout.navigator.first.urlParams}">
      {if isset($layout.navigator.first.item.thumbnail)}
	{g->image item=$layout.navigator.first.item image=$layout.navigator.first.item.thumbnail
		  maxSize=40 class="giThumbnail"}
      {/if}
      {g->text text="&lt;&lt; first"}
    </a>
    {/if}
    &nbsp;
    {if isset($layout.navigator.back)}
    <a href="{g->url params=$layout.navigator.back.urlParams}">
      {if isset($layout.navigator.back.item.thumbnail)}
	{g->image item=$layout.navigator.back.item image=$layout.navigator.back.item.thumbnail
		  maxSize=40 border=0 class="giThumbnail"}
      {/if}
      {g->text text="&lt; previous"}
    </a>
    {/if}
  </div>
  {/if}

</div>
{/if}

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{strip}
{if isset($layout.navigator.first) || isset($layout.navigator.back)}
<ul class="giHorizontalLinksLeft">
  {if isset($layout.navigator.first)}
  <li>
    <a href="{g->url params=$layout.navigator.first.urlParams}">
      {if isset($layout.navigator.first.item.thumbnail)}
      {g->image item=$layout.navigator.first.item image=$layout.navigator.first.item.thumbnail maxSize=40 class="giThumbImage"}
      {g->text text="&lt;&lt; first"}
      {else}
      {g->text text="&lt;&lt; first"}
      {/if}
    </a>
  </li>
  {/if}
  
  {if isset($layout.navigator.back)}
  <li>
    <a href="{g->url params=$layout.navigator.back.urlParams}">
      {if isset($layout.navigator.back.item.thumbnail)}
      {g->image item=$layout.navigator.back.item image=$layout.navigator.back.item.thumbnail maxSize=40 border=0 class="giThumbImage"}
      {g->text text="&lt; previous"}
      {else}
      {g->text text="&lt; previous"}
      {/if}
    </a>
  </li>
  {/if}
</ul>
{/if}

{if isset($layout.navigator.next) || isset($layout.navigator.last)}
<ul class="giHorizontalLinks">
  {if isset($layout.navigator.next)}
  <li>
    <a href="{g->url params=$layout.navigator.next.urlParams}">
      {g->text text="next &gt;"}
      {if isset($layout.navigator.next.item.thumbnail)}
      {g->image item=$layout.navigator.next.item image=$layout.navigator.next.item.thumbnail maxSize=40 class="giThumbImage"}
      {/if}
    </a>
  </li>
  {/if}

  {if isset($layout.navigator.last)}
  <li>
    <a href="{g->url params=$layout.navigator.last.urlParams}">
      {g->text text="last &gt;&gt;"}
      {if isset($layout.navigator.last.item.thumbnail)}
      {g->image item=$layout.navigator.last.item image=$layout.navigator.last.item.thumbnail maxSize=40 class="giThumbImage"}
      {/if}
    </a>
  </li>
  {/if}
</ul>
{/if}
{/strip}

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if isset($layout.navigator.first) || isset($layout.navigator.back)}
<ul class="giHorizontalLinksLeft">
  {if isset($layout.navigator.first)}
  <li><a href="{g->url params=$layout.navigator.first}">{g->text text="&lt;&lt; first"}</a></li>
  {/if}
  
  {if isset($layout.navigator.back)}
  <li>
    <a href="{g->url params=$layout.navigator.back}">{g->text text="&lt; previous"}</a></li>
  {/if}
</ul>
{/if}

{if isset($layout.navigator.next) || isset($layout.navigator.last)}
<ul class="giHorizontalLinks">
  {if isset($layout.navigator.next)}
  <li><a href="{g->url params=$layout.navigator.next}">{g->text text="next &gt;"}</a></li>
  {/if}

  {if isset($layout.navigator.last)}
  <li><a href="{g->url params=$layout.navigator.last}">{g->text text="last &gt;&gt;"}</a></li>
  {/if}
</ul>
{/if}


{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if ($layout.itemLinks)}
  <hr style="margin-top: 30px"/>

  {* Item Links *}
  <ul>
    {foreach from=$layout.itemLinks item=item}
      <li>
        <a href="{g->url params=$item.params}"> {$item.text} </a>
      </li>
    {/foreach}
  </ul>
{/if}

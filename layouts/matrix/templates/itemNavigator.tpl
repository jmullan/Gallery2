{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to itemNavigator.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="giHorizontalLinks">
  {if isset($layout.navigator.first)}
  <span>
    <a href="{g->url params=$layout.navigator.first}">
      {g->text text="first"}
    </a>
  </span>
  {/if}
  
  {if isset($layout.navigator.back)}
  <span>
    <a href="{g->url params=$layout.navigator.back}">
      {g->text text="back"}
    </a>
  </span>
  {/if}

  {if isset($layout.navigator.next)}
  <span>
    <a href="{g->url params=$layout.navigator.next}">
      {g->text text="next"}
    </a>
  </span>
  {/if}

  {if isset($layout.navigator.last)}
  <span>
    <a href="{g->url params=$layout.navigator.last}">
      {g->text text="last"}
    </a>
  </span>
  {/if}
</div>

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{* This XHTML snippet is included from other pages that display G2
 * debug output.
 *
 * You shouldn't have to modify this page unless you're a G2 developer.
 *}
<div id="gpDebug">
  <div class="giTitle">
      {g->text text="Gallery Debug Output"} 
  </div>

  {if isset($main.debug)}
  <span>
      <pre>
      {$main.debug}
      </pre>
  </span>
  {/if}

  {if isset($main.profile)}
  <span>
    {$main.profile}
  </span>
  {/if}

  {if isset($main.debug) && isset($fetchDebug)}
  {debug output=""}
  {/if}
</div>

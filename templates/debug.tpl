{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to debug.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gpDebug">
  <div class="giTitle">
      {g->text text="Gallery Debug Output"} 
  </div>

  <span>
      <pre>
      {$main.debug}
      </pre>
  </span>

  {debug output=""}
</div>

{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to DebugStatusFormatter.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div>
  <span>
    <b>
      {if isset($message)}
      {g->text text="Error (%s): %s" arg1=$codes arg2=$message}
      {else}
      {g->text text="Error (%s)" arg1=$codes}
      {/if}
    </b>
  </span>
  <ul>
    {foreach from=$trace item=traceEntry}
    <li> 
      <b>
	{g->text text="in file"}
      </b>
      <a href="{g->url arg1="view=debug:FileViewer" arg2="file=`$traceEntry.file`"}">
	{$traceEntry.file}
      </a>
      <b>
	{g->text text="at line"}
      </b>
      <a href="{g->url arg1="view=debug:FileViewer" arg2="file=`$traceEntry.file`" arg3="line=`$traceEntry.line`"}#{$traceEntry.line}">
	{$traceEntry.line}
      </a>

      {if ! empty($traceEntry.class) && ! empty($traceEntry.function)}
      {g->text text="(%s::%s)" arg1=$traceEntry.class arg2=$traceEntry.function}
      {else}
      {if ! empty($traceEntry.class)}
      {g->text text="(%s)" arg1=$traceEntry.class}
      {/if}
      {/if}
    </li>
  {/foreach}
  </ul>
</div>
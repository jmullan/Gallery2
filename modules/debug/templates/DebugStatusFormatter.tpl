    {g->text text="Error (%s)" arg1=$codes}
    <ul>
      {foreach from=$trace item=traceEntry}
      <li> 
	<b>{g->text text="in file"}</b>
	<a href="{g->url view="debug:FileViewer" file=$traceEntry.file}">{$traceEntry.file}</a>
	<b>{g->text text="at line"}</b>
	<a href="{g->url view="debug:FileViewer" file=$traceEntry.file line=$traceEntry.line}#{$traceEntry.line}">{$traceEntry.line}</a>
	{if ! empty($traceEntry.class) && ! empty($traceEntry.function)}
	{g->text text="(%s::%s)" arg1=$traceEntry.class arg2=$traceEntry.function}
	{else}
	{if ! empty($traceEntry.class)}
	{g->text text="(%s)" arg1=$traceEntry.class}
	{/if}
	{/if}
	{/foreach}
      </li>
    </ul>
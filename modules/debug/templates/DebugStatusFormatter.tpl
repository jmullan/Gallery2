    {gallery->text text="Error (%s)" arg1=$codes}
    <UL>
      {foreach from=$trace item=traceEntry}
      <LI> 
	<B>{gallery->text text="in file"}</B>
	<a href="{gallery->url view="debug:FileViewer" file=$traceEntry.file}">{$traceEntry.file}</a>
	<B>{gallery->text text="at line"}</B>
	<a href="{gallery->url view="debug:FileViewer" file=$traceEntry.file line=$traceEntry.line}#{$traceEntry.line}">{$traceEntry.line}</a>
	{if ! empty($traceEntry.class) && ! empty($traceEntry.function)}
	{gallery->text text="(%s::%s)" arg1=$traceEntry.class arg2=$traceEntry.function}
	{else}
	{if ! empty($traceEntry.class)}
	{gallery->text text="(%s)" arg1=$traceEntry.class}
	{/if}
	{/if}
	{/foreach}
    </UL>
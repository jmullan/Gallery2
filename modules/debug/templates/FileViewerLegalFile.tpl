{g->main}
  {g->pagebox}
    {g->banner}
      {g->title}
	{g->text text="Source code for file: %s" arg1=$FileViewer.fileName} 
      {/g->title}
    {/g->banner}

    {g->box}
      {counter print=false start=1 assign=lineNumber}
      {g->table}
	{foreach from=$FileViewer.lines item=line}
	  {g->row}
	    {g->column}
	      {if ($lineNumber == $FileViewer.currentLine)}
		--->
	      {else}
		&nbsp;
	      {/if}
	    {/g->column}
	    {g->column}
	      <a name="{$lineNumber}">
	      {$lineNumber}
	      </a>
	    {/g->column}

	    {g->column}
	      {if ($lineNumber == $FileViewer.currentLine)}
		<b>
	      {/if}
	      {$line|escape|replace:" ":"&nbsp;"|replace:"\t":"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"}
	      {if ($lineNumber == $FileViewer.currentLine)}
		</b>
	      {/if}
	    {/g->column}
	  {/g->row}
	  {counter}
	{/foreach}
      {/g->table}
    {/g->box}
  {/g->pagebox}
{/g->main}

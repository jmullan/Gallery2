{gallery->main}
  {gallery->bannerbox}
    {gallery->title}
      {gallery->text text="Source code for file: %s" arg1=$FileViewer.fileName} 
    {/gallery->title}
  {/gallery->bannerbox}

  {gallery->component}
    {gallery->detailedbox}
      {gallery->body}
	{counter print=false start=1 assign=lineNumber}
	{gallery->table}
	  {foreach from=$FileViewer.lines item=line}
	    {gallery->row}
	      {gallery->column}
		{if ($lineNumber == $FileViewer.currentLine)}
		  --->
		{else}
		  &nbsp;
		{/if}
	      {/gallery->column}
	      {gallery->column}
		<a name="{$lineNumber}">
		{$lineNumber}
		</a>
	      {/gallery->column}

	      {gallery->column}
		{if ($lineNumber == $FileViewer.currentLine)}
		  <b>
		{/if}
		{$line|escape|replace:" ":"&nbsp;"|replace:"\t":"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"}
		{if ($lineNumber == $FileViewer.currentLine)}
		  </b>
		{/if}
	      {/gallery->column}
	    {/gallery->row}
	    {counter}
	  {/foreach}
	{/gallery->table}
      {/gallery->body}
    {/gallery->detailedbox}
  {/gallery->component}
{/gallery->main}

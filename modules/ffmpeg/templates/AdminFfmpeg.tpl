{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="FFMPEG Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Settings saved successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text text="FFMPEG is a graphics toolkit that can be used to process video files that you upload to Gallery.  You must install the FFMPEG binary on your machine, then enter the path to it in the text box below.  If you're on a Unix machine, don't forget to make the binary executable (<i>chmod 755 ffmpeg</i> in the right directory should do it)"}
    {/g->description}

    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Path to FFMPEG:"}
	{/g->column}
	
	{g->column}
	  {g->input type="text" size="40" name="form.path"}{$form.path}{/g->input}
	{/g->column}
      {/g->row}
      
      {if isset($form.error.path.missing)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="You must enter a path to your FFMPEG binary"}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}
      
      {if isset($form.error.path.testError)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="The path you entered doesn't contain a valid FFMPEG binary. Use the 'test' button to check where the error is."}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}
      
      {if isset($form.error.path.badPath)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="The path you entered isn't a valid path to a <b>ffmpeg</b> binary."}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}

      {if isset($form.error.path.notExecutable)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="The <b>ffmpeg</b> binary is not executable.  To fix it, run <b>chmod 755 %s</b> in a shell." arg1=$form.path}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}

    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save Settings"}{/g->input}
      {g->input type="submit" name="form.action.test"}{g->text text="Test Settings"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}

  {if !empty($AdminFfmpeg.tests)}
    {g->box style="admin"}
      {g->title}
	{g->text text="FFMPEG binary test results"}
      {/g->title}
      
      {g->table style="admin_listing"}
	{g->row}
	  {g->column header="true"}
	    {g->text text="Binary Name"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Pass/Fail"}
	  {/g->column}
	{/g->row}

	{foreach from=$AdminFfmpeg.tests item=test}
	  {g->row}
	    {g->column}
	      {$test.name}
	    {/g->column}
	    {g->column}
	      {if ($test.success)}
		{g->success}
		  {g->text text="Passed"}
		{/g->success}
	      {else}
		{g->error}
		  {g->text text="Failed"}
		{/g->error}

		{if ! empty($test.message)}
		  {g->text text="Error messages:"}
		  <br />
		  {foreach from=$test.message item=line}
		    <pre>{$line}</pre>
		  {/foreach}
		{/if}
	      {/if}
	    {/g->column}
	  {/g->row}
	{/foreach}
      {/g->table}
    {/g->box}

    {if $AdminFfmpeg.mimeTypes}
      {g->box style="admin"}
	{g->title}
	  {g->text text="Supported MIME Types"}
	{/g->title}

	{g->description}
	  {g->text text="The FFMPEG module can support files with the following MIME types"}
	{/g->description}
	
	{g->element}
	  {foreach from=$AdminFfmpeg.mimeTypes item=mimeType}
	    {$mimeType} 
	  {/foreach}
	{/g->element}
      {/g->box}
    {/if}
  {/if}
{/g->pagebox}

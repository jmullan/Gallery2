{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="NetPBM Settings"}
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
      {g->text text="NetPBM is a graphics toolkit that can be used to process images that you upload to Gallery.  You must install the NetPBM binaries on your machine, then enter the path to them in the text box below.  If you're on a Unix machine, don't forget to make the binaries executable (<i>chmod 755 *</i> in the NetPBM directory should do it)"}
    {/g->description}

    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Path to NetPBM:"}
	{/g->column}
	
	{g->column}
	  {g->input type="text" size="40" name="form.path"}{$form.path}{/g->input}
	{/g->column}
      {/g->row}
      
      {if isset($form.error.path.missing)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="You must enter a path to your NetPBM binaries"}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}
      
      {if isset($form.error.path.testError)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="The path you entered doesn't contain valid NetPBM binaries. Use the 'test' button to check where the error is."}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}
      
      {if isset($form.error.path.badPath)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="The path you entered isn't a valid path."}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}

      {g->row}
	{g->column}
	  {g->text text="PNM to JPEG converter"}
	{/g->column}

	{g->column}
	  {g->select name="form.pnmtojpeg"}
	    {html_options values=$AdminNetPbm.pnmToJpegList selected=$form.pnmtojpeg output=$AdminNetPbm.pnmToJpegList}
	  {/g->select}
	{/g->column}
      {/g->row}

      {g->row}
	{g->column}
	  {g->text text="JPEG Quality"}
	{/g->column}

	{g->column}
	  {g->select name="form.jpegQuality"}
	    {html_options values=$AdminNetPbm.jpegQualityList selected=$form.jpegQuality output=$AdminNetPbm.jpegQualityList}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save Settings"}{/g->input}
      {g->input type="submit" name="form.action.test"}{g->text text="Test Settings"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}

  {if !empty($AdminNetPbm.tests)}
    {g->box style="admin"}
      {g->title}
	{g->text text="NetPBM binary test results"}
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

	{foreach from=$AdminNetPbm.tests item=test}
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

    {if $AdminNetPbm.mimeTypes}
      {g->box style="admin"}
	{g->title}
	  {g->text text="Supported MIME Types"}
	{/g->title}

	{g->description}
	  {g->text text="The ImageMagick module can support files with the following MIME types"}
	{/g->description}
	
	{g->element}
	  {foreach from=$AdminNetPbm.mimeTypes item=mimeType}
	    {$mimeType} 
	  {/foreach}
	{/g->element}
      {/g->box}
    {/if}
  {/if}
{/g->pagebox}

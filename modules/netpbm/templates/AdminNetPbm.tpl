{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="NetPBM Settings"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Settings saved successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="NetPBM is a graphics toolkit that can be used to process images that you upload to Gallery.  You must install the NetPBM binaries on your machine, then enter the path to them in the text box below.  If you're on a Unix machine, don't forget to make the binaries executable (<i>chmod 755 *</i> in the NetPBM directory should do it)"}
  {/gallery->description}

  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Path to NetPBM:"}
	{/gallery->title}
	
	{gallery->body}
	  {gallery->input type="text" size="40" name="form.path"}{$form.path}{/gallery->input}
	  
	  {if isset($form.error.path.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a path to your NetPBM binaries"}
	    {/gallery->error}
	  {/if}

	  {if isset($form.error.path.testError)}
	    {gallery->error}
	      {gallery->text text="The path you entered doesn't contain valid NetPBM binaries. Use the 'test' button to check where the error is."}
	    {/gallery->error}
	  {/if}

	  {if isset($form.error.path.badPath)}
	    {gallery->error}
	      {gallery->text text="The path you entered isn't a valid path."}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget1}

      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="PNM to JPEG converter"}
	{/gallery->title}

	{gallery->body}
	  {gallery->select name="form.pnmtojpeg"}
	    {html_options values=$AdminNetPbm.pnmToJpegList selected=$form.pnmtojpeg output=$AdminNetPbm.pnmToJpegList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}

      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="JPEG Quality"}
	{/gallery->title}

	{gallery->body}
	  {gallery->select name="form.jpegQuality"}
	    {html_options values=$AdminNetPbm.jpegQualityList selected=$form.jpegQuality output=$AdminNetPbm.jpegQualityList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save Settings"}{/gallery->input}
    {gallery->input type="submit" name="form.action.test"}{gallery->text text="Test Settings"}{/gallery->input}
    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

{if !empty($AdminNetPbm.tests)}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="NetPBM binary test results"}
    {/gallery->title}
    
    {gallery->body}
      {gallery->table}
	{gallery->row}
	  {gallery->column header="true"}
	    {gallery->text text="Binary Name"}
	  {/gallery->column}
	  {gallery->column header="true"}
	    {gallery->text text="Pass/Fail"}
	  {/gallery->column}
	{/gallery->row}

	{foreach from=$AdminNetPbm.tests item=test}
	  {gallery->row}
	    {gallery->column}
	      {$test.name}
	    {/gallery->column}
	    {gallery->column}
	      {if ($test.success)}
		{gallery->text text="Passed"}
	      {else}
		{gallery->text text="Failed"}
	      {/if}
	    {/gallery->column}
	  {/gallery->row}

	  {if ! $test.success && ! empty($test.message)}
	    {gallery->row}
	      {gallery->column}
		{gallery->text text="Error messages:"}
		<br />
		{foreach from=$test.message item=line}
		  <pre>{$line}</pre>
		{/foreach}
	      {/gallery->column}
	    {/gallery->row}
	  {/if}
	{/foreach}
      {/gallery->table}
    {/gallery->body}
  {/gallery->detailedbox}

  {if $AdminNetPbm.mimeTypes}
    {gallery->detailedbox}
      {gallery->title}
	{gallery->text text="Supported MIME Types"}
      {/gallery->title}

      {gallery->description}
	{gallery->text text="The ImageMagick module can support files with the following MIME types"}
      {/gallery->description}
      
      {gallery->body}
	{foreach from=$AdminNetPbm.mimeTypes item=mimeType}
	  {$mimeType} 
	{/foreach}
      {/gallery->body}
    {/gallery->detailedbox}
  {/if}
{/if}

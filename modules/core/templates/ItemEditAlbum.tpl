{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Album Settings"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Settings saved successfully."}
	{/if}
	{if isset($status.createdAlbum)}
	  {gallery->text text="Album created successfully."}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Sort order"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text=" This sets the default sort order for the album.  This applies to all new items."}
	{/gallery->description}
	{gallery->body}
	  {gallery->select name="form.orderBy"}
	    {html_options options=$ItemEditAlbum.orderByList selected=$form.orderBy}
	  {/gallery->select}
	  {gallery->select name="form.orderDirection"}
	    {html_options options=$ItemEditAlbum.orderDirectionList selected=$form.orderDirection}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Layout"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="Choose a layout for this album. (The way the gallery is arranged on the page.)"}
	{/gallery->description}
	{gallery->body}
	  {gallery->select name="form.layout"}
	    {html_options values=$ItemEditAlbum.layoutList selected=$form.layout output=$ItemEditAlbum.layoutList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Theme"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="Choose a theme for this album.  (The look and feel of this album)"}
	{/gallery->description}
	{gallery->body}
	  {gallery->select name="form.theme"}
	    {html_options values=$ItemEditAlbum.themeList selected=$form.theme output=$ItemEditAlbum.themeList}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Thumbnails"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text=" Every item requires a thumbnail. Set the default value in pixels here."}
	{/gallery->description}
	{gallery->body}
	  {gallery->input type=text size=6 name="form.thumbnail.size"}{$form.thumbnail.size}{/gallery->input}

	  {if !empty($form.error.thumbnail.size.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a thumbnail size"}
	    {/gallery->error}
          {/if}

	  {if !empty($form.error.thumbnail.size.invalid)}
	    {gallery->error}
	      {gallery->text text="You must enter a number (greater than zero)"}
	    {/gallery->error}
          {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Resized Images"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="Each item in your album can have multiple sizes. Define the default sizes here."}
	{/gallery->description}
	{gallery->body}
	  {gallery->table}
	    {gallery->row}
	      {gallery->column header="true"}
		{gallery->text text="Active"}
	      {/gallery->column}
	      {gallery->column header="true"}
		{gallery->text text="Target Size (pixels)"}
	      {/gallery->column}
	    {/gallery->row}
	    {counter start=0 assign=index}
	    {foreach from=$form.resizes item=resize}
	      {gallery->row}
		{gallery->column}
		  {gallery->input type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/gallery->input}
		{/gallery->column}
		{gallery->column}
		  {gallery->input type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/gallery->input}
		{/gallery->column}
	      {/gallery->row}

	      {if !empty($form.error.resizes.$index.size.missing)}
		{gallery->row}
		  {gallery->column colspan="2"}
		    {gallery->error}
		      {gallery->text text="You must enter a valid size"}
		    {/gallery->error}
		  {/gallery->column}
		{/gallery->row}
              {/if}
	      
	      {if !empty($form.error.resizes.$index.size.invalid)}
		{gallery->row}
		  {gallery->column colspan="2"}
		    {gallery->error}
		      {gallery->text text="You must enter a number (greater than zero)"}
		    {/gallery->error}
		  {/gallery->column}
		{/gallery->row}
              {/if}
              {counter}
	    {/foreach}
	  {/gallery->table}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Recreate thumbnails and resizes"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="The thumbnail and resized image settings are for all new items. To apply these settings to all the items in your album, check the appropriate box."}
	{/gallery->description}
	{gallery->body}
	  {gallery->input type="checkbox" name="form.recreateThumbnails"}{$form.recreateThumbnails}{/gallery->input}
	  {gallery->text text="Recreate thumbnails"}
	  <br />
	  {gallery->input type="checkbox" name="form.recreateResizes"}{$form.recreateResizes}{/gallery->input}
	  {gallery->text text="Recreate resized images"}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
    {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

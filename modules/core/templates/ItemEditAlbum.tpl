{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Album Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Settings saved successfully."}
      {/if}
      {if isset($status.createdAlbum)}
	{g->text text="Album created successfully."}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Sort order"}
    {/g->title}
    {g->description}
      {g->text text="This sets the default sort order for the album.  This applies to all new items."}
    {/g->description}
    {g->element}
      {g->select name="form.orderBy"}
	{html_options options=$ItemEditAlbum.orderByList selected=$form.orderBy}
      {/g->select}
      {g->select name="form.orderDirection"}
	{html_options options=$ItemEditAlbum.orderDirectionList selected=$form.orderDirection}
      {/g->select}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Layout"}
    {/g->title}
    {g->description}
      {g->text text="Choose a layout for this album. (The way the album is arranged on the page.)"}
    {/g->description}
    {g->element}
      {g->select name="form.layout"}
	{html_options options=$ItemEditAlbum.layoutList selected=$form.layout}
      {/g->select}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Theme"}
    {/g->title}
    {g->description}
      {g->text text="Choose a theme for this album.  (The look and feel of this album)"}
    {/g->description}
    {g->element}
      {g->select name="form.theme"}
	{html_options options=$ItemEditAlbum.themeList selected=$form.theme}
      {/g->select}
    {/g->element}
  {/g->box}
  
  {g->box style="admin"}
    {g->title}
      {g->text text="Thumbnails"}
    {/g->title}
    {g->description}
      {g->text text=" Every item requires a thumbnail. Set the default value in pixels here."}
    {/g->description}
    {g->element}
      {g->input type=text size=6 name="form.thumbnail.size"}{$form.thumbnail.size}{/g->input}
    {/g->element}
    
    {if !empty($form.error.thumbnail.size.invalid)}
      {g->error}
	{g->text text="You must enter a number (greater than zero)"}
      {/g->error}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Resized Images"}
    {/g->title}
    {g->description}
      {g->text text="Each item in your album can have multiple sizes. Define the default sizes here."}
    {/g->description}
    {g->element}
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column width="10%" header="true" align="center"}
	    {g->text text="Active"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Target Size (pixels)"}
	  {/g->column}
	{/g->row}
	{counter start=0 assign=index}
	{foreach from=$form.resizes item=resize}
	  {g->row}
	    {g->column align="center"}
	      {g->input type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/g->input}
	    {/g->column}
	    {g->column}
	      {g->input type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/g->input}
	    {/g->column}
	  {/g->row}

	  {if !empty($form.error.resizes.$index.size.missing)}
	    {g->row}
	      {g->column colspan="2"}
		{g->error}
		  {g->text text="You must enter a valid size"}
		{/g->error}
	      {/g->column}
	    {/g->row}
	  {/if}
	  
	  {if !empty($form.error.resizes.$index.size.invalid)}
	    {g->row}
	      {g->column colspan="2"}
		{g->error}
		  {g->text text="You must enter a number (greater than zero)"}
		{/g->error}
	      {/g->column}
	    {/g->row}
	  {/if}
	  {counter}
	{/foreach}
      {/g->table}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Recreate thumbnails and resizes"}
    {/g->title}
    {g->description}
      {g->text text="The thumbnail and resized image settings are for all new items. To apply these settings to all the items in your album, check the appropriate box."}
    {/g->description}
    {g->element}
      {g->input type="checkbox" name="form.recreateThumbnails"}{$form.recreateThumbnails}{/g->input}
      {g->text text="Recreate thumbnails"}
    {/g->element}
    {g->element}
      {g->input type="checkbox" name="form.recreateResizes"}{$form.recreateResizes}{/g->input}
      {g->text text="Recreate resized images"}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

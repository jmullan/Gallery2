{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Item Thumbnail Size and Resizes"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Changes saved successfully."}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Thumbnails"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="Specify the thumbnail size of this item here:"}
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
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Resized Images"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="These sizes are alternate resized versions of the original you would like to have available for viewing."}
  {/gallery->description}

  {gallery->body}
    {gallery->widget1box}
      {counter start=0 assign=index}
      {foreach from=$form.resizes item=resize}
	{gallery->widget1}
	  {gallery->body}
	    {gallery->input type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/gallery->input}
	    {gallery->input type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/gallery->input}

	    {if !empty($form.error.resizes.$index.size.missing)}
	      {gallery->error}
	        {gallery->text text="You must enter a valid size"}
	      {/gallery->error}
            {/if}
	    
	    {if !empty($form.error.resizes.$index.size.invalid)}
	      {gallery->error}
	        {gallery->text text="You must enter a number (greater than zero)"}
	      {/gallery->error}
            {/if}
            {counter}
	  {/gallery->body}
	{/gallery->widget1}
      {/foreach}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
    {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

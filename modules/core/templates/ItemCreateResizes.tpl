{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Item Thumbnail Size and Resizes"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Changes saved successfully."}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Thumbnails"}
    {/g->title}

    {g->description}
      {g->text text="Specify the thumbnail size of this item here:"}
    {/g->description}

    {g->element}
      {g->input type=text size=6 name="form.thumbnail.size"}{$form.thumbnail.size}{/g->input}
    {/g->element}
  {/g->box}

  {if !empty($form.error.thumbnail.size.missing)}
    {g->error}
      {g->text text="You must enter a thumbnail size"}
    {/g->error}
  {/if}
  
  {if !empty($form.error.thumbnail.size.invalid)}
    {g->error}
      {g->text text="You must enter a number (greater than zero)"}
    {/g->error}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Resized Images"}
    {/g->title}

    {g->description}
      {g->text text="These sizes are alternate resized versions of the original you would like to have available for viewing."}
    {/g->description}

    {counter start=0 assign=index}
    {foreach from=$form.resizes item=resize}
      {g->element}
	{g->input type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/g->input}
	{g->input type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/g->input}
      {/g->element}

      {if !empty($form.error.resizes.$index.size.missing)}
	{g->error}
	  {g->text text="You must enter a valid size"}
	{/g->error}
      {/if}
	      
      {if !empty($form.error.resizes.$index.size.invalid)}
	{g->error}
	  {g->text text="You must enter a number (greater than zero)"}
	{/g->error}
      {/if}
      {counter}
    {/foreach}
  {/g->box}

  {g->box}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

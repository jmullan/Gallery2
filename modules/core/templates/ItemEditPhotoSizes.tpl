{g->box style="admin"}
  {g->title}
    {g->text text="Thumbnail"}
  {/g->title}

  {g->description}
    {g->text text="Set the size of the thumbnail.  The largest side of the thumbnail will be no larger than this value."}
  {/g->description}

  {if $ItemEditPhotoSizes.editSizes.can.createThumbnail}
    {g->element}
      {g->input type=text size=6 name="form[thumbnail][size]"}{$form.thumbnail.size}{/g->input}
    {/g->element}
  {else}
    {g->element style="emphasized"}
      {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify a thumbnail."}
      {if $ItemEditPhotoSizes.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {/if}
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
    {g->text text="Resized Photos"}
  {/g->title}

  {g->description}
    {g->text text="These sizes are alternate resized versions of the original you would like to have available for viewing."}
  {/g->description}

  {if $ItemEditPhotoSizes.editSizes.can.createThumbnail}
    {counter start=0 assign=index}
    {foreach from=$form.resizes item=resize}
      {g->element}
	{g->input type="checkbox" name="form[resizes][$index][active]"}{$form.resizes.$index.active}{/g->input}
	{g->input type="text" size="6" name="form[resizes][$index][size]"}{$form.resizes.$index.size}{/g->input}
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
  {else}
    {g->element style="emphasized"}
      {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify resized versions."}
      {if $ItemEditPhotoSizes.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {/if}
{/g->box}

{g->box}
  {g->element}
    {g->input type="hidden" name="mode"}editSizes{/g->input}
    {g->input type="submit" name="form[action][save]"}{g->text text="Save"}{/g->input}
    {g->input type="submit" name="form[action][undo]"}{g->text text="Undo"}{/g->input}
  {/g->element}
{/g->box}

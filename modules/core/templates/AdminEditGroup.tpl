{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Edit a group"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Group Name"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}

	{gallery->body}
	  {gallery->input type="text" name="form.groupName"}{$form.groupName}{/gallery->input}
	  {gallery->input type="hidden" name="groupId"}{$AdminEditGroup.group.id}{/gallery->input}
	    {if isset($form.error.groupName.missing)}
	      {gallery->error}
		{gallery->text text="You must enter a group name"}
	      {/gallery->error}
	    {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Create A New Group"}
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
	  {if isset($form.error.groupName.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a group name"}
	    {/gallery->error}
	  {/if}
	  
	  {if isset($form.error.groupName.exists)}
	    {gallery->error}
	      {gallery->text text="Group '%s' already exists" arg1=$form.groupName}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.create"}{gallery->text text="Create Group"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="General Item Properties"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Settings saved successfully."}
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
	  {gallery->text text="Name"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="The name of this item on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes."}
	{/gallery->description}
	{gallery->body}
	  {strip}
	    {foreach from=$ItemAdmin.parents item=parent}
	      {if empty($parent.parentId)}
		/
	      {else}
		{$parent.pathComponent}/
	      {/if}
	    {/foreach}
	  {/strip}
	  {gallery->input type=text size=40 name="form.pathComponent"}{$form.pathComponent}{/gallery->input}

	  {if !empty($form.error.pathComponent.invalid)}
	    {gallery->error}
	      {gallery->text text="Your name contains invalid characters.  Please choose another."}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.pathComponent.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a name for this item."}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.pathComponent.collision)}
	    {gallery->error}
	      {gallery->text text="The name you entered is already in use.  Please choose another."}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Title"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="The title of this item."}
	{/gallery->description}
	{gallery->body}
	  {gallery->input type="text" size="40" name="form.title"}{$form.title}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Summary"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="The summary of this item."}
	{/gallery->description}
	{gallery->body}
	  {gallery->input type="text" size="40" name="form.summary"}{$form.summary}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Keywords"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="Keywords are not visible, but are searchable."}
	{/gallery->description}
	{gallery->body}
	  {gallery->textarea rows="2" cols="60" name="form.keywords"}{$form.keywords}{/gallery->textarea}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Description"}
	{/gallery->title}
	{gallery->description}
	  {gallery->text text="This is the long description of the item."}
	{/gallery->description}
	{gallery->body}
	  {gallery->textarea rows="4" cols="60" name="form.description"}{$form.description}{/gallery->textarea}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

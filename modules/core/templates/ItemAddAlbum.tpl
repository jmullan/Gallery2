{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Add Album"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Name"}
	{/gallery->title}

	{gallery->description}
	  {gallery->text text="The name of this album on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes.  You will be able to rename it later."}
	{/gallery->description}
	{gallery->body}
	  {strip}
	    {foreach from=$ItemAdmin.parents item=parent}
	      {$parent.pathComponent}/
	    {/foreach}
	    {$ItemAdmin.item.pathComponent}/
	  {/strip}
	  {gallery->input type="text" size="10" name="form.pathComponent"}{$form.pathComponent}{/gallery->input}

          {if !empty($form.error.pathComponent.invalid)}
	    {gallery->error}
	      {gallery->text text="Your name contains invalid characters.  Please enter another."}
	    {/gallery->error}
          {/if}

          {if !empty($form.error.pathComponent.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a name for this album."}
	    {/gallery->error}
          {/if}

          {if !empty($form.error.pathComponent.collision)}
	    {gallery->error}
	      {gallery->text text="The name you entered is already in use.  Please enter another."}
	    {/gallery->error}
          {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Title"}
	{/gallery->title}

	{gallery->description}
	  {gallery->text text="This is the album title.  Do not use HTML."}
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
	  {gallery->text text="This is the album summary.  Do not use HTML"}
	{/gallery->description}

	{gallery->body}
	  {gallery->input type=text size=40 name="form.summary"}{$form.summary}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Keywords"}
	{/gallery->title}

	{gallery->description}
	  {gallery->text text="Keywords are not visible, but are searchable. Do not use HTML."}
	{/gallery->description}
	{gallery->body}
	  {gallery->textarea rows=2 cols=60 name="form.keywords"}{$form.keywords}{/gallery->textarea}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Description"}
	{/gallery->title}

	{gallery->description}
	  {gallery->text text="This is the long description of the album.  HTML is ok."}
	{/gallery->description}
	{gallery->body}
	  {gallery->textarea rows=4 cols=60 name="form.description"}{$form.description}{/gallery->textarea}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.create"}{gallery->text text="Create"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

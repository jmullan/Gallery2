{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Add Album"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="Name"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}

      {g->description}
	{g->text text="The name of this album on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes.  You will be able to rename it later."}
      {/g->description}

      {g->element}
	{strip}
	  {foreach from=$ItemAdmin.parents item=parent}
	    {$parent.pathComponent}/
	  {/foreach}
	  {$ItemAdmin.item.pathComponent}/
	{/strip}
	{g->input type="text" size="10" name="form.pathComponent"}{$form.pathComponent}{/g->input}
      {/g->element}
    {/g->box}

    {if !empty($form.error.pathComponent.invalid)}
      {g->error}
	{g->text text="Your name contains invalid characters.  Please enter another."}
      {/g->error}
    {/if}

    {if !empty($form.error.pathComponent.missing)}
      {g->error}
	{g->text text="You must enter a name for this album."}
      {/g->error}
    {/if}

    {if !empty($form.error.pathComponent.collision)}
      {g->error}
	{g->text text="The name you entered is already in use.  Please enter another."}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Title"}
      {/g->title}

      {g->description}
	{g->text text="This is the album title."}
      {/g->description}

      {g->element}
	{g->input type="text" size="40" name="form.title"}{$form.title}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Summary"}
      {/g->title}

      {g->description}
	{g->text text="This is the album summary."}
      {/g->description}

      {g->element}
	{g->input type=text size=40 name="form.summary"}{$form.summary}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Keywords"}
      {/g->title}

      {g->description}
	{g->text text="Keywords are not visible, but are searchable."}
      {/g->description}

      {g->element}
	{g->textarea rows=2 cols=60 name="form.keywords"}{$form.keywords}{/g->textarea}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Description"}
      {/g->title}

      {g->description}
	{g->text text="This is the long description of the album."}
      {/g->description}

      {g->element}
	{g->textarea rows=4 cols=60 name="form.description"}{$form.description}{/g->textarea}
      {/g->element}
    {/g->box}

    {g->box}
      {g->element}
	{g->input type="submit" name="form.action.create"}{g->text text="Create"}{/g->input}
      {/g->element}
    {/g->box}
  {/g->box}
{/g->pagebox}

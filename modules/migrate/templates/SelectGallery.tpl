{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Migrate"}
    {/g->title}
    {g->description}
      {g->text text="THIS MODULE IS NOT COMPLETE.  USE IT AT YOUR OWN RISK."}
    {/g->description}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Enter the path to migrate"}
    {/g->title}
    {g->description}
      {g->text text="Use this module to migrate a gallery from v1 to this version."}
    {/g->description}

    {g->box}
      {g->title}
	{g->text text="Path:"}
      {/g->title}

      {g->element}
	{g->input type="text" size="60" name="form.albumsPath"}{$form.albumsPath}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.albumsPath.missing)}
      {g->error}
	{g->text text="You did not enter a path."}
      {/g->error}
    {/if}

    {if isset($form.error.albumsPath.invalid)}
      {g->error}
	{g->text text="The path that you entered is invalid."}
      {/g->error}
    {/if}
	
    {g->element}
      {g->input type="submit" name="form.action.select"}
	{g->text text="Select"}
      {/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

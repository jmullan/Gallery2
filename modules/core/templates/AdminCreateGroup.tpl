{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Create A New Group"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Group Name"}
    {/g->title}

    {g->subtitle}
      {g->text text="required"}
    {/g->subtitle}

    {g->element}
      {g->input type="text" name="form[groupName]"}{$form.groupName}{/g->input}
    {/g->element}

    {if isset($form.error.groupName.missing)}
      {g->error}
	{g->text text="You must enter a group name"}
      {/g->error}
    {/if}
    
    {if isset($form.error.groupName.exists)}
      {g->error}
	{g->text text="Group '%s' already exists" arg1=$form.groupName}
      {/g->error}
    {/if}
  {/g->box}

  {g->box}
    {g->element}
      {g->input type="submit" name="form[action][create]"}{g->text text="Create Group"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

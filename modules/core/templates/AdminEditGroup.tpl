{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit a group"}
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
      {g->input type="text" name="form.groupName"}{$form.groupName}{/g->input}
      {g->input type="hidden" name="groupId"}{$AdminEditGroup.group.id}{/g->input}
    {/g->element}

    {if isset($form.error.groupName.missing)}
      {g->error}
	{g->text text="You must enter a group name"}
      {/g->error}
    {/if}

    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

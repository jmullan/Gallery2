{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Delete a group"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Are you sure?"}
    {/g->title}

    {g->description}
      {g->text text="This will completely remove <b>%s</b> from Gallery.  There is no undo!"
      arg1=$AdminDeleteGroup.group.groupName}
    {/g->description}

    {g->element}
      {g->input type="hidden" name="groupId"}{$AdminDeleteGroup.group.id}{/g->input}
      {g->input type="submit" name="form.action.delete"}{g->text text="Delete"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit Group Members"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.addedUser)}
	{g->text text="Added user '%s' to group" arg1=$status.addedUser}
      {/if}
      
      {if isset($status.removedUser)}
	{g->text text="Removed user '%s' from group" arg1=$status.removedUser}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text one="This group contains %d user"
      many="This group contains %d users"
      count=$form.userCount
      arg1=$form.userCount}
    {/g->description}
  {/g->box}

  {if !empty($form.list.users)}
    {g->box style="admin"}
      {g->title}
	{g->text text="Remove Member"}
      {/g->title}

      {g->element}
	{g->select name="form[list][userId]" size=1}
	  {html_options options=$form.list.users}
	{/g->select}
	{g->input type="submit" name="form[action][remove]"}
	  {g->text text="Remove"}
	{/g->input}
      {/g->element}

      {if isset($form.error.list.noUserSelected)}
	{g->error}
	  {g->text text="You must select a user to remove."}
	{/g->error}
      {/if}
    {/g->box}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Add Member"}
    {/g->title}

    {g->element}
      {g->input type="text" name="form[text][userName]"}{$form.text.userName}{/g->input}
      {g->input type="submit" name="form[action][add]"}
	{g->text text="Add"}
      {/g->input}
    {/g->element}

    {if isset($form.error.text.userName.missing)}
      {g->error}
	{g->text text="You must enter a username."}
      {/g->error}
    {/if}

    {if isset($form.error.text.userName.invalid)}
      {g->error}
	{g->text text="User '%s' does not exist." arg1=$form.text.userName}
      {/g->error}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="hidden" name="groupId"}{$AdminEditGroupUsers.group.id}{/g->input}
      {g->input type="submit" name="form[action][done]"}{g->text text="Done"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Permissions"}
    {/g->title}
  {/g->banner}

  {if isset($status.changedOwner)}
    {g->success}
      {g->text text="Owner changed successfully"}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text text="Each item has its own independent set of permissions.  Changing the parent's permissions has no effect on the permissions of the child.  This allows you to restrict access to the parent of this item, but still grant full access to this item, or vice versa.  The most efficient way to use this permission system is to create groups and assign permissions to them.  Then if you want to grant permissions to a specific user, you can add (or remove) the user from the appropriate group."}
    {/g->description}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Owner"}
    {/g->title}
    
    {g->description}
      {if empty($ItemEditPermissions.owner.fullName)}
	{g->text text="This item is owned by user: %s" arg1=$ItemEditPermissions.owner.userName}
      {else}
	{g->text text="This item is owned by user: %s (%s)" arg1=$ItemEditPermissions.owner.userName arg2=$ItemEditPermissions.owner.fullName}
      {/if}
    {/g->description}
    
    {if $ItemEditPermissions.can.changeOwner}
      {g->box}
	{g->title}
	  {g->text text="New owner"}
	{/g->title}

	{g->element}
	  {g->input type="text" name="form[owner][ownerName]"}{$form.owner.ownerName}{/g->input}
	  {g->input type="submit" name="form[action][changeOwner]"}
	    {g->text text="Change"}
	  {/g->input}
	{/g->element}
      {/g->box}

      {if !empty($form.error.owner.missingUser)}
	{g->error}
	  {g->text text="You must enter a user name"}
	{/g->error}
      {/if}

      {if !empty($form.error.owner.invalidUser)}
	{g->error}
	  {g->text text="The user name you entered is invalid"}
	{/g->error}
      {/if}
    {/if}
  {/g->box}

  {if $ItemEditPermissions.can.applyToSubItems}
    {g->box style="admin"}
      {g->title}
	{g->text text="Apply changes"}
      {/g->title}
      
      {g->description}
	{g->text text="This item has sub-items.  The changes you make here can be applied to just this item, or you can apply them to all sub-items.  Note that applying changes to sub-items will merge your change into the existing permissions of the sub-items and may be very time consuming if you have many of sub-items.  It's more efficient to grant permissions to groups and then add and remove users from groups whenever possible."}
      {/g->description}
      
      {g->element}
	{g->input type="checkbox" name="form[applyToSubItems]"}{/g->input}
	{g->text text="Apply to sub-items"}
      {/g->element}
    {/g->box}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Group Permissions"}
    {/g->title}
    {g->element}
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
	    {g->text text="Group name"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Permission"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Action"}
	  {/g->column}
	{/g->row}

	{if $ItemEditPermissions.groupPermissions}
	  {section name=group loop=$ItemEditPermissions.groupPermissions}
	    {assign var="entry" value=$ItemEditPermissions.groupPermissions[group]}
	    {assign var="index" value=$smarty.section.group.iteration}
	    {g->row}
	      {g->column}
		{$entry.group.groupName}
	      {/g->column}

	      {g->column}
		{$entry.permission.description}
	      {/g->column}

	      {g->column}
		{if ! empty($entry.deleteList)}
		  {g->select name="form[group][delete][$index]" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		      <option value="{$entry.group.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
		    {/foreach}
		  {/g->select}
		{else}
		  &nbsp;
		{/if}
		{if ! empty($entry.deleteList)}
		  {g->input type="submit" name="form[action][deleteGroupPermission][$index]"}
		    {g->text text="Remove"}
		  {/g->input}
		{else}
		  &nbsp;
		{/if}
	      {/g->column}
	    {/g->row}
	  {/section}
	{/if}
      {/g->table}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="New Group Permission"}
    {/g->title}
    
    {g->element}
      {g->input type="text" name="form[group][groupName]"}
	{$form.group.groupName}
      {/g->input}
	    
      {g->select name="form[group][permission]" size="1"}
	{html_options options=$ItemEditPermissions.allPermissions selected=$form.group.permission}
      {/g->select}

      {g->input type="submit" name="form[action][addGroupPermission]"}
	{g->text text="Add Permission"}
      {/g->input}
    {/g->element}

    {if !empty($form.error.group.invalidPermission)}
      {g->error}
	{g->text text="The permission you chose is invalid"}
      {/g->error}
    {/if}

    {if !empty($form.error.group.missingGroup)}
      {g->error}
	{g->text text="You must enter a group name"}
      {/g->error}
    {/if}

    {if !empty($form.error.group.invalidGroup)}
      {g->error}
	{g->text text="The group name you entered is invalid"}
      {/g->error}
    {/if}

    {if !empty($form.error.group.alreadyHadPermission)}
      {g->error}
	{g->text text="Group already has this permission (check sub-permissions)"}
      {/g->error}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="User Permissions"}
    {/g->title}

    {g->element}
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
	    {g->text text="User name"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Permission"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Action"}
	  {/g->column}
	{/g->row}

	{if $ItemEditPermissions.userPermissions}
	  {section name=user loop=$ItemEditPermissions.userPermissions}
	    {assign var="entry" value=$ItemEditPermissions.userPermissions[user]}
	    {assign var="index" value=$smarty.section.user.iteration}
	    {g->row}
	      {g->column}
		{$entry.user.userName}
	      {/g->column}

	      {g->column}
		{$entry.permission.description}
	      {/g->column}

	      {g->column}
		{if ! empty($entry.deleteList) }
		  {g->select name="form[user][delete][$index]" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		      <option value="{$entry.user.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
		    {/foreach}
		  {/g->select}
		{else}
		  &nbsp;
		{/if}
		{if ! empty($entry.deleteList) }
		  {g->input type="submit" name="form[action][deleteUserPermission][$index]"}
		    {g->text text="Remove"}
		  {/g->input}
		{else}
		  &nbsp;
		{/if}
	      {/g->column}
	    {/g->row}
	  {/section}
	{/if}
      {/g->table}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="New User Permission"}
    {/g->title}

    {g->element}
      {g->input type="text" name="form[user][userName]"}
	{$form.user.userName}
      {/g->input}

      {g->select name="form[user][permission]" size="1"}
	{html_options options=$ItemEditPermissions.allPermissions selected=$form.user.permission}
      {/g->select}
      
      {g->input type="submit" name="form[action][addUserPermission]"}
	{g->text text="Add Permission"}
      {/g->input}
    {/g->element}

    {if !empty($form.error.user.invalidPermission)}
      {g->error}
	{g->text text="The permission you chose is invalid"}
      {/g->error}
    {/if}

    {if !empty($form.error.user.missingUser)}
      {g->error}
	{g->text text="You must enter a user name"}
      {/g->error}
    {/if}

    {if !empty($form.error.user.invalidUser)}
      {g->error}
	{g->text text="The user name you entered is invalid"}
      {/g->error}
    {/if}

    {if !empty($form.error.user.alreadyHadPermission)}
      {g->error}
	{g->text text="The user already has this permission (check sub-permissions)"}
      {/g->error}
    {/if}
  {/g->box}

{/g->pagebox}

{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Permissions"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="Each item has its own independent set of permissions.  Changing the parent's permissions has no effect on the permissions of the child.  This allows you to restrict access to the parent of this item, but still grant full access to this item, or vice versa.  The most efficient way to use this permission system is to create groups and assign permissions to them.  Then if you want to grant permissions to a specific user, you can add (or remove) the user from the appropriate group."}
  {/gallery->description}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Owner"}
  {/gallery->title}

  {gallery->description}
    {if empty($ItemEditPermissions.owner.fullName)}
      {gallery->text text="This item is owned by user: %s" arg1=$ItemEditPermissions.owner.userName}
    {else}
      {gallery->text text="This item is owned by user: %s (%s)" arg1=$ItemEditPermissions.owner.userName arg2=$ItemEditPermissions.owner.fullName}
    {/if}
  {/gallery->description}

  {if $ItemEditPermissions.can.changeOwner}
    {gallery->body}
      {gallery->widget1box}
	{gallery->widget1}
	  {gallery->title}
	    {gallery->text text="New owner"}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->input type="text" name="form.owner.ownerName"}{$form.owner.ownerName}{/gallery->input}
	    {gallery->input type="submit" name="form.action.changeOwner"}
	      {gallery->text text="Change"}
	    {/gallery->input}

	    {if !empty($form.error.owner.missingUser)}
	      {gallery->error}
		{gallery->text text="You must enter a user name"}
	      {/gallery->error}
	    {/if}

	    {if !empty($form.error.owner.invalidUser)}
	      {gallery->error}
		{gallery->text text="The user name you entered is invalid"}
	      {/gallery->error}
	    {/if}
	  {/gallery->body}
	{/gallery->widget1}
      {/gallery->widget1box}
    {/gallery->body}
  {/if}
{/gallery->detailedbox}

{if $ItemEditPermissions.can.applyToSubItems}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="Apply changes"}
    {/gallery->title}
    
    {gallery->description}
      {gallery->text text="This item has sub-items.  The changes you make here can be applied to just this item, or you can apply them to all sub-items.  Note that applying changes to sub-items will merge your change into the existing permissions of the sub-items and may be very time consuming if you have many of sub-items.  It's more efficient to grant permissions to groups and then add and remove users from groups whenever possible."}
    {/gallery->description}

    {gallery->body}
      {gallery->input type="checkbox" name="form.applyToSubItems"}{/gallery->input}
      {gallery->text text="Apply to sub-items"}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Group Permissions"}
  {/gallery->title}
  {gallery->body}
    {if $ItemEditPermissions.groupPermissions}
      {gallery->table}
	{gallery->row}
	  {gallery->column header="true"}
	    {gallery->text text="Group name"}
	  {/gallery->column}
	  {gallery->column header="true"}
	    {gallery->text text="Permission"}
	  {/gallery->column}
	  {gallery->column header="true"}
	    {gallery->text text="Action"}
	  {/gallery->column}
	{/gallery->row}

	{section name=group loop=$ItemEditPermissions.groupPermissions}
	  {assign var="entry" value=$ItemEditPermissions.groupPermissions[group]}
	  {assign var="index" value=$smarty.section.group.iteration}
	  {gallery->row}
	    {gallery->column}
	      {$entry.group.groupName}
	    {/gallery->column}

	    {gallery->column}
	      {$entry.permission.description}
	    {/gallery->column}

	    {gallery->column}
	      {if ! empty($entry.deleteList)}
		{gallery->select name="form.group.delete.$index" size="1"}
		  {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.group.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
		  {/foreach}
		{/gallery->select}
	      {else}
		&nbsp;
	      {/if}
	      {if ! empty($entry.deleteList)}
		{gallery->input type="submit" name="form.action.deleteGroupPermission.$index"}
		  {gallery->text text="Remove"}
		{/gallery->input}
	      {else}
		&nbsp;
	      {/if}
	    {/gallery->column}
	  {/gallery->row}
	{/section}
      {/gallery->table}
    {/if}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="Group:"}
	{/gallery->title}

	{gallery->body}
	  {gallery->input type="text" name="form.group.groupName"}
	    {$form.group.groupName}
	  {/gallery->input}
	  
	  {gallery->select name="form.group.permission" size="1"}
	    {html_options options=$ItemEditPermissions.allPermissions selected=$form.group.permission}
	  {/gallery->select}

	  {gallery->input type="submit" name="form.action.addGroupPermission"}
	    {gallery->text text="Add Permission"}
	  {/gallery->input}

	  {if !empty($form.error.group.invalidPermission)}
	    {gallery->error}
	      {gallery->text text="The permission you chose is invalid"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.group.missingGroup)}
	    {gallery->error}
	      {gallery->text text="You must enter a group name"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.group.invalidGroup)}
	    {gallery->error}
	      {gallery->text text="The group name you entered is invalid"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.group.alreadyHadPermission)}
	    {gallery->error}
	      {gallery->text text="Group already has this permission (maybe it's included in one of the permissions the group already has)"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}


{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="User Permissions"}
  {/gallery->title}
  {gallery->body}
    {if $ItemEditPermissions.userPermissions}
      {gallery->table}
	{gallery->row}
	  {gallery->column header="true"}
	    {gallery->text text="User name"}
	  {/gallery->column}
	  {gallery->column header="true"}
	    {gallery->text text="Permission"}
	  {/gallery->column}
	  {gallery->column header="true"}
	    {gallery->text text="Action"}
	  {/gallery->column}
	{/gallery->row}

	{section name=user loop=$ItemEditPermissions.userPermissions}
	  {assign var="entry" value=$ItemEditPermissions.userPermissions[user]}
	  {assign var="index" value=$smarty.section.user.iteration}
	  {gallery->row}
	    {gallery->column}
	      {$entry.user.userName}
	    {/gallery->column}

	    {gallery->column}
	      {$entry.permission.description}
	    {/gallery->column}

	    {gallery->column}
	      {if ! empty($entry.deleteList) }
		{gallery->select name="form.user.delete.$index" size="1"}
		  {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.user.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
		  {/foreach}
		{/gallery->select}
	      {else}
		&nbsp;
	      {/if}
	      {if ! empty($entry.deleteList) }
		{gallery->input type="submit" name="form.action.deleteUserPermission.$index"}
		  {gallery->text text="Remove"}
		{/gallery->input}
	      {else}
		&nbsp;
	      {/if}
	    {/gallery->column}
	  {/gallery->row}
	{/section}
      {/gallery->table}
    {/if}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->title}
	  {gallery->text text="User:"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="text" name="form.user.userName"}
	    {$form.user.userName}
	  {/gallery->input}

	  {gallery->select name="form.user.permission" size="1"}
	    {html_options options=$ItemEditPermissions.allPermissions selected=$form.user.permission}
	  {/gallery->select}
	  
	  {gallery->input type="submit" name="form.action.addUserPermission"}
	    {gallery->text text="Add Permission"}
	  {/gallery->input}

	  {if !empty($form.error.user.invalidPermission)}
	    {gallery->error}
	      {gallery->text text="The permission you chose is invalid"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.user.missingUser)}
	    {gallery->error}
	      {gallery->text text="You must enter a user name"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.user.invalidUser)}
	    {gallery->error}
	      {gallery->text text="The user name you entered is invalid"}
	    {/gallery->error}
	  {/if}

	  {if !empty($form.error.user.alreadyHadPermission)}
	    {gallery->error}
	      {gallery->text text="The user already has this permission (maybe it's included in one of the permissions the user already has)"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

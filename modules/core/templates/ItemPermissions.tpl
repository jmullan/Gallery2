{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemPermissions.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Permissions"}
      </h2>
    </div>
      
  </div>
  
  {if isset($status.changedOwner)}
  <div id="gsStatus">
    <div class="giStatus">
      {g->text text="Owner changed successfully"}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Each item has its own independent set of permissions.  Changing the parent's permissions has no effect on the permissions of the child.  This allows you to restrict access to the parent of this item, but still grant full access to this item, or vice versa.  The most efficient way to use this permission system is to create groups and assign permissions to them.  Then if you want to grant permissions to a specific user, you can add (or remove) the user from the appropriate group."}
    </p>
  </div>

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Owner"}
    </h2>
    
    <p class="giDescription">
      {if empty($ItemPermissions.owner.fullName)}
      {g->text text="This item is owned by user: %s" arg1=$ItemPermissions.owner.userName}
      {else}
      {g->text text="This item is owned by user: %s (%s)" arg1=$ItemPermissions.owner.userName arg2=$ItemPermissions.owner.fullName}
      {/if}
    </p>
    
    {if $ItemPermissions.can.changeOwner}
    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="New owner"}
      </h2>

      <input id="ownername" class="giFormUsername" type="text" name="{g->formVar var="form[owner][ownerName]"}" value="{$form.owner.ownerName}" autocomplete="off"/>
      {g->autoComplete element="ownername"}
      {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupUsername" arg3="prefix=__VALUE__"}
      {/g->autoComplete}

      <input type="hidden" name="{g->formVar var="form[serialNumber]"}" value="{$form.serialNumber}"/>
      <input type="submit" name="{g->formVar var="form[action][changeOwner]"}" value="{g->text text="Change"}"/>

      {if !empty($form.error.owner.missingUser)}
      <div class="giError">
	{g->text text="You must enter a user name"}
      </div>
      {/if}
      
      {if !empty($form.error.owner.invalidUser)}
      <div class="giError">
	{g->text text="The user name you entered is invalid"}
      </div>
      {/if}
    </div>
    {/if}
  </div>

  {if $ItemPermissions.can.applyToSubItems}
  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Apply changes"}
    </h2>
      
    <p class="giDescription">
      {g->text text="This item has sub-items.  The changes you make here can be applied to just this item, or you can apply them to all sub-items.  Note that applying changes to sub-items will merge your change into the existing permissions of the sub-items and may be very time consuming if you have many of sub-items.  It's more efficient to grant permissions to groups and then add and remove users from groups whenever possible. Changes are applied to sub-albums by default."}
    </p>

    <input type="checkbox" name="{g->formVar var="form[applyToSubItems]"}" value="{g->text text="Apply to sub-items"}" checked="checked"/>
  </div>
  {/if}

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Group Permissions"}
    </h2>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Group name"}
	</th>
	<th>
	  {g->text text="Permission"}
	</th>
	<th>
	  {g->text text="Action"}
	</th>
      </tr>

      {if $ItemPermissions.groupPermissions}
      {section name=group loop=$ItemPermissions.groupPermissions}
      {assign var="entry" value=$ItemPermissions.groupPermissions[group]}
      {assign var="index" value=$smarty.section.group.iteration}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$entry.group.groupName}
	</td>

	<td>
	  {$entry.permission.description}
	</td>

	<td>
	  {if ! empty($entry.deleteList)}
	  <select name="{g->formVar var="form[group][delete][$index]"}" size="1">
	    {foreach from=$entry.deleteList item=deleteEntry}
	    <option value="{$entry.group.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
	    {/foreach}
	  </select>
	  {else}
	  &nbsp;
	  {/if}

	  {if ! empty($entry.deleteList)}
	  <input type="submit" name="{g->formVar var="form[action][deleteGroupPermission][$index]"}" value="{g->text text="Remove"}"/>
	  {else}
	  &nbsp;
	  {/if}
	</td>
      </tr>
      {/section}
      {/if}
    </table>
  </div>

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="New Group Permission"}
    </h2>
    
    <input id="groupname" class="giFormGroupname" type="text" name="{g->formVar var="form[group][groupName]"}" value="{$form.group.groupName}" autocomplete="off"/>
    {g->autoComplete element="groupname"}
    {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupGroupname" arg3="prefix=__VALUE__"}
    {/g->autoComplete}
	    
    <select name="{g->formVar var="form[group][permission]"}" size="1">
	{html_options options=$ItemPermissions.allPermissions selected=$form.group.permission}
    </select>

    <input type="submit" name="{g->formVar var="form[action][addGroupPermission]"}" value="{g->text text="Add Permission"}"/>

    {if !empty($form.error.group.invalidPermission)}
    <div class="giError">
      {g->text text="The permission you chose is invalid"}
    </div>
    {/if}
    
    {if !empty($form.error.group.missingGroup)}
    <div class="giError">
      {g->text text="You must enter a group name"}
    </div>
    {/if}
    
    {if !empty($form.error.group.invalidGroup)}
    <div class="giError">
      {g->text text="The group name you entered is invalid"}
    </div>
    {/if}
    
    {if !empty($form.error.group.alreadyHadPermission)}
    <div class="giError">
      {g->text text="Group already has this permission (check sub-permissions)"}
    </div>
    {/if}
  </div>

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="User Permissions"}
    </h2>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="User name"}
	</th>
	<th>
	  {g->text text="Permission"}
	</th>
	<th>
	  {g->text text="Action"}
	</th>
      </tr>

      {if $ItemPermissions.userPermissions}
      {section name=user loop=$ItemPermissions.userPermissions}
      {assign var="entry" value=$ItemPermissions.userPermissions[user]}
      {assign var="index" value=$smarty.section.user.iteration}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$entry.user.userName}
	</td>
	
	<td>
	  {$entry.permission.description}
	</td>

	<td>
	  {if ! empty($entry.deleteList) }
	  <select name="{g->formVar var="form[user][delete][$index]"}" size="1">
	    {foreach from=$entry.deleteList item=deleteEntry}
	    <option value="{$entry.user.id},{$deleteEntry.id}">{$deleteEntry.description}</option>
	    {/foreach}
	  </select>
	  {else}
	  &nbsp;
	  {/if}
	  {if ! empty($entry.deleteList) }
	  <input type="submit" name="{g->formVar var="form[action][deleteUserPermission][$index]"}" value="{g->text text="Remove"}"/>
	  {else}
	  &nbsp;
	  {/if}
	</td>
      </tr>
      {/section}
      {/if}
    </table>
  </div>

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="New User Permission"}
    </h2>

    <input id="username" class="giFormUsername" type="text" name="{g->formVar var="form[user][userName]"}" value="{$form.user.userName}" autocomplete="off"/>
    {g->autoComplete element="username"}
    {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupUsername" arg3="prefix=__VALUE__"}
    {/g->autoComplete}

    <select name="{g->formVar var="form[user][permission]"}" size="1">
	{html_options options=$ItemPermissions.allPermissions selected=$form.user.permission}
    </select>
      
    <input type="submit" name="{g->formVar var="form[action][addUserPermission]"}" value="{g->text text="Add Permission"}"/>

    {if !empty($form.error.user.invalidPermission)}
    <div class="giError">
      {g->text text="The permission you chose is invalid"}
    </div>
    {/if}
    
    {if !empty($form.error.user.missingUser)}
    <div class="giError">
      {g->text text="You must enter a user name"}
    </div>
    {/if}

    {if !empty($form.error.user.invalidUser)}
    <div class="giError">
      {g->text text="The user name you entered is invalid"}
    </div>
    {/if}

    {if !empty($form.error.user.alreadyHadPermission)}
    <div class="giError">
      {g->text text="The user already has this permission (check sub-permissions)"}
    </div>
    {/if}
  </div>
</div>

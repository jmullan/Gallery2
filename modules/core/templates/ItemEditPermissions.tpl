    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="formName"}ItemEditPermissions{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="Item Permissions"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Each item has its own independent set of permissions.  Changing the parent's permissions has no effect on the permissions of the child.  This allows you to restrict access to the parent of this item, but still grant full access to this item, or vice versa.  The most efficient way to use this permission system is to create groups and assign permissions to them.  Then if you want to grant permissions to a specific user, you can add (or remove) the user from the appropriate group."}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Owner"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {if empty($owner.fullName)}
	    {gallery->text text="This item is owned by user: %s"
	                 arg1=$owner.userName}
	    {else}
	    {gallery->text text="This item is owned by user: %s (%s)"
	                 arg1=$owner.userName
	                 arg2=$owner.fullName}
	    {/if}
	  </td>
	</tr>

	<!-- {if $canChangeOwner} -->
	<tr>
	  <td>
	    {gallery->text text="Change album owner to:"}
	    {gallery->input type="text" name="form.owner.ownerName"}
	    {$form.owner.ownerName}
	    {/gallery->input}
	    {gallery->input type="submit" name="form.action.changeOwner"}
	    {gallery->text text="Change"}
	    {/gallery->input}
	  </td>
	</tr>

	<!-- {if !empty($form.error.owner.missingUser)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a user name"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.owner.invalidUser)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The user name you entered is invalid"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->
	<!-- {/if} {* canChangeOwner *}-->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Apply changes"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="This item has sub-items.  The changes you make here can be applied to just this item, or you can apply them to all sub-items.  Note that applying changes to sub-items will merge your change into the existing permissions of the sub-items and may be very time consuming if you have many of sub-items.  It's more efficient to grant permissions to groups and then add and remove users from groups whenever possible."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="checkbox" name="form.applyToSubItems"}{/gallery->input}
	    <b>{gallery->text text="Apply to sub-items"}</b>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Group Permissions"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<!-- {if $groupPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {gallery->text text="User name"}
		  <th> {gallery->text text="Permission"}
		  <th colspan="2"> {gallery->text text="Action"}
		</tr>

		<!-- {section name=group loop=$groupPermissions} -->
		<!-- {assign var="entry" value=$groupPermissions[group]} -->
		<!-- {assign var="index" value=$smarty.section.group.iteration}} -->
		<tr>
		  <td align="left">
		    {$entry.group.groupName}
		  </td>
		  <td align="left">
		    {$entry.permission.description}
		  </td>
		  <td align="left">
		    {if ! empty($entry.deleteList) }
		    {gallery->select name="form.group.delete.$index" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.group.id},{$deleteEntry.id}"> 
		      {$deleteEntry.description}
		    </option>
		    {/foreach}
		    {/gallery->select}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		  <td>
		    {if ! empty($entry.deleteList) }
		    {gallery->input type="submit" name="form.action.deleteGroupPermission.$index"}
		    {gallery->text text="Remove"}
		    {/gallery->input}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		</tr>
		<!-- {/section} -->
	    </table>
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    <br>
	    {gallery->text text="Group name:"}
	    {gallery->input type="text" name="form.group.groupName"}
	    {$form.group.groupName}
	    {/gallery->input}

	    {gallery->select name="form.group.permission" size="1"}
	    {html_options options=$allPermissions selected=$form.group.permission}
	    {/gallery->select}

	    {gallery->input type="submit" name="form.action.addGroupPermission"}
	    {gallery->text text="Add Permission"}
	    {/gallery->input}
	  </td>
	</tr>

	<!-- {if !empty($form.error.group.invalidPermission)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The permission you chose is invalid"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.group.missingGroup)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a group name"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.group.invalidGroup)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The group name you entered is invalid"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.group.alreadyHadPermission)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="Group already has this permission (maybe it's included in one of the permissions the group already has)"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="User Permissions"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<!-- {if $userPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {gallery->text text="User name"}
		  <th> {gallery->text text="Permission"}
		  <th colspan="2"> {gallery->text text="Action"}
		</tr>

		<!-- {section name=user loop=$userPermissions} -->
		<!-- {assign var="entry" value=$userPermissions[user]} -->
		<!-- {assign var="index" value=$smarty.section.user.iteration}} -->
		<tr>
		  <td align="left">
		    {$entry.user.userName}
		  </td>
		  <td align="left">
		    {$entry.permission.description}
		  </td>
		  <td align="left">
		    {if ! empty($entry.deleteList) }
		    {gallery->select name="form.user.delete.$index" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.user.id},{$deleteEntry.id}"> 
		      {$deleteEntry.description}
		    </option>
		    {/foreach}
		    {/gallery->select}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		  <td>
		    {if ! empty($entry.deleteList) }
		    {gallery->input type="submit" name="form.action.deleteUserPermission.$index"}
		    {gallery->text text="Remove"}
		    {/gallery->input}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		</tr>
		<!-- {/section} -->
	    </table>
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    <br>
	    {gallery->text text="User name:"}
	    {gallery->input type="text" name="form.user.userName"}
	    {$form.user.userName}
	    {/gallery->input}

	    {gallery->select name="form.user.permission" size="1"}
	    {html_options options=$allPermissions selected=$form.user.permission}
	    {/gallery->select}

	    {gallery->input type="submit" name="form.action.addUserPermission"}
	    {gallery->text text="Add Permission"}
	    {/gallery->input}
	  </td>
	</tr>

	<!-- {if !empty($form.error.user.invalidPermission)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The permission you chose is invalid"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.user.missingUser)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a user name"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.user.invalidUser)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The user name you entered is invalid"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.user.alreadyHadPermission)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The user already has this permission (maybe it's included in one of the permissions the user already has)"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

    </table>
    {/gallery->form}

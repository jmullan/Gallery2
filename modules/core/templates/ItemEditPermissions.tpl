    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditPermissions{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFontSize}
	    {galleryText text="Item Permissions"}
	    {/galleryBiggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Each item has its own independent set of permissions.  Changing the parent's permissions has no effect on the permissions of the child.  This allows you to restrict access to the parent of this item, but still grant full access to this item, or vice versa.  The most efficient way to use this permission system is to create groups and assign permissions to them.  Then if you want to grant permissions to a specific user, you can add (or remove) the user from the appropriate group."}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Owner"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {if empty($owner.fullName)}
	    {galleryText text="This item is owned by user: %s"
	                 arg1=$owner.userName}
	    {else}
	    {galleryText text="This item is owned by user: %s (%s)"
	                 arg1=$owner.userName
	                 arg2=$owner.fullName}
	    {/if}
	  </td>
	</tr>

	<!-- {if $canChangeOwner} -->
	<tr>
	  <td>
	    {galleryText text="Change album owner to:"}
	    {galleryInput type="text" name="form.owner.ownerName"}
	    {$form.owner.ownerName}
	    {/galleryInput}
	    {galleryInput type="submit" name="form.action.changeOwner"}
	    {galleryText text="Change"}
	    {/galleryInput}
	  </td>
	</tr>

	<!-- {if !empty($form.error.owner.missingUser)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a user name"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.owner.invalidUser)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The user name you entered is invalid"}
	    {/galleryErrorFontColor}
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
	    {galleryBigFontSize}
	    {galleryText text="Apply changes"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="This item has sub-items.  The changes you make here can be applied to just this item, or you can apply them to all sub-items.  Note that applying changes to sub-items will merge your change into the existing permissions of the sub-items and may be very time consuming if you have many of sub-items.  It's more efficient to grant permissions to groups and then add and remove users from groups whenever possible."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type="checkbox" name="form.applyToSubItems"}{/galleryInput}
	    <b>{galleryText text="Apply to sub-items"}</b>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Group Permissions"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<!-- {if $groupPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {galleryText text="User name"}
		  <th> {galleryText text="Permission"}
		  <th colspan="2"> {galleryText text="Action"}
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
		    {gallerySelect name="form.group.delete.$index" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.group.id},{$deleteEntry.id}"> 
		      {$deleteEntry.description}
		    </option>
		    {/foreach}
		    {/gallerySelect}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		  <td>
		    {if ! empty($entry.deleteList) }
		    {galleryInput type="submit" name="form.action.deleteGroupPermission.$index"}
		    {galleryText text="Remove"}
		    {/galleryInput}
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
	    {galleryText text="Group name:"}
	    {galleryInput type="text" name="form.group.groupName"}
	    {$form.group.groupName}
	    {/galleryInput}

	    {gallerySelect name="form.group.permission" size="1"}
	    {html_options options=$allPermissions selected=$form.group.permission}
	    {/gallerySelect}

	    {galleryInput type="submit" name="form.action.addGroupPermission"}
	    {galleryText text="Add Permission"}
	    {/galleryInput}
	  </td>
	</tr>

	<!-- {if !empty($form.error.group.invalidPermission)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The permission you chose is invalid"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.group.missingGroup)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a group name"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.group.invalidGroup)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The group name you entered is invalid"}
	    {/galleryErrorFontColor}
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
	    {galleryBigFontSize}
	    {galleryText text="User Permissions"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<!-- {if $userPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {galleryText text="User name"}
		  <th> {galleryText text="Permission"}
		  <th colspan="2"> {galleryText text="Action"}
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
		    {gallerySelect name="form.user.delete.$index" size="1"}
		    {foreach from=$entry.deleteList item=deleteEntry}
		    <option value="{$entry.user.id},{$deleteEntry.id}"> 
		      {$deleteEntry.description}
		    </option>
		    {/foreach}
		    {/gallerySelect}
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		  <td>
		    {if ! empty($entry.deleteList) }
		    {galleryInput type="submit" name="form.action.deleteUserPermission.$index"}
		    {galleryText text="Remove"}
		    {/galleryInput}
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
	    {galleryText text="User name:"}
	    {galleryInput type="text" name="form.user.userName"}
	    {$form.user.userName}
	    {/galleryInput}

	    {gallerySelect name="form.user.permission" size="1"}
	    {html_options options=$allPermissions selected=$form.user.permission}
	    {/gallerySelect}

	    {galleryInput type="submit" name="form.action.addUserPermission"}
	    {galleryText text="Add Permission"}
	    {/galleryInput}
	  </td>
	</tr>

	<!-- {if !empty($form.error.user.invalidPermission)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The permission you chose is invalid"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.user.missingUser)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a user name"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.user.invalidUser)} -->
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The user name you entered is invalid"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

    </table>
    {/galleryForm}

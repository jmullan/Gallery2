    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditPermissions{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFont}
	    {galleryText text="Item Permissions"}
	    {/galleryBiggerFont}
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
	    {galleryBigFont}
	    {galleryText text="Group Permissions"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<!-- {if $groupPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {galleryText text="User name"}
		  <th> {galleryText text="Permission"}
		  <th> {galleryText text="Action"}
		</tr>

		<!-- {foreach from=$groupPermissions item=entry} -->
		<tr>
		  <td align="left">
		    {$entry.group.groupName}
		  </td>
		  <td align="left">
		    {$entry.permission.description}
		  </td>
		  <td align="left">
		    {if $entry.deleteable}
		    <a href="{galleryUrl controller=$controller
		                         itemId=$item.id
		                         form_action_delete=1
		                         form_group_id=$entry.group.id
		                         form_permission_id=$entry.permission.id}">
		      [{galleryText text="delete"}]
		    </a>
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		</tr>
		<!-- {/foreach} -->
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
	    {html_options options=$allPermissions}
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
	    {galleryBigFont}
	    {galleryText text="User Permissions"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<!-- {if $userPermissions} -->
	<tr>
	  <td>
	    <table border="1" cellspacing="0" cellpadding="3">
		<tr>
		  <th> {galleryText text="User name"}
		  <th> {galleryText text="Permission"}
		  <th> {galleryText text="Action"}
		</tr>

		<!-- {foreach from=$userPermissions item=entry} -->
		<tr>
		  <td align="left">
		    {$entry.user.userName}
		  </td>
		  <td align="left">
		    {$entry.permission.description}
		  </td>
		  <td align="left">
		    {if $entry.deleteable}
		    <a href="{galleryUrl controller=$controller
		                         itemId=$item.id
		                         form_action_delete=1
		                         form_user_id=$entry.user.id
		                         form_permission_id=$entry.permission.id}">
		      [{galleryText text="delete"}]
		    </a>
		    {else}
		    &nbsp;
		    {/if}
		  </td>
		</tr>
		<!-- {/foreach} -->
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
	    {html_options options=$allPermissions}
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

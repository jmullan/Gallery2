  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}AdminEditGroupUsers{/gallery->input}
  {gallery->input type="hidden" name="groupId"}{$group.id}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td colspan="2" align="center">
	{gallery->biggerFontSize}
	{gallery->text text="Add/Remove Group's Users"}
	{/gallery->biggerFontSize}
      </td>
    </tr>

    {if isset($form.status)}
    <tr>
      <td colspan="2" align="center">
	{gallery->lightFrame}
	<table width="100%" border="0">
	    <!-- {if isset($form.status.addedUser)} -->
	    <tr>
	      <td>
		{gallery->text text="Added user '%s' to group" arg1=$form.status.addedUser}
	      </td>
	    </tr>
	    <!-- {/if} -->

	    <!-- {if isset($form.status.removedUser)} -->
	    <tr>
	      <td>
		{gallery->text text="Removed user '%s' from group" arg1=$form.status.removedUser}
	      </td>
	    </tr>
	    <!-- {/if} -->
	</table>
	{/gallery->lightFrame}
      </td>
    </tr>
    {/if}

    <tr>
      <td align="center">
	{gallery->lightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->bigFontSize}
	      {gallery->text text="Editing Group '%s'"
	                   arg1=$group.groupName}
	      {/gallery->bigFontSize}
	    </td>
	  </tr>
	      
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->text one="This group contains %d user"
	                   many="This group contains %d users"
	                   count=$form.userCount
	                   arg1=$form.userCount}
	    </td>
	  </tr>

	  {if !empty($form.list.users)}
	  <tr>
	    <td align="right">
	      {gallery->select name="form.list.userId" size=1}
	      {html_options options=$form.list.users}
	      {/gallery->select}
	    </td>
	    <td align="left">
	      {gallery->input type="submit" name="form.action.remove"}
	      {gallery->text text="Remove"}
	      {/gallery->input}
	    </td>
	  </tr>

	  {if isset($form.error.list.noUserSelected)}
	  <tr>
	    <td align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="You must select a user to remove."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}
	  {/if}

	  <tr>
	    <td align="right">
	      {gallery->input type="text" name="form.text.userName"}{$form.text.userName}{/gallery->input}
	    </td>
	    <td align="left">
	      {gallery->input type="submit" name="form.action.add"}
	      {gallery->text text="Add"}
	      {/gallery->input}
	    </td>
	  </tr>

	  {if isset($form.error.text.userName.missing)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="You must enter a username."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if isset($form.error.text.userName.invalid)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="User '%s' does not exist."
	                   arg1=$form.text.userName}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  <tr>
	    <td colspan="2" align="center">
	      {gallery->input type="submit" name="form.action.done"}{gallery->text text="Done"}{/gallery->input}
	    </td>
	  </tr>

	</table>
	{/gallery->lightFrame}
      </td>
    </tr>
  </table>
  {/gallery->form}

  
  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="formName"}AdminEditGroupUsers{/gallery->input}
  {gallery->input type="hidden" name="form.groupId"}{$form.groupId}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td colspan="2" align="center">
	{gallery->biggerFontSize}
	{gallery->text text="Add/Remove Group's Users"}
	{/gallery->biggerFontSize}
      </td>
    </tr>

    <tr>
      <td align="center">
	{gallery->lightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->bigFontSize}
	      {gallery->text text="Editing Group '%s'"
	                   arg1=$form.groupName}
	      {/gallery->bigFontSize}
	    </td>
	  </tr>
	      
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->text one="This group contains %d user"
	                   many="This group contains %d users"
	                   count=$userCount
	                   arg1=$userCount}
	    </td>
	  </tr>

	  {if ($form.groupType == GROUP_SITE_ADMINS)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->warningFontColor}
	      {gallery->text text="Note: This is the site administrator group.  Any users you add to this group will have site-wide administrative privileges"}
	      {/gallery->warningFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if ($form.groupType == GROUP_ALL_USERS)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->text text="This group contains all Gallery users.  You cannot add or remove users from it."}
	    </td>
	  </tr>
	  {else}

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

	  {if isset($form.error.text.missingUserName)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="You must enter a username."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if isset($form.error.text.noSuchUser)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="User '%s' does not exist."
	                   arg1=$form.text.userName}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}
	  {/if}

	  <tr>
	    <td colspan="2" align="center">
	      {gallery->input type="submit" name="form.action.done"}{gallery->text text="Done"}{/gallery->input}
	    </td>
	  </tr>

	  {if !empty($userAdded)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->successFontColor}
	      {gallery->text text="Successfully added user '%s' to group."
	                   arg1=$userAdded}
	      {/gallery->successFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if !empty($userRemoved)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->successFontColor}
	      {gallery->text text="Successfully removed user '%s' from group."
	                   arg1=$userRemoved}
	      {/gallery->successFontColor}
	    </td>
	  </tr>
	  {/if}

	</table>
	{/gallery->lightFrame}
      </td>
    </tr>
  </table>
  {/gallery->form}

  
  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="formName"}AdminEditGroupUsers{/galleryInput}
  {galleryInput type="hidden" name="form.groupId"}{$form.groupId}{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td colspan="2" align="center">
	{galleryBiggerFont}
	{galleryText text="Add/Remove Group's Users"}
	{/galleryBiggerFont}
      </td>
    </tr>

    <tr>
      <td align="center">
	{galleryLightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td colspan="2" align="center">
	      {galleryBigFont}
	      {galleryText text="Editing Group '%s'"
	                   arg1=$form.groupName}
	      {/galleryBigFont}
	    </td>
	  </tr>
	      
	  <tr>
	    <td colspan="2" align="center">
	      {galleryText one="This group contains %d user"
	                   many="This group contains %d users"
	                   count=$userCount
	                   arg1=$userCount}
	    </td>
	  </tr>

	  {if ($form.groupType == GROUP_SITE_ADMINS)}
	  <tr>
	    <td colspan="2" align="center">
	      {galleryWarningFontColor}
	      {galleryText text="Note: This is the site administrator group.  Any users you add to this group will have site-wide administrative privileges"}
	      {/galleryWarningFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if ($form.groupType == GROUP_ALL_USERS)}
	  <tr>
	    <td colspan="2" align="center">
	      {galleryText text="This group contains all Gallery users.  You cannot add or remove users from it."}
	    </td>
	  </tr>
	  {else}

	  {if !empty($form.list.users)}
	  <tr>
	    <td align="right">
	      {gallerySelect name="form.list.userId" size=1}
	      {html_options options=$form['list']['users']}
	      {/gallerySelect}
	    </td>
	    <td align="left">
	      {galleryInput type="submit" name="form.action.remove"}
	      {galleryText text="Remove"}
	      {/galleryInput}
	    </td>
	  </tr>

	  {if isset($form.error.list.noUserSelected)}
	  <tr>
	    <td align="center">
	      {galleryErrorFontColor}
	      {galleryText text="You must select a user to remove."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  {/if}
	  {/if}

	  <tr>
	    <td align="right">
	      {galleryInput type="text" name="form.text.userName"}{$form.text.userName}{/galleryInput}
	    </td>
	    <td align="left">
	      {galleryInput type="submit" name="form.action.add"}
	      {galleryText text="Add"}
	      {/galleryInput}
	    </td>
	  </tr>

	  {if isset($form.error.text.missingUserName)}
	  <tr>
	    <td colspan="2" align="center">
	      {galleryErrorFontColor}
	      {galleryText text="You must enter a username."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if isset($form.error.text.noSuchUser)}
	  <tr>
	    <td colspan="2" align="center">
	      {galleryErrorFontColor}
	      {galleryText text="User '%s' does not exist."
	                   arg1=$form.text.userName}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  {/if}
	  {/if}

	  <tr>
	    <td colspan="2" align="center">
	      {galleryInput type="submit" name="form.action.done"}{galleryText text="Done"}{/galleryInput}
	    </td>
	  </tr>

	  {if !empty($userAdded)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallerySuccessFontColor}
	      {galleryText text="Successfully added user '%s' to group."
	                   arg1=$userAdded}
	      {/gallerySuccessFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if !empty($userRemoved)}
	  <tr>
	    <td colspan="2" align="center">
	      {gallerySuccessFontColor}
	      {galleryText text="Successfully removed user '%s' from group."
	                   arg1=$userRemoved}
	      {/gallerySuccessFontColor}
	    </td>
	  </tr>
	  {/if}

	</table>
	{/galleryLightFrame}
      </td>
    </tr>
  </table>
  {/galleryForm}

  
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
	      {galleryText text="Editting Group '%s'"
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
	      {galleryInput name="form.text.userName"}{$form.text.userName}{/galleryInput}
	    </td>
	    <td align="left">
	      {galleryInput type="submit" name="form.action.add"}
	      {galleryText text="Add"}
	      {/galleryInput}
	    </td>
	  </tr>

	  {if isset($form.error.list.missingUserName)}
	  <tr>
	    <td align="center">
	      {galleryErrorFontColor}
	      {galleryText text="You must enter a username."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if isset($form.error.list.noSuchUser)}
	  <tr>
	    <td align="center">
	      {galleryErrorFontColor}
	      {galleryText text="Username '%s' does not exist."
	                   arg1=$form.text.username}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
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

  
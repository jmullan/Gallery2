  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="form.groupId"}{$form.groupId}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Edit a group"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    {if $form.groupType == GROUP_ALL_USERS}
    <tr>
      <td colspan="2" align="center">
	{gallery->text text="This group contains all Gallery users.  You cannot add or remove users from it."}
      </td>
    </tr>
    {/if}

    {if $form.groupType == GROUP_SITE_ADMINS}
    <tr>
      <td colspan="2" align="center">
	{gallery->text text="This group contains all Gallery site administrators.  Any users you add to this group will have Gallery administrative privileges."}
      </td>
    </tr>
    {/if}

    <tr>
      <td align="right" width="40%">
	{gallery->text text="Group Name"}
      </td>
      <td width="60%">
	{gallery->input type="text" name="form.groupName"}{$form.groupName}{/gallery->input}
      </td>
    </tr>

    <tr>
      <td align="center" colspan="2">
	{gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	{gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  
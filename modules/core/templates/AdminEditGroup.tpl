  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="form.groupId"}{$form.groupId}{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{galleryBigFont}
	{galleryText text="Edit a group"}
	{/galleryBigFont}
      </td>
    </tr>

    {if $form.groupType == GROUP_ALL_USERS}
    <tr>
      <td colspan="2" align="center">
	{galleryText text="This group contains all Gallery users.  You cannot add or remove users from it."}
      </td>
    </tr>
    {/if}

    {if $form.groupType == GROUP_SITE_ADMINS}
    <tr>
      <td colspan="2" align="center">
	{galleryText text="This group contains all Gallery site administrators.  Any users you add to this group will have Gallery administrative privileges."}
      </td>
    </tr>
    {/if}

    <tr>
      <td align="right" width="40%">
	{galleryText text="Group Name"}
      </td>
      <td width="60%">
	{galleryInput name="form.groupName"}{$form.groupName}{/galleryInput}
      </td>
    </tr>

    <tr>
      <td align="center" colspan="2">
	{galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	{galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  
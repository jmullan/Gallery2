  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="groupId"}{$groupId}{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{galleryBigFont}
	{galleryText text="Delete a group"}
	{/galleryBigFont}
      </td>
    </tr>

    {if !$isAllAdmins && !$isAllUsers}
    <tr>
      <td align="center">
	{galleryText text="Do you really want to delete group '%s'?"
	             arg1=$groupName}
      </td>
    </tr>
    {/if}

    {if $isAllAdmins}
    <tr>
      <td align="center">
	{galleryErrorFontColor}
	{galleryText text="You cannot delete the 'all admins' group!"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    {if $isAllUsers}
    <tr>
      <td align="center">
	{galleryErrorFontColor}
	{galleryText text="You cannot delete the 'all users' group!"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{if !$isAllAdmins && !$isAllUsers}
	{galleryInput type="submit" name="form.action.delete"}{galleryText text="Delete"}{/galleryInput}
	{/if}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  
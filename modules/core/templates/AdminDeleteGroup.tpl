  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="groupId"}{$groupId}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Delete a group"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    {if !$isAllAdmins && !$isAllUsers}
    <tr>
      <td align="center">
	{gallery->text text="Do you really want to delete group '%s'?"
	             arg1=$groupName}
      </td>
    </tr>
    {/if}

    {if $isAllAdmins}
    <tr>
      <td align="center">
	{gallery->errorFontColor}
	{gallery->text text="You cannot delete the 'all admins' group!"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if $isAllUsers}
    <tr>
      <td align="center">
	{gallery->errorFontColor}
	{gallery->text text="You cannot delete the 'all users' group!"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{if !$isAllAdmins && !$isAllUsers}
	{gallery->input type="submit" name="form.action.delete"}{gallery->text text="Delete"}{/gallery->input}
	{/if}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  
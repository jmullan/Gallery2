  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="formName"}AdminDeleteUser{/gallery->input}
  {gallery->input type="hidden" name="form.userId"}{$form.userId}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Delete a user"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    <tr>
      <td align="center">
	{gallery->text text="Do you really want to delete user '%s'?"
	             arg1=$form.userName}
      </td>
    </tr>

    <tr>
      <td align="center" colspan="2">
	{gallery->input type="submit" name="form.action.delete"}{gallery->text text="Delete"}{/gallery->input}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  
  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}AdminEditGroup{/gallery->input}
  {gallery->input type="hidden" name="groupId"}{$group.id}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Edit a group"}
	{/gallery->bigFontSize}
      </td>
    </tr>

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

  
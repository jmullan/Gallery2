  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="formName"}AdminCreateGroup{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2"}
	{gallery->bigFontSize}
	{gallery->text text="Create a new group"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{gallery->text text="Group Name"}
      </td>
      <td width="60%">
	{gallery->input type="text" name="form.groupName"}{$form.groupName}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>

    {if isset($form.error.groupName.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter a name"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if isset($form.error.groupName.exists)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="Group '%s' already exists"
	             arg1=$form.groupName}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{gallery->input type="submit" name="form.action.create"}{gallery->text text="Create Group"}{/gallery->input}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  
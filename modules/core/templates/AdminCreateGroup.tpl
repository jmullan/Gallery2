  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="formName"}AdminCreateGroup{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2"}
	{galleryBigFont}
	{galleryText text="Create a new group"}
	{/galleryBigFont}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{galleryText text="Group Name"}
      </td>
      <td width="60%">
	{galleryInput name="form.groupName"}{$form.groupName}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>

    {if isset($form.error.groupName.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="You must enter a name"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    {if isset($form.error.groupName.exists)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="Group '%s' already exists"
	             arg1=$form.groupName}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{galleryInput type="submit" name="form.action.create"}{galleryText text="Create Group"}{/galleryInput}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  
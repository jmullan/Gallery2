  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="userid"}{$userid}{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{galleryBigFontSize}
	{galleryText text="Delete a user"}
	{/galleryBigFontSize}
      </td>
    </tr>

    {if !$isSelf && !$isAnonymous}
    <tr>
      <td align="center">
	{galleryText text="Do you really want to delete user '%s'?"
	             arg1=$username}
      </td>
    </tr>
    {/if}

    {if $isSelf}
    <tr>
      <td align="center">
	{galleryErrorFontColor}
	{galleryText text="You cannot delete yourself!"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    {if $isAnonymous}
    <tr>
      <td align="center">
	{galleryErrorFontColor}
	{galleryText text="You cannot delete the anonymous user!"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{if !$isSelf && !$isAnonymous}
	{galleryInput type="submit" name="form.action.delete"}{galleryText text="Delete"}{/galleryInput}
	{/if}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  
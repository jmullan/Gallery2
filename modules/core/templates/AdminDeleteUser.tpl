  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="userid"}{$userid}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Delete a user"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    {if !$isSelf && !$isAnonymous}
    <tr>
      <td align="center">
	{gallery->text text="Do you really want to delete user '%s'?"
	             arg1=$username}
      </td>
    </tr>
    {/if}

    {if $isSelf}
    <tr>
      <td align="center">
	{gallery->errorFontColor}
	{gallery->text text="You cannot delete yourself!"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if $isAnonymous}
    <tr>
      <td align="center">
	{gallery->errorFontColor}
	{gallery->text text="You cannot delete the anonymous user!"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{if !$isSelf && !$isAnonymous}
	{gallery->input type="submit" name="form.action.delete"}{gallery->text text="Delete"}{/gallery->input}
	{/if}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  
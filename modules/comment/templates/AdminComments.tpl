  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="formName"}AdminComments{/galleryInput}
  <table border="1" cellspacing="0" cellpadding="0" width="100%">

    <tr>
      <td colspan="2" align="center">
	{galleryBiggerFont}{galleryText text="Comments Settings"}{/galleryBiggerFont}
      </td>
    </tr>

    {if ($needsConfiguration)}
    <tr>
      <td align="center">
	{galleryText text="This module must be successfully configured before you can activate it"}
	<br>
	{galleryInput type="submit" name="configure"}{galleryText text="Configure"}{/galleryInput}
      </td>
    </tr>
    {/if}
  </table>
  {/galleryForm}
  

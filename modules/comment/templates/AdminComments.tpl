  {galleryForm controller="$controller"}
  <table border="1" cellspacing="0" cellpadding="0" width="100%">

    <tr>
      <td colspan="2" align="center">
	<h2>{galleryText text="Comments Settings"}</h2>
      </td>
    </tr>

    {if ($needsConfiguration)}
    <tr>
      <td align="center">
	{galleryText text="This module must be successfully configured before you can activate it"}
      </td
    </tr>
    {/if}

    <tr>
      <td align="center">
	<input type="submit" name="{galleryFormVar var=configure}" value="{galleryText text="Configure"}">
      </td>
    </tr>
  </table>
  {/galleryForm}
  

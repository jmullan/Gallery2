      {galleryForm controller=$controller}
      {galleryInput type="hidden" name="formName"}ItemMakeHighlight{/galleryInput}
      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      
    <table border="0" cellspacing="0" cellpadding="5">
	<tr>
	  <td align="center">
	    {galleryBigFontSize}
	    {galleryText text="Do you want to make this item the highlight of its album?"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td align="center">
	    {galleryInput type="submit" name="form.action.makeHighlight"}{galleryText text="Yes, this is the highlight!"}{/galleryInput}
	  </td>
	</tr>
    </table>
    {/galleryForm}

      {galleryForm controller=$controller}
      {galleryInput type="hidden" name="formName"}ItemMakeHighlight{/galleryInput}
      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      
    <table border="0" cellspacing="0" cellpadding="5">
	<tr>
	  <td align="center">
	    {galleryBigFontSize}
	    {galleryText text="Do you want to make this item the highlight of its parent album?"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Each album can have a thumbnail image that is representative of its contents.  This is called the <i>highlight image</i>.  You can select this item's thumbnail to be the album's highlight image."}
	  </td>
	</tr>

	<tr>
	  <td align="center">
	    {galleryInput type="submit" name="form.action.makeHighlight"}{galleryText text="Yes, make this item the highlight!"}{/galleryInput}
	  </td>
	</tr>
    </table>
    {/galleryForm}

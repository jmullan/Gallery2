      {gallery->form controller=$controller}
      {gallery->input type="hidden" name="formName"}ItemMakeHighlight{/gallery->input}
      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
      
    <table border="0" cellspacing="0" cellpadding="5">
	<tr>
	  <td align="center">
	    {gallery->bigFontSize}
	    {gallery->text text="Do you want to make this item the highlight of its parent album?"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Each album can have a thumbnail image that is representative of its contents.  This is called the <i>highlight image</i>.  You can select this item's thumbnail to be the album's highlight image."}
	  </td>
	</tr>

	<tr>
	  <td align="center">
	    {gallery->input type="submit" name="form.action.makeHighlight"}{gallery->text text="Yes, make this item the highlight!"}{/gallery->input}
	  </td>
	</tr>
    </table>
    {/gallery->form}

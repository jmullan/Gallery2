      {gallery->form controller=$controller}
      {gallery->input type="hidden" name="form.formName"}ItemDelete{/gallery->input}
      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
      
    <table border="0" cellspacing="0" cellpadding="5">
	<tr>
	  <td align="center">
	    {gallery->bigFontSize}
	    {gallery->text text="Do you really want to delete this item?"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<!-- {if ($childCount > 0)} -->
	<tr>
	  <td>
	    {gallery->text one="This item has %d child."
	                 many="This item has %d children."
	                 count=$childCount
	                 arg1=$childCount}
	    {gallery->text text="If you delete it, all of its children and any related data will be deleted also!"}
	  </td>
	</tr>
        <!-- {/if} -->

	<tr>
	  <td align="center">
	    {gallery->input type="submit" name="form.action.delete"}{gallery->text text="Yes, delete it!"}{/gallery->input}
	  </td>
	</tr>
    </table>
    {/gallery->form}
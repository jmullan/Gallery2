      {galleryForm controller=$controller}
      {galleryInput type="hidden" name="formName"}ItemDelete{/galleryInput}
      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      
    <table border="0" cellspacing="0" cellpadding="5">
	<tr>
	  <td align="center">
	    {galleryBigFontSize}
	    {galleryText text="Do you really want to delete this item?"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<!-- {if ($childCount > 0)} -->
	<tr>
	  <td>
	    {galleryText one="This item has %d child."
	                 many="This item has %d children."
	                 count=$childCount
	                 arg1=$childCount}
	    {galleryText text="If you delete it, all of its children and any related data will be deleted also!"}
	  </td>
	</tr>
        <!-- {/if} -->

	<tr>
	  <td align="center">
	    {galleryInput type="submit" name="form.action.delete"}{galleryText text="Yes, delete it!"}{/galleryInput}
	  </td>
	</tr>
    </table>
    {/galleryForm}
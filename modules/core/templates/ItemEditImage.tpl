    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditImage{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFont}
	    {galleryText text="Edit Image"}
	    {/galleryBiggerFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Rotate"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The title can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type=text size=40 name="form.title"}{$form.title}{/galleryInput}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	   {galleryInput type=checkbox name="form.preserveOriginal"}{$form.preserveOriginal}{/galleryInput} {galleryText text="Preserve Original Version"}
	   <br>
	   {galleryText text="Certain image manipulation operations (such as resizing and scaling) can permanently change 
Gallery avoids modifying the original images that you upload to it.  Some operations can cause you to 
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	    {galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	  </td>
	</tr>

    </table>
    {/galleryForm}

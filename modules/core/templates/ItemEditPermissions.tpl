    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditPermissions{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td colspan="3" align="center">
	    {galleryBiggerFont}
	    {galleryText text="Item Permissions"}
	    {/galleryBiggerFont}
	  </td>
	</tr>

	<tr>
	  <td colspan="3">
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="3">
	    {galleryErrorFontColor}
	    {galleryText text="This is a work in progress.  Move along"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Users"}
	    {/galleryBigFont}
	  </td>
	  
	  <td>
	    {galleryBigFont}
	    {galleryText text="Groups"}
	    {/galleryBigFont}
	  </td>
	  
	  <td>
	    {galleryBigFont}
	    {galleryText text="Permissions"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    <select size=15>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	    </select>
	  </td>

	  <td>
	    <select size=15>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	    </select>
	  </td>

	  <td>
	    <select size=15>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	      <option> foo bar baz </option>
	    </select>
	  </td>
	</tr>

	<tr>
	  <td colspan="3">
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="3">
	    {galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	    {galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	  </td>
	</tr>

    </table>
    {/galleryForm}

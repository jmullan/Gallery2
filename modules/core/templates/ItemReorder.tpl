      {gallery->form controller="$controller"}
      {gallery->input type="hidden" name="form.formName"}ItemReorder{/gallery->input}
      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Reorder Album"}
	      {/gallery->biggerFontSize}
	    </center>
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="You can change the order of the items in this album."}
	  </td>
	</tr>

        <tr>
          <td>
	    &nbsp;
          </td>
        </tr>

	<tr>
	  <td>
	    {gallery->text text="Move this item:"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->select name="form.selectedId"}
	    {foreach from=$peers item=item}
	    <option value="{$item.id}"> {$item.title|default:$item.pathComponent}
	    {/foreach}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->select name="form.placement"}
	    <option value="before"> {gallery->text text="before this item:"}
	    <option value="after"> {gallery->text text="after this item:"}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->select name="form.targetId"}
	    {foreach from=$peers item=item}
	    <option value="{$item.id}"> {$item.title|default:$item.pathComponent}
	    {/foreach}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.reorder"}{gallery->text text="Reorder"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	  </td>
	</tr>

    </table>
    {/gallery->form}

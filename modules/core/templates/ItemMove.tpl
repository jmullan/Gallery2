    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="formName"}ItemMove{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$itemId}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Move an Item"}
	      {/gallery->biggerFontSize}
	    </center>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Items to move"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Choose the items you want to move"}
	  </td>
	</tr>

	<tr>
	  <td>
	    <table>
	    {foreach from=$peers item=item}
	    {assign var="peerItemId" value=$item.id}
		<tr>
		<td>
		 {gallery->input type="checkbox" name="form.selectedIds.$peerItemId"}{if $item.selected}Checked{/if}{/gallery->input}
		</td>
		<td>
		 {if $item.title}
		  {$item.title}
		 {else}
		  {$item.pathComponent}
		 {/if}
		 {if $item.type == "album"}
		  ({gallery->text text="Album"})
		 {else}
		  ({gallery->text text="Item"})
		 {/if}
		</td>

		<td>
		{if !empty($form.error.source.$peerItemId.permission.deleteSource)}
		  {gallery->errorFontColor}
		  {gallery->text text="You are not allowed to move this item away from here."}<br>
		  {/gallery->errorFontColor}
		{/if}

		{if !empty($form.error.source.$peerItemId.permission.addAlbum)}
		  {gallery->errorFontColor}
		  {gallery->text text="You are not allowed to move an album to the chosen destination."}<br>
		  {/gallery->errorFontColor}
		{/if}

		{if !empty($form.error.source.$peerItemId.permission.addItem)}
		  {gallery->errorFontColor}
		  {gallery->text text="You are not allowed to move an item to the chosen destination."}<br>
		  {/gallery->errorFontColor}
		{/if}

		{if !empty($form.error.source.$peerItemId.selfMove)}
		  {gallery->errorFontColor}
		  {gallery->text text="You cannot move an album into its own subtree."}<br>
		  {/gallery->errorFontColor}
		{/if}
		</td>

		</tr>
	    {/foreach}
	    </table>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Destination"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Choose the destination of the selected items"}
	  </td>
	</tr>

	<tr>
	  <td>
	    <table>
	    <tr>
	    <td>
	    {gallery->select name="form.destination"}
	    {foreach from=$destinations item=album}
	    <option value="{$album.id}" {if $album.id == $form.destination}SELECTED{/if}>
	    {"&nbsp;&nbsp;&nbsp;"|repeat:$album.level}{$album.title}
	    </option>
	    {/foreach}
	    {/gallery->select}
	    </td>
	    </tr>
	    </table>
	  </td>
	</tr>

	{if !empty($form.error.destination.permission)}
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You don't have the permission to add items in this album"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	{/if}

	{if !empty($form.error.destination.empty)}
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="No destination chosen"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	{/if}

	<tr>
	  <td>
	  
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.move"}{gallery->text text="Move"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	  </td>
	</tr>

    </table>
    {/gallery->form}

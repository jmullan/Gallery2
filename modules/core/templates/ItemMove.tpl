    <script type="text/javascript" language="javascript">
      // Validation code.  This Javascript snippet validates the source and destination
      // information to make sure that you don't attempt to do something that you shouldn't,
      // ie, it will help you to avoid the situation where you try to move an item into
      // an album where you don't have the right permissions.  This is only a hint to the
      // UI -- we perform the same permission checks on the server side (so circumventing
      // or disabling this javascript won't allow you to do something that you don't have
      // permission to do anyway).
      
      // The user can add data items to these albums
      permission = new Array();
      permission['addDataItem'] = new Array();
      {foreach from=$albumIds.addDataItem item=id}
      permission['addDataItem'][{$id}] = 1;
      {/foreach}
      
      // The user can add album items to these albums
      permission['addAlbumItem'] = new Array();
      {foreach from=$albumIds.addAlbumItem item=id}
      permission['addAlbumItem'][{$id}] = 1;
      {/foreach}

      // Check what the destination album accepts.  If it can handle data items and
      // album items then we're done.  Else, scan the selected items and make sure that
      // we haven't selected something that we can't handle.  If we have, then remove
      // the selection and alert the user.
      function checkPermissions(form, quiet) {ldelim}
          destinationId = form.elements['{gallery->elementName name="form.destination"}'].value;
          if (permission['addDataItem'][destinationId] && permission['addAlbumItem'][destinationId]) {ldelim}
              {foreach from=$peerTypes.album key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              {foreach from=$peerTypes.data key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              return;
          {rdelim}

          changed = 0;
          if (permission['addDataItem'][destinationId]) {ldelim}
              {foreach from=$peerTypes.album key=id item=unused}
              if (form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked) {ldelim}
                  form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked = 0;
                  changed = 1;
              {rdelim}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 1;
              {/foreach}
              {foreach from=$peerTypes.data key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              if (changed && !quiet) {ldelim}
                  alert("{gallery->text text="The destination you chose does not accept sub-albums, so all sub-albums have been deselected."}");
              {rdelim}
          {rdelim} else {ldelim}
              {foreach from=$peerTypes.data key=id item=unused}
              if (form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked) {ldelim}
                  form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked = 0;
                  changed = 1;
              {rdelim}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 1;
              {/foreach}
              {foreach from=$peerTypes.album key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              if (changed && !quiet) {ldelim}
                  alert("{gallery->text text="The destination you chose only accepts sub-albums, so all non-albums have been deselected."}");
              {rdelim}
          {rdelim}
      {rdelim}
    </script>
    
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
	      <!-- {foreach from=$peers item=item} -->
	      <!-- {assign var="peerItemId" value=$item.id} -->
		<tr>
		  <td>
		    {gallery->input type="checkbox" name="form.selectedIds.$peerItemId"}{$item.selected}{/gallery->input}
		  </td>
		  <td>
		    {if $item.title}
		    {$item.title}
		    {else}
		    {$item.pathComponent}
		    {/if}
		    <i>
		      {if isset($peerTypes.data.$peerItemId)}
		      {gallery->text text="(data)"}
		      {/if}
		      {if isset($peerTypes.album.$peerItemId)}
		      {gallery->text text="(album)"}
		      {/if}
		    </i>
		  </td>
		</tr>

		<!-- {if !empty($form.error.source.$peerItemId.permission.delete)} -->
		<tr>
		  <td colspan="2">
		    {gallery->errorFontColor}
		    {gallery->text text="You are not allowed to move this item away from here."}<br>
		    {/gallery->errorFontColor}
		  </td>
		</tr>
		<!-- {/if} -->

		<!-- {if !empty($form.error.source.$peerItemId.permission.addAlbumItem)} -->
		<tr>
		  <td colspan="2">
		    {gallery->errorFontColor}
		    {gallery->text text="You are not allowed to move an album to the chosen destination."}<br>
		    {/gallery->errorFontColor}
		  </td>
		</tr>
		<!-- {/if} -->

		<!-- {if !empty($form.error.source.$peerItemId.permission.addDataItem)} -->
		<tr>
		  <td colspan="2">
		    {gallery->errorFontColor}
		    {gallery->text text="You are not allowed to move an item to the chosen destination."}<br>
		    {/gallery->errorFontColor}
		  </td>
		</tr>
		<!-- {/if} -->

		<!-- {if !empty($form.error.source.$peerItemId.selfMove)} -->
		<tr>
		  <td colspan="2">
		    {gallery->errorFontColor}
		    {gallery->text text="You cannot move an album into its own subtree."}<br>
		    {/gallery->errorFontColor}
		  </td>
		</tr>
		<!-- {/if} -->
		<!-- {/foreach} -->
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
		    {gallery->select name="form.destination" onChange="javascript:checkPermissions(this.form)"}
		    {foreach from=$albumTree item=album}
		    <option value="{$album.data.id}">
		      {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
		      {$album.data.title|default:$album.data.pathComponent}
		    </option>
		    {/foreach}
		    {/gallery->select}
		  </td>
		</tr>
	    </table>
	  </td>
	</tr>

	<!-- {if !empty($form.error.destination.permission)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You don't have the permission to add items in this album"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.destination.empty)} -->
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="No destination chosen"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

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

    <script type="text/javascript" language="javascript">
      checkPermissions(document.forms[0], true);
    </script>
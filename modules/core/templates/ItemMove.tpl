{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Move an Item"}
  {/gallery->title}
{/gallery->bannerbox}
    
{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Source"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="Choose the items you want to move"}
  {/gallery->description}
      
  {gallery->body}
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
      {foreach from=$ItemMove.albumIds.addDataItem item=id}
      permission['addDataItem'][{$id}] = 1;
      {/foreach}
      
      // The user can add album items to these albums
      permission['addAlbumItem'] = new Array();
      {foreach from=$ItemMove.albumIds.addAlbumItem item=id}
      permission['addAlbumItem'][{$id}] = 1;
      {/foreach}
    
      // Check what the destination album accepts.  If it can handle data items and
      // album items then we're done.  Else, scan the selected items and make sure that
      // we haven't selected something that we can't handle.  If we have, then remove
      // the selection and alert the user.
      function checkPermissions(form, quiet) {ldelim}
          destinationId = form.elements['{gallery->elementName name="form.destination"}'].value;
          if (permission['addDataItem'][destinationId] && permission['addAlbumItem'][destinationId]) {ldelim}
              {foreach from=$ItemMove.peerTypes.album key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              {foreach from=$ItemMove.peerTypes.data key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              return;
          {rdelim}
    
          changed = 0;
          if (permission['addDataItem'][destinationId]) {ldelim}
              {foreach from=$ItemMove.peerTypes.album key=id item=unused}
              if (form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked) {ldelim}
                  form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked = 0;
                  changed = 1;
              {rdelim}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 1;
              {/foreach}
              {foreach from=$ItemMove.peerTypes.data key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              if (changed && !quiet) {ldelim}
                  alert("{gallery->text text="The destination you chose does not accept sub-albums, so all sub-albums have been deselected."}");
              {rdelim}
          {rdelim} else {ldelim}
              {foreach from=$ItemMove.peerTypes.data key=id item=unused}
              if (form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked) {ldelim}
                  form.elements['{gallery->elementName name="form.selectedIds.$id"}'].checked = 0;
                  changed = 1;
              {rdelim}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 1;
              {/foreach}
              {foreach from=$ItemMove.peerTypes.album key=id item=unused}
              form.elements['{gallery->elementName name="form.selectedIds.$id"}'].disabled = 0;
              {/foreach}
              if (changed && !quiet) {ldelim}
                  alert("{gallery->text text="The destination you chose only accepts sub-albums, so all non-albums have been deselected."}");
              {rdelim}
          {rdelim}
      {rdelim}
    </script>
    
    {gallery->widget1box}
      {foreach from=$ItemMove.peers item=peer}
	{assign var="peerItemId" value=$peer.id}
	    
	{gallery->widget1}
	  {gallery->body}
	    {gallery->input type="checkbox" name="form.selectedIds.$peerItemId"}{$peer.selected}{/gallery->input}
	    {$peer.title|default:$peer.pathComponent}
	    {if isset($ItemMove.peerTypes.data.$peerItemId)}
	      {gallery->text text="(data)"}
	    {/if}
	    {if isset($ItemMove.peerTypes.album.$peerItemId)}
	      {gallery->text text="(album)"}
	    {/if}
	    
	    {if !empty($form.error.source.$peerItemId.permission.delete)}
	      {gallery->error}
		{gallery->text text="You are not allowed to move this item away from here."}<br>
	      {/gallery->error}
	    {/if}
	    
	    {if !empty($form.error.source.$peerItemId.permission.addAlbumItem)}
	      {gallery->error}
		{gallery->text text="You are not allowed to move an album to the chosen destination."}<br>
	      {/gallery->error}
	    {/if}

	    {if !empty($form.error.source.$peerItemId.permission.addDataItem)}
	      {gallery->error}
		{gallery->text text="You are not allowed to move an item to the chosen destination."}<br>
	      {/gallery->error}
	    {/if}
	    
	    {if !empty($form.error.source.$peerItemId.selfMove)}
	      {gallery->error}
		{gallery->text text="You cannot move an album into its own subtree."}<br>
	      {/gallery->error}
	    {/if}
	  {/gallery->body}
	{/gallery->widget1}
      {/foreach}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Destination"}
  {/gallery->title}
  
  {gallery->description}
    {gallery->text text="Choose a new album for them"}
  {/gallery->description}
  
  {gallery->body}
    {gallery->select name="form.destination" onChange="javascript:checkPermissions(this.form)"}
      {foreach from=$ItemMove.albumTree item=album}
	<option value="{$album.data.id}">
	{"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
	{$album.data.title|default:$album.data.pathComponent}
	</option>
      {/foreach}
    {/gallery->select}
    
    {if !empty($form.error.destination.permission)}
      {gallery->error}
	{gallery->text text="You don't have the permission to add items in this album"}
      {/gallery->error}
    {/if}
    
    {if !empty($form.error.destination.empty)}
      {gallery->error}
	{gallery->text text="No destination chosen"}
      {/gallery->error}
    {/if}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.move"}{gallery->text text="Move"}{/gallery->input}
    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

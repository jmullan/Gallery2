{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Move an Item"}
    {/g->title}
  {/g->banner}

  {if (isset($status))}
    {g->success}
      {g->text one="Successfully moved %d item"
               many="Successfully moved %d items" 
               count=$status.moved.count
               arg1=$status.moved.count}
    {/g->success}
  {/if}

  {if !empty($ItemMove.peers)}
    {g->box style="admin"}
      {g->title}
	{g->text text="Source"}
      {/g->title}
      
      {g->description}
	{g->text text="Choose the items you want to move"}
      {/g->description}
      
      {g->element}
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
	      destinationId = form.elements['{g->elementName name="form[destination]"}'].value;
	      if (permission['addDataItem'][destinationId] && permission['addAlbumItem'][destinationId]) {ldelim}
		  {foreach from=$ItemMove.peerTypes.album key=id item=unused}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 0;
		  {/foreach}
		  {foreach from=$ItemMove.peerTypes.data key=id item=unused}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 0;
		  {/foreach}
		  return;
	      {rdelim}

	      changed = 0;
	      if (permission['addDataItem'][destinationId]) {ldelim}
		  {foreach from=$ItemMove.peerTypes.album key=id item=unused}
		  if (form.elements['{g->elementName name="form[selectedIds][$id]"}'].checked) {ldelim}
		      form.elements['{g->elementName name="form[selectedIds][$id]"}'].checked = 0;
		      changed = 1;
		  {rdelim}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 1;
		  {/foreach}
		  {foreach from=$ItemMove.peerTypes.data key=id item=unused}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 0;
		  {/foreach}
		  if (changed && !quiet) {ldelim}
		      alert("{g->text text="The destination you chose does not accept sub-albums, so all sub-albums have been deselected."}");
		  {rdelim}
	      {rdelim} else {ldelim}
		  {foreach from=$ItemMove.peerTypes.data key=id item=unused}
		  if (form.elements['{g->elementName name="form[selectedIds][$id]"}'].checked) {ldelim}
		      form.elements['{g->elementName name="form[selectedIds][$id]"}'].checked = 0;
		      changed = 1;
		  {rdelim}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 1;
		  {/foreach}
		  {foreach from=$ItemMove.peerTypes.album key=id item=unused}
		  form.elements['{g->elementName name="form[selectedIds][$id]"}'].disabled = 0;
		  {/foreach}
		  if (changed && !quiet) {ldelim}
		      alert("{g->text text="The destination you chose only accepts sub-albums, so all non-albums have been deselected."}");
		  {rdelim}
	      {rdelim}
	  {rdelim}
	</script>
      {/g->element}
      
      {foreach from=$ItemMove.peers item=peer}
	{assign var="peerItemId" value=$peer.id}
	{g->element}
  	  {g->input type="checkbox" name="form[selectedIds][$peerItemId]"}{$peer.selected}{/g->input}
  	  {$peer.title|default:$peer.pathComponent}
  	  {if isset($ItemMove.peerTypes.data.$peerItemId)}
  	    {g->text text="(data)"}
  	  {/if}
  	  {if isset($ItemMove.peerTypes.album.$peerItemId)}
  	    {g->text text="(album)"}
  	  {/if}
	{/g->element}

	{if !empty($form.error.source.$peerItemId.permission.delete)}
  	  {g->error}
  	    {g->text text="You are not allowed to move this item away from here."}<br>
  	  {/g->error}
	{/if}
	
	{if !empty($form.error.source.$peerItemId.permission.addAlbumItem)}
  	  {g->error}
  	    {g->text text="You are not allowed to move an album to the chosen destination."}<br>
  	  {/g->error}
	{/if}
	
	{if !empty($form.error.source.$peerItemId.permission.addDataItem)}
  	  {g->error}
  	    {g->text text="You are not allowed to move an item to the chosen destination."}<br>
  	  {/g->error}
	{/if}
	
	{if !empty($form.error.source.$peerItemId.selfMove)}
  	  {g->error}
  	    {g->text text="You cannot move an album into its own subtree."}<br>
  	  {/g->error}
	{/if}
      {/foreach}
    {/g->box}
    
    {g->box style="admin"}
      {g->title}
	{g->text text="Destination"}
      {/g->title}
      
      {g->description}
	{g->text text="Choose a new album for them"}
      {/g->description}
      
      {g->element}
	{g->select name="form[destination]" onChange="javascript:checkPermissions(this.form)"}
          {foreach from=$ItemMove.albumTree item=album}
  	    <option value="{$album.data.id}">
  	    {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
  	    {$album.data.title|default:$album.data.pathComponent}
  	    </option>
          {/foreach}
	{/g->select}
      {/g->element}
      
      {if !empty($form.error.destination.permission)}
	{g->error}
  	  {g->text text="You don't have the permission to add items in this album"}
	{/g->error}
      {/if}
      
      {if !empty($form.error.destination.empty)}
	{g->error}
  	  {g->text text="No destination chosen"}
	{/g->error}
      {/if}
    {/g->box}
    
    {g->box style="admin"}
      {g->element}
	{g->input type="submit" name="form[action][move]"}{g->text text="Move"}{/g->input}
	{g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
      {/g->element}
    {/g->box}
  {else}
    {g->box style="admin"}
      {g->description}
	{g->text text="This album contains no items to move."}
      {/g->description}
    {/g->box}
  {/if}
{/g->pagebox}
  
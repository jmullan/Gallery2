{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Confirm Migration"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Users to import"}
    {/g->title}
    {if isset($form.migrateUser)}
     {g->element}
       {foreach from=$form.migrateUser key=uid item=junk}
	 {$ConfirmImport.uids.$uid} &nbsp;
	 {g->input type="hidden" name="form.migrateUser.$uid"}1{/g->input}
       {/foreach}
     {/g->element}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Albums to import"}
    {/g->title}

    {g->element}
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
	    {g->text text="Album Name"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Album Title"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Album Already Exists"}
	  {/g->column}
	{/g->row}

	{foreach from=$form.sourceAlbums item=albumName}
	  {g->row}
	    {g->column width="25%"}
	      {$albumName}
	      {g->input type="hidden" name="form.sourceAlbums.$albumName"}1{/g->input}
	    {/g->column}
	    {g->column}
	      {$ConfirmImport.albums.$albumName.title}
	    {/g->column}
	    {g->column}
              {if ($ConfirmImport.existingAlbums.$albumName)> 0}
		Exists
	      {/if}
            {/g->column}
	  {/g->row}
	{/foreach}
      {/g->table}
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
            Top level albums and albums whose parents are not
            selected will be imported into this album:
          {/g->column}
        {/g->row}
	{g->row}
	  {g->column}
            {$ConfirmImport.targetAlbum->_title}:
            {$ConfirmImport.targetAlbum->_description}
            {g->input type="hidden" name="form.destinationAlbumID"}{$ConfirmImport.destinationAlbumID}{/g->input}
	  {/g->column}
        {/g->row}
      {/g->table}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="hidden" name="albumsPath"}{$ConfirmImport.albumsPath}{/g->input}
      {g->input type="submit" name="form.action.import"}{g->text text="Import"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

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
	 {g->input type="hidden" name="form[migrateUser][$uid]"}1{/g->input}
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
	    {g->text text="Album Notes"}
	  {/g->column}
	{/g->row}
	{foreach from=$form.sourceAlbums item=albumName}
	  {g->row}
	    {g->column width="25%"}
	      {$ConfirmImport.urlDecoded.$albumName}
	      {g->input type="hidden" name="form[sourceAlbums][$albumName]"}1{/g->input}
	    {/g->column}
	    {g->column}
	      {$ConfirmImport.titles.$albumName}
	    {/g->column}
	    {g->column}
	      <p>
              {if ($ConfirmImport.existingAlbums.$albumName)> 0}
		{g->text text="An album already exists with this name.  This album will be renamed."}<br />
	      {/if}
	      {if ($ConfirmImport.illegalAlbumNames.$albumName) != ''}
		{g->text text="This album has an illegal name and will be renamed: "}{$ConfirmImport.illegalAlbumNames.$albumName}<br />
	      {/if}
	      {if (!$ConfirmImport.albumValidOwner.$albumName)}
                {g->text text="This album's owner hasn't been imported"}
              {/if}
	      </p>
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
            {g->input type="hidden" name="form[destinationAlbumID]"}{$ConfirmImport.destinationAlbumID}{/g->input}
	  {/g->column}
        {/g->row}
      {/g->table}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="hidden" name="albumsPath"}{$ConfirmImport.albumsPath}{/g->input}
      {g->input type="submit" name="form[action][import]"}{g->text text="Import"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

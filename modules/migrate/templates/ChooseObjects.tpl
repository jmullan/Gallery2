{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Select Albums and Users"}
    {/g->title}
  {/g->banner}

  {if isset($form.error.nothingSelected)}
    {g->error}
      {g->text text="You must choose something to import!"}
    {/g->error}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Import Users"}
    {/g->title}

    {g->description}
      {g->text text="Select the users to migrate"}
    {/g->description}

    {if (sizeof($ChooseObjects.newUsers) > 0)} 
      {g->table style="admin_listing" evenodd="true"}
	{g->row}
	  {g->column header="true"}
	    {g->text text="Select"}
	  {/g->column}
	  {g->column header="true"}
	    {g->text text="Username"}
	  {/g->column}
	{/g->row}

	{foreach key=uid item=username from=$ChooseObjects.newUsers}
	  {g->row}
	    {g->column width="10%"}
              {g->input type="checkbox" name=form.migrateUser.$uid}{$form.migrateUser.$uid}{/g->input}
	    {/g->column}
	    {g->column}
              {$username}
	    {/g->column}
	  {/g->row}
	{/foreach}
      {/g->table}
    {else}
      {g->element style="emphasized"}
	{g->text text="No available users"}
      {/g->element}
    {/if}

    {if sizeof($ChooseObjects.existingUsers) > 0}
      {g->element}
	{g->text text="These users are already in your gallery, and will not be imported:"}
      {/g->element}

      {g->element}
	{foreach key=uid item=username from=$ChooseObjects.existingUsers}
          {$username} 
	{/foreach}
      {/g->element}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Import Albums"}
    {/g->title}

    {g->description}
      {g->text text="Select the albums to migrate"}
    {/g->description}

    {g->element style="emphasized"}
      Note: album migration is not yet implemented!
    {/g->element}

    {g->element style="emphasized"}
      {g->text text="Source:"}
    {/g->element}

    {g->element}
      {g->select multiple="true" size="10" name="form.sourceAlbums[]"}
        {foreach from=$ChooseObjects.g1AlbumTree item=album}
  	  <option value="{$album.data.name}">
  	  {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
  	  {g->text text="%s (%s)" arg1=$album.data.title arg2=$album.data.name}
  	  </option>
        {/foreach}
      {/g->select}
    {/g->element}

    {g->element style="emphasized"}
      {g->text text="Destination:"}
    {/g->element}

    {g->element}
      {g->select name="form.destinationAlbum"}
        {foreach from=$ChooseObjects.g2AlbumTree item=album}
  	  <option value="{$album.data.id}">
  	  {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
  	  {$album.data.title|default:$album.data.pathComponent}
  	  </option>
        {/foreach}
      {/g->select}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="hidden" name="albumsPath"}{$ChooseObjects.albumsPath}{/g->input}
      {g->input type="submit" name="form.action.import"}
	{g->text text="Import"}
      {/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

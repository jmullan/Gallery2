{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="General Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Settings saved successfully."}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {if isset($ItemEditItem.can.changePathComponent)}
      {g->box}
	{g->title}
	  {g->text text="Name"}
	{/g->title}
	{g->subtitle}
	  {g->text text="required"}
	{/g->subtitle}
	{g->description}
	  {g->text text="The name of this item on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes."}
	{/g->description}
	{g->element}
	  {strip}
	    {foreach from=$ItemAdmin.parents item=parent}
	      {if empty($parent.parentId)}
		/
	      {else}
		{$parent.pathComponent}/
	      {/if}
	    {/foreach}
	  {/strip}
	  {g->input type=text size=40 name="form[pathComponent]"}{$form.pathComponent}{/g->input}
	{/g->element}
      {/g->box}

      {if !empty($form.error.pathComponent.invalid)}
	{g->error}
	  {g->text text="Your name contains invalid characters.  Please choose another."}
	{/g->error}
      {/if}

      {if !empty($form.error.pathComponent.missing)}
	{g->error}
	  {g->text text="You must enter a name for this item."}
	{/g->error}
      {/if}

      {if !empty($form.error.pathComponent.collision)}
	{g->error}
	  {g->text text="The name you entered is already in use.  Please choose another."}
	{/g->error}
      {/if}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Title"}
      {/g->title}
      {g->description}
	{g->text text="The title of this item."}
      {/g->description}
      {g->element}
	{g->input type="text" size="40" name="form[title]"}{$form.title}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Summary"}
      {/g->title}
      {g->description}
	{g->text text="The summary of this item."}
      {/g->description}
      {g->element}
	{g->input type="text" size="40" name="form[summary]"}{$form.summary}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Keywords"}
      {/g->title}
      {g->description}
	{g->text text="Keywords are not visible, but are searchable."}
      {/g->description}
      {g->element}
	{g->textarea rows="2" cols="60" name="form[keywords]"}{$form.keywords}{/g->textarea}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Description"}
      {/g->title}
      {g->description}
	{g->text text="This is the long description of the item."}
      {/g->description}
      {g->element}
	{g->textarea rows="4" cols="60" name="form[description]"}{$form.description}{/g->textarea}
      {/g->element}
    {/g->box}

    {g->box}
      {g->element}
	{g->input type="hidden" name="form[serialNumber]"}{$form.serialNumber}{/g->input}
	{g->input type="submit" name="form[action][save]"}{g->text text="Save"}{/g->input}
	{g->input type="submit" name="form[action][undo]"}{g->text text="Undo"}{/g->input}
      {/g->element}
    {/g->box}
  {/g->box}
{/g->pagebox}

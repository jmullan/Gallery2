{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Group Management"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.deletedGroup)}
	{g->text text="Removed group '%s'" arg1=$status.deletedGroup}
      {/if}
      {if isset($status.createdGroup)}
	{g->text text="Created group '%s'" arg1=$status.createdGroup}
      {/if}
      {if isset($status.modifiedGroup)}
	{g->text text="Modified group '%s'" arg1=$status.modifiedGroup}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text one="There is %d group in the system." 
      many="There are %d total groups in the system." 
      count=$AdminGroups.totalGroupCount
      arg1=$AdminGroups.totalGroupCount}
    {/g->description}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Edit Group"}
    {/g->title}

    {g->element}
      {g->input type="text" name="form.text.groupName" size="20"}{$form.text.groupName}{/g->input}
    {/g->element}

    {if isset($form.error.text.noSuchGroup)}
      {g->error}
	{g->text text="Group '%s' does not exist." arg1=$form.text.groupName}
      {/g->error}
    {/if}

    {if isset($form.error.text.noGroupSpecified)}
      {g->error}
	{g->text text="You must enter a group name"}
      {/g->error}
    {/if}

    {g->element}
      {g->input type="submit" name="form.action.editFromText"}{g->text text="Edit"}{/g->input}
      {g->input type="submit" name="form.action.deleteFromText"}{g->text text="Delete"}{/g->input}
      {g->input type="submit" name="form.action.addRemoveUsersFromText"}{g->text text="Add/Remove Users"}{/g->input}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Edit Group (by list)"}
    {/g->title}

    {g->table style="admin_listing" evenodd="true"}
      {if ($form.list.maxPages > 1)}
	{g->row}
	  {g->column header="true" colspan="2"}
	    {g->table style="admin_listing"}
	      {g->row}
		{g->column align="left" header="true" width="33%"}
		  {g->input type="hidden" name="form.list.page"}{$form.list.page}{/g->input}
		  {g->input type="hidden" name="form.list.maxPages"}{$form.list.maxPages}{/g->input}
		  
		  {if ($form.list.page > 1)}
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminGroups" url_form_list_page=1}
		      {g->text text="&laquo; first"}
		    {/g->link}
		    &nbsp;
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminGroups" url_form_list_page=$form.list.backPage}
		      {g->text text="&laquo; back"}
		    {/g->link}
		  {/if}
		{/g->column}

		{g->column align="center" header="true" width="33%"}
		  {g->text text="Viewing page %d of %d"
		  arg1=$form.list.page
		  arg2=$form.list.maxPages}
		{/g->column}

		{g->column align="right" header="true" width="33%"}
		  {if ($form.list.page < $form.list.maxPages)}
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminGroups" url_form_list_page=$form.list.nextPage}
		      {g->text text="next &raquo;"}
		    {/g->link}
		    &nbsp;
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminGroups" url_form_list_page=$form.list.maxPages}
		      {g->text text="last &raquo;"}
		    {/g->link}
		  {/if}
		{/g->column}
	      {/g->row}
	    {/g->table}
	  {/g->column}
	{/g->row}
      {/if}
	  
      {g->row}
	{g->column header="true"}
	  {g->text text="Group Name"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Action"}
	{/g->column}
      {/g->row}

      {foreach from=$form.list.groupNames key=groupId item=group}
	{g->row}
	  {g->column}
	    {$group.groupName}
	  {/g->column}

	  {g->column}
	    {g->linkset}
	      {g->item}
		{g->title}
		  {g->link url_view="core:SiteAdmin" url_subView="core:AdminEditGroup" url_groupId=$groupId}
		    {g->text text="edit"}
		  {/g->link}
		{/g->title}
	      {/g->item}

	      {if ($group.can.delete)}
		{g->item}
		  {g->title}
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminDeleteGroup" url_groupId=$groupId}
		      {g->text text="delete"}
		    {/g->link}
		  {/g->title}
		{/g->item}
	      {/if}

	      {if ($group.can.editUsers)}
		{g->item}
		  {g->title}
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminEditGroupUsers" url_groupId=$groupId}
		      {g->text text="edit users"}
		    {/g->link}
		  {/g->title}
		{/g->item}
	      {/if}
	    {/g->linkset}
	  {/g->column}
	{/g->row}
      {/foreach}
    {/g->table}

    {if !empty($form.list.filter) || ($form.list.maxPages > 1)}
      {g->element}
	{g->input type="text" name="form.list.filter"}{$form.list.filter}{/g->input}
	{g->input type="submit" name="form.action.filterBySubstring"}{g->text text="Filter:"}{/g->input}
	{g->input type="submit" name="form.action.filterClear"}{g->text text="Clear"}{/g->input}
      {/g->element}
    {/if}
      
    {if (!empty($form.list.filter))}
      {g->element}
	{g->text one="%d group matches your filter"
	many="%d groups match your filter"
	count=$form.list.count
	arg1=$form.list.count}
      {/g->element}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Create Group"}
    {/g->title}
    {g->element}
      {g->input type="submit" name="form.action.create"}{g->text text="Create"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
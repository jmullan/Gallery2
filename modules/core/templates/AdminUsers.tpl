{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="User Management"}
    {/g->title}
  {/g->banner}
  
  {if isset($status)}
    {g->success}
      {if isset($status.deletedUser)}
	{g->text text="Removed user '%s'" arg1=$status.deletedUser}
      {/if}
      {if isset($status.createdUser)}
	{g->text text="Created user '%s'" arg1=$status.createdUser}
      {/if}
      {if isset($status.modifiedUser)}
	{g->text text="Modified user '%s'" arg1=$status.modifiedUser}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text one="There is %d user in the system." 
      many="There are %d total users in the system." 
      count=$AdminUsers.totalUserCount
      arg1=$AdminUsers.totalUserCount}
    {/g->description}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Edit User"}
    {/g->title}
    
    {g->element}
      {g->input type="text" name="form.text.userName" size="20"}{$form.text.userName}{/g->input}
    {/g->element}

    {g->element}
      {g->input type="submit" name="form.action.editFromText"}{g->text text="Edit"}{/g->input}
      {g->input type="submit" name="form.action.deleteFromText"}{g->text text="Delete"}{/g->input}
    {/g->element}

    {if isset($form.error.text.noSuchUser)}
      {g->error}
	{g->text text="User '%s' does not exist." arg1=$form.text.userName}
      {/g->error}
    {/if}

    {if isset($form.error.text.noUserSpecified)}
      {g->error}
	{g->text text="You must enter a username"}
      {/g->error}
    {/if}

    {if isset($form.error.text.cantDeleteSelf)}
      {g->error}
	{g->text text="You cannot delete yourself!"}
      {/g->error}
    {/if}

    {if isset($form.error.text.cantDeleteAnonymous)}
      {g->error}
	{g->text text="You cannot delete the special guest user."}
      {/g->error}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Edit User (by list)"}
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
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminUsers" url_form_list_page=1}
		      {g->text text="&laquo; first"}
		    {/g->link}
		    &nbsp;
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminUsers" url_form_list_page=$form.list.backPage}
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
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminUsers" url_form_list_page=$form.list.nextPage}
		      {g->text text="next &raquo;"}
		    {/g->link}
		    &nbsp;
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminUsers" url_form_list_page=$form.list.maxPages}
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
	  {g->text text="Username"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Action"}
	{/g->column}
      {/g->row}

      {foreach from=$form.list.userNames key=userId item=user}
	{g->row}
	  {g->column}
	    {$user.userName}
	  {/g->column}
	  {g->column}
	    {g->linkset}
	      {g->item}
		{g->title}
		  {g->link url_view="core:SiteAdmin" url_subView="core:AdminEditUser" url_userId=$userId}
		    {g->text text="edit"}
		  {/g->link}
		{/g->title}
	      {/g->item}

	      {if ($user.can.delete)}
		{g->item}
		  {g->title}
		    {g->link url_view="core:SiteAdmin" url_subView="core:AdminDeleteUser" url_userId=$userId}
		      {g->text text="delete"}
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
	{g->text one="%d user matches your filter"
	many="%d users match your filter"
	count=$form.list.count
	arg1=$form.list.count}
      {/g->element}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Create User"}
    {/g->title}
    
    {g->element}
      {g->input type="submit" name="form.action.create"}{g->text text="Create"}{/g->input}
    {/g->element}
  {/g->box}

{/g->pagebox}

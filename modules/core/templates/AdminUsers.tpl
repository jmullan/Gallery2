{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="User Management"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.deletedUser)}
	  {gallery->text text="Removed user '%s'" arg1=$status.deletedUser}
	{/if}
	{if isset($status.createdUser)}
	  {gallery->text text="Created user '%s'" arg1=$status.createdUser}
	{/if}
	{if isset($status.modifiedUser)}
	  {gallery->text text="Modified user '%s'" arg1=$status.modifiedUser}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text one="There is %d user in the system." 
    many="There are %d total users in the system." 
    count=$AdminUsers.totalUserCount
    arg1=$AdminUsers.totalUserCount}
  {/gallery->description}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="User Edit"}
  {/gallery->title}
  
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->body}
	  {gallery->input type="text" name="form.text.userName" size="20"}{$form.text.userName}{/gallery->input}
	  {if isset($form.error.text.noSuchUser)}
	    {gallery->error}
	      {gallery->text text="User '%s' does not exist." arg1=$form.text.userName}
	    {/gallery->error}
	  {/if}
	  {if isset($form.error.text.noUserSpecified)}
	    {gallery->error}
	      {gallery->text text="You must enter a username"}
	    {/gallery->error}
	  {/if}
	  <br />
	  {gallery->input type="submit" name="form.action.editFromText"}{gallery->text text="Edit"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.deleteFromText"}{gallery->text text="Delete"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="User Edit (by list)"}
  {/gallery->title}
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->body}
	  {gallery->select name="form.list.userId" size=$form.list.pageSize}
	    {html_options options=$form.list.userNames}
	  {/gallery->select}
	  <br/>
	  {gallery->input type="submit" name="form.action.editFromList"}{gallery->text text="Edit"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.deleteFromList"}{gallery->text text="Delete"}{/gallery->input}
	  {if ($form.list.maxPages > 1)}
	    {gallery->text text="Viewing page %d of %d"
	    arg1=$form.list.page
	    arg2=$form.list.maxPages}
	    
	    {if ($form.list.page > 1)}
	      {gallery->input type="submit" name="form.action.firstPage"}{gallery->text text="First Page"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.backPage"}{gallery->text text="<< Back"}{/gallery->input}
	    {/if}
	    {if ($form.list.page < $form.list.maxPages)}
	      {gallery->input type="submit" name="form.action.nextPage"}{gallery->text text="Next >>"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.lastPage"}{gallery->text text="Last Page"}{/gallery->input}
	    {/if}
	    
	    {gallery->input type="text" name="form.list.filter"}{$form.list.filter}{/gallery->input}
	    {gallery->input type="submit" name="form.action.filterBySubstring"}{gallery->text text="Filter:"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.filterClear"}{gallery->text text="Clear"}{/gallery->input}
	    
	    {gallery->input type="hidden" name="form.list.page"}{$form.list.page}{/gallery->input}
	    {gallery->input type="hidden" name="form.list.maxPages"}{$form.list.maxPages}{/gallery->input}
	  {/if}
	  
	  {if (!empty($form.list.filter))}
	    {gallery->text one="%d user matches your filter"
	    many="%d users match your filter"
	    count=$form.list.count
	    arg1=$form.list.count}
	  {/if}
	  
	  {if isset($form.error.list.noUserSelected)}
	    {gallery->error}
	      {gallery->text text="You must select a user"}
	    {/gallery->error}
	  {/if}
	  
	  {if isset($form.error.list.cantDeleteActiveUser)}
	    {gallery->error}
	      {gallery->text text="You cannot delete yourself!"}
	    {/gallery->error}
	  {/if}
	  
	  {if isset($form.error.list.cantDeleteAnonymousUser)}
	    {gallery->error}
	      {gallery->text text="You cannot delete the anonymous user!"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Create User"}
  {/gallery->title}
  {gallery->body}
    {gallery->input type="submit" name="form.action.create"}{gallery->text text="Create"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

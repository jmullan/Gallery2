{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Edit Group Members"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.addedUser)}
	  {gallery->text text="Added user '%s' to group" arg1=$status.addedUser}
	{/if}

	{if isset($status.removedUser)}
	  {gallery->text text="Removed user '%s' from group" arg1=$status.removedUser}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text one="This group contains %d user"
    many="This group contains %d users"
    count=$form.userCount
    arg1=$form.userCount}
  {/gallery->description}
{/gallery->detailedbox}

{if !empty($form.list.users)}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="Remove Member"}
    {/gallery->title}
    {gallery->body}
      {gallery->widget1box}
	{gallery->widget1}
	  {gallery->body}
	    {gallery->select name="form.list.userId" size=1}
	      {html_options options=$form.list.users}
	    {/gallery->select}

	    {gallery->input type="submit" name="form.action.remove"}
	      {gallery->text text="Remove"}
	    {/gallery->input}
	    
	    {if isset($form.error.list.noUserSelected)}
	      {gallery->error}
		{gallery->text text="You must select a user to remove."}
	      {/gallery->error}
	    {/if}
	  {/gallery->body}
	{/gallery->widget1}
      {/gallery->widget1box}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Add Member"}
  {/gallery->title}
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->body}
	  {gallery->input type="text" name="form.text.userName"}{$form.text.userName}{/gallery->input}
	  {gallery->input type="submit" name="form.action.add"}
	    {gallery->text text="Add"}
	  {/gallery->input}
	  {if isset($form.error.text.userName.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a username."}
	    {/gallery->error}
	  {/if}
	  {if isset($form.error.text.userName.invalid)}
	    {gallery->error}
	      {gallery->text text="User '%s' does not exist." arg1=$form.text.userName}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget1box}
      {gallery->widget1}
	{gallery->body}
	  {gallery->input type="hidden" name="groupId"}{$AdminEditGroupUsers.group.id}{/gallery->input}
	  {gallery->input type="submit" name="form.action.done"}{gallery->text text="Done"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget1}
    {/gallery->widget1box}
  {/gallery->body}
{/gallery->detailedbox}


{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Delete a User"}
      </h2>
    </div>    
  </div>

  <div class="gbAdmin">
    {if isset($AdminDeleteUser.numberOfItems) && $AdminDeleteUser.numberOfItems > 0}
    <h2 class="giTitle">
      {g->text text="User %s is the owner of %s items." arg1=$AdminDeleteUser.user.userName 
	       arg2=$AdminDeleteUser.numberOfItems}
    </h2>
    <p class="giDescription">
      {g->text text="Delete user <strong>%s</strong> and..." arg1=$AdminDeleteUser.user.userName}
      <br/>
      <input type="radio" name="{g->formVar var="form[deletionVariant]"}" value="assignNewOwner" checked="checked"/>
      {g->text text="assign a new owner for all items of %s." arg1=$AdminDeleteUser.user.userName}
      <br/>
      <input type="radio" name="{g->formVar var="form[deletionVariant]"}" value="deleteItems"/>
      {g->text text="delete all items of %s and assign a new owner for all remaining non empty albums"
		  arg1=$AdminDeleteUser.user.userName}
      <br/>
      {g->text text="New owner (leaving blank means one of the Site Admins):"}
      <br/>
      <input id="username" class="giFormUsername" type="text" name="{g->formVar var="form[text][newOwner]"}" size="20" value="{$form.text.newOwner}"/>
      {g->autoComplete element="username"}
      {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupUsername" arg3="prefix=__VALUE__"}
      {/g->autoComplete}

      <br/>
      {if isset($form.error.text.noSuchUser)}
      <div class="giError">
        {g->text text="User '%s' does not exist! Cannot assign items to a nonexistent user."
		    arg1=$form.text.newOwner}
      </div>
      {/if}
      {if isset($form.error.text.newOwnerIsDeletedUser)}
      <div class="giError">
        {g->text text="The new owner must be a different user than the user we are deleting!"}
      </div>
      {/if}
      {if isset($form.error.text.newOwnerIsGuest)}
      <div class="giError">
        {g->text text="The new owner cannot be a Guest / Anonymous user!"}
      </div>
      {/if}
      <br/> 
    </p>
    {/if}
	
    <h2 class="giTitle">
      {g->text text="Are you sure?"}
    </h2>

    <p class="giDescription">
      {g->text text="This will completely remove <strong>%s</strong> from Gallery.  There is no undo!"
		arg1=$AdminDeleteUser.user.userName}
    </p>

    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="hidden" name="{g->formVar var="userId"}" value="{$AdminDeleteUser.user.id}"/>
	<input type="submit" name="{g->formVar var="form[action][delete]"}" value="{g->text text="Delete"}"/>
	<input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
      </div>
    </div>
  </div>
</div>

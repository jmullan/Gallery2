{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminEditGroupUsers.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Edit Group Members"}
      </h2>
    </div>
    
  </div>

  {if isset($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.addedUser)}
	{g->text text="Added user '%s' to group" arg1=$status.addedUser}
      {/if}
      
      {if isset($status.removedUser)}
	{g->text text="Removed user '%s' from group" arg1=$status.removedUser}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text one="This group contains %d user"
               many="This group contains %d users"
               count=$form.userCount
               arg1=$form.userCount}
    </p>
  </div>

  {if !empty($form.list.users)}
  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Remove Member"}
    </h2>

    <select name="{g->formVar var="form[list][userId]"}" size="1">
	{html_options options=$form.list.users}
    </select>

    <input type="submit" name="{g->formVar var="form[action][remove]"}" value="{g->text text="Remove"}"/>

    {if isset($form.error.list.noUserSelected)}
    <div class="giError">
      {g->text text="You must select a user to remove."}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Add Member"}
    </h2>

    <input type="text" name="{g->formVar var="form[text][userName]"}" value="{$form.text.userName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="Add"}"/>

    {if isset($form.error.text.userName.missing)}
    <div class="giError">
      {g->text text="You must enter a username."}
    </div>
    {/if}

    {if isset($form.error.text.userName.invalid)}
    <div class="giError">
      {g->text text="User '%s' does not exist." arg1=$form.text.userName}
    </div>
    {/if}
  </div>

  <div class="gbBottomFlag">
    <div class="gbButtons">
      <input type="hidden" name="{g->formVar var="groupId"}" value="{$AdminEditGroupUsers.group.id}"/>
      <input type="submit" name="{g->formVar var="form[action][done]"}" value="{g->text text="Done"}"/>
    </div>
  </div>
</div>

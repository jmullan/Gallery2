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
	{g->text text="Edit Members of Group '%s'" arg1=$AdminEditGroupUsers.group.groupName}
      </h2>
    </div>
    
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.addedUser)}
	{g->text text="Added user '%s' to group '%s'" arg1=$status.addedUser arg2=$AdminEditGroupUsers.group.groupName}
      {/if}
      
      {if isset($status.removedUser)}
	{g->text text="Removed user '%s' from group '%s'" arg1=$status.removedUser arg2=$AdminEditGroupUsers.group.groupName}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text one="This group contains %d user"
               many="This group contains %d users"
               count=$AdminEditGroupUsers.totalUserCount
               arg1=$AdminEditGroupUsers.totalUserCount}
    </p>
  </div>

  {if isset($form.error.list.noUserSelected)}
  <div class="giError">
    {g->text text="You must select a user to remove."}
  </div>
  {/if}

  {if isset($form.error.list.cantRemoveSelf)}
  <div class="giError">
    {g->text text="You can't remove yourself from this group."}
  </div>
  {/if}

  {if !empty($form.list.userNames)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Members"}
    </h3>

    <table class="gbDataTable">
      {if ($form.list.maxPages > 1)}
      <tr>
	<th colspan="2">
	  <table>
	    <tr>
	      <th align="left">
		<input type="hidden" name="{g->formVar var="form[list][page]"}" value="{$form.list.page}"/>
		<input type="hidden" name="{g->formVar var="form[list][maxPages]"}" value="{$form.list.maxPages}"/>
		  
		{if ($form.list.page > 1)}
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditGroupUsers" arg3="form[list][page]=1" arg4="groupId=`$AdminEditGroupUsers.group.id`"}">{g->text text="&laquo; first"}</a>
		&nbsp;
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditGroupUsers" arg3="form[list][page]=`$form.list.backPage`" arg4="groupId=`$AdminEditGroupUsers.group.id`"}">{g->text text="&laquo; back"}</a>
		{/if}
	      </th>

	      <th align="center">
		{g->text text="Viewing page %d of %d"
		         arg1=$form.list.page
		         arg2=$form.list.maxPages}
	      </th>

	      <th align="right">
		{if ($form.list.page < $form.list.maxPages)}
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditGroupUsers" arg3="form[list][page]=`$form.list.nextPage`" arg4="groupId=`$AdminEditGroupUsers.group.id`"}">{g->text text="next &raquo;"}</a>
		&nbsp;
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditGroupUsers" arg3="form[list][page]=`$form.list.maxPages`" arg4="groupId=`$AdminEditGroupUsers.group.id`"}">{g->text text="last &raquo;"}</a>
		{/if}
	      </th>
	    </tr>
	  </table>
	</th>
      </tr>
      {/if}
	  
      <tr>
	<th>
	</th>
	<th>
	  {g->text text="Username"}
	</th>
      </tr>

      {foreach from=$form.list.userNames key=userId item=user}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
          {if ($user.can.remove)}
	  <span>
            <input type="checkbox" name="{g->formVar var="form[userIds][$userId]}">
	  </span>
	  {/if}
	</td>

	<td>
	  {$user.userName}
	</td>
      </tr>
      {/foreach}
    </table>

    {if !empty($form.list.filter) || ($form.list.maxPages > 1)}
    <input type="text" name="{g->formVar var="form[list][filter]"}" value="{$form.list.filter}"/>
    <input type="submit" name="{g->formVar var="form[action][filterBySubstring]"}" value="{g->text text="Filter:"}"/>
    <input type="submit" name="{g->formVar var="form[action][filterClear]"}" value="{g->text text="Clear"}"/>
    {/if}
      
    {if (!empty($form.list.filter))}
    <span>
      {g->text one="%d user matches your filter"
               many="%d users match your filter"
               count=$form.list.count
               arg1=$form.list.count}
    </span>
    {/if}

    {if $AdminEditGroupUsers.canRemove}
    <div>
      <input type="submit" name="{g->formVar var="form[action][remove]"}" value="{g->text text="Remove selected"}"/>
    </div>
    {/if}

  </div>
  {/if}

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Add Member"}
    </h2>

    <input id="username" class="giFormUsername" type="text" name="{g->formVar var="form[text][userName]"}" value="{$form.text.userName}"/>
    {g->autoComplete element="username"}
    {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupUsername" arg3="prefix=__VALUE__"}
    {/g->autoComplete}

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

    {if isset($form.error.text.userName.alreadyInGroup)}
    <div class="giError">
      {g->text text="This user already is in this group."}
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

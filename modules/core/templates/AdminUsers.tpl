{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminUsers.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="User Management"}
      </h2>
    </div>
    
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.deletedUser)}
	{g->text text="Removed user '%s'" arg1=$status.deletedUser}
      {/if}
      {if isset($status.createdUser)}
	{g->text text="Created user '%s'" arg1=$status.createdUser}
      {/if}
      {if isset($status.modifiedUser)}
	{g->text text="Modified user '%s'" arg1=$status.modifiedUser}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text one="There is %d user in the system." 
               many="There are %d total users in the system." 
               count=$AdminUsers.totalUserCount
               arg1=$AdminUsers.totalUserCount}
    </p>
  </div>

  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Edit User"}
    </h3>
    
    <input id="username" class="giFormUsername" type="text" name="{g->formVar var="form[text][userName]"}" size="20" value="{$form.text.userName}" autocomplete="off"/> 
    {g->autoComplete element="username"}
    {g->url forJavascript="true" arg1="view=core:SimpleCallback" arg2="command=lookupUsername" arg3="prefix=__VALUE__"}
    {/g->autoComplete}

    <input type="submit" name="{g->formVar var="form[action][editFromText]"}" value="{g->text text="Edit"}"/> 
    <input type="submit" name="{g->formVar var="form[action][deleteFromText]"}" value="{g->text text="Delete"}"/>

    {if isset($form.error.text.noSuchUser)}
    <div class="giError">
      {g->text text="User '%s' does not exist." arg1=$form.text.userName}
    </div>
    {/if}

    {if isset($form.error.text.noUserSpecified)}
    <div class="giError">
      {g->text text="You must enter a username"}
    </div>
    {/if}

    {if isset($form.error.text.cantDeleteSelf)}
    <div class="giError">
      {g->text text="You cannot delete yourself!"}
    </div>
    {/if}

    {if isset($form.error.text.cantDeleteAnonymous)}
    <div class="giError">
      {g->text text="You cannot delete the special guest user."}
    </div>
    {/if}
  </div>

  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Edit User (by list)"}
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
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminUsers" arg3="form[list][page]=1"}">{g->text text="&laquo; first"}</a>
		&nbsp;
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminUsers" arg3="form[list][page]=`$form.list.backPage`"}">{g->text text="&laquo; back"}</a>
		{/if}
	      </th>

	      <th align="center">
		{g->text text="Viewing page %d of %d"
		         arg1=$form.list.page
		         arg2=$form.list.maxPages}
	      </th>

	      <th align="right">
		{if ($form.list.page < $form.list.maxPages)}
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminUsers" arg3="form[list][page]=`$form.list.nextPage`"}">{g->text text="next &raquo;"}</a>
		&nbsp;
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminUsers" arg3="form[list][page]=`$form.list.maxPages`"}">{g->text text="last &raquo;"}</a>
		{/if}
	      </th>
	    </tr>
	  </table>
	</th>
      </tr>
      {/if}

      <tr>
	<th>
	  {g->text text="Username"}
	</th>

	<th>
	  {g->text text="Action"}
	</th>
      </tr>

      {foreach from=$form.list.userNames key=userId item=user}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$user.userName}
	</td>

	<td>
	  <div class="giHorizontalLinks">
	    <span>
	      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditUser" arg3="userId=$userId"}">{g->text text="edit"}</a>
	    </span>

	    {if ($user.can.delete)}
	    <span>
	      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminDeleteUser" arg3="userId=$userId"}">{g->text text="delete"}</a>
	    </span>
	    {/if}
	  </div>
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
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Create User"}"/>
    </div>
  </div>
</div>


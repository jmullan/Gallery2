{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminSelfRegistration.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Registration Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
      <div class="giStatus"> {g->text text="Settings saved successfully"} </div>
    {/if}
    {if isset($status.activated)}
      <div class="giStatus"> {g->text text="Activated user %s" arg1=$status.activated} </div>
    {/if}
    {if isset($status.deleted)}
      <div class="giStatus"> {g->text text="Deleted user %s" arg1=$status.deleted} </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <h3> {g->text text="Confirmation Policy"} </h3>
    <p class="giDescription">
     {g->text text="The Registration module can accept new user registrations instantly, require the user to click a confirmation link in an email that is sent by the module, or require account activation by a site administrator."}
    </p>
    
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="Choose policy:"}
	</td>
	<td>
	  <select name="{g->formVar var="form[confirmation]"}">
	    {html_options options=$SelfRegistration.emailConfirmationList selected=$form.confirmation}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <h3> {g->text text="Email details"} </h3>
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="Sender(From) Email Address:"}
	</td>
	<td>
	  <input type="text" name="{g->formVar var="form[from]"}" value="{$form.from}" size="30"/>
	</td>
      </tr>
      <tr>
	<td>
	  {g->text text="Confirmation Email Subject:"}
	</td>
	<td>
	  <input type="text" name="{g->formVar var="form[subject]"}" value="{$form.subject}" size="30"/>
	</td>
      </tr>
      <tr>
	<td>
	  {g->text text="Admin Email Subject:"}
	</td>
	<td>
	  <input type="text" name="{g->formVar var="form[adminsubject]"}" value="{$form.adminsubject}" size="30"/>
	</td>
      </tr>
      <tr>
	<td colspan="2">
	  <input type="checkbox" name="{g->formVar var="form[emailadmins]"}"{if $form.emailadmins} checked="checked"{/if}/>
	  {g->text text="Email Site Administrators for all new registrations"}
	</td>
      </tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Reset"}"/>
  </div>

  {if $form.list.count>0}
  <div class="gbAdmin">
    <h3> {g->text text="Pending Registrations"} </h3>

    <table class="gbDataTable">
      {if ($form.list.maxPages > 1)}
      <tr><th colspan="2">
	<table><tr>
	  <th align="left">
	    <input type="hidden" name="{g->formVar var="form[list][page]"}" value="{$form.list.page}"/>
	    <input type="hidden" name="{g->formVar var="form[list][maxPages]"}" value="{$form.list.maxPages}"/>

	    {if ($form.list.page > 1)}
	    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=register:AdminSelfRegistration" arg3="form[list][page]=1"}">{g->text text="&laquo; first"}</a>
	    &nbsp;
	    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=register:AdminSelfRegistration" arg3="form[list][page]=`$form.list.backPage`"}">{g->text text="&laquo; back"}</a>
	    {/if}
	  </th>
	  <th align="center">
	    {g->text text="Viewing page %d of %d" arg1=$form.list.page arg2=$form.list.maxPages}
	  </th>
	  <th align="right">
	    {if ($form.list.page < $form.list.maxPages)}
	    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=register:AdminSelfRegistration" arg3="form[list][page]=`$form.list.nextPage`"}">{g->text text="next &raquo;"}</a>
	    &nbsp;
	    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=register:AdminSelfRegistration" arg3="form[list][page]=`$form.list.maxPages`"}">{g->text text="last &raquo;"}</a>
	    {/if}
	  </th>
	</tr></table>
      </th></tr>
      {/if}

      <tr>
	<th> {g->text text="Username"} </th>
	<th> {g->text text="Full Name"} </th>
	<th> {g->text text="Email"} </th>
	<th> {g->text text="Date"} </th>
	<th> {g->text text="Action"} </th>
      </tr>

      {foreach from=$form.list.userNames key=userId item=user}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td> {$user.userName} </td>
	<td> {$user.fullName} </td>
	<td> {$user.email} </td>
	<td> {g->date timestamp=$user.creationTimestamp} </td>
	<td>
	  <div class="giHorizontalLinks">
	    <span>
	      <a href="{g->url arg1="controller=register:AdminSelfRegistration" arg2="form[action][activate]=1" arg3="form[userId]=$userId"}">{g->text text="activate"}</a>
	    </span>
	    <span>
	      <a href="{g->url arg1="controller=register:AdminSelfRegistration" arg2="form[action][delete]=1" arg3="form[userId]=$userId"}">{g->text text="delete"}</a>
	    </span>
	  </div>
	</td>
      </tr>
      {/foreach}
    </table>
  </div>
  {/if}
</div>

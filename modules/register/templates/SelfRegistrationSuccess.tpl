{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SelfRegistrationSuccess.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Registration successful"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">

  {if isset($status.registeredUser) || isset($status.registeredUserNoEmail)}
    <div class="gbDataEntry">
      <span>
	{g->text text="Your registration was successful."}
      </span>
    </div>
    <div class="gbDataEntry">
      {if isset($status.registeredUserNoEmail)}
      <span>
	{g->text text="Your registration will be processed and your account activated soon."}
      </span>
      {else}
      <span>
	{g->text text="You will shortly receive an email containing a link. You have to click this link to confirm and activate your account."}
      </span>
      <span>
	{g->text text="This procedure is necessary to prevent account abuse."}
      </span>
      {/if}
    </div>

  {elseif isset($status.activatedUser)}

    <div class="gbDataEntry">
      <span>
	{g->text text="Your registration was successful and your account has been activated."}
      </span>
    </div>
    <div class="gbDataEntry">
      <span>
	{g->text text="You can now"}
	<a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin"}">{g->text text="login"}</a> 
	{g->text text="to your account with your username and password."}
      </span>
    </div>
  
  {else}
 
    <h2 class="giTitle">
      {g->text text="This page can only be called once."}
    </h2>
    <div class="gbDataEntry">
      <span>
	{g->text text="This page has been requested before and can only be called once. Probable you have hit the Reload button. Please proceed to "}
	<a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin"}">{g->text text="login"}</a>.
      </span>
    </div>
  
  {/if}
  </div>
</div>

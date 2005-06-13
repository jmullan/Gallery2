{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Recover a lost or forgotten password"} </h2>
</div>

<div class="gbBlock">
  {g->text text="Recovering your password requires that your user account has an email address assigned, and that you have access to the listed email address.  A confirmation will be emailed to you containing a URL which you must visit to set a new password for your account.  To prevent abuse, password recovery requests can not be attempted more than once in a 20 minute period.  A recovery confirmation is valid for seven days.  If it is not used during that time, it will be purged from the system and a new request will have to be made."}
</div>

<div class="gbBlock">
  {if isset($status.requestSent)}
  <div class="gbBlock">
    <h2 class="giSuccess">
      {g->text text="Your recovery request has been sent!"}
    </h2>
    <h2> 
      {g->text text="Note that if the account does not have an email address, you may not receive the email and you should contact your system administrator for help."}
    </h2>
  </div>
  {/if}
  {if isset($status.adminReset)}
  <div class="gbBlock">
    <h2>
      {g->text text="Administrator Recovery"}
    </h2>
    <h2>
      {capture name="adminResetUrl"}
      <a href='{g->url arg1="view=core.UserAdmin" arg2="subView=core.UserRecoverPasswordAdmin"}'>
      {/capture}
      {g->text text="You can use the %sAdministrator Password Recovery%s if you don't receive a recovery email from Gallery." arg1=$smarty.capture.adminResetUrl arg2="</a>"}
    </h2>
  </div>
  {/if}

  <h4>{g->text text="Username"}</h4>

  <input type="text" id="giFormUsername" size="16"
   name="{g->formVar var="form[userName]"}" value="{$form.userName}"/>

  <script type="text/javascript">
    document.forms[0]['{g->formVar var="form[userName]"}'].focus();
  </script>

  {if isset($form.error.userName.missing)}
  <div class="giError">
    {g->text text="You must enter a username"}
  </div>
  {/if}
</div>

{* Include our extra ItemAddOptions *}
{foreach from=$UserRecoverPassword.plugins item=plugin}
  {include file="gallery:`$plugin.file`" l10Domain=$plugin.l10Domain}
{/foreach}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][recover]"}" value="{g->text text="Recover"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>

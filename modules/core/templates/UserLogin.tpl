{*
 * $Revision: 1.25 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Login to your account"} </h2>
</div>

<div class="gbBlock">
  {if isset($status.passwordRecovered)}
  <div class="gbBlock"><h2 class="giSuccess">
    {g->text text="Your password has been recovered, please login."}
  </h2></div>
  {/if}

  <h4> {g->text text="Username"} </h4>

  <input type="text" id="giFormUsername" size="16"
   name="{g->formVar var="form[username]"}" value="{$form.username}"/>

  <script type="text/javascript">
    document.getElementById('userAdminForm')['{g->formVar var="form[username]"}'].focus();
  </script>

  {if isset($form.error.username.missing)}
  <div class="giError">
    {g->text text="You must enter a username"}
  </div>
  {/if}

  <h4> {g->text text="Password"} </h4>

  <input type="password" id="giFormPassword" size="16" name="{g->formVar var="form[password]"}"/>

  {if isset($form.error.password.missing)}
  <div class="giError">
    {g->text text="You must enter a password"}
  </div>
  {/if}
  {if isset($form.error.invalidPassword)}
  <div class="giError">
    {g->text text="Your login information is incorrect.  Please try again."}
  </div>
  {/if}
</div>

{* Include our extra ItemAddOptions *}
{foreach from=$UserLogin.plugins item=plugin}
  {include file="gallery:`$plugin.file`" l10Domain=$plugin.l10Domain}
{/foreach}

<div class="gbBlock">
  {capture name="recoverUrl"}
  {g->url arg1="view=core.UserAdmin" arg2="subView=core.UserRecoverPassword" arg3="return=1"}
  {/capture}
  {g->text text="Lost or forgotten passwords can be retrieved using the <a href=\"%s\">recover password</a> page" arg1=$smarty.capture.recoverUrl}
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][login]"}" value="{g->text text="Login"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>

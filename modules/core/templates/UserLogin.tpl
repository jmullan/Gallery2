{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Login to your account"} </h2>
</div>

<div class="gbBlock">
  <h4> {g->text text="Username"} </h4>

  <input type="text" id="giFormUsername" size="16"
   name="{g->formVar var="form[username]"}" value="{$form.username}"/>

  <script type="text/javascript">
    document.forms[0]['{g->formVar var="form[username]"}'].focus();
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

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][login]"}" value="{g->text text="Login"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>

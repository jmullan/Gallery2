{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserLogin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Login to your account"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Username"}
      </h2>

      <input class="giFormUsername" type="text" name="{g->formVar var="form[username]"}" size="16" value="{$form.username}"/>
      <script type="text/javascript">document.forms[0]['{g->formVar var="form[username]"}'].focus();</script>

      {if isset($form.error.username.missing)}
      <div class="giError">
	{g->text text="You must enter a username"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Password"}
      </h2>

      <input class="giFormPassword" type="password" size="16" name="{g->formVar var="form[password]"}"/>

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
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][login]"}" value="{g->text text="Login"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>

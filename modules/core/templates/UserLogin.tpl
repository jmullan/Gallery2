<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Log in to your account"}
      </div>
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="User name"}
      </div>

      <input type="text" name="{g->formVar var="form[username]"}" value="{$form.username}"/>

      {if isset($form.error.username.missing)}
      <div class="giError">
	{g->text text="You must enter a username"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Password"}
      </div>

      <input type="password" name="{g->formVar var="form[password]"}"/>

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

  <input type="submit" name="{g->formVar var="form[action][login]"}" value="{g->text text="Login"}"/>
  <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>

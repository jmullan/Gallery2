{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserSelfRegistration.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Register As New User"}
      </h2> 
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <h3> {g->text text="Username"} </h3>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>
      <input size="32" type="text" name="{g->formVar var="form[userName]"}" value="{$form.userName}"/>
    </div>

    {if isset($form.error.userName.missing)}
      <div class="giError">
	{g->text text="You must enter a username"}
      </div>
    {/if}
    {if isset($form.error.userName.exists)}
      <div class="giError">
	{g->text text="Username '%s' already exists" arg1=$form.userName}
      </div>
    {/if}

    <div class="gbDataEntry">
      <h3> {g->text text="Full Name"} </h3>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>
      <input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}"/>
    </div>
    
    {if isset($form.error.fullName.missing)}
      <div class="giError">
	{g->text text="You must enter your full name"}
      </div>
    {/if}

    <div class="gbDataEntry">
      <h3> {g->text text="Email Address"} </h3>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>
      <input size="32" type="text" name="{g->formVar var="form[email]"}" value="{$form.email}"/>
    </div>

    {if isset($form.error.email.missing)}
      <div class="giError">
	{g->text text="You must enter an email address"}
      </div>
    {/if}

    {if false} {* added by S.E., 17.06.04 *}
    <div class="gbDataEntry">
      <h3> {g->text text="Language"} </h3>
      <select name="g->formVar var="form[language]"}">
	{html_options options=$AdminCreateUser.languageList selected=$form.language}
      </select>	
    </div>
    {/if}

    <div class="gbDataEntry">
      <h3> {g->text text="Password"} </h3>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>
      <input size="32" type="password" name="{g->formVar var="form[password1]"}"/>
    </div>

    {if isset($form.error.password1.missing)}
      <div class="giError">
	{g->text text="You must enter a password"}
      </div>
    {/if}

    <div class="gbDataEntry">
      <h3> {g->text text="Verify Password"} </h3>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>
      <input size="32" type="password" name="{g->formVar var="form[password2]"}"/>
    </div>

    {if isset($form.error.password2.missing)}
      <div class="giError">
	{g->text text="You must enter the password a second time"}
      </div>
    {/if}
    {if isset($form.error.password2.mismatch)}
      <div class="giError">
	{g->text text="The passwords you entered did not match"}
      </div>
    {/if}
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Register"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>	
</div>

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
	{g->text text="Register As New User"}
      </h2> 
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Username (required)"}
      </h2>
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
      <h2 class="giTitle">
	{g->text text="Full Name (required)"} 
      </h2>
      <input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}"/>
    </div>
    
    {if isset($form.error.fullName.missing)}
      <div class="giError">
	{g->text text="You must enter your full name"}
      </div>
    {/if}

    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Email Address (required)"} 
      </h2>
      <input size="32" type="text" name="{g->formVar var="form[email]"}" value="{$form.email}"/>
    </div>

    {if isset($form.error.email.missing)}
      <div class="giError">
	{g->text text="You must enter an email address"}
      </div>
    {/if}
    {if isset($form.error.email.invalid)}
      <div class="giError">
	{g->text text="Invalid email address"}
      </div>
    {/if}

    {if false} {* added by S.E., 17.06.04 *}
    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Language"} 
      </h2>
      <select name="g->formVar var="form[language]"}">
	{html_options options=$AdminCreateUser.languageList selected=$form.language}
      </select>	
    </div>
    {/if}

    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Password (required)"} 
      </h2>
      <input size="32" type="password" name="{g->formVar var="form[password1]"}"/>
    </div>

    {if isset($form.error.password1.missing)}
      <div class="giError">
	{g->text text="You must enter a password"}
      </div>
    {/if}

    <div class="gbDataEntry">
      <h2 class="giTitle">
	{g->text text="Verify Password (required)"} 
      </h2>
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

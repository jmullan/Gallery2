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
	{g->text text="Edit a user"}
      </h2>
    </div>
    
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Username"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
      </h3>

      <input type="hidden" name="{g->formVar var="userId"}" value="{$AdminEditUser.user.id}"/>
      <input class="giFormUsername" size="30" type="text" name="{g->formVar var="form[userName]"}" value="{$form.userName}"/>

      {if isset($form.error.userName.duplicate)}
      <div class="giError">
	{g->text text="That username is already in use"}
      </div>
      {/if}

      {if isset($form.error.userName.missing)}
      <div class="giError">
	{g->text text="You must enter a new username"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Full Name"}
      </h3>
      
      <input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}"/>
    </div>

    {if $AdminEditUser.show.email}
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="E-mail Address"}
        <span class="giSubtitle">
          {g->text text="(suggested)"}
        </span>
      </h3>

      <input size="32" type="text" name="{g->formVar var="form[email]"}" value="{$form.email}"/>
	  
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
    </div>
    {/if}

    {if $AdminEditUser.show.language}
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Language"}
      </h3>

      <select name="{g->formVar var="form[language]"}">
	  {html_options options=$AdminEditUser.languageList selected=$form.language}
      </select>
    </div>
    {/if}

    {if $AdminEditUser.show.password}
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Password"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
      </h3>
      <input size="32" type="password" name="{g->formVar var="form[password1]"}"/>

      {if isset($form.error.password1.missing)}
      <div class="giError">
	{g->text text="You must enter a password"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Verify Password"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
      </h3>
      
      <input size="32" type="password" name="{g->formVar var="form[password2]"}"/>

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
    {/if}
	      
    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="edit user"}"/>
	<input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="undo"}"/>
	<input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="cancel"}"/>
      </div>
    </div>
  </div>
</div>

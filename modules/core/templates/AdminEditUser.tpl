{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminEditUser.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
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
      <input size="32" type="text" name="{g->formVar var="form[userName]"}" value="{$form.userName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

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
      
      <input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
    </div>

    {if $AdminEditUser.show.email}
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="E-mail Address"}
        <div class="giSubtitle">
          {g->text text="required"}
        </div>
      </h3>

      <input size="32" type="text" name="{g->formVar var="form[email]"}" value="{$form.email}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
	  
      {if isset($form.error.email.missing)}
      <div class="giError">
	{g->text text="You must enter an email address"}
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
          {g->text text="required"}
        </span>
      </h3>
      <input size="32" type="password" name="{g->formVar var="form[password1]"}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

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
          {g->text text="required"}
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
	<input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="edit user"}" class="button"/>
	<input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="undo"}" class="button"/>
	<input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="cancel"}" class="button"/>
      </div>
    </div>
  </div>
</div>

{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminCreateUser.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Create A New User"}
      </div>
    </div>
    
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Username"}
      </div>

      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input size="32" type="text" name="{g->formVar var="form[userName]"}" value="{$form.userName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
      <script type="text/javascript">document.forms[0]['{g->formVar var="form[userName]"}'].focus();</script>

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
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Full Name"}
      </div>
      
      <input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Email Address"}
      </div>

      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input size="32" type="text" name="{g->formVar var="form[email]"}" value="{$form.email}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
	  
      {if isset($form.error.email.missing)}
      <div class="giError">
	{g->text text="You must enter an email address"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Language"}
      </div>

      <select name="{g->formVar var="form[language]"}">
	  {html_options options=$AdminCreateUser.languageList selected=$form.language}
      </select>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Password"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input size="32" type="password" name="{g->formVar var="form[password1]"}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

      {if isset($form.error.password1.missing)}
      <div class="giError">
	{g->text text="You must enter a password"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Verify Password"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input size="32" type="password" name="{g->formVar var="form[password2]"}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

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

    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Create User"}" class="button"/>
	<input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}" class="button"/>
      </div>
    </div>
  </div>
</div>


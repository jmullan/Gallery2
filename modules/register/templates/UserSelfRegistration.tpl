<div id="gsAdminContents">
	<div class="gbTopFlag">
  	<div class="gbTitle">
			<div class="giTitle">
				{g->text text="Register As New User"}
			</div> 
		</div>
    <div class="spacer">
      &nbsp;
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
      <div class="giTitle">
				{g->text text="Full Name"}
      </div>
      
	{if true} {* added by S.E., 17.06.04 *}
      <div class="giSubtitle">
				{g->text text="required"}
      </div>
    {/if}
			<input size="32" type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}"/>
    </div>
    
    {if isset($form.error.fullName.missing)} {* added by S.E., 17.06.04 *}
      <div class="giError">
				{g->text text="You must enter your full name"}
      </div>
    {/if}


    <div class="gbDataEntry">
      <div class="giTitle">
				{g->text text="Email Address"}
      </div>
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
      <div class="giTitle">
				{g->text text="Language"}
      </div>
			<select name="g->formVar var="form[language]"}">
				{html_options options=$AdminCreateUser.languageList selected=$form.language}
			</select>	
    </div>
	{/if}
	
    <div class="gbDataEntry">
      <div class="giTitle">
				{g->text text="Password"}
      </div>
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
      <div class="giTitle">
				{g->text text="Verify Password"}
      </div>
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

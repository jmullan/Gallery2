{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit a user"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="Username"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}
      {g->element}
	{g->input type="hidden" name="userId"}{$AdminEditUser.user.id}{/g->input}
	{g->input type="text" name="form[userName]"}{$form.userName}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.userName.duplicate)}
      {g->error}
	{g->text text="That username is already in use"}
      {/g->error}
    {/if}

    {if isset($form.error.userName.missing)}
      {g->error}
	{g->text text="You must enter a new username"}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Full Name"}
      {/g->title}
      {g->element}
	{g->input size="32" type="text" name="form[fullName]"}{$form.fullName}{/g->input}
      {/g->element}
    {/g->box}

    {if $AdminEditUser.show.email}
      {g->box}
	{g->title}
	  {g->text text="Email Address"}
	{/g->title}
	{g->subtitle}
	  {g->text text="required"}
	{/g->subtitle}

	{g->element}
	  {g->input size="32" type="text" name="form[email]"}{$form.email}{/g->input}
	{/g->element}
      {/g->box}
    {/if}
		
    {if isset($form.error.email.missing)}
      {g->error}
	{g->text text="You must enter an email address"}
      {/g->error}
    {/if}

    {if $AdminEditUser.show.language}
      {g->box}
	{g->title}
	  {g->text text="Language"}
	{/g->title}
	{g->element}
	  {g->select name="form[language]"}
	    {html_options options=$AdminEditUser.languageList selected=$form.language}
	  {/g->select}
	{/g->element}
      {/g->box}
    {/if}

    {if $AdminEditUser.show.password}
      {g->box}
	{g->title}
	  {g->text text="Password"}
	{/g->title}
	{g->subtitle}
	  {g->text text="required"}
	{/g->subtitle}
	{g->element}
	  {g->input size="32" type="password" name="form[password1]"}{/g->input}
	{/g->element}
      {/g->box}
      
      {if isset($form.error.password1.missing)}
	{g->error}
	  {g->text text="You must enter a password"}
	{/g->error}
      {/if}
  
      {g->box}
	{g->title}
	  {g->text text="Verify Password"}
	{/g->title}
	{g->subtitle}
	  {g->text text="required"}
	{/g->subtitle}
	{g->element}
	  {g->input size="32" type="password" name="form[password2]"}{/g->input}
	{/g->element}
      {/g->box}

      {if isset($form.error.password2.missing)}
	{g->error}
	  {g->text text="You must enter the password a second time"}
	{/g->error}
      {/if}
      
      {if isset($form.error.password2.mismatch)}
	{g->error}
	  {g->text text="The passwords you entered did not match"}
	{/g->error}
      {/if}
    {/if}
	      
    {g->element}
      {g->input type="submit" name="form[action][save]"}{g->text text="edit user"}{/g->input}
      {g->input type="submit" name="form[action][undo]"}{g->text text="undo"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}


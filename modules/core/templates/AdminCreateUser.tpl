{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Create A New User"}
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
	{g->input size="32" type="text" name="form.userName"}{$form.userName}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.userName.missing)}
      {g->error}
	{g->text text="You must enter a username"}
      {/g->error}
    {/if}
    
    {if isset($form.error.userName.exists)}
      {g->error}
	{g->text text="Username '%s' already exists" arg1=$form.userName}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Full Name"}
      {/g->title}
      {g->element}
	{g->input size="32" type="text" name="form.fullName"}{$form.fullName}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Email Address"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}

      {g->element}
	  {g->input size="32" type="text" name="form.email"}{$form.email}{/g->input}
      {/g->element}
    {/g->box}
	  
    {if isset($form.error.email.missing)}
      {g->error}
	{g->text text="You must enter an email address"}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Language"}
      {/g->title}
      {g->element}
	{g->select name="form.language"}
	  {html_options options=$AdminCreateUser.languageList selected=$form.language}
	{/g->select}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Password"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}
      {g->element}
	  {g->input size="32" type="password" name="form.password1"}{/g->input}
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
	  {g->input size="32" type="password" name="form.password2"}{/g->input}
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

    {g->box}
      {g->element}
	{g->input type="submit" name="form.action.create"}{g->text text="Create User"}{/g->input}
	{g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
      {/g->element}
    {/g->box}
  {/g->box}
{/g->pagebox}

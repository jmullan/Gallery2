{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Log in to your account"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="User name"}
      {/g->title}
      {g->element}
	{g->input type="text" name="form[username]"}{$form.username}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.username.missing)}
      {g->error}
	{g->text text="You must enter a username"}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Password"}
      {/g->title}

      {g->element}
	{g->input type="password" name="form[password]"}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.password.missing)}
      {g->error}
	{g->text text="You must enter a password"}
      {/g->error}
    {/if}

    {if isset($form.error.invalidPassword)}
      {g->error}
	{g->text text="Your login information is incorrect.  Please try again."}
      {/g->error}
    {/if}

    {g->footer}
      {g->input type="submit" name="form[action][login]"}{g->text text="Login"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
    {/g->footer}
  {/g->box}
{/g->pagebox}

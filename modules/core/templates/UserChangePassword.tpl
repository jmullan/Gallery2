{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Change Password"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.changedPassword)}
	{g->text text="Password changed successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box}
    {g->description}
      {g->text text="You must enter a new password twice to change passwords."}
    {/g->description}
  {/g->box}

  {g->box}
    {g->title}
      {g->text text="Password"}
    {/g->title}
    {g->subtitle}
      {g->text text="required"}
    {/g->subtitle}
    {g->element}
      {g->input type="password" name="form.password1"}{/g->input}
    {/g->element}
    {if isset($form.error.password1.missing)}
      {g->error}
	{g->text text="You must enter a password"}
      {/g->error}
    {/if}
  {/g->box}

  {g->box}
    {g->title}
      {g->text text="Verify Password"}
    {/g->title}
    {g->subtitle}
      {g->text text="required"}
    {/g->subtitle}
    {g->element}
      {g->input type="password" name="form.password2"}{/g->input}
    {/g->element}

    {if isset($form.error.password2.missing)}
      {g->error}
	{g->text text="You must enter your password again!"}
      {/g->error}
    {/if}

    {if isset($form.error.password2.mismatch)}
      {g->error}
	{g->text text="The passwords you entered did not match"}
      {/g->error}
    {/if}
  {/g->box}

  {g->box}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Change"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}


{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Account Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Account settings saved successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="Username"}
      {/g->title}
      {g->element}
	{$UserAdmin.user.userName}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Full name"}
      {/g->title}
      {g->element}
	{g->input type="text" name="form.fullName"}{$form.fullName}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Email address"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}
      {g->element}
	{g->input type="text" name="form.email"}{$form.email}{/g->input}
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
	  {html_options options=$UserPreferences.languageList selected=$form.language}
	{/g->select}
      {/g->element}
    {/g->box}

    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
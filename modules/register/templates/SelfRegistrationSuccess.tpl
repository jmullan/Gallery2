{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Registration successful"}
    {/g->title}
  {/g->banner}

 {if isset($status.registeredUser)}
  {g->box style="admin"}
    {g->box}
      {g->element}
		{g->text text="Your registration was successful."}
      {/g->element}
    {/g->box}
    {g->box}
      {g->element}
		{g->text text="You will shortly receive an email  containing a link. You have to click this link to confirm and activate your account."}
      {/g->element}
      {g->element}
		{g->text text="This procedure is necessary to prevent account abuse."}
      {/g->element}
    {/g->box}
  {/g->box}
 {/if}

 {if isset($status.activatedUser)}
  {g->box style="admin"}
    {g->box}
      {g->element}
		{g->text text="Your registration was successful and your account has been activated."}
      {/g->element}
    {/g->box}
    {g->box}
      {g->element}
		{g->text text="You can now login to your account with your username and password."}
      {/g->element}
    {/g->box}
  {/g->box}
 {/if}
 
{/g->pagebox}

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Account activation"}
    {/g->title}
  {/g->banner}


 {if isset($form.error.unknownUser)}
  {g->box style="admin"}
    {g->box}
     {g->error}
	   {g->text text="This user cannot be activated."}
      {/g->error}
    {/g->box}
    {g->box}
      {g->element}
		{g->text text="This can happen if the URL you entered is not correct or you already activated this account. Please check if your mailclient broke the link into several lines and append them without spaces."}
      {/g->element}
    {/g->box}
  {/g->box}

 {else}
  {g->box style="admin"}
    {g->box}
      {g->element}
		{g->text text="Your account has been activated."}
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

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Comment change confirmation"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.added)}
	{g->text text="Commented added successfully"}
      {/if}
      {if isset($status.deleted)}
	{g->text text="Commented deleted successfully"}
      {/if}
      {if isset($status.saved)}
	{g->text text="Commented modified successfully"}
      {/if}
    {/g->success}
  {/if}
{/g->pagebox}

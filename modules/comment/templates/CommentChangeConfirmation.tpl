{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Comment change confirmation"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.added)}
	{g->text text="Comment added successfully"}
      {/if}
      {if isset($status.deleted)}
	{g->text text="Comment deleted successfully"}
      {/if}
      {if isset($status.saved)}
	{g->text text="Comment modified successfully"}
      {/if}
    {/g->success}
  {/if}
{/g->pagebox}

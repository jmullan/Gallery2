{if !empty($main.debug)}
  {g->box style="debug"}
    {g->title}
      {g->text text="Gallery Debug Output"} 
    {/g->title}

    {g->element}
      <pre>
      {$main.debug}
      </pre>
    {/g->element}
  {/g->box}
{/if}

{g->link arg1="debug:ShowTree" arg2="entityId=$entityId"}
  {g->text text="%d: (%s)" arg1=$entityId arg2=$ShowTree.entityTable.$entityId._className}
{/g->link}

{if !empty($ShowTree.isItem.$entityId)}
  {g->link arg1="itemId=$entityId"}
    {g->text text="[browse]"}
  {/g->link}
{/if}

  


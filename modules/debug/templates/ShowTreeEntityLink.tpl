    <a href="{g->url arg1="view=debug:ShowTree" arg2="entityId=$entityId"}">
      {g->text text="%d: (%s)" arg1=$entityId arg2=$ShowTree.entityTable.$entityId._className}
    </a>

    {if !empty($ShowTree.isItem.$entityId)}
    <a href="{g->url arg1="itemId=$entityId"}">
      {g->text text="[browse]"}
    </a>
    {/if}

  


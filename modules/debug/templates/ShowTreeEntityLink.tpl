{g->link url_view="debug:ShowTree" url_entityId=$entityId}
  {g->text text="%d: (%s)" arg1=$entityId arg2=$ShowTree.entityTable.$entityId._className}
{/g->link}

{if !empty($ShowTree.isItem.$entityId)}
  {g->link url_itemId=$entityId}
    {g->text text="[browse]"}
  {/g->link}
{/if}

  


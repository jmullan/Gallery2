{gallery->link url_view="debug:ShowTree" url_entityId=$entityId}
  {gallery->text text="%d: (%s)" arg1=$entityId arg2=$ShowTree.entityTable.$entityId._className}
{/gallery->link}

{if !empty($ShowTree.isItem.$entityId)}
  {gallery->link url_itemId=$entityId}
    {gallery->text text="[browse]"}
  {/gallery->link}
{/if}

  


{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Use as parent's thumbnail?"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->description}
      {g->text text="You can make use this item as the thumbnail for its parent album."}
    {/g->description}
    
    {g->element}
      {g->input type="submit" name="form[action][makeHighlight]"}{g->text text="Yes, highlight this item!"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}

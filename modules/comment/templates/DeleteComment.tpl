{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Delete this comment?"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Are you sure?"}
    {/g->title}

    {g->description}
      {g->text text="Delete this comment?  There is no undo!"}
    {/g->description}

    {g->element}
      {g->input type="hidden" name="commentId"}{$DeleteComment.comment.id}{/g->input}
      {g->input type="submit" name="form[action][delete]"}{g->text text="Delete"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}

  {include file="modules/comment/templates/Comment.tpl" item=$ItemAdmin.item comment=$DeleteComment.comment user=$DeleteComment.commenter}
{/g->pagebox}

{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Delete this comment?"}
  {/gallery->title}
{/gallery->bannerbox}


{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Are you sure?"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="Delete this comment?  There is no undo!"}
  {/gallery->description}

  {gallery->body}
    {gallery->input type="hidden" name="commentId"}{$DeleteComment.comment.id}{/gallery->input}
    {gallery->input type="submit" name="form.action.delete"}
      {gallery->text text="Delete"}
    {/gallery->input}
    {gallery->input type="submit" name="form.action.cancel"}
      {gallery->text text="Cancel"}
    {/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

{include file="modules/comment/templates/Comment.tpl" item=$ItemAdmin.item comment=$DeleteComment.comment user=$DeleteComment.commenter}
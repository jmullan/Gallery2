<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Delete this comment?"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Are you sure?"}
    </div>
    
    <div class="giDescription">
      {g->text text="Delete this comment?  There is no undo!"}
    </div>
    
    <input type="hidden" name="{g->formVar var="commentId"}" value="{$DeleteComment.comment.id}"/>
    <input type="submit" name="{g->formVar var="form[action][delete]"}" value="{g->text text="Delete"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>

  {include file="modules/comment/templates/Comment.tpl" 
           item=$ItemAdmin.item comment=$DeleteComment.comment user=$DeleteComment.commenter}
</div>

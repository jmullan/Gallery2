{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to DeleteComment.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Delete this comment?"}
      </div>
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

  {include file="gallery:modules/comment/templates/Comment.tpl" 
           item=$ItemAdmin.item comment=$DeleteComment.comment user=$DeleteComment.commenter}
</div>

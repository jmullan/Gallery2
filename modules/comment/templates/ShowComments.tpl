<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="View Comments"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  {if isset($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.changed)}
      {g->text text="Comment changed successfully"}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    {if empty($ShowComments.comments)}
      <div class="giTitle">
	{g->text text="There are no comments for this item"}
      </div>
    {else}
      {foreach from=$ShowComments.comments item=comment}
	{assign var="userId" value=$comment.commenterId}
	{assign var="user" value=$ShowComments.commenters.$userId}
	{include file="modules/comment/templates/Comment.tpl" user=$user comment=$comment item=$ItemAdmin.item can=$ShowComments.can}
      {/foreach}
    {/if}
  </div>
</div>

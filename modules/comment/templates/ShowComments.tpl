{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="View Comments"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.changed)}
	{g->text text="Comment changed successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {if empty($ShowComments.comments)}
      {g->title}
	{g->text text="There are no comments for this item"}
      {/g->title}
    {else}
      {foreach from=$ShowComments.comments item=comment}
	{assign var="userId" value=$comment.commenterId}
	{assign var="user" value=$ShowComments.commenters.$userId}
	{include file="modules/comment/templates/Comment.tpl" user=$user comment=$comment item=$ItemAdmin.item can=$ShowComments.can}
      {/foreach}
    {/if}
  {/g->box}
{/g->pagebox}

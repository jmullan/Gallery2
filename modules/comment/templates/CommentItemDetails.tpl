{if !empty($CommentItemDetails.comments)}
  {gallery->simplebox}
    {gallery->title}
      {gallery->text text="Recent comments"}

      {if sizeof($CommentItemDetails.comments) < $CommentItemDetails.totalComments }
	{gallery->link url_view="core:ItemAdmin" url_subView="comment:ShowComments" url_itemId=$CommentItemDetails.item.id}
	  {gallery->text text="(view all %d comments)" arg1=$CommentItemDetails.totalComments}
	{/gallery->link}
      {/if}
    {/gallery->title}

    {gallery->body}
      {foreach from=$CommentItemDetails.comments item=comment}
	{assign var="userId" value=$comment.commenterId}
	{assign var="user" value=$CommentItemDetails.commenters.$userId}
	{capture name="date"}{gallery->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}{/capture}
	{include file="modules/comment/templates/Comment.tpl" user=$user comment=$comment can=$CommentItemDetails.can item=$CommentItemDetails.item truncate=256}
      {/foreach}
    {/gallery->body}
  {/gallery->simplebox}
{/if}

{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to CommentItemDetails.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if !empty($CommentItemDetails.comments)}
<div id="gsComments">
  <div class="giTitle">
    {g->text text="Recent comments"}

    {if sizeof($CommentItemDetails.comments) < $CommentItemDetails.totalComments }
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=comment:ShowComments" arg3="itemId=`$CommentItemDetails.item.id`"}">
        {g->text text="(view all %d comments)" arg1=$CommentItemDetails.totalComments}
      </a>
    {/if}
  </div>

  {foreach from=$CommentItemDetails.comments item=comment}
  {assign var="userId" value=$comment.commenterId}
  {assign var="user" value=$CommentItemDetails.commenters.$userId}
  {capture name="date"}{g->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}{/capture}
  {include file="gallery:modules/comment/templates/Comment.tpl" user=$user comment=$comment can=$CommentItemDetails.can item=$CommentItemDetails.item truncate=256}
  {/foreach}
</div>
{/if}

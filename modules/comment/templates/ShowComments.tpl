{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="View Comments"}
      </h2>
    </div>

  </div>

  {if !empty($status)}
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
      <h2 class="giTitle">
	{g->text text="There are no comments for this item"}
      </h2>
    {else}
      {foreach from=$ShowComments.comments item=comment}
	{assign var="userId" value=$comment.commenterId}
	{assign var="user" value=$ShowComments.commenters.$userId}
	{include file="gallery:modules/comment/templates/Comment.tpl" user=$user comment=$comment item=$ItemAdmin.item can=$ShowComments.can}
      {/foreach}
    {/if}
  </div>
</div>

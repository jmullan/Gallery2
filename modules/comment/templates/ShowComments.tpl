{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="View Comments"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.changed)}
	  {gallery->text text="Comment changed successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{if empty($ShowComments.comments)}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="There are no comments for this item"}
    {/gallery->title}
  {/gallery->detailedbox}
{else}
  {foreach from=$ShowComments.comments item=comment}
    {assign var="userId" value=$comment.commenterId}
    {assign var="user" value=$ShowComments.commenters.$userId}
    {include file="modules/comment/templates/Comment.tpl" user=$user comment=$comment item=$ItemAdmin.item can=$ShowComments.can}
  {/foreach}
{/if}

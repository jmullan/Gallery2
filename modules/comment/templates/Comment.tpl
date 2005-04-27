{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <h3 class="giTitle">
    {$comment.subject|markup}
  </h3>

  {if isset($can) && ($can.edit || $can.delete || ($can.view && isset($truncate)))}
  <div>
    {if $can.edit}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=comment:EditComment"
       arg3="itemId=`$item.id`" arg4="commentId=`$comment.id`" arg5="return=true"}">
	{g->text text="edit"}
      </a>
      &nbsp;
    {/if}

    {if $can.delete}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=comment:DeleteComment"
       arg3="itemId=`$item.id`" arg4="commentId=`$comment.id`" arg5="return=true"}">
	{g->text text="delete"}
      </a>
      &nbsp;
    {/if}

    {if $can.view && isset($truncate)}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=comment:ShowComments"
       arg3="itemId=`$item.id`" arg4="commentId=`$comment.id`" arg5="return=true"}">
	{g->text text="full"}
      </a>
    {/if}
  </div>
  {/if}

  <p class="giDescription">
    {if isset($truncate)}
      {$comment.comment|entitytruncate:$truncate|markup}
    {else}
      {$comment.comment|markup}
    {/if}
  </p>

  <p class="giInfo">
    {capture name="date"}{g->date timestamp=$comment.date format="%x %X"}{/capture}
    {if isset($can) && $can.edit}
      {g->text text="Posted by %s on %s (%s)"
	       arg1=$user.fullName|default:$user.userName
	       arg2=$smarty.capture.date
	       arg3=$comment.host}

    {else}
      {g->text text="Posted by %s on %s"
	       arg1=$user.fullName|default:$user.userName
	       arg2=$smarty.capture.date}
    {/if}
  </p>
</div>

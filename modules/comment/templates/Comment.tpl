{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Comment.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbComment">
  <h3 class="giTitle">
    {$comment.subject|markup}
  </h3>
  {if isset($can) && ($can.edit || $can.delete || ($can.view && isset($truncate)))}

  <ul class="giHorizontalLinks">
    {if $can.edit}
    <li>
      <a href="{g->url arg1="return=true" arg2="view=core:ItemAdmin" arg3="subView=comment:EditComment" arg4="itemId=`$item.id`" arg5="commentId=`$comment.id`"}">
        {g->text text="edit"}
      </a>
    </li>
    {/if}

    {if $can.delete}
    <li>
      <a href="{g->url arg1="return=true" arg2="view=core:ItemAdmin" arg3="subView=comment:DeleteComment" arg4="itemId=`$item.id`" arg5="commentId=`$comment.id`"}">
        {g->text text="delete"}
      </a>
    </li>
    {/if}

    {if $can.view && isset($truncate)}
    <li>
      <a href="{g->url arg1="return=true" arg2="view=core:ItemAdmin" arg3="subView=comment:ShowComments" arg4="itemId=`$item.id`" arg5="commentId=`$comment.id`"}">
        {g->text text="full"}
      </a>
    </li>
    {/if}
  </ul>

  {/if}

  <p class="giDescription">
  {if isset($truncate)}
  {$comment.comment|entitytruncate:$truncate|markup}
  {else}
  {$comment.comment|markup}
  {/if}
  </p>

  <p class="giInfo">
    {capture name="date"}{g->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}{/capture}
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

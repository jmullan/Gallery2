<div class="gbComment">
  <div class="giTitle">
    {$comment.subject|markup}
  </div>
  {if isset($can.edit) || isset($can.delete)}
  <div class="giSubtitle">
    <div class="giHorizontalLinks">
      {if $can.edit}
      <span>
	<a href="{g->url arg1="return=true" arg2="view=core:ItemAdmin" arg3="subView=comment:EditComment" arg4="itemId=`$item.id`" arg5="commentId=`$comment.id`"}">
	  {g->text text="edit"}
	</a>
      </span>
      {/if}

      {if $can.delete}
      <span>
	<a href="{g->url arg1="return=true" arg2="view=core:ItemAdmin" arg3="subView=comment:DeleteComment" arg4="itemId=`$item.id`" arg5="commentId=`$comment.id`"}">
	  {g->text text="delete"}
	</a>
      </span>
      {/if}
    </div>
  </div>
  {/if}

  <div class="giDescription">
    {capture name="date"}{g->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}{/capture}
    {if isset($can.edit)}
    {g->text text="Posted by %s on %s (%s)" 
             arg1=$user.fullName|default:$user.userName
             arg2=$smarty.capture.date
             arg3=$comment.host}
    {else}
    {g->text text="Posted by %s on %s" 
             arg1=$user.fullName|default:$user.userName
             arg2=$smarty.capture.date}
    {/if}
  </div>

  {if isset($truncate)}
  {$comment.comment|truncate:$truncate|markup}
  {else}
  {$comment.comment|markup}
  {/if}
</div>

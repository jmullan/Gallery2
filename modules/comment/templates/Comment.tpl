{capture name="date"}{gallery->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}{/capture}
{gallery->detailedbox}
  {gallery->title}
    {$comment.subject}
  {/gallery->title}
  {gallery->description}
    {if isset($can.edit)}
      {gallery->text text="Posted by %s on %s (%s)" 
      arg1=$user.fullName|default:$user.userName
      arg2=$smarty.capture.date
      arg3=$comment.host}
    {else}
      {gallery->text text="Posted by %s on %s" 
      arg1=$user.fullName|default:$user.userName
      arg2=$smarty.capture.date}
    {/if}

    {if isset($can.edit) || isset($can.delete)}
      {gallery->linksbox}
	{if $can.edit}
	  {gallery->item}
	    {gallery->link url_return="true" url_view="core:ItemAdmin" url_subView="comment:EditComment" url_itemId=$item.id url_commentId=$comment.id}
	      {gallery->text text="edit"}
	    {/gallery->link}
	  {/gallery->item}
	{/if}
	{if $can.delete}
	  {gallery->item}
	    {gallery->link url_return="true" url_view="core:ItemAdmin" url_subView="comment:DeleteComment" url_itemId=$item.id url_commentId=$comment.id}
	      {gallery->text text="delete"}
	    {/gallery->link}
	  {/gallery->item}
	{/if}
      {/gallery->linksbox}
    {/if}
  {/gallery->description}
  {gallery->body}
    {if isset($truncate)}
      {$comment.comment|truncate:$truncate}
    {else}
      {$comment.comment}
    {/if}
  {/gallery->body}
{/gallery->detailedbox}

  {if !empty($comments)}
  <table width="100%" border="0" cellspacing="4" cellpadding="0">
    {if sizeof($comments) < $totalComments }
    <tr>
      <td align="center">
	{gallery->bigFontSize}
	{gallery->text text="Recent comments"}
	{/gallery->bigFontSize}
	{gallery->smallFontSize}
	<a href="{gallery->url view="comment:ShowComments" itemId=$item.id}">
	  {gallery->text text="(view all %d comments)" arg1=$totalComments}
	</a>
	{/gallery->smallFontSize}
      </td>
    </tr>
    {/if}
    {foreach from=$comments item=comment}
    <tr>
      <td width="100%">
	{gallery->lightFrame width="100%"}
	{gallery->highlight1}
	{gallery->bigFontSize}
	{$comment.commenter.userName}
	{/gallery->bigFontSize}
	{if !empty($comment.host)}
	{if $can.viewIp}
	({$comment.host})
	{/if}
	{/if}
	{if $can.edit}
	<a href="{gallery->url view="comment:EditComment"
	               itemId=$item.id
	               commentId=$comment.id
	               return_view="core:ShowItem"
	               return_itemId=$item.id}">
	  [{gallery->text text="edit"}]
	</a>
	{/if}
	{if $can.delete}
	<a href="{gallery->url view="comment:DeleteComment"
	               itemId=$item.id
	               commentId=$comment.id
	               return_view="core:ShowItem"
	               return_itemId=$item.id}">
	  [{gallery->text text="delete"}]
	</a>
	{/if}
	<br>
	{gallery->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}
	{/gallery->highlight1}
	{gallery->highlight2}
	{$comment.comment}
	{/gallery->highlight2}
	{/gallery->lightFrame}
      </td>
    </tr>
    {/foreach}
  </table>
  {/if}

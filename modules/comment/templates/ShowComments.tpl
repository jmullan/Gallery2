    <center>
      {if !empty($thumbnail)}
      <img src="{galleryUrl view='core:DownloadItem' itemId=$thumbnail.id}"
      {if $thumbnail.width} width="{$thumbnail.width}" {/if}
      {if $thumbnail.height} height="{$thumbnail.height}" {/if}
      >
      {else}
      {galleryBigFont}
      {galleryText text="There is no thumbnail for this item"}
      {/galleryBigFont}
      {/if}
      <br>
      <a href="{galleryUrl view="core:ShowItem" itemId=$item.id}">
	[{galleryText text="Return to item view"}]
      </a>
      {if $can.all || $can.add}
      <br>
      <a href="{galleryUrl view="comment:AddComment"
	                   itemId=$item.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	{galleryBigFont}
	[{galleryText text="Add a comment"}]
	{/galleryBigFont}
      </a>
      {/if}
    </center>
    
    {if empty($comments)}
    {galleryText text="There are no comments for this item"}
    {else}
    <table width="100%" border="0" cellspacing="4" cellpadding="0">
        <!-- {foreach from=$comments item=comment} -->
	<tr>
	  <td width="100%">
	    {galleryLightFrame width="100%"}
	    {galleryHighlight1}
	    {galleryBigFont}
	    {$comment.commenter.userName}
	    {/galleryBigFont}
	    {if !empty($comment.host)}
	    {if $can.all || $can.viewIps}
	    ({$comment.host})
	    {/if}
	    {/if}
	    {if $can.all || $can.edit}
	    <a href="{galleryUrl view="comment:EditComment"
	                   itemId=$item.id
	                   commentId=$comment.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	      [{galleryText text="edit"}]
	    </a>
	    {/if}
	    {if $can.all || $can.delete}
	    <a href="{galleryUrl view="comment:DeleteComment"
	                   itemId=$item.id
	                   commentId=$comment.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	      [{galleryText text="delete"}]
	    </a>
	    {/if}
	    <br>
	    {galleryDate timestamp=$comment.date format="%e-%b-%Y %H:%M"}
	    {/galleryHighlight1}
	    {galleryHighlight2}
	    {$comment.comment}
	    {/galleryHighlight2}
	    {/galleryLightFrame}
	  </td>
	</tr>
	<!-- {/foreach} -->
    </table>
    {/if}

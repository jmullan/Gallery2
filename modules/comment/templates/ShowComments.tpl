    <center>
      {if !empty($thumbnail)}
      <img src="{galleryUrl view='core:DownloadItem' itemId=$thumbnail.id}"
      {if $thumbnail.width} width="{$thumbnail.width}" {/if}
      {if $thumbnail.height} height="{$thumbnail.height}" {/if}
      >
      {else}
      {galleryBigFontSize}
      {galleryText text="There is no thumbnail for this item"}
      {/galleryBigFontSize}
      {/if}
      <br>
      <a href="{galleryUrl view="core:ShowItem" itemId=$item.id}">
	[{galleryText text="Return to item view"}]
      </a>
      {if $can.add}
      <br>
      <a href="{galleryUrl view="comment:AddComment"
	                   itemId=$item.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	{galleryBigFontSize}
	[{galleryText text="Add a comment"}]
	{/galleryBigFontSize}
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
	    {galleryBigFontSize}
	    {$comment.commenter.userName}
	    {/galleryBigFontSize}
	    {if !empty($comment.host)}
	    {if $can.viewIp}
	    ({$comment.host})
	    {/if}
	    {/if}
	    {if $can.edit}
	    <a href="{galleryUrl view="comment:EditComment"
	                   itemId=$item.id
	                   commentId=$comment.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	      [{galleryText text="edit"}]
	    </a>
	    {/if}
	    {if $can.delete}
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

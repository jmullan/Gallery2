    <center>
      {if !empty($thumbnail)}
      <img src="{gallery->url view='core:DownloadItem' itemId=$thumbnail.id}"
      {if $thumbnail.width} width="{$thumbnail.width}" {/if}
      {if $thumbnail.height} height="{$thumbnail.height}" {/if}
      >
      {else}
      {gallery->bigFontSize}
      {gallery->text text="There is no thumbnail for this item"}
      {/gallery->bigFontSize}
      {/if}
      <br>
      <a href="{gallery->url view="core:ShowItem" itemId=$item.id}">
	[{gallery->text text="Return to item view"}]
      </a>
      {if $can.add}
      <br>
      <a href="{gallery->url view="comment:AddComment"
	                   itemId=$item.id
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	{gallery->bigFontSize}
	[{gallery->text text="Add a comment"}]
	{/gallery->bigFontSize}
      </a>
      {/if}
    </center>
    
    {if empty($comments)}
    {gallery->text text="There are no comments for this item"}
    {else}
    <table width="100%" border="0" cellspacing="4" cellpadding="0">
        <!-- {foreach from=$comments item=comment} -->
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
	                   return_view="comment:ShowComments"
	                   return_itemId=$item.id}">
	      [{gallery->text text="edit"}]
	    </a>
	    {/if}
	    {if $can.delete}
	    <a href="{gallery->url view="comment:DeleteComment"
	                   itemId=$item.id
	                   commentId=$comment.id
	                   return_view="comment:ShowComments"
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
	<!-- {/foreach} -->
    </table>
    {/if}

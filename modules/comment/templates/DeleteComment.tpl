      {galleryForm controller=$controller}
      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      {galleryInput type="hidden" name="commentId"}{$comment.id}{/galleryInput}
      
      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {galleryInput type="hidden" name=$key|string_format:"return.%s"}{$value}{/galleryInput}
      {/foreach}
      
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

      {galleryBiggerFont}
      {galleryText text="Delete this comment?"}
      {/galleryBiggerFont}

      <br>

      <table>
	  <tr>
	    <td valign="top">
	      <b>{galleryText text="Commenter:"}</b>
	    </td>
	    <td>
	      {$commenter.userName}
	    </td>
	  </tr>
	  <tr>
	    <td valign="top">
	      <b>{galleryText text="Date:"}</b>
	    </td>
	    <td>
	      {galleryDate timestamp=$comment.date format="%e-%b-%Y %H:%M"}
	    </td>
	  </tr>
	  <tr>
	    <td valign="top">
	      <b>{galleryText text="Comment:"}</b>
	    </td>
	    <td>
	      {$comment.comment}
	    </td>
	  </tr>
	  <tr>
	    <td colspan="2" align="center">
	      {galleryInput type="submit" name="form.action.delete"}
	      {galleryText text="Delete"}
	      {/galleryInput}
	      {galleryInput type="submit" name="form.action.cancel"}
	      {galleryText text="Cancel"}
	      {/galleryInput}
	    </td>
	  </tr>
      </table>
    </center>
    {/galleryForm}
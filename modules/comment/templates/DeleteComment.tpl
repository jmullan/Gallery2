      {gallery->form controller=$controller}
      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
      {gallery->input type="hidden" name="commentId"}{$comment.id}{/gallery->input}
      
      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {gallery->input type="hidden" name=$key|string_format:"return.%s"}{$value}{/gallery->input}
      {/foreach}
      
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

      {gallery->biggerFontSize}
      {gallery->text text="Delete this comment?"}
      {/gallery->biggerFontSize}

      <br>

      <table>
	  <tr>
	    <td valign="top">
	      <b>{gallery->text text="Commenter:"}</b>
	    </td>
	    <td>
	      {$commenter.userName}
	    </td>
	  </tr>
	  <tr>
	    <td valign="top">
	      <b>{gallery->text text="Date:"}</b>
	    </td>
	    <td>
	      {gallery->date timestamp=$comment.date format="%e-%b-%Y %H:%M"}
	    </td>
	  </tr>
	  <tr>
	    <td valign="top">
	      <b>{gallery->text text="Comment:"}</b>
	    </td>
	    <td>
	      {$comment.comment}
	    </td>
	  </tr>
	  <tr>
	    <td colspan="2" align="center">
	      {gallery->input type="submit" name="form.action.delete"}
	      {gallery->text text="Delete"}
	      {/gallery->input}
	      {gallery->input type="submit" name="form.action.cancel"}
	      {gallery->text text="Cancel"}
	      {/gallery->input}
	    </td>
	  </tr>
      </table>
    </center>
    {/gallery->form}
  {galleryForm controller=$controller}
  {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
  {if !empty($thumbnail)}
  <center>
    <img src="{galleryUrl view='core:DownloadItem' itemId=$thumbnail.id}"
      {if $thumbnail.width} width="{$thumbnail.width}" {/if}
      {if $thumbnail.height} height="{$thumbnail.height}" {/if}
      >
  </center>
  <br>
  {/if}
  <center>
    <table border="0" cellspacing="0" cellpadding="5">
      <tr>
	<td align="center">
	  {galleryBigFont}{galleryText text="Add a comment for this item"}{/galleryBigFont}
	</td>
      </tr>
      <tr>
	<td>
	  {galleryTextArea rows="15" cols="60" name="comment"}{/galleryTextArea}
	</td>
      </tr>

      <tr>
	<td align="center">
	  {galleryInput type="submit" name="add"}{galleryText text="Save"}{/galleryInput}
	  {galleryInput type="submit" name="cancel"}{galleryText text="Cancel"}{/galleryInput}
	</td>
      </tr>
    </table>
  </center>
  {/galleryForm}
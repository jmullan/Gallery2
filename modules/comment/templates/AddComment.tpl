      {galleryForm controller=$controller}
      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      
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
      <i>{galleryText text="No thumbnail"}</i>
      {/if}
      <br>
      <b>
	{if empty($item.title)}
	{$item.pathComponent}
	{else}
	{$item.title}
	{/if}
      </b>
      <br>
      <table border="0" cellspacing="0" cellpadding="5">
	  <tr>
	    <td align="center">
	      {galleryBigFontSize}
	      {galleryText text="Add a comment for this item"}
	      {/galleryBigFontSize}
	    </td>
	  </tr>
	  <tr>
	    <td>
	      {galleryTextArea rows="15" cols="60" name="form.comment"}{/galleryTextArea}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {galleryInput type="submit" name="form.action.add"}{galleryText text="Save"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
	    </td>
	  </tr>
      </table>
    </center>
    {/galleryForm}
      {gallery->form controller=$controller}
      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
      
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
      <i>{gallery->text text="No thumbnail"}</i>
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
	      {gallery->bigFontSize}
	      {gallery->text text="Add a comment for this item"}
	      {/gallery->bigFontSize}
	    </td>
	  </tr>
	  <tr>
	    <td>
	      {gallery->textArea rows="15" cols="60" name="form.comment"}{/gallery->textArea}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallery->input type="submit" name="form.action.add"}{gallery->text text="Save"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	    </td>
	  </tr>
      </table>
    </center>
    {/gallery->form}
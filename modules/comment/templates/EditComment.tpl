      {galleryForm controller=$controller}

      {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
      {galleryInput type="hidden" name="commentId"}{$comment.id}{/galleryInput}
      {galleryInput type="hidden" name="formName"}EditComment{/galleryInput}
      
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
	    <td align="center" colspan="2">
	      {galleryBigFontSize}
	      {galleryText text="Edit comment"}
	      {/galleryBigFontSize}
	    </td>
	  </tr>
	  <tr>
	    <td>
	      {galleryText text="Commenter: "}
	    </td>
	    <td>
	      {galleryInput type="text" name="form.commenterName"}
	      {$form.commenterName}
	      {/galleryInput}
	    </td>
	  </tr>

	  <!-- {if !empty($form.error.missingCommenterName)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {galleryErrorFontColor}
	      {galleryText text="You must enter a username."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <!-- {if !empty($form.error.invalidCommenterName)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {galleryErrorFontColor}
	      {galleryText text="The username you entered is invalid."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <tr>
	    <td>
	      {galleryText text="Host: "}
	    </td>
	    <td>
	      {galleryInput type="text" name="form.host"}
	      {$form.host}
	      {/galleryInput}
	    </td>
	  </tr>

	  <tr>
	    <td>
	      {galleryText text="Date: "}
	    </td>
	    <td>
	      {galleryInput type="text" name="form.date"}
	      {galleryDate timestamp=$form.date format="%e-%b-%Y %H:%M"}
	      {/galleryInput}
	    </td>
	  </tr>
	  
	  <!-- {if !empty($form.error.invalidDate)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {galleryErrorFontColor}
	      {galleryText text="The date you entered is invalid."}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <!-- {if !empty($form.error.missingDate)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {galleryErrorFontColor}
	      {galleryText text="You must enter a date"}
	      {/galleryErrorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <tr>
	    <td>
	      {galleryText text="Comment: "}
	    </td>
	    <td>
	      {strip}
	      {galleryTextArea rows="15" cols="60" name="form.comment"}
	      {$form.comment}
	      {/galleryTextArea}
	      {/strip}
	    </td>
	  </tr>

	  <tr>
	    <td colspan="2" align="center">
	      {galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
	    </td>
	  </tr>
      </table>
    </center>
    {/galleryForm}
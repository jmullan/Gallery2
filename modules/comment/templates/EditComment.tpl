      {gallery->form controller=$controller}

      {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
      {gallery->input type="hidden" name="commentId"}{$comment.id}{/gallery->input}
      {gallery->input type="hidden" name="formName"}EditComment{/gallery->input}
      
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
	    <td align="center" colspan="2">
	      {gallery->bigFontSize}
	      {gallery->text text="Edit comment"}
	      {/gallery->bigFontSize}
	    </td>
	  </tr>
	  <tr>
	    <td>
	      {gallery->text text="Commenter: "}
	    </td>
	    <td>
	      {gallery->input type="text" name="form.commenterName"}
	      {$form.commenterName}
	      {/gallery->input}
	    </td>
	  </tr>

	  <!-- {if !empty($form.error.missingCommenterName)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {gallery->errorFontColor}
	      {gallery->text text="You must enter a username."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <!-- {if !empty($form.error.invalidCommenterName)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {gallery->errorFontColor}
	      {gallery->text text="The username you entered is invalid."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <tr>
	    <td>
	      {gallery->text text="Host: "}
	    </td>
	    <td>
	      {gallery->input type="text" name="form.host"}
	      {$form.host}
	      {/gallery->input}
	    </td>
	  </tr>

	  <tr>
	    <td>
	      {gallery->text text="Date: "}
	    </td>
	    <td>
	      {gallery->input type="text" name="form.date"}
	      {gallery->date timestamp=$form.date format="%e-%b-%Y %H:%M"}
	      {/gallery->input}
	    </td>
	  </tr>
	  
	  <!-- {if !empty($form.error.invalidDate)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {gallery->errorFontColor}
	      {gallery->text text="The date you entered is invalid."}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <!-- {if !empty($form.error.missingDate)} -->
	  <tr>
	    <td>
	      &nbsp;
	    </td>
	    <td>
	      {gallery->errorFontColor}
	      {gallery->text text="You must enter a date"}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  <!-- {/if} -->

	  <tr>
	    <td>
	      {gallery->text text="Comment: "}
	    </td>
	    <td>
	      {strip}
	      {gallery->textArea rows="15" cols="60" name="form.comment"}
	      {$form.comment}
	      {/gallery->textArea}
	      {/strip}
	    </td>
	  </tr>

	  <tr>
	    <td colspan="2" align="center">
	      {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	    </td>
	  </tr>
      </table>
    </center>
    {/gallery->form}
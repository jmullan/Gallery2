    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditGeneral{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFontSize}
	    {galleryText text="General Item Properties"}
	    {/galleryBiggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Name"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The name represents the location of this item on your hard drive.  It is not visible anywhere, except possibly in the URL.  It must be unique in this album.  <b>Note:</b> You can only use alphanumeric characters, underscore (_) and hyphen (-) in your names."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {strip}
	    {foreach from=$parents item=parent}
	    {if empty($parent.parentId)}
	    /
	    {else}
	    {$parent.pathComponent}/
	    {/if}
	    {/foreach}
	    {/strip}
	    {galleryInput type=text size=40 name="form.pathComponent"}{$form.pathComponent}{/galleryInput}
	  </td>
	</tr>

        {if !empty($form.error.pathComponent.invalid)}
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="Your name contains invalid characters.  Please enter another."}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
        {/if}

        {if !empty($form.error.pathComponent.collision)}
	<tr>
	  <td>
	    {galleryErrorFontColor}
	    {galleryText text="The name you entered is already in use.  Please enter another."}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
        {/if}

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Title"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The title can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type=text size=40 name="form.title"}{$form.title}{/galleryInput}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Summary"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The summary can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type=text size=40 name="form.summary"}{$form.summary}{/galleryInput}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Keywords"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Keywords will not be visible to the end user, but are searchable. This can be any character string.  It should not contain HTML."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryTextArea rows=2 cols=60 name="form.keywords"}{$form.keywords}{/galleryTextArea}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFontSize}
	    {galleryText text="Description"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="A longer description of this item."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryTextArea rows=8 cols=60 name="form.description"}{$form.description}{/galleryTextArea}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	    {galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	  </td>
	</tr>

    </table>
    {/galleryForm}

    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="form.formName"}ItemEditDataItem{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="General Item Properties"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Name"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="The name represents the location of this item on your hard drive.  It is not visible anywhere, except possibly in the URL.  It must be unique in this album.  <b>Note:</b> You can only use alphanumeric characters, underscore (_) and hyphen (-) in your names."}
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
	    {gallery->input type=text size=40 name="form.pathComponent"}{$form.pathComponent}{/gallery->input}
	  </td>
	</tr>

        {if !empty($form.error.pathComponent.invalid)}
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="Your name contains invalid characters.  Please choose another."}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
        {/if}

        {if !empty($form.error.pathComponent.missing)}
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a name for this item."}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
        {/if}

        {if !empty($form.error.pathComponent.collision)}
	<tr>
	  <td>
	    {gallery->errorFontColor}
	    {gallery->text text="The name you entered is already in use.  Please choose another."}
	    {/gallery->errorFontColor}
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
	    {gallery->bigFontSize}
	    {gallery->text text="Title"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="The title can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type=text size=40 name="form.title"}{$form.title}{/gallery->input}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Summary"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="The summary can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type=text size=40 name="form.summary"}{$form.summary}{/gallery->input}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Keywords"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Keywords will not be visible to the end user, but are searchable. This can be any character string.  It should not contain HTML."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->textArea rows=2 cols=60 name="form.keywords"}{$form.keywords}{/gallery->textArea}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Description"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="A longer description of this item."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->textArea rows=8 cols=60 name="form.description"}{$form.description}{/gallery->textArea}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	  </td>
	</tr>

    </table>
    {/gallery->form}

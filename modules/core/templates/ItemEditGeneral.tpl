    {galleryForm controller="$controller"}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFont}
	    {galleryText text="General Item Properties"}
	    {/galleryBiggerFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Title"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The title can be any character string, and should not contain any HTML"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput size=40 name="form.item.title"}{$form.item.title}{/galleryInput}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Name"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="The name must be unique in this album.  NOTE: The name cannot contain any of the following characters: \ / * ? &quot; ' &amp; < > | . + # or spaces"}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput size=40 name="form.item.pathComponent"}{$form.item.pathComponent}{/galleryInput}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Keywords"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Keywords will not be visible to the end user, but are searchable. This can be any character string.  It should not contain HTML."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryTextArea rows=2 cols=60 name="form.item.keywords"}{$form.item.keywords}{/galleryTextArea}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Description"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="A longer description of this item."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryTextArea rows=8 cols=60 name="form.item.description"}{$form.item.description}{/galleryTextArea}
	  </td>
	</tr>

    </table>
    {/galleryForm}

    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="form.formName"}ItemEditAlbum{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Album Settings"}
	      {/gallery->biggerFontSize}
	    </center>
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
	  {gallery->text text="Sort order"}
	  {/gallery->bigFontSize}
	  <br>
	  {gallery->text text="How the items in this album are sorted.  New items that are added will be placed in the album according to the order you specify here."}
	  <br>
	  {gallery->select name="form.orderBy"}
	  {html_options options=$orderByList selected=$form.orderBy}
	  {/gallery->select}
	  {gallery->select name="form.orderDirection"}
	  {html_options options=$orderDirectionList selected=$form.orderDirection}
	  {/gallery->select}
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
	    {gallery->text text="Layout"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="The way that items will be arranged on the page when viewing this album."}
	    <br>
	    {gallery->select name="form.layout"}
	    {html_options values=$layoutList selected=$form.layout output=$layoutList}
	    {/gallery->select}
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
	    {gallery->text text="Theme"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="The colors and images that will be used when viewing this album."}
	    <br>
	    {gallery->select name="form.theme"}
	    {html_options values=$themeList selected=$form.theme output=$themeList}
	    {/gallery->select}
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
	    {gallery->text text="Thumbnails"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Every item will have a thumbnail.  The default thumbnail size you specify here will create a uniform look for your album.  Gallery will create a thumbnail that is no larger than the size you specify."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Size (in pixels): "}
	    {gallery->input type=text size=6 name="form.thumbnail.size"}{$form.thumbnail.size}{/gallery->input}
	  </td>
	</tr>

	{if !empty($form.error.thumbnail.size.missing)}
        <tr>
          <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a thumbnail size"}
	    {/gallery->errorFontColor}
          </td>
        </tr>
        {/if}

	{if !empty($form.error.thumbnail.size.invalid)}
        <tr>
          <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a number (greater than zero)"}
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
	    {gallery->text text="Resized Images"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Gallery can automatically create intermediate resized versions of images added to this album.  This is useful when you want to present larger versions of an image without showing the full size image."}
	  </td>
	</tr>
	
	<tr>
	  <td>
	    <table cellspacing="0" cellpadding="0" border="0" width="100%">
		<tr>
		  <td align="center">
		    <b>{gallery->text text="Active"}</b>
		  </td>
		  <td align="left">
		    <b>{gallery->text text="Target Size (in pixels)"}</b>
		  </td>
		</tr>

	        {counter start=0 assign=index}
		{foreach from=$form.resizes item=resize}
		<tr>
		  <td align="center">
		    {gallery->input type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/gallery->input}
		  </td>
		  <td align="left">
		    {gallery->input type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/gallery->input}
		  </td>
		</tr>

	        {if !empty($form.error.resizes.$index.size.missing)}
                <tr>
	          <td>
	            &nbsp;
	          </td>
                  <td>
	            {gallery->errorFontColor}
	            {gallery->text text="You must enter a valid size"}
	            {/gallery->errorFontColor}
                  </td>
                </tr>
                {/if}
	        
	        {if !empty($form.error.resizes.$index.size.invalid)}
                <tr>
	          <td>
	            &nbsp;
	          </td>
                  <td>
	            {gallery->errorFontColor}
	            {gallery->text text="You must enter a number (greater than zero)"}
	            {/gallery->errorFontColor}
                  </td>
                </tr>
                {/if}

                {counter}
	        {/foreach}
	    </table>
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
	    {gallery->text text="Recreate thumbnails and resizes"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="When you make changes to the values of the thumbnail size and/or the size of the resized images, this will only apply to newly uploaded images. Other images remain with their currently (possibly customized) thumbnails and resizes. Click here to recreate the thumbnails and/or resizes based on the new information."}
	    <br>
	    {gallery->input type="checkbox" name="form.recreateThumbnails"}{$form.recreateThumbnails}{/gallery->input}
	    {gallery->text text="Recreate thumbnails"}
	    <br>
	    {gallery->input type="checkbox" name="form.recreateResizes"}{$form.recreateResizes}{/gallery->input}
	    {gallery->text text="Recreate resized images"}
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

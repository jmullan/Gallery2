    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditChildPreferences{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$itemId}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {galleryBiggerFont}
	      {galleryText text="Sub-Item Preferences"}
	      {/galleryBiggerFont}
	    </center>
	    <br>
	    <br>
	    {galleryText text="Here you can choose default values for items in this album.  These values will only apply to new items that are added to the album, not ones that are already in it."}
	    <br>
	    <br>
	    {galleryText text="When Gallery resizes images, it will maintain the same aspect ratio (height to width) of the original image to avoid distortion.  For resizes, you only enter one value and that forms a bounding box (in pixels).  Gallery will resize the image until it is as large as possible while still fitting inside the box."} 
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
	    {galleryText text="Thumbnails"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Every item will have a thumbnail.  The default thumbnail size you specify here will create a uniform look for your album.  You must enter a number greater than 0."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Size (in pixels): "}
	    {galleryInput type=text size=6 name="form.thumbnail.size"}{$form.thumbnail.size}{/galleryInput}
	  </td>
	</tr>

	{if !empty($form.error.thumbnail.size.missing)}
        <tr>
          <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a thumbnail size"}
	    {/galleryErrorFontColor}
          </td>
        </tr>
        {/if}

	{if !empty($form.error.thumbnail.size.invalid)}
        <tr>
          <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a number (greater than zero)"}
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
	    {galleryBigFont}
	    {galleryText text="Resized Images"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Gallery can automatically create intermediate resized versions of images added to this album.  This is useful when you want to present larger versions of an image without showing the full size image."}
	  </td>
	</tr>
	
	<tr>
	  <td>
	    <table cellspacing="0" cellpadding="0" border="0" width="100%">
		<tr>
		  <td align="center">
		    <b>{galleryText text="Active"}</b>
		  </td>
		  <td align="left">
		    <b>{galleryText text="Target Size (in pixels)"}</b>
		  </td>
		</tr>

	        {counter start=0 assign=index}
		{foreach from=$form.resizes item=resize}
		<tr>
		  <td align="center">
		    {galleryInput type="checkbox" name="form.resizes.$index.active"}{$form.resizes.$index.active}{/galleryInput}
		  </td>
		  <td align="left">
		    {galleryInput type="text" size="6" name="form.resizes.$index.size"}{$form.resizes.$index.size}{/galleryInput}
		  </td>
		</tr>

	        {if !empty($form.error.resizes.$index.size.missing)}
                <tr>
	          <td>
	            &nbsp;
	          </td>
                  <td>
	            {galleryErrorFontColor}
	            {galleryText text="You must enter a valid size"}
	            {/galleryErrorFontColor}
                  </td>
                </tr>
                {/if}
	        
	        {if !empty($form.error.resizes.$index.size.invalid)}
                <tr>
	          <td>
	            &nbsp;
	          </td>
                  <td>
	            {galleryErrorFontColor}
	            {galleryText text="You must enter a number (greater than zero)"}
	            {/galleryErrorFontColor}
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
	    {galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	    {galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	  </td>
	</tr>

    </table>
    {/galleryForm}

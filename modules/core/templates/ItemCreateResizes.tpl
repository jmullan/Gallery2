    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemCreateResizes{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {galleryBiggerFontSize}
	      {galleryText text="Item Thumbnail Size and Resizes"}
	      {/galleryBiggerFontSize}
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
	    {galleryBigFontSize}
	    {galleryText text="Thumbnails"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Gallery will create a thumbnail that is no larger than the size you specify here."}
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
	    {galleryBigFontSize}
	    {galleryText text="Resized Images"}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Other intermediate resized versions of this image."}
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

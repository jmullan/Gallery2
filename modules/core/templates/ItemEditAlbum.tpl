    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditAlbum{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {galleryBiggerFontSize}
	      {galleryText text="Album Settings"}
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
	  {galleryText text="Sort order"}
	  {/galleryBigFontSize}
	  <br>
	  {galleryText text="How the items in this album are sorted.  New items that are added will be placed in the album according to the order you specify here."}
	  <br>
	  {gallerySelect name="form.orderBy"}
	  {html_options options=$orderByList selected=$form.orderBy}
	  {/gallerySelect}
	  {gallerySelect name="form.orderDirection"}
	  {html_options options=$orderDirectionList selected=$form.orderDirection}
	  {/gallerySelect}
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
	    {galleryText text="Layout"}
	    {/galleryBigFontSize}
	    <br>
	    {galleryText text="The way that items will be arranged on the page when viewing this album."}
	    <br>
	    {gallerySelect name="form.layout"}
	    {html_options values=$layoutList selected=$form.layout output=$layoutList}
	    {/gallerySelect}
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
	    {galleryText text="Theme"}
	    {/galleryBigFontSize}
	    <br>
	    {galleryText text="The colors and images that will be used when viewing this album."}
	    <br>
	    {gallerySelect name="form.theme"}
	    {html_options values=$themeList selected=$form.theme output=$themeList}
	    {/gallerySelect}
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
	    {galleryText text="Every item will have a thumbnail.  The default thumbnail size you specify here will create a uniform look for your album.  Gallery will create a thumbnail that is no larger than the size you specify."}
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

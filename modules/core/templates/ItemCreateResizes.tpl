    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="form.formName"}ItemCreateResizes{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Item Thumbnail Size and Resizes"}
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
	    {gallery->text text="Thumbnails"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Gallery will create a thumbnail that is no larger than the size you specify here."}
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
	    {gallery->text text="Other intermediate resized versions of this image."}
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
	    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	  </td>
	</tr>

    </table>
    {/gallery->form}

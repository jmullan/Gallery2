    {gallery->form controller="$controller"}
    {gallery->input type="hidden" name="form.formName"}ItemEditImage{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="Edit Image"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	   {gallery->text text="Certain image manipulation operations (such as rotating and scaling) can cause a permanent change to the original image.  In these cases, Gallery avoids modifying the original image by creating a duplicate that is rotated or scaled to the dimensions that you prefer.  Future operations (viewing, modifying) apply to the duplicate leaving your original image intact.  This preserves your original image, but will consume more disk space."}
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
	    {gallery->text text="Rotate"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="You can only rotate the image in 90 degree increments."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.rotate.counterClockwise"}
	    {gallery->text text="Counter-Clockwise 90&deg;"}
	    {/gallery->input}
	    {gallery->input type="submit" name="form.action.rotate.flip"}
	    {gallery->text text="Flip 180&deg;"}
	    {/gallery->input}
	    {gallery->input type="submit" name="form.action.rotate.clockwise"}
	    {gallery->text text="Clockwise 90&deg;"}
	    {/gallery->input}
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
	    {gallery->text text="Scale"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Shrink or enlarge the original image.  When Gallery scales an image, it maintains the same aspect ratio (height to width) of the original image to avoid distortion.  The value you enter below forms a bounding box in pixels.  Gallery will scale the image until it is as large as possible while still fitting inside the box."}
	  </td> 
	</tr>

	<tr>
	  <td>
	    {gallery->text text="Target size (in pixels):"}
	    {gallery->input type="text" size="6" name="form.scale.size"}{$form.scale.size}{/gallery->input}
	    {gallery->input type="submit" name="form.action.scale"}
	    {gallery->text text="Scale"}
	    {/gallery->input}
	  </td>
	</tr>

	{if !empty($form.error.scale.size.missing)}
        <tr>
          <td>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a size"}
	    {/gallery->errorFontColor}
          </td>
        </tr>
        {/if}

	{if !empty($form.error.scale.size.invalid)}
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

	{if empty($hasPreferredSource)}
	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Preserve Original"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	   {gallery->text text="Disabling this option will cause any actions to happen to the original image.  This will permanently change your original image!"}
	   <br>
	   {gallery->input type="checkbox" name="form.preserveOriginal"}{$form.preserveOriginal}{/gallery->input} {gallery->text text="Preserve Original Image"}
	  </td>
	</tr>
        {else}
	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Modified Image"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	   {gallery->text text="You are using a copy of the original image that has been scaled or rotated.  The original image is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
	   <br>
	   {gallery->input type="submit" name="form.action.revertToOriginal"}
	   {gallery->text text="Revert to original"}
	   {/gallery->input}
	  </td>
	</tr>
        {/if}

    </table>
    {/gallery->form}

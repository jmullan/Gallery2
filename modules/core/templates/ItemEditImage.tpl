    {galleryForm controller="$controller"}
    {galleryInput type="hidden" name="formName"}ItemEditImage{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td align="center">
	    {galleryBiggerFont}
	    {galleryText text="Edit Image"}
	    {/galleryBiggerFont}
	  </td>
	</tr>

	<tr>
	  <td>
	   {galleryText text="Certain image manipulation operations (such as rotating and scaling) can cause a permanent change to the original image.  In these cases, Gallery avoids modifying the original image by creating a duplicate that is rotated or scaled to the dimensions that you prefer.  Future operations (viewing, modifying) apply to the duplicate leaving your original image intact.  This preserves your original image, but will consume more disk space."}
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
	    {galleryText text="Rotate"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="You can only rotate the image in 90 degree increments."}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryInput type="submit" name="form.action.rotate.counterClockwise"}
	    {galleryText text="Counter-Clockwise 90&ordm;"}
	    {/galleryInput}
	    {galleryInput type="submit" name="form.action.rotate.flip"}
	    {galleryText text="Flip 180&ordm;"}
	    {/galleryInput}
	    {galleryInput type="submit" name="form.action.rotate.clockwise"}
	    {galleryText text="Clockwise 90&ordm;"}
	    {/galleryInput}
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
	    {galleryText text="Scale"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	    {galleryText text="Shrink or enlarge the original image.  When Gallery scales an image, it maintains the same aspect ratio (height to width) of the original image to avoid distortion.  The value you enter below forms a bounding box in pixels.  Gallery will scale the image until it is as large as possible while still fitting inside the box."}
	  </td> 
	</tr>

	<tr>
	  <td>
	    {galleryText text="Target size (in pixels):"}
	    {galleryInput type="text" size="6" name="form.scale.size"}{$form.scale.size}{/galleryInput}
	    {galleryInput type="submit" name="form.action.scale"}
	    {galleryText text="Scale"}
	    {/galleryInput}
	  </td>
	</tr>

	{if !empty($form.error.scale.size.missing)}
        <tr>
          <td>
	    {galleryErrorFontColor}
	    {galleryText text="You must enter a size"}
	    {/galleryErrorFontColor}
          </td>
        </tr>
        {/if}

	{if !empty($form.error.scale.size.invalid)}
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

	{if empty($hasPreferredSource)}
	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Preserve Original"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	   {galleryText text="Disabling this option will cause any actions to happen to the original image.  This will permanently change your original image!"}
	   <br>
	   {galleryInput type="checkbox" name="form.preserveOriginal"}{$form.preserveOriginal}{/galleryInput} {galleryText text="Preserve Original Image"}
	  </td>
	</tr>
        {else}
	<tr>
	  <td>
	    {galleryBigFont}
	    {galleryText text="Modified Image"}
	    {/galleryBigFont}
	  </td>
	</tr>

	<tr>
	  <td>
	   {galleryText text="You are using a copy of the original image that has been scaled or rotated.  The original image is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
	   <br>
	   {galleryInput type="submit" name="form.action.revertToOriginal"}
	   {galleryText text="Revert to original"}
	   {/galleryInput}
	  </td>
	</tr>
        {/if}

    </table>
    {/galleryForm}

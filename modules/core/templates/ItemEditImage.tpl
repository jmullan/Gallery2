{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Edit Image"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.rotatedImage)}
	  {gallery->text text="Rotated image successfully"}
	{/if}
	{if isset($status.scaledImage)}
	  {gallery->text text="Scaled image successfully"}
	{/if}
	{if isset($status.revertedImage)}
	  {gallery->text text="Restored original image successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Rotate"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="You can only rotate the image in 90 degree increments."}
  {/gallery->description}

  {gallery->body}
    {gallery->input type="submit" name="form.action.rotate.counterClockwise"}
      {gallery->text text="CC 90&deg;"}
    {/gallery->input}
    &nbsp;
    {gallery->input type="submit" name="form.action.rotate.flip"}
      {gallery->text text="180&deg;"}
    {/gallery->input}
    &nbsp;
    {gallery->input type="submit" name="form.action.rotate.clockwise"}
      {gallery->text text="C 90&deg;"}
    {/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Scale"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="Shrink or enlarge the original image.  When Gallery scales an image, it maintains the same aspect ratio (height to width) of the original image to avoid distortion.  The value you enter below (in pixels) forms a bounding box.  Gallery will scale the image until it is as large as possible while still fitting inside the box."}
  {/gallery->description}
  
  {gallery->body}
    {gallery->input type="text" size="6" name="form.scale.size"}{$form.scale.size}{/gallery->input}
    {gallery->input type="submit" name="form.action.scale"}
      {gallery->text text="Scale"}
    {/gallery->input}

    {if !empty($form.error.scale.size.missing)}
      {gallery->error}
	{gallery->text text="You must enter a size"}
      {/gallery->error}
    {/if}

    {if !empty($form.error.scale.size.invalid)}
      {gallery->error}
	{gallery->text text="You must enter a number (greater than zero)"}
      {/gallery->error}
    {/if}
  {/gallery->body}
{/gallery->detailedbox}

{if empty($ItemEditImage.hasPreferredSource)}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="Preserve Original"}
    {/gallery->title}

    {gallery->description}
      {gallery->text text="Gallery does not modify your original image when rotating and scaling. Instead, it duplicates your image and works with copies.  This requires a little extra disk space.  Disabling this option will cause any actions to happen to the original image.  This will permanently change your original image!"}
    {/gallery->description}

    {gallery->body}
      {gallery->input type="checkbox" name="form.preserveOriginal"}{$form.preserveOriginal}{/gallery->input} {gallery->text text="Preserve Original Image"}
    {/gallery->body}
  {/gallery->detailedbox}
{else}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="Modified Image"}
    {/gallery->title}

    {gallery->description}
      {gallery->text text="You are using a copy of the original image that has been scaled or rotated.  The original image is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
    {/gallery->description}

    {gallery->body}
      {gallery->input type="submit" name="form.action.revertToOriginal"}
	{gallery->text text="Restore original"}
      {/gallery->input}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit Image"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.rotatedImage)}
	{g->text text="Rotated image successfully"}
      {/if}
      {if isset($status.scaledImage)}
	{g->text text="Scaled image successfully"}
      {/if}
      {if isset($status.revertedImage)}
	{g->text text="Restored original image successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Rotate"}
    {/g->title}

    {g->description}
      {g->text text="You can only rotate the image in 90 degree increments."}
    {/g->description}

    {g->element}
      {g->input type="submit" name="form.action.rotate.counterClockwise"}
	{g->text text="CC 90&deg;"}
      {/g->input}
      &nbsp;
      {g->input type="submit" name="form.action.rotate.flip"}
	{g->text text="180&deg;"}
      {/g->input}
      &nbsp;
      {g->input type="submit" name="form.action.rotate.clockwise"}
	{g->text text="C 90&deg;"}
      {/g->input}
    {/g->element}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Scale"}
    {/g->title}

    {g->description}
      {g->text text="Shrink or enlarge the original image.  When Gallery scales an image, it maintains the same aspect ratio (height to width) of the original image to avoid distortion.  The value you enter below (in pixels) forms a bounding box.  Gallery will scale the image until it is as large as possible while still fitting inside the box."}
    {/g->description}
    
    {g->element}
      {g->input type="text" size="6" name="form.scale.size"}{$form.scale.size}{/g->input}
      {g->input type="submit" name="form.action.scale"}
	{g->text text="Scale"}
      {/g->input}
    {/g->element}

    {if !empty($form.error.scale.size.missing)}
      {g->error}
	{g->text text="You must enter a size"}
      {/g->error}
    {/if}

    {if !empty($form.error.scale.size.invalid)}
      {g->error}
	{g->text text="You must enter a number (greater than zero)"}
      {/g->error}
    {/if}
  {/g->box}

  {g->box style="admin"}
    {if empty($ItemEditImage.hasPreferredSource)}
      {g->title}
	{g->text text="Preserve Original"}
      {/g->title}

      {g->description}
	{g->text text="Gallery does not modify your original image when rotating and scaling. Instead, it duplicates your image and works with copies.  This requires a little extra disk space but prevents your original from getting damaged.  Disabling this option will cause any actions (rotating, scaling, etc) to modify the original."}
      {/g->description}

      {g->element}
	{g->input type="checkbox" name="form.preserveOriginal"}{$form.preserveOriginal}{/g->input} {g->text text="Preserve Original Image"}
      {/g->element}
    {else}
      {g->title}
	{g->text text="Modified Image"}
      {/g->title}

      {g->description}
	{g->text text="You are using a copy of the original image that has been scaled or rotated.  The original image is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
      {/g->description}

      {g->element}
	{g->input type="submit" name="form.action.revertToOriginal"}
	  {g->text text="Restore original"}
	{/g->input}
      {/g->element}
    {/if}
  {/g->box}
{/g->pagebox}

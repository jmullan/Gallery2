{g->box style="admin"}
  {g->title}
    {g->text text="Rotate"}
  {/g->title}

  {g->description}
    {g->text text="You can only rotate the photo in 90 degree increments."}
  {/g->description}

  {if $ItemEditRotateAndScalePhoto.editPhoto.can.rotate}
    {g->element}
      {g->input type="hidden" name="mode"}editPhoto{/g->input}
      {g->input type="submit" name="form[action][rotate][counterClockwise]"}
	{g->text text="CC 90&deg;"}
      {/g->input}
      &nbsp;
      {g->input type="submit" name="form[action][rotate][flip]"}
	{g->text text="180&deg;"}
      {/g->input}
      &nbsp;
      {g->input type="submit" name="form[action][rotate][clockwise]"}
	{g->text text="C 90&deg;"}
      {/g->input}
    {/g->element}
  {else}
    {g->element style="emphasized"}
      {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot rotate it."}
      {if $ItemEditRotateAndScalePhoto.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {/if}
{/g->box}

{g->box style="admin"}
  {g->title}
    {g->text text="Scale"}
  {/g->title}

  {g->description}
    {g->text text="Shrink or enlarge the original photo.  When Gallery scales a photo, it maintains the same aspect ratio (height to width) of the original photo to avoid distortion.  The value you enter below (in pixels) forms a bounding box.  Gallery will scale the photo until it is as large as possible while still fitting inside the box."}
  {/g->description}
  

  {if $ItemEditRotateAndScalePhoto.editPhoto.can.scale}
    {g->element}
      {g->input type="text" size="6" name="form[scale][size]"}{$form.scale.size}{/g->input}
      {g->input type="submit" name="form[action][scale]"}
	{g->text text="Scale"}
      {/g->input}
    {/g->element}
  {else}
    {g->element style="emphasized"}
      {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot scale it."}
      {if $ItemEditRotateAndScalePhoto.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {/if}

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

{if $ItemEditRotateAndScalePhoto.editPhoto.can.rotate || $ItemEditRotateAndScalePhoto.editPhoto.can.scale}
  {g->box style="admin"}
    {if empty($ItemEditRotateAndScalePhoto.editPhoto.hasPreferredSource)}
      {g->title}
	{g->text text="Preserve Original"}
      {/g->title}

      {g->description}
	{g->text text="Gallery does not modify your original photo when rotating and scaling. Instead, it duplicates your photo and works with copies.  This requires a little extra disk space but prevents your original from getting damaged.  Disabling this option will cause any actions (rotating, scaling, etc) to modify the original."}
      {/g->description}

      {if $ItemEditRotateAndScalePhoto.editPhoto.isLinked}
	{g->element style="emphasized"}
	  {g->text text="This is a link to another photo, so you cannot change the original"}
	{/g->element}
      {else}
	{if $ItemEditRotateAndScalePhoto.editPhoto.isLinkedTo}
	  {g->element style="emphasized"}
	    {g->text text="There are links to this photo, so you cannot change the original"}
	  {/g->element}
	{else}
	  {g->element}
	    {g->input type="checkbox" name="form[preserveOriginal]"}{$form.preserveOriginal}{/g->input} {g->text text="Preserve Original Photo"}
	  {/g->element}
	{/if}
      {/if}
    {else}
      {g->title}
	{g->text text="Modified Photo"}
      {/g->title}

      {g->description}
	{g->text text="You are using a copy of the original photo that has been scaled or rotated.  The original photo is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
      {/g->description}

      {g->element}
	{g->input type="submit" name="form[action][revertToOriginal]"}
	  {g->text text="Restore original"}
	{/g->input}
      {/g->element}
    {/if}
  {/g->box}
{/if}


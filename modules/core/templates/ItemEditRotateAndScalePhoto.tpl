{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEditRotateAndScalePhoto.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Rotate"}
  </h2>

  <p class="giDescription">
    {g->text text="You can only rotate the photo in 90 degree increments."}
  </p>

  {if $ItemEditRotateAndScalePhoto.editPhoto.can.rotate}
  <input type="hidden" name="{g->formVar var="mode"}" value="editPhoto"/>
  <input type="submit" name="{g->formVar var="form[action][rotate][counterClockwise]"}" value="{g->text text="CC 90&deg;"}"/>
  &nbsp;
  <input type="submit" name="{g->formVar var="form[action][rotate][flip]"}" value="{g->text text="180&deg;"}"/>
  &nbsp;
  <input type="submit" name="{g->formVar var="form[action][rotate][clockwise]"}" value="{g->text text="C 90&deg;"}"/>
  {else}
  <b>
    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot rotate it."}
    {if $ItemEditRotateAndScalePhoto.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}">
      {g->text text="site admin"}
    </a>
    {/if}
  </b>
  {/if}
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Scale"}
  </h2>
  
  <p class="giDescription">
    {g->text text="Shrink or enlarge the original photo.  When Gallery scales a photo, it maintains the same aspect ratio (height to width) of the original photo to avoid distortion.  Your photo will be scaled until the larger side is the same as the value you enter here."}
  </p>
  
  {if $ItemEditRotateAndScalePhoto.editPhoto.can.scale}
  <input type="text" size="6" name="{g->formVar var="form[scale][size]"}" value="{$form.scale.size}"/>
  <input type="submit" name="{g->formVar var="form[action][scale]"}" value="{g->text text="Scale"}"/>
  {else}
  <b>
    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot scale it."}
    {if $ItemEditRotateAndScalePhoto.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}">
      {g->text text="site admin"}
    </a>
    {/if}
  </b>
  {/if}

  {if !empty($form.error.scale.size.missing)}
  <div class="giError">
    {g->text text="You must enter a size"}
  </div>
  {/if}
  
  {if !empty($form.error.scale.size.invalid)}
  <div class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </div>
  {/if}
</div>

{* Include our extra ItemEditOptions *}
{foreach from=$ItemEdit.options item=option}
  {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
{/foreach}

{if $ItemEditRotateAndScalePhoto.editPhoto.can.rotate || $ItemEditRotateAndScalePhoto.editPhoto.can.scale}
<div class="gbAdmin">
  {if empty($ItemEditRotateAndScalePhoto.editPhoto.hasPreferredSource)}
  <h2 class="giTitle">
    {g->text text="Preserve Original"}
  </h2>

  <p class="giDescription">
    {g->text text="Gallery does not modify your original photo when rotating and scaling. Instead, it duplicates your photo and works with copies.  This requires a little extra disk space but prevents your original from getting damaged.  Disabling this option will cause any actions (rotating, scaling, etc) to modify the original."}
  </p>

  {if $ItemEditRotateAndScalePhoto.editPhoto.isLinked}
  <b>
    {g->text text="This is a link to another photo, so you cannot change the original"}
  </b>
  {else if $ItemEditRotateAndScalePhoto.editPhoto.isLinkedTo}
  <b>
    {g->text text="There are links to this photo, so you cannot change the original"}
  </b>
  {else}
  <input type="checkbox" name="{g->formVar var="form[preserveOriginal]"}" {if $form.preserveOriginal}checked="checked"{/if}/> {g->text text="Preserve Original Photo"}
  {/if}
  {else}
  <h2 class="giTitle">
    {g->text text="Modified Photo"}
  </h2>

  <p class="giDescription">
    {g->text text="You are using a copy of the original photo that has been scaled or rotated.  The original photo is still available, but is no longer being used.  Any changes you make will be applied to the copy instead."}
  </p>
	
  <input type="submit" name="{g->formVar var="form[action][revertToOriginal]"}" value="{g->text text="Restore original"}"/>
  {/if}
</div>
{/if}

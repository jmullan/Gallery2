{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Photo Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.editPhoto.rotatedPhoto)}
	{g->text text="Rotated photo successfully"}
      {/if}
      {if isset($status.editPhoto.scaledPhoto)}
	{g->text text="Scaled photo successfully"}
      {/if}
      {if isset($status.editPhoto.revertedPhoto)}
	{g->text text="Restored original photo successfully"}
      {/if}
      {if isset($status.editSizes.saved)}
	{g->text text="Changes saved successfully."}
      {/if}
      {if isset($status.editThumbnail.cropped)}
	{g->text text="Thumbnail cropped successfully."}
      {/if}
    {/g->success}
  {/if}

  {g->tabbedbox}
    {g->tabset}
      {if $ItemEditPhoto.mode == 'editPhoto'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="Rotate/Scale"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link url_view="core:ItemAdmin" url_subView="core:ItemEditPhoto" url_itemId=$ItemAdmin.item.id url_mode="editPhoto"}
	      {g->text text="Rotate/Scale"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}

      {if $ItemEditPhoto.mode == 'editSizes'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="Sizes"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link url_view="core:ItemAdmin" url_subView="core:ItemEditPhoto" url_itemId=$ItemAdmin.item.id url_mode="editSizes"}
	      {g->text text="Sizes"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}

      {if $ItemEditPhoto.showEditThumbnail}
	{if $ItemEditPhoto.mode == 'editThumbnail'}
	  {g->item selected="true"}
	    {g->title}
	      {g->text text="Thumbnail"}
	    {/g->title}
	  {/g->item}
	{else}
	  {g->item}
	    {g->title}
	      {g->link url_view="core:ItemAdmin" url_subView="core:ItemEditPhoto" url_itemId=$ItemAdmin.item.id url_mode="editThumbnail"}
		{g->text text="Thumbnail"}
	      {/g->link}
	    {/g->title}
	  {/g->item}
	{/if}
      {/if}
    {/g->tabset}

    {if $ItemEditPhoto.mode == 'editPhoto'}
      {g->box style="admin"}
	{g->title}
	  {g->text text="Rotate"}
	{/g->title}

	{g->description}
	  {g->text text="You can only rotate the photo in 90 degree increments."}
	{/g->description}

	{if $ItemEditPhoto.editPhoto.can.rotate}
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
	    {if $ItemEditPhoto.isAdmin} 
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminModules"}
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
	

	{if $ItemEditPhoto.editPhoto.can.scale}
	  {g->element}
	    {g->input type="text" size="6" name="form[scale][size]"}{$form.scale.size}{/g->input}
	    {g->input type="submit" name="form[action][scale]"}
	      {g->text text="Scale"}
	    {/g->input}
	  {/g->element}
	{else}
	  {g->element style="emphasized"}
	    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot scale it."}
	    {if $ItemEditPhoto.isAdmin} 
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminModules"}
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

      {if $ItemEditPhoto.editPhoto.can.rotate || $ItemEditPhoto.editPhoto.can.scale}
	{g->box style="admin"}
	  {if empty($ItemEditPhoto.editPhoto.hasPreferredSource)}
	    {g->title}
	      {g->text text="Preserve Original"}
	    {/g->title}

	    {g->description}
	      {g->text text="Gallery does not modify your original photo when rotating and scaling. Instead, it duplicates your photo and works with copies.  This requires a little extra disk space but prevents your original from getting damaged.  Disabling this option will cause any actions (rotating, scaling, etc) to modify the original."}
	    {/g->description}

	    {g->element}
	      {g->input type="checkbox" name="form[preserveOriginal]"}{$form.preserveOriginal}{/g->input} {g->text text="Preserve Original Photo"}
	    {/g->element}
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
    {/if}

    {if $ItemEditPhoto.mode == 'editSizes'}
      {g->box style="admin"}
	{g->title}
	  {g->text text="Thumbnail"}
	{/g->title}

	{g->description}
	  {g->text text="Set the size of the thumbnail.  The largest side of the thumbnail will be no larger than this value."}
	{/g->description}

	{if $ItemEditPhoto.editSizes.can.createThumbnail}
	  {g->element}
	    {g->input type=text size=6 name="form[thumbnail][size]"}{$form.thumbnail.size}{/g->input}
	  {/g->element}
	{else}
	  {g->element style="emphasized"}
	    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify a thumbnail."}
	    {if $ItemEditPhoto.isAdmin} 
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminModules"}
		{g->text text="site admin"}
	      {/g->link}
	    {/if}
	  {/g->element}
        {/if}
      {/g->box}

      {if !empty($form.error.thumbnail.size.missing)}
	{g->error}
	  {g->text text="You must enter a thumbnail size"}
	{/g->error}
      {/if}
      
      {if !empty($form.error.thumbnail.size.invalid)}
	{g->error}
	  {g->text text="You must enter a number (greater than zero)"}
	{/g->error}
      {/if}

      {g->box style="admin"}
	{g->title}
	  {g->text text="Resized Photos"}
	{/g->title}

	{g->description}
	  {g->text text="These sizes are alternate resized versions of the original you would like to have available for viewing."}
	{/g->description}

	{if $ItemEditPhoto.editSizes.can.createThumbnail}
	  {counter start=0 assign=index}
	  {foreach from=$form.resizes item=resize}
	    {g->element}
	      {g->input type="checkbox" name="form[resizes][$index][active]"}{$form.resizes.$index.active}{/g->input}
	      {g->input type="text" size="6" name="form[resizes][$index][size]"}{$form.resizes.$index.size}{/g->input}
	    {/g->element}

	    {if !empty($form.error.resizes.$index.size.missing)}
	      {g->error}
		{g->text text="You must enter a valid size"}
	      {/g->error}
	    {/if}
	    
	    {if !empty($form.error.resizes.$index.size.invalid)}
	      {g->error}
		{g->text text="You must enter a number (greater than zero)"}
	      {/g->error}
	    {/if}
	    {counter}
	  {/foreach}
	{else}
	  {g->element style="emphasized"}
	    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify resized versions."}
	    {if $ItemEditPhoto.isAdmin} 
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminModules"}
		{g->text text="site admin"}
	      {/g->link}
	    {/if}
	  {/g->element}
        {/if}

      {/g->box}

      {g->box}
	{g->element}
	  {g->input type="hidden" name="mode"}editSizes{/g->input}
	  {g->input type="submit" name="form[action][save]"}{g->text text="Save"}{/g->input}
	  {g->input type="submit" name="form[action][undo]"}{g->text text="Undo"}{/g->input}
	{/g->element}
      {/g->box}
    {/if}

    {if $ItemEditPhoto.mode == 'editThumbnail'}
      {g->box style="admin"}
	{g->title}
	  {g->text text="Thumbnail"}
	{/g->title}

	{g->description}
	  {g->text text="You can select which part of the photo will be used for the thumbnail.  This will have no effect on the resized or original versions of the image."}
	{/g->description}

	{if $ItemEditPhoto.editThumbnail.can.crop}
	  {g->element}
  	    <APPLET ID="ImageCrop"
                    CODE="ImageCrop" 
	            WIDTH="630" 
	            HEIGHT="480" 
	            CODEBASE="{$ItemEditPhoto.editThumbnail.appletCodeBase}"
	            ARCHIVE="{$ItemEditPhoto.editThumbnail.appletJarFile}">
	      <PARAM NAME="type"               VALUE="application/x-java-applet;version=1.1.2">
  	      <PARAM NAME="image"              VALUE="{$ItemEditPhoto.editThumbnail.imageUrl}">
	      <PARAM NAME="image_width"        VALUE="{$ItemEditPhoto.editThumbnail.imageWidth}">
	      <PARAM NAME="image_height"       VALUE="{$ItemEditPhoto.editThumbnail.imageHeight}">
	      <PARAM NAME="crop_x"             VALUE="{$ItemEditPhoto.editThumbnail.cropLeft}">
	      <PARAM NAME="crop_y"             VALUE="{$ItemEditPhoto.editThumbnail.cropTop}">
	      <PARAM NAME="crop_width"         VALUE="{$ItemEditPhoto.editThumbnail.cropWidth}">
	      <PARAM NAME="crop_height"        VALUE="{$ItemEditPhoto.editThumbnail.cropHeight}">
	      <PARAM NAME="crop_ratio_width"   VALUE="{$ItemEditPhoto.editThumbnail.cropRatioWidth}">
	      <PARAM NAME="crop_ratio_height"  VALUE="{$ItemEditPhoto.editThumbnail.cropRatioHeight}">
	      <PARAM NAME="crop_orientation"   VALUE="{$ItemEditPhoto.editThumbnail.selectedOrientation}">
	      <PARAM NAME="crop_to_size"       VALUE="{$ItemEditPhoto.editThumbnail.targetThumbnailSize}">
	    </APPLET>

	    <script type="text/javascript" language="javascript">
	      function setAspectRatio(value) {ldelim}
		switch(value) {ldelim}
		{foreach from=$ItemEditPhoto.editThumbnail.aspectRatioList key=index item=aspectRatio}
		  case "{$index}":
		    document.ImageCrop.setCropRatio({$aspectRatio.width}, {$aspectRatio.height});
		    break;
		{/foreach}
		{rdelim}
	      {rdelim}

	      function setCropFields() {ldelim}
		document.forms[0].crop_x.value=document.ImageCrop.getCropX();
		document.forms[0].crop_y.value=document.ImageCrop.getCropY();
		document.forms[0].crop_width.value=document.ImageCrop.getCropWidth();
		document.forms[0].crop_height.value=document.ImageCrop.getCropHeight();
	      {rdelim}

	      function setOrientation(orientation) {ldelim}
		document.ImageCrop.setCropOrientation(orientation);
	      {rdelim}
	    </script>
	  {/g->element}
	  
	  {g->table style="admin_widgets"}
	    {g->row}
	      {g->column}
		{g->text text="Aspect Ratio: "}
	      {/g->column}

	      {g->column}
		{g->select onChange="javascript:setAspectRatio(this.value)"}
		  {foreach from=$ItemEditPhoto.editThumbnail.aspectRatioList key=index item=aspect}
		    <option label="{$aspect.label}" value="{$index}" 
		    {if $ItemEditPhoto.editThumbnail.selectedAspect == $index}
		      selected="selected"
		    {/if}
		    >{$aspect.label}
		  {/foreach}
		{/g->select}
	      {/g->column}

	      {g->column}
		{g->select onChange="javascript:setOrientation(this.value)"}
		  {html_options options=$ItemEditPhoto.editThumbnail.orientationList selected=$ItemEditPhoto.editThumbnail.selectedOrientation}
		{/g->select}
	      {/g->column}
	    {/g->row}
	  {/g->table}

	  {g->element}
	    {g->input type="hidden" name="mode"}editThumbnail{/g->input}
	    {g->input id="crop_x" type="hidden" name="form[crop][x]"}{/g->input}
	    {g->input id="crop_y" type="hidden" name="form[crop][y]"}{/g->input}
	    {g->input id="crop_width" type="hidden" name="form[crop][width]"}{/g->input}
	    {g->input id="crop_height" type="hidden" name="form[crop][height]"}{/g->input}
	    {g->input type="submit" name="form[action][crop]" onClick="javascript:setCropFields(); submit()"}
	      {g->text text="Crop"}
	    {/g->input}
	  {/g->element}
	{else}
	  {g->element style="emphasized"}
	    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot crop the thumbnail."}
	    {if $ItemEditPhoto.isAdmin} 
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminModules"}
		{g->text text="site admin"}
	      {/g->link}
	    {/if}
	  {/g->element}
	{/if}
      {/g->box}
    {/if}

  {/g->tabbedbox}
{/g->pagebox}

{g->box style="admin"}
  {g->title}
    {g->text text="Thumbnail"}
  {/g->title}

  {g->description}
    {g->text text="You can select which part of the photo will be used for the thumbnail.  This will have no effect on the resized or original versions of the image."}
  {/g->description}

  {if $ItemEditPhotoThumbnail.editThumbnail.can.crop}
    {g->element}
      <APPLET ID="ImageCrop"
	      CODE="ImageCrop" 
	      WIDTH="630" 
	      HEIGHT="480" 
	      CODEBASE="{$ItemEditPhotoThumbnail.editThumbnail.appletCodeBase}"
	      ARCHIVE="{$ItemEditPhotoThumbnail.editThumbnail.appletJarFile}">
	<PARAM NAME="type"               VALUE="application/x-java-applet;version=1.1.2">
	<PARAM NAME="image"              VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageUrl}">
	<PARAM NAME="image_width"        VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageWidth}">
	<PARAM NAME="image_height"       VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageHeight}">
	<PARAM NAME="crop_x"             VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropLeft}">
	<PARAM NAME="crop_y"             VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropTop}">
	<PARAM NAME="crop_width"         VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropWidth}">
	<PARAM NAME="crop_height"        VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropHeight}">
	<PARAM NAME="crop_ratio_width"   VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioWidth}">
	<PARAM NAME="crop_ratio_height"  VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioHeight}">
	<PARAM NAME="crop_orientation"   VALUE="{$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}">
	<PARAM NAME="crop_to_size"       VALUE="{$ItemEditPhotoThumbnail.editThumbnail.targetThumbnailSize}">
      </APPLET>

      <script type="text/javascript" language="javascript">
	function setAspectRatio(value) {ldelim}
	  switch(value) {ldelim}
	  {foreach from=$ItemEditPhotoThumbnail.editThumbnail.aspectRatioList key=index item=aspectRatio}
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
	    {foreach from=$ItemEditPhotoThumbnail.editThumbnail.aspectRatioList key=index item=aspect}
	      <option label="{$aspect.label}" value="{$index}" 
	      {if $ItemEditPhotoThumbnail.editThumbnail.selectedAspect == $index}
		selected="selected"
	      {/if}
	      >{$aspect.label}
	    {/foreach}
	  {/g->select}
	{/g->column}

	{g->column}
	  {g->select onChange="javascript:setOrientation(this.value)"}
	    {html_options options=$ItemEditPhotoThumbnail.editThumbnail.orientationList selected=$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}

    {g->element}
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
      {if $ItemEditPhotoThumbnail.isAdmin} 
	{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
	  {g->text text="site admin"}
	{/g->link}
      {/if}
    {/g->element}
  {/if}
{/g->box}

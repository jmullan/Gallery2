{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEditPhotoThumbnail.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Thumbnail"}
  </h2>
  
  <p class="giDescription">
    {g->text text="You can select which part of the photo will be used for the thumbnail.  This will have no effect on the resized or original versions of the image."}
  </p>

  {if $ItemEditPhotoThumbnail.editThumbnail.can.crop}
  <!--
  <object
    classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
    codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4-windows-i586.cab#Version=1,4,0,0"
    width="630" 
    height="480">
    <param name="code" value="{$ItemEditPhotoThumbnail.editThumbnail.appletCodeBase}"/>
    <param name="archive" value="{$ItemEditPhotoThumbnail.editThumbnail.appletJarFile}"/>
    <param name="type" value="application/x-java-applet;version=1.1.8"/>
    <param name="scriptable" value="true"/>
	    
    <param name="image"              value="{$ItemEditPhotoThumbnail.editThumbnail.imageUrl}"/>
    <param name="image_width"        value="{$ItemEditPhotoThumbnail.editThumbnail.imageWidth}"/>
    <param name="image_height"       value="{$ItemEditPhotoThumbnail.editThumbnail.imageHeight}"/>
    <param name="crop_x"             value="{$ItemEditPhotoThumbnail.editThumbnail.cropLeft}"/>
    <param name="crop_y"             value="{$ItemEditPhotoThumbnail.editThumbnail.cropTop}"/>
    <param name="crop_width"         value="{$ItemEditPhotoThumbnail.editThumbnail.cropWidth}"/>
    <param name="crop_height"        value="{$ItemEditPhotoThumbnail.editThumbnail.cropHeight}"/>
    <param name="crop_ratio_width"   value="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioWidth}"/>
    <param name="crop_ratio_height"  value="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioHeight}"/>
    <param name="crop_orientation"   value="{$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}"/>
    <param name="crop_to_size"       value="{$ItemEditPhotoThumbnail.editThumbnail.targetThumbnailSize}"/>

    <comment>
      <embed
         type="application/x-java-applet;version=1.1.8"
         code="{$ItemEditPhotoThumbnail.editThumbnail.appletCodeBase}"
         archive="{$ItemEditPhotoThumbnail.editThumbnail.appletJarFile}"
         width="630"
         height="480"
         scriptable="true"
         image="{$ItemEditPhotoThumbnail.editThumbnail.imageUrl}"
         image_width="{$ItemEditPhotoThumbnail.editThumbnail.imageWidth}"
         image_height="{$ItemEditPhotoThumbnail.editThumbnail.imageHeight}"
         crop_x="{$ItemEditPhotoThumbnail.editThumbnail.cropLeft}"
         crop_y="{$ItemEditPhotoThumbnail.editThumbnail.cropTop}"
         crop_width="{$ItemEditPhotoThumbnail.editThumbnail.cropWidth}"
         crop_height="{$ItemEditPhotoThumbnail.editThumbnail.cropHeight}"
         crop_ratio_width="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioWidth}"
         crop_ratio_height="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioHeight}"
         crop_orientation="{$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}"
         crop_to_size="{$ItemEditPhotoThumbnail.editThumbnail.targetThumbnailSize}"/>
    </comment>				  
  </object>
   -->

  <APPLET ID="ImageCrop"
          CODE="ImageCrop" 
          WIDTH="630" 
          HEIGHT="480" 
          CODEBASE="{$ItemEditPhotoThumbnail.editThumbnail.appletCodeBase}"
          ARCHIVE="{$ItemEditPhotoThumbnail.editThumbnail.appletJarFile}"
          SCRIPTABLE="TRUE"
          MAYSCRIPT="TRUE">
       <PARAM NAME="type"               VALUE="application/x-java-applet;version=1.1.2"/>
       <PARAM NAME="image"              VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageUrl}"/>
       <PARAM NAME="image_width"        VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageWidth}"/>
       <PARAM NAME="image_height"       VALUE="{$ItemEditPhotoThumbnail.editThumbnail.imageHeight}"/>
       <PARAM NAME="crop_x"             VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropLeft}"/>
       <PARAM NAME="crop_y"             VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropTop}"/>
       <PARAM NAME="crop_width"         VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropWidth}"/>
       <PARAM NAME="crop_height"        VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropHeight}"/>
       <PARAM NAME="crop_ratio_width"   VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioWidth}"/>
       <PARAM NAME="crop_ratio_height"  VALUE="{$ItemEditPhotoThumbnail.editThumbnail.cropRatioHeight}"/>
       <PARAM NAME="crop_orientation"   VALUE="{$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}"/>
       <PARAM NAME="crop_to_size"       VALUE="{$ItemEditPhotoThumbnail.editThumbnail.targetThumbnailSize}"/>
  </APPLET>

  <script type="text/javascript">
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

  <div class="gbDataEntry">
    <h2 class="giTitle">
      {g->text text="Aspect Ratio: "}
    </h2>

    <select onchange="javascript:setAspectRatio(this.value)">
      {foreach from=$ItemEditPhotoThumbnail.editThumbnail.aspectRatioList key=index item=aspect}
      <option label="{$aspect.label}" value="{$index}" 
	{if $ItemEditPhotoThumbnail.editThumbnail.selectedAspect == $index}
	selected="selected"
	{/if}
	> {$aspect.label}
      </option>
      {/foreach}
    </select>

    <select onchange="javascript:setOrientation(this.value)">
      {html_options options=$ItemEditPhotoThumbnail.editThumbnail.orientationList selected=$ItemEditPhotoThumbnail.editThumbnail.selectedOrientation}
    </select>
  </div>

  <input id="crop_x" type="hidden" name="{g->formVar var="form[crop][x]"}"/>
  <input id="crop_y" type="hidden" name="{g->formVar var="form[crop][y]"}"/>
  <input id="crop_width" type="hidden" name="{g->formVar var="form[crop][width]"}"/>
  <input id="crop_height" type="hidden" name="{g->formVar var="form[crop][height]"}"/>
  <input type="submit" name="{g->formVar var="form[action][crop]"}" onclick="javascript:setCropFields(); submit()" value="{g->text text="Crop"}"/>
  {else}
  <b>
    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot crop the thumbnail."}
    {if $ItemEditPhotoThumbnail.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}">
      {g->text text="site admin"}
      </a>
    {/if}
  </b>
  {/if}
</div>

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gsImageContents">
  <div class="giTitle">
    {g->text text=$Panorama.item.title|default:$Panorama.item.pathComponent}
  </div>

  {assign var="totalHeight" value=$Panorama.image.height+17}
  <applet archive="{$Panorama.moduleUrl}/java/Metamorphose.jar"
    code="Metamorphose" 
    width="{$Panorama.width}" 
    height="{$totalHeight}">
    <param name="BackgroundColor" value="#666666"/>
    <param name="PanoramaRect"    value="0,0,{$Panorama.width},{$Panorama.image.height}"/>
    <param name="ScrollerRect"    value="0,{$Panorama.image.height},{$Panorama.width},17"/>
    <param name="ScrollerThumb"   value="{$Panorama.moduleUrl}/images/slider.png"/>
    <param name="PanoramaTile"    value="{$Panorama.imageUrl}"/>
    <param name="PanoramaSize"    value="{$Panorama.image.width},{$Panorama.image.height}"/>
  </applet>
</div>

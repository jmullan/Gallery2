{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">
  // <![CDATA[
  var watermarkUrlMap = new Array;
  {foreach from=$ItemEditWatermark.watermarks item=watermark}
  watermarkUrlMap[{$watermark.id}] = {ldelim}
  'url': '{g->url htmlEntities=false arg1="view=core.DownloadItem" arg2="itemId=`$watermark.id`"}',
  'width': {$watermark.width},
  'height': {$watermark.height},
  'xPercent': {if $watermark.id==$form.watermarkId}{$form.xPercent}{else}{$watermark.xPercentage}{/if},
  'yPercent': {if $watermark.id==$form.watermarkId}{$form.yPercent}{else}{$watermark.yPercentage}{/if}
  {rdelim};
  {/foreach}

  {literal}
  function chooseWatermark(id) {
    newImage = watermarkUrlMap[id];
    var floater = document.getElementById("watermark_floater");
    floater.src = newImage.url;
    floater.style.width = newImage.width + "px";
    floater.style.height = newImage.height + "px";
    initWatermarkFloater("watermark_floater", "watermark_original",
	newImage.width, newImage.height,
	newImage.xPercent, newImage.yPercent);
  }
  {/literal}
  // ]]>
</script>

<div class="gbBlock">
  <h3> {g->text text="Watermark"} </h3>

  <p class="giDescription">
    {g->text text="You can choose a watermark to apply to this image.  Watermarks do not affect the original image, so they they can be applied to resizes and thumbnails without damaging the original."}
  </p>
</div>

{if empty($ItemEditWatermark.watermarks)}
<div class="gbBlock">
  <h3> {g->text text="You have no watermarks"} </h3>

  <p class="giDescription">
    {g->text text="You must first upload some watermark images so that you can apply them to your image."}
    <a href="{g->url arg1="view=core.UserAdmin" arg2="subView=watermark.UserWatermarks"}">
      {g->text text="Upload some watermarks now."}
    </a>
  </p>
</div>
{else}
<div class="gbBlock">
  <h3> {g->text text="Step 1.  Choose which watermark you want to use"} </h3>

  <select name="{g->formVar var="form[watermarkId]"}" onchange="chooseWatermark(this.value)"
   id="watermarkList">
    {foreach from=$ItemEditWatermark.watermarks item=watermark}
    <option value="{$watermark.id}"{if
     ($form.watermarkId == $watermark.id)} selected="selected"{/if}>{$watermark.name}</option>
    {/foreach}
  </select>
</div>

<div class="gbBlock">
  <h3> {g->text text="Step 2.  Place the watermark on your image."} </h3>

  {g->image id="watermark_original" maxSize=400 style="display: block"
	    item=$ItemEditWatermark.item forceRawImage=true
	    image=$ItemEditWatermark.derivative|default:$ItemEditWatermark.item}
  <img id="watermark_floater"
   src="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$form.watermarkId`"}"
   width="{$ItemEditWatermark.watermarks[$form.watermarkId].width}"
   height="{$ItemEditWatermark.watermarks[$form.watermarkId].height}"
   alt="{g->text text="watermark"}" style="position: absolute"/>
</div>

<div class="gbBlock">
  <h3> {g->text text="Step 3.  Choose which versions of the image you'd like to watermark"} </h3>

  {if isset($form.error.versions.missing)}
  <div class="giError">
    {g->text text="You must choose something to watermark!"}
  </div>
  {/if}

  <input type="checkbox"{if isset($form.whichDerivative.preferred)} checked="checked"{/if}
   name="{g->formVar var="form[whichDerivative][preferred]"}"/>
  {g->text text="Full size (won't damage the original file)"}
  <br/>

  <input type="checkbox"{if isset($form.whichDerivative.resize)} checked="checked"{/if}
   name="{g->formVar var="form[whichDerivative][resize]"}"/>
  {g->text text="Resizes"}
  <br/>

  <input type="checkbox"{if isset($form.whichDerivative.thumbnail)} checked="checked"{/if}
   name="{g->formVar var="form[whichDerivative][thumbnail]"}"/>
  {g->text text="Thumbnail"}
  <br/>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit" onclick="calculatePercentages('watermark_floater'); return true"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Apply Watermark"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][remove]"}" value="{g->text text="Remove Watermark"}"/>
</div>

<input type="hidden" id="xPercent"
 name="{g->formVar var="form[xPercent]"}" value="{$form.xPercent}"/>
<input type="hidden" id="yPercent"
 name="{g->formVar var="form[yPercent]"}" value="{$form.yPercent}"/>

{g->addToTrailer}
<script type="text/javascript">
// <![CDATA[
chooseWatermark(document.getElementById("watermarkList").value);
// ]]>
</script>
{/g->addToTrailer}
{/if}

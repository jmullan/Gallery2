{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEditWatermark.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}

<!-- Load up the WZ_DragDrop library -->
<script type="text/javascript" src="{g->url href="lib/wz_dragdrop/wz_dragdrop.js"}">
</script>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Watermark"}
  </h2>
  
  <p class="giDescription">
    {g->text text="You can choose a watermark to apply to this image.  Watermarks do not affect the original image, so they they can be applied to resizes and thumbnails without damaging the original."}
  </p>
</div>

{if empty($ItemEditWatermark.watermarks)}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="You have no watermarks"}
  </h2>

  <p class="giDescription">
    {g->text text="You must first upload some watermark images so that you can apply them to your image."}
    <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=watermark:UserWatermarks"}">
      {g->text text="Upload some watermarks now."}
    </a>
  </p>
</div>
{else}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Step 1.  Choose which watermark you want to use"}
  </h2>

  <script type="text/javascript">
    watermarkUrlMap = new Array;
    {foreach from=$ItemEditWatermark.watermarks item=watermark}
    watermarkUrlMap[{$watermark.id}] = new Array;
    watermarkUrlMap[{$watermark.id}]['url'] = '{g->url forJavascript="true" arg1="view=core:DownloadItem" arg2="itemId=`$watermark.id`"}';
    watermarkUrlMap[{$watermark.id}]['width'] = {$watermark.width};
    watermarkUrlMap[{$watermark.id}]['height'] = {$watermark.height};
    {/foreach}

    function moveToOriginalLocation() {ldelim}
      orig = dd.elements.watermark_original;
      floater = dd.elements.watermark_floater;
      
      newX = orig.x + ({$form.xPercent|default:0} / 100 * orig.w);
      newY = orig.y + ({$form.yPercent|default:0} / 100 * orig.h);
      floater.moveTo(newX, newY);
    {rdelim}

    {literal}
    function calculatePercentages() {
      orig = dd.elements.watermark_original;
      floater = dd.elements.watermark_floater;
      document.getElementById("xPercent").value = 100.0 * (floater.x - orig.x) / orig.w;
      document.getElementById("yPercent").value = 100.0 * (floater.y - orig.y) / orig.h;
    }

    function chooseWatermark(id) {
      orig = dd.elements.watermark_original;
      floater = dd.elements.watermark_floater;
      newImage = watermarkUrlMap[id];
      floater.swapImage(newImage['url']);
      floater.resizeTo(Math.min(newImage['width'], (0.9 * orig.w)),
	               Math.min(newImage['height'], (0.9 * orig.h)));
      verifyBounds();
    }

    function my_DragFunc() {
      verifyBounds();
    }

    // Keep from dragging the watermark off the image
    function verifyBounds() {
      orig = dd.elements.watermark_original;
      floater = dd.elements.watermark_floater;
     
      if (floater.x < orig.x) {
        newX = orig.x;
      } else if (floater.x + floater.w > orig.x + orig.w) {
        newX = orig.x + (orig.w - floater.w);
      } else {
	newX = floater.x;
      }

      if (floater.y < orig.y) {
        newY = orig.y;
      } else if (floater.y + floater.h > orig.y + orig.h) {
        newY = orig.y + (orig.h - floater.h);
      } else {
        newY = floater.y;
      }

      if (newX != floater.x || newY != floater.y) {
        floater.moveTo(newX, newY);
      }
    }
    {/literal}
  </script>

  <select name="{g->formVar var="form[watermarkId]"}" onchange="chooseWatermark(this.value)">
    {foreach from=$ItemEditWatermark.watermarks item=watermark}
    <option value="{$watermark.id}" {if ($form.watermarkId == $watermark.id)}selected="selected"{/if}>{$watermark.name}</option>
    {/foreach}
  </select>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Step 2.  Place the watermark on your image."}
  </h2>

  {strip}
  <div>
    {g->image name="watermark_original" 
	  item=$ItemEditWatermark.item
          image=$ItemEditWatermark.derivative|default:$ItemEditWatermark.item
	  maxSize=400}
    <img name="watermark_floater" src="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$form.watermarkId`"}" width="{$ItemEditWatermark.watermarks[form.watermarkId].width}" height="{$ItemEditWatermark.watermarks[form.watermarkId].height}"/>
  </div>
  {/strip}
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Step 3.  Choose which versions of the image you'd like to watermark"}
  </h2>

  {if isset($form.error.versions.missing)}
  <div class="giError">
    {g->text text="You must choose something to watermark!"}
  </div>
  {/if}

  <input type="checkbox" name="{g->formVar var="form[whichDerivative][preferred]"}"
	{if isset($form.whichDerivative.preferred)}checked="checked"{/if}
	/>
  {g->text text="Full size (won't damage the original file)"}
  <br/>

  <input type="checkbox" name="{g->formVar var="form[whichDerivative][resize]"}"
	{if isset($form.whichDerivative.resize)}checked="checked"{/if}
	/>
  {g->text text="Resizes"}
  <br/>

  <input type="checkbox" name="{g->formVar var="form[whichDerivative][thumbnail]"}"
	{if isset($form.whichDerivative.thumbnail)}checked="checked"{/if}
	/>
  {g->text text="Thumbnail"}
  <br/>
</div>

<div class="gbBottomFlag">
  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}"
           value="{g->text text="Apply Watermark"}"
	   onclick="calculatePercentages(); submit()"/>
    <input type="submit" name="{g->formVar var="form[action][remove]"}"
           value="{g->text text="Remove Watermark"}"/>
  </div>
</div>

<input id="xPercent" type="hidden" name="{g->formVar var="form[xPercent]"}" value="{$form.xPercent}"/>
<input id="yPercent" type="hidden" name="{g->formVar var="form[yPercent]"}" value="{$form.yPercent}"/>

<script type="text/javascript">
<!--
SET_DHTML("watermark_original"+NO_DRAG, "watermark_floater");
dd.elements.watermark_floater.moveTo(dd.elements.watermark_original.x, 
	                             dd.elements.watermark_original.y);
dd.elements.watermark_floater.setZ(dd.elements.watermark_original.z+1);
moveToOriginalLocation()
verifyBounds();
-->
</script>
{/if}

{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to WatermarkOption.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<script type="text/javascript">
    WatermarkOption_watermarkUrlMap = new Array;
    {foreach from=$WatermarkOption.watermarks item=watermark}
    WatermarkOption_watermarkUrlMap[{$watermark.id}] = new Array;
    WatermarkOption_watermarkUrlMap[{$watermark.id}]['url'] = '{g->url forJavascript="true" arg1="view=core:DownloadItem" arg2="itemId=`$watermark.id`"}';
    WatermarkOption_watermarkUrlMap[{$watermark.id}]['width'] = {$watermark.width};
    WatermarkOption_watermarkUrlMap[{$watermark.id}]['height'] = {$watermark.height};
    {/foreach}

    {literal}
    function WatermarkOption_chooseWatermark(id) {
      watermark = document.getElementById("WatermarkOption_watermark");
      if (id) {
          watermark.src = WatermarkOption_watermarkUrlMap[id]['url'];
          watermark.width = WatermarkOption_watermarkUrlMap[id]['width'];
          watermark.height = WatermarkOption_watermarkUrlMap[id]['height'];
      } else {
          watermark.src = "";
      }
    }
    {/literal}
</script>

<div class="gbAdmin">
  <div class="giTitle">
    {g->text text="Watermark"}
  </div>

  <div class="giDescription">
    {g->text text="Choose a watermark to apply to the images you add."}
    <br/>
    <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=watermark:UserWatermarks"}">{g->text text="Edit your watermarks"}</a>
  </div>

  <div style="position: relative; width: 100%; height: 80px">
    <select style="position: relative; left: 0px; top: 0px;" name="{g->formVar var="form[WatermarkOption][watermarkId]"}" onchange="WatermarkOption_chooseWatermark(this.value)">
      <option value="">&laquo; {g->text text="none"} &raquo;</option>
      {foreach from=$WatermarkOption.watermarks item=watermark}
      <option value="{$watermark.id}">{$watermark.name}</option>
      {/foreach}
    </select>
    <img style="position: relative; left: 100px; top: 0px;" id="WatermarkOption_watermark" src="" width="{$WatermarkOption.watermarks[$WatermarkOption.currentId].width}" height="{$WatermarkOption.watermarks[$WatermarkOption.currentId].height}"/>
  </div>
</div>

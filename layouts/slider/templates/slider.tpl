{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to hybrid.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div style="position:absolute;visibility:hidden;left:0px">
{foreach from=$layout.children key=i item=it}
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:ShowItem"
          arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:DownloadItem"
          arg2="itemId=`$it.image.id`"
          arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <span id="title_{$it.imageIndex}">{$it.title|default:$it.pathComponent|markup}</span>
  {/if}
{/foreach}
</div>

<div id="titlebar" style="margin-bottom:{$layout.maxThumbHeight+15}px">
<div id="tools_left">
<img name="opts" src="{$layout.layoutUrl}/images/tool.png" width="18" height="18" class="on" onclick="options_onoff()" alt="Slideshow options" title="Slideshow options"
/><img name="slide_poz" src="{$layout.layoutUrl}/../hybrid/images/poz.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Pause Slideshow" title="Pause Slideshow"
/><img name="slide_fwd" src="{$layout.layoutUrl}/../hybrid/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img name="slide_rev" src="{$layout.layoutUrl}/../hybrid/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img name="slide_rand" src="{$layout.layoutUrl}/../hybrid/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/></div>
<div id="tools_right">
<img name="full_size" src="{$layout.layoutUrl}/../hybrid/images/full.png" width="18" height="18" class="off" onclick="image_zoom(1)" alt="Full Size" title="Full Size"
/><img name="fit_size" src="{$layout.layoutUrl}/../hybrid/images/fit.png" width="18" height="18" class="off" onclick="image_zoom(0)" alt="Fit Size" title="Fit Size"
/><img name="prev_off" src="{$layout.layoutUrl}/../hybrid/images/prev-off.png" width="18" height="18" class="off" alt="No Previous Image" title="No Previous Image"
/><img name="prev_img" src="{$layout.layoutUrl}/../hybrid/images/prev.png" width="18" height="18" class="on" onclick="image_prev()" alt="Previous Image" title="Previous Image"
/><img name="next_off" src="{$layout.layoutUrl}/../hybrid/images/next-off.png" width="18" height="18" class="off" alt="No Next Image" title="No Next Image"
/><img name="next_img" src="{$layout.layoutUrl}/../hybrid/images/next.png" width="18" height="18" class="on" onclick="image_next()" alt="Next Image" title="Next Image"
/></div>
<span id="title" class="giTitle"></span>
</div>

<div id="thumbs" style="height:{$layout.maxThumbHeight+15}px">
<noscript><p class="giError">
    {g->text text="Warning: This site requires javascript."}
</p></noscript>
{foreach from=$layout.children key=i item=it}
{if isset($it.image)}<a href="" onclick="image_show({$it.imageIndex});return false"
 >{if isset($it.thumbnail)}{g->image item=$it image=$it.thumbnail class=hthumb}{
   else}<p>{g->text text="no thumbnail"}</p>{/if}</a
 >{/if}
{/foreach}
</div>

<div id="image"><div id="image_view"></div></div>

{* Slideshow options *}
<div id="options" class="gbMenu" style="visibility:hidden">
  {include file="gallery:templates/sidebar.tpl"}
  <div class="sideopt">
  <div class="gbMenu">
    <div class="giTitle"> {g->text text="Slideshow&nbsp;Options"} </div>
    <ul><li>
	{g->text text="delay"}:
	<select id="slide_delay" onchange="slide_setdelay(this.value)">
	 <option value="3">{g->text text="3 seconds"}</option>
	 <option selected="selected" value="5">{g->text text="5 seconds"}</option>
	 <option value="7">{g->text text="7 seconds"}</option>
	 <option value="10">{g->text text="10 seconds"}</option>
	 <option value="15">{g->text text="15 seconds"}</option>
	 <option value="20">{g->text text="20 seconds"}</option>
	</select> <br />
	{g->text text="direction"}:
	<select id="slide_order" onchange="slide_setorder(this.value)">
	 <option selected="selected" value="1">{g->text text="forward"}</option>
	 <option value="-1">{g->text text="reverse"}</option>
	 <option value="0">{g->text text="random"}</option>
	</select> <br />
    </li></ul>
  </div>
  <div class="gbMenu">
    <div class="giTitle" style="margin-top:3px"> {g->text text="Image&nbsp;Bar"} </div>
    <ul><li>
	<a href="" onclick="options_onoff();thumbs_horizvert();return false">
	{g->text text="Horizontal/Vertical"}</a>
    </li></ul>
  </div>
  </div>
</div>

<script type="text/javascript">app_init();</script>

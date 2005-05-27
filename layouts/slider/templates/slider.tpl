{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div style="display: none">
{foreach from=$layout.children key=i item=it}
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core.ShowItem"
          arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core.DownloadItem"
       arg2="itemId=`$it.image.id`" arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <span id="title_{$it.imageIndex}">{$it.title|markup}</span>
    <select id="links_{$it.imageIndex}">
     {foreach from=$it.itemLinks item=link}
      <option label="{$link.text}" value="{$link.url}">{$link.text}</option>
     {/foreach}
    </select>
  {/if}
{/foreach}
</div>

<div id="imagearea" class="gcBackground1"><div id="image"></div></div>

<div id="titlebar" class="gcBackground2 gcBorder2">
  <div id="tools_left">
    <img id="opts" src="{$layout.layoutUrl}/images/tool.png" width="18" height="18"
     onclick="options_onoff()" alt="{g->text text="Options"}" title="{g->text text="Options"}"
  /><img id="slide_poz" src="{$layout.layoutUrl}/images/poz.png" width="18" height="18"
     onclick="slide_onoff()"
     alt="{g->text text="Pause Slideshow"}" title="{g->text text="Pause Slideshow"}"
  /><img id="slide_fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18"
     onclick="slide_onoff()"
     alt="{g->text text="Start Slideshow"}" title="{g->text text="Start Slideshow"}"
  /><img id="slide_rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18"
     onclick="slide_onoff()"
     alt="{g->text text="Start Slideshow"}" title="{g->text text="Start Slideshow"}"
  /><img id="slide_rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18"
     onclick="slide_onoff()"
     alt="{g->text text="Start Slideshow"}" title="{g->text text="Start Slideshow"}"
  /></div>
  <div id="tools_right">
    <img id="full_size" src="{$layout.layoutUrl}/images/full.png" width="18" height="18"
     onclick="image_zoom(1)" alt="{g->text text="Full Size"}" title="{g->text text="Full Size"}"
  /><img id="fit_size" src="{$layout.layoutUrl}/images/fit.png" width="18" height="18"
     onclick="image_zoom(0)" alt="{g->text text="Fit Size"}" title="{g->text text="Fit Size"}"
  /><img id="prev_off" src="{$layout.layoutUrl}/images/prev-off.png" width="18" height="18"
     alt="{g->text text="No Previous Image"}" title="{g->text text="No Previous Image"}"
  /><img id="prev_img" src="{$layout.layoutUrl}/images/prev.png" width="18" height="18"
     onclick="image_prev()"
     alt="{g->text text="Previous Image"}" title="{g->text text="Previous Image"}"
  /><img id="next_off" src="{$layout.layoutUrl}/images/next-off.png" width="18" height="18"
     alt="{g->text text="No Next Image"}" title="{g->text text="No Next Image"}"
  /><img id="next_img" src="{$layout.layoutUrl}/images/next.png" width="18" height="18"
     onclick="image_next()" alt="{g->text text="Next Image"}" title="{g->text text="Next Image"}"
  /></div>
  <div id="title" class="giTitle">&nbsp;</div>

  <div id="thumbs" class="gcBackground1 gcBorder2 sliderHoriz">
    <noscript><p class="giError">
      {g->text text="Warning: This site requires javascript."}
    </p></noscript>
    {foreach from=$layout.children key=i item=it}{strip}
    {if isset($it.image)}
      <a href="" onclick="image_show({$it.imageIndex});return false">
	{if isset($it.thumbnail)}
	  {g->image item=$it image=$it.thumbnail class=hthumb}
	{else}
	  <p>{g->text text="no thumbnail"}</p>
	{/if}
      </a>
    {/if}
    {/strip}{/foreach}
  </div>
</div>

{capture name="sidebarInsert_2"}
  {if !empty($layout.itemLinks)}
  <div class="gbBlock">
    <h3> {g->text text="Album"} </h3>
    <select onchange="{literal}if (this.value) { var u=this.value; this.options[0].selected=1; location.href=u; }{/literal}" style="margin-left: 1em">
      <option label="{g->text text="&laquo; actions &raquo;"}" value="">
	{g->text text="&laquo; actions &raquo;"}
      </option>
     {foreach from=$layout.itemLinks item=link}
	<option label="{$link.text}" value="{$link.url}">{$link.text}</option>
     {/foreach}
    </select>
  </div>
  {/if}
  <div id="photoActions" class="gbBlock" style="display: none">
    <h3> {g->text text="Photo"} </h3>
    <select id="linkList" onchange="{literal}if (this.value) { var u=this.value; this.options[0].selected=1; location.href=u; }{/literal}" style="margin-left: 1em">
      <option label="{g->text text="&laquo; actions &raquo;"}" value="">
	{g->text text="&laquo; actions &raquo;"}
      </option>
    </select>
  </div>
{/capture}
{capture name="sidebarInsert_3"}
  <div class="gbBlock">
    <h3> {g->text text="Slideshow&nbsp;Options"} </h3>
    <ul><li>
      {g->text text="delay"}:
      <select id="slide_delay" onchange="slide_setdelay(this.value)">
	<option value="3">{g->text text="3 seconds"}</option>
	<option selected="selected" value="5">{g->text text="5 seconds"}</option>
	<option value="7">{g->text text="7 seconds"}</option>
	<option value="10">{g->text text="10 seconds"}</option>
	<option value="15">{g->text text="15 seconds"}</option>
	<option value="20">{g->text text="20 seconds"}</option>
      </select>
      <br/>
      {g->text text="direction"}:
      <select id="slide_order" onchange="slide_setorder(this.value)">
	<option selected="selected" value="1">{g->text text="forward"}</option>
	<option value="-1">{g->text text="reverse"}</option>
	<option value="0">{g->text text="random"}</option>
      </select>
    </li></ul>
  </div>
  <div class="gbBlock">
    <h3> {g->text text="Image&nbsp;Bar"} </h3>
    <ul><li>
      <a href="" onclick="options_onoff();thumbs_horizvert();return false">
	{g->text text="Horizontal/Vertical"}
      </a>
    </li></ul>
  </div>
{/capture}
<div id="options" class="gcBorder2">
  {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}
</div>

<script type="text/javascript">app_init();</script>

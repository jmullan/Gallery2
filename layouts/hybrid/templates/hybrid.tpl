<div id="album"
><div id="album_titlebar"
><div id="album_tools"><img name="sidebar_min" src="{$layout.layoutUrl}/images/left.png" width="18" height="18" class="on" onclick="sidebar_onoff()" alt="Hide sidebar" title="Hide sidebar"
><img name="sidebar_max" src="{$layout.layoutUrl}/images/right.png" width="18" height="18" class="off" onclick="sidebar_onoff()" alt="Show sidebar" title="Show sidebar"
><img name="slide__fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide__rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide__rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
></div>
<table cellspacing="0"><tr><td>
<span id="album_title">{$layout.title|markup}</span>
<span id="album_summary" class="text">{if isset($layout.item.summary)}
<br />{$layout.item.summary|markup}{/if}</span>
</td><td>
<span id="album_info" class="info">{g->text text="Owner: %s"
 arg1=$layout.owner.fullName|default:$layout.owner.userName}<br />
{g->text one="Viewed: %d time" many="Viewed: %d times"
    count=$layout.viewCounts[$layout.item.id]
    arg1=$layout.viewCounts[$layout.item.id]}</span>
</td></tr>
{if isset($layout.item.description)}
<tr><td colspan="2">
<span class="text">{$layout.item.description|markup}</span>
</td></tr>{/if}
</table></div
><div id="album_content"
><table class="content" cellspacing="0">
{foreach from=$layout.itemList key=i item=it}
 {if ($i is even)}<tr>{/if}
 <td class="i">
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_`$it.imageIndex`" href="{g->url arg1="view=core:ShowItem"
          arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_`$it.imageIndex`" href="{g->url arg1="view=core:DownloadItem"
          arg2="itemId=`$it.image.id`"
          arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <a id="info_`$it.imageIndex`" href="{g->url arg1="view=core:ShowItem"
        arg2="itemId=`$it.id`" arg3="detail=1"}"></a>
    <a href="" onclick="image_show({$it.imageIndex});return false">
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </a>
  {elseif ($it.isContainer)}
    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$it.id`"}">
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </a>
  {else}
    <a href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$it.id`"}">
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </a>
  {/if}
 </td>
 <td class="t"><table class="text"><tr><td><span class="title">
  {if isset($it.image) || isset($it.moduleItemLinks)}
   <span style="float:right;margin-left:2px"><img src="{$layout.layoutUrl}/images/menu.png" class="vis" width="18" height="18" alt="Item Actions" title="Item Actions" onclick="popup_menu(event,{$i}
    {if isset($it.image)},{$it.imageIndex})"></span>
      <span id="title_{$it.imageIndex}">
    {else},-1)"></span><span>{/if}
  {else}<span>{/if}
  {$it.data.title|markup}</span></span></td>
  </tr><tr>
  <td><span class="text" {if isset($it.image)}id="text_{$it.imageIndex}"{/if}>
  {if isset($it.data.summary)}{$it.data.summary|markup}<br />{/if}
  {$it.data.description|markup}</span></td></tr></table>
  {if isset($it.moduleItemLinks)}
   <span id="links_{$i}" style="position:absolute;visibility:hidden;top:0px">
   {foreach from=$it.moduleItemLinks item=link}
    <a href="{g->url params=$link.params}">{$link.text}</a><br />
   {/foreach}
   </span>
  {/if}
 </td>
 {if ($i is odd)}</tr>{/if}
{/foreach}
{if ($layout.count is odd)}<td></td><td></td></tr>{/if}
</table></div></div

><div id="sidebar">
<div id="gsSidebar">
  {* Module links *}
  <div class="gbMenu">
    <div class="giTitle">
      <noscript><br />{g->error}
	{g->text text="Warning: This site requires javascript."}
      {/g->error}<br /></noscript>
      {g->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
    </div>
    <ul>
      {foreach from=$layout.moduleSystemLinks item=module}
	{foreach from=$module item=link}
	  <li>
	    <a href="{g->url params=$link.params}">{$link.text}</a>
	  </li>
	{/foreach}
      {/foreach}
    </ul>
  </div>
  {* Modules system content *}
  {foreach from=$layout.moduleSystemContentFiles key=moduleId item=moduleFile}
    {if ($moduleId != 'core')}
      {include file=$moduleFile l10Domain="modules_$moduleId"}
    {/if}
  {/foreach}
  {* Breadcrumb *}
  {if (count($layout.parents)>0)}
    <div class="gbMenu">
      <div class="giTitle"> {g->text text="Navigation"} </div>
      <ul>
	{foreach from=$layout.parents item=parent}
	  <li>
	    &raquo;
	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$parent.id`"}">
	      {$parent.title|default:$parent.pathComponent|markup}
	    </a>
	  </li>
	{/foreach}
      </ul>
    </div>
  {/if}
  {* Album links *}
  <div class="gbMenu">
    <div class="giTitle"> {g->text text="Album"} </div>
    <ul>
      <li>
	<a id="dtl_link" href="" onclick="album_detailsonoff();this.blur();return false"}{g->text text="hide details"}</a>
      </li>
      <li>
	<a id="lnk_link" href="" onclick="album_itemlinksonoff();this.blur();return false"}{g->text text="hide item links"}</a>
      </li>
      {foreach from=$layout.moduleItemLinks item=link}
	<li>
	  <a href="{g->url params=$link.params}">{$link.text}</a>
	</li>
      {/foreach}
    </ul>
  </div>
  {* Slideshow options *}
  <div class="gbMenu">
    <div class="giTitle"> {g->text text="Slideshow&nbsp;Options"} </div>
    <ul><li>
	{g->text text="delay"}:
	<select id="slide_delay" onchange="slide_setdelay(this.value)">
	 <option value="3">{g->text text="3 seconds"}
	 <option selected value="5">{g->text text="5 seconds"}
	 <option value="7">{g->text text="7 seconds"}
	 <option value="10">{g->text text="10 seconds"}
	 <option value="15">{g->text text="15 seconds"}
	 <option value="20">{g->text text="20 seconds"}
	</select> <br />
	{g->text text="direction"}:
	<select id="slide_order" onchange="slide_setorder(this.value)">
	 <option selected value="1">{g->text text="forward"}
	 <option value="-1">{g->text text="reverse"}
	 <option value="0">{g->text text="random"}
	</select> <br />
    </li></ul>
  </div>
  <div class="gbMenu">
    <ul><li>
      <a href="http://validator.w3.org/check/referer"><img style="border: 0px"
         src="{g->url href="images/xhtml10.png"}"
         alt="{g->text text="This page is valid XHTML 1.0"}"
         height="15" width="80"></a>
    </li><li>
      <a href="http://gallery.sourceforge.net"><img style="border: 0px"
         src="{g->url href="images/gallery.gif"}"
         alt="{g->text text="Gallery %s" arg1=$main.gallery.version}"
         height="15" width="80"></a>
    </li></ul>
  </div>
</div>
</div

><div id="image" style="visibility:hidden" onclick="image_vis(0)"
><span id="image_view"></span></div

><div id="toolbar" style="visibility:hidden"><div id="tools_left"
><img name="text_on" src="{$layout.layoutUrl}/images/up.png" width="18" height="18" class="on" onclick="text_onoff()" alt="Show text" title="Show text"
><img name="text_off" src="{$layout.layoutUrl}/images/down.png" width="18" height="18" class="off" onclick="text_onoff()" alt="Hide text" title="Hide text"
><img src="{$layout.layoutUrl}/images/alb.png" width="18" height="18" class="on" onclick="image_vis(0)" alt="Back to Album View" title="Back to Album View"
><img name="slide_poz" src="{$layout.layoutUrl}/images/poz.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Pause Slideshow" title="Pause Slideshow"
><img name="slide_fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide_rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide_rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
></div><div id="tools_right"
><img name="full_size" src="{$layout.layoutUrl}/images/full.png" width="18" height="18" class="off" onclick="image_zoom(1)" alt="Full Size" title="Full Size"
><img name="fit_size" src="{$layout.layoutUrl}/images/fit.png" width="18" height="18" class="off" onclick="image_zoom(0)" alt="Fit Size" title="Fit Size"
><img src="{$layout.layoutUrl}/images/info.png" width="18" height="18" class="on" onclick="popup_info(-1)" alt="Item Details" title="Item Details"
><img name="prev_off" src="{$layout.layoutUrl}/images/prev-off.png" width="18" height="18" class="off" alt="No Previous Image" title="No Previous Image"
><img name="prev_img" src="{$layout.layoutUrl}/images/prev.png" width="18" height="18" class="on" onclick="image_prev()" alt="Previous Image" title="Previous Image"
><img name="next_off" src="{$layout.layoutUrl}/images/next-off.png" width="18" height="18" class="off" alt="No Next Image" title="No Next Image"
><img name="next_img" src="{$layout.layoutUrl}/images/next.png" width="18" height="18" class="on" onclick="image_next()" alt="Next Image" title="Next Image"
></div><div id="title"></div></div

><div id="text" style="visibility:hidden"></div

><iframe id="popup" frameborder="0" style="visibility:hidden"></iframe
><div id="popup_titlebar" style="visibility:hidden"
><div style="float:right;margin-left:2px"><img src="{$layout.layoutUrl}/images/down.png" width="18" height="18" onclick="popup_vis(0)" alt=""></div
>Item Details</div

><div id="popup_menu" onmouseover="clearTimeout(popup_timer)"
 onmouseout="popup_timer=setTimeout('ui_vis(\'popup_menu\',0)',1000)"
><div id="popup_links" onclick="ui_vis('popup_menu',0)"></div></div

><script type="text/javascript">app_init();</script>

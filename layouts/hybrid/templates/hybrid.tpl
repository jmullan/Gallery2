{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsContents"
><div id="album_titlebar" class="gbTopFlag"
><div id="album_tools"><img id="sidebar_min" src="{$layout.layoutUrl}/images/left.png" width="18" height="18" class="on" onclick="sidebar_onoff()" alt="Hide sidebar" title="Hide sidebar"
/><img id="sidebar_max" src="{$layout.layoutUrl}/images/right.png" width="18" height="18" class="off" onclick="sidebar_onoff()" alt="Show sidebar" title="Show sidebar"
/><img id="slide__fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img id="slide__rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img id="slide__rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/></div>
<table class="gbTitleBanner" cellspacing="0"><tr><td>
<span id="album_title" class="giTitle">{$layout.item.title|default:$layout.item.pathComponent|markup}</span>
<span id="album_summary" class="giDescription">{if isset($layout.item.summary)}
<br />{$layout.item.summary|markup}{/if}</span>
</td><td>
<span id="album_info" class="giInfo">{g->text text="Owner: %s"
 arg1=$layout.owner.fullName|default:$layout.owner.userName}<br />
{g->text one="Viewed: %d time" many="Viewed: %d times"
    count=$layout.viewCount arg1=$layout.viewCount}</span>
</td></tr>
{if isset($layout.item.description)}
<tr><td colspan="2">
<span class="giDescription">{$layout.item.description|markup}</span>
</td></tr>{/if}
</table></div
><div id="gsAlbumContents"
><table class="content" cellspacing="0">
{foreach from=$layout.children key=i item=it}
 {if ($i is even)}<tr>{/if}
 <td class="i">
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:ShowItem"
          arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:DownloadItem"
          arg2="itemId=`$it.image.id`"
          arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <a id="info_{$it.imageIndex}" href="{g->url arg1="view=core:ShowItem"
        arg2="itemId=`$it.id`" arg3="detail=1"}"></a>
    {capture name="link"}<a href="" onclick="image_show({$it.imageIndex});return false">{/capture}
    {if isset($it.thumbnail) && isset($layout.frame) && isset($layout.params.imageFrame)}
      {include file=$layout.frame.template ImageFrame_data=$layout.frame.data
       ImageFrame_frame=$layout.params.imageFrame item=$it image=$it.thumbnail
       ImageFrame_pre=$smarty.capture.link ImageFrame_post="</a>"}
    {else}
      {$smarty.capture.link}
      {if isset($it.thumbnail)}
        {g->image item=$it image=$it.thumbnail class=thumb}
      {else} {g->text text="no thumbnail"} {/if}
      </a>
    {/if}
  {elseif ($it.canContainChildren)}
    {capture name="link"}<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$it.id`"}">{/capture}
    {if isset($it.thumbnail) && isset($layout.frame) && isset($layout.params.albumFrame)}
      {include file=$layout.frame.template ImageFrame_data=$layout.frame.data
       ImageFrame_frame=$layout.params.albumFrame item=$it image=$it.thumbnail
       ImageFrame_pre=$smarty.capture.link ImageFrame_post="</a>"}
    {else}
      {$smarty.capture.link}
      {if isset($it.thumbnail)}
        {g->image item=$it image=$it.thumbnail class=thumb}
      {else} {g->text text="no thumbnail"} {/if}
      </a>
    {/if}
  {else}
    <a href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$it.id`"}">
    {if isset($it.thumbnail)}
      {g->image item=$it image=$it.thumbnail class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </a>
  {/if}
 </td>
 <td class="t"><table class="text"><tr><td><span class="title">
  {if isset($it.image) || isset($it.itemLinks)}
   <span style="float:right;margin-left:2px"><img src="{$layout.layoutUrl}/images/menu.png" class="vis" width="18" height="18" alt="Item Actions" title="Item Actions" onclick="popup_menu(event,{$i}
    {if isset($it.image)},{$it.imageIndex})" /></span>
      <span id="title_{$it.imageIndex}" class="giTitle">
    {else},-1)" /></span><span class="giTitle">{/if}
  {else}<span class="giTitle">{/if}
  {$it.title|default:$it.pathComponent|markup}</span></span></td>
  </tr><tr>
  <td><span class="giDescription" {if isset($it.image)}id="text_{$it.imageIndex}"{/if}>
  {if isset($it.summary)}{$it.summary|markup}<br />{/if}
  {$it.description|markup}</span></td></tr></table>
  {if isset($it.itemLinks)}
   <span id="links_{$i}" style="position:absolute;visibility:hidden;top:0px">
   {foreach from=$it.itemLinks item=link}
    <a href="{$link.url}">{$link.text}</a><br />
   {/foreach}
   </span>
  {/if}
 </td>
 {if ($i is odd)}</tr>{/if}
{/foreach}
{if count($layout.children) is odd}<td></td><td></td></tr>{/if}
</table></div></div>

{capture name="sidebarInsert_2"}
  <div class="gbMenu">
    <h3 class="giTitle"> {g->text text="Display Options"} </h3>
    <ul>
      <li>
	<a id="dtl_link" href="" onclick="album_detailsonoff();this.blur();return false">{g->text text="hide details"}</a>
      </li>
      <li>
	<a id="lnk_link" href="" onclick="album_itemlinksonoff();this.blur();return false">{g->text text="hide item links"}</a>
      </li>
    </ul>
    <ul style="margin-top:4px">
      <li>
        <strong>{g->text text="Slideshow Options"}:</strong>
      </li>
      <li>
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
      </li>
    </ul>
  </div>
{/capture}
{capture name="sidebarInsert_3"}
  <div class="gbMenu">
    <ul><li>
      <a href="http://validator.w3.org/check?uri={$main.validationUri}&amp;ss=1"><img style="border: 0px"
         src="{g->url href="images/xhtml10.png"}"
         alt="{g->text text="This page is valid XHTML 1.0"}"
         height="15" width="80" /></a>
    </li><li>
      <a href="http://gallery.sourceforge.net"><img style="border: 0px"
         src="{g->url href="images/gallery.gif"}"
         alt="{g->text text="Gallery %s" arg1=$main.gallery.version}"
         height="15" width="80" /></a>
    </li></ul>
  </div>
{/capture}
<div id="sidebar">{include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}</div>
<div id="image" style="visibility:hidden" onclick="image_vis(0)"
><div id="image_view"></div></div

><div id="toolbar" style="visibility:hidden"><div id="tools_left"
><img id="text_on" src="{$layout.layoutUrl}/images/up.png" width="18" height="18" class="on" onclick="text_onoff()" alt="Show text" title="Show text"
/><img id="text_off" src="{$layout.layoutUrl}/images/down.png" width="18" height="18" class="off" onclick="text_onoff()" alt="Hide text" title="Hide text"
/><img src="{$layout.layoutUrl}/images/alb.png" width="18" height="18" class="on" onclick="image_vis(0)" alt="Back to Album View" title="Back to Album View"
/><img id="slide_poz" src="{$layout.layoutUrl}/images/poz.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Pause Slideshow" title="Pause Slideshow"
/><img id="slide_fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img id="slide_rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/><img id="slide_rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
/></div><div id="tools_right"
><img id="full_size" src="{$layout.layoutUrl}/images/full.png" width="18" height="18" class="off" onclick="image_zoom(1)" alt="Full Size" title="Full Size"
/><img id="fit_size" src="{$layout.layoutUrl}/images/fit.png" width="18" height="18" class="off" onclick="image_zoom(0)" alt="Fit Size" title="Fit Size"
/><img src="{$layout.layoutUrl}/images/info.png" width="18" height="18" class="on" onclick="popup_info(-1)" alt="Item Details" title="Item Details"
/><img id="prev_off" src="{$layout.layoutUrl}/images/prev-off.png" width="18" height="18" class="off" alt="No Previous Image" title="No Previous Image"
/><img id="prev_img" src="{$layout.layoutUrl}/images/prev.png" width="18" height="18" class="on" onclick="image_prev()" alt="Previous Image" title="Previous Image"
/><img id="next_off" src="{$layout.layoutUrl}/images/next-off.png" width="18" height="18" class="off" alt="No Next Image" title="No Next Image"
/><img id="next_img" src="{$layout.layoutUrl}/images/next.png" width="18" height="18" class="on" onclick="image_next()" alt="Next Image" title="Next Image"
/></div><div id="title" class="giTitle"></div></div

><div id="text" style="visibility:hidden"></div

><iframe id="popup" frameborder="0" style="visibility:hidden"></iframe
><div id="popup_titlebar" style="visibility:hidden"
><div style="float:right;margin-left:2px"><img src="{$layout.layoutUrl}/images/down.png" width="18" height="18" onclick="popup_vis(0)" alt="" /></div
>Item Details</div

><div id="popup_menu" onmouseover="clearTimeout(popup_timer)"
 onmouseout="popup_timer=setTimeout('ui_vis(\'popup_menu\',0)',1000)"
><div id="popup_links" onclick="ui_vis('popup_menu',0)"></div></div

><script type="text/javascript">app_init();</script>

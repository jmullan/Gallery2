<div id="album"
><div id="album_titlebar"
><div id="album_tools"><img name="sidebar_max" src="{$layout.layoutUrl}/images/right.png" width="18" height="18" class="off" onclick="sidebar_onoff()" alt="Show sidebar" title="Show sidebar"
><img name="slide__fwd" src="{$layout.layoutUrl}/images/fwd.png" width="18" height="18" class="on" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide__rev" src="{$layout.layoutUrl}/images/rev.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
><img name="slide__rand" src="{$layout.layoutUrl}/images/rand.png" width="18" height="18" class="off" onclick="slide_onoff()" alt="Start Slideshow" title="Start Slideshow"
></div>{$layout.title|markup}<div id="album_details"
>{if isset($layout.item.summary)}{$layout.item.summary|markup}<br>{/if}
{$layout.item.description|markup}</div></div
><div id="album_content"
><table class="content" cellspacing="0">
{foreach from=$layout.itemList key=i item=it}
 {if ($i is even)}<tr>{/if}
 <td class="i">
  {if isset($it.image)}
    {g->link id="img_`$it.imageIndex`" arg1="view=core:DownloadItem"
        arg2="itemId=`$it.image.id`"
        arg3="serialNumber=`$it.image.serialNumber`"}{/g->link}
    {g->link id="info_`$it.imageIndex`" arg1="view=core:ShowItem"
        arg2="itemId=`$it.id`"}{/g->link}
    <a href="" onclick="image_show({$it.imageIndex});return false">
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </a>
  {elseif ($it.isContainer)}
    {g->link arg1="view=core:ShowItem" arg2="itemId=`$it.id`"}
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    {/g->link}
  {else}
    {g->link arg1="view=core:DownloadItem" arg2="itemId=`$it.id`"}
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    {/g->link}
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
  {if isset($it.data.summary)}{$it.data.summary|markup}<br>{/if}
  {$it.data.description|markup}</span></td></tr></table>
  {if isset($it.moduleItemLinks)}
   <span id="links_{$i}" style="position:absolute;visibility:hidden;top:0px">
   {foreach from=$it.moduleItemLinks item=link}
    {g->link params=$link.params}{$link.text}{/g->link}<br>
   {/foreach}
   </span>
  {/if}
 </td>
 {if ($i is odd)}</tr>{/if}
{/foreach}
{if ($layout.count is odd)}<td></td><td></td></tr>{/if}
</table></div></div

><div id="sidebar"
><div id="sidebar_min"
><img src="{$layout.layoutUrl}/images/left.png" width="18" height="18" onclick="sidebar_onoff()" alt="Hide sidebar" title="Hide sidebar"></div>
{g->sidebar side="right"}
  {* Module links *}
  {g->box style="sidebar"}
    {g->title}
      <noscript><br>{g->error}
	{g->text text="Warning: This site requires javascript."}
      {/g->error}<br></noscript>
      {g->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
    {/g->title}
    {g->listing}
      {foreach from=$layout.moduleSystemLinks item=module}
	{foreach from=$module item=link}
	  {g->item}
	    {g->title}
	      {g->link params=$link.params}{$link.text}{/g->link}
	    {/g->title}
	  {/g->item}
	{/foreach}
      {/foreach}
    {/g->listing}
  {/g->box}
  {* Modules system content *}
  {foreach from=$layout.moduleSystemContentFiles key=moduleId item=moduleFile}
    {if ($moduleId != 'core')}
      {g->box style="sidebar"}
	{include file=$moduleFile l10Domain="modules_$moduleId"}
      {/g->box}
    {/if}
  {/foreach}
  {* Breadcrumb *}
  {if (count($layout.parents)>0)}
    {g->box style="sidebar"}
      {g->title} {g->text text="Navigation"} {/g->title}
      {g->listing}
	{foreach from=$layout.parents item=parent}
	  {g->item}{g->title}
	    &raquo;
	    {g->link arg1="view=core:ShowItem" arg2="itemId=`$parent.id`"}
	      {$parent.title|default:$parent.pathComponent|markup}
	    {/g->link}
	  {/g->title}{/g->item}
	{/foreach}
      {/g->listing}
    {/g->box}
  {/if}
  {* Album links *}
  {g->box style="sidebar"}
    {g->title} {g->text text="Album"} {/g->title}
    {g->listing}
      {g->item}{g->title}
	{g->link id="dtl_link" href="" onclick="album_detailsonoff();this.blur();return false"}{g->text text="hide details"}{/g->link}
      {/g->title}{/g->item}
      {g->item}{g->title}
	{g->link id="lnk_link" href="" onclick="album_itemlinksonoff();this.blur();return false"}{g->text text="hide item links"}{/g->link}
      {/g->title}{/g->item}
      {foreach from=$layout.moduleItemLinks item=link}
	{g->item}{g->title}
	  {g->link params=$link.params}{$link.text}{/g->link}
	{/g->title}{/g->item}
      {/foreach}
    {/g->listing}
  {/g->box}
  {* Slideshow options *}
  {g->box style="sidebar"}
    {g->title}
      {g->text text="Slideshow&nbsp;Options"}
    {/g->title}
    {g->listing}{g->item}{g->title}
	{g->text text="delay"}:
	<select id="slide_delay" onchange="slide_setdelay(this.value)">
	 <option value="3">{g->text text="3 seconds"}
	 <option selected value="5">{g->text text="5 seconds"}
	 <option value="7">{g->text text="7 seconds"}
	 <option value="10">{g->text text="10 seconds"}
	 <option value="15">{g->text text="15 seconds"}
	 <option value="20">{g->text text="20 seconds"}
	</select> <br>
	{g->text text="direction"}:
	<select id="slide_order" onchange="slide_setorder(this.value)">
	 <option selected value="1">{g->text text="forward"}
	 <option value="-1">{g->text text="reverse"}
	 <option value="0">{g->text text="random"}
	</select> <br>
    {/g->title}{/g->item}{/g->listing}
  {/g->box}
  {g->box style="sidebar"}
    {g->title}&nbsp;{/g->title}
    {g->listing}{g->item}{g->title}
      <a href="http://validator.w3.org/check/referer"><img border="0"
         src="{g->url href="images/html401.gif"}"
         alt="{g->text text="This page is valid HTML 4.01"}"
         title="{g->text text="This page is valid HTML 4.01"}"
         height="15" width="80"></a>
    {/g->title}{/g->item}{g->item}{g->title}
      <a href="http://gallery.sourceforge.net"><img border="0"
         src="{g->url href="images/gallery.gif"}"
         alt="{g->text text="Gallery %s" arg1=$main.gallery.version}"
         title="{g->text text="Gallery %s" arg1=$main.gallery.version}"
         height="15"
         width="80"></a>
    {/g->title}{/g->item}{/g->listing}
  {/g->box}
{/g->sidebar}
</div

><div id="image" style="visibility:hidden" onclick="image_vis(0)"
><span id="image_view"></span></div

><div id="toolbar" style="visibility:hidden"><div id="tools_left"
><img name="text_on" src="{$layout.layoutUrl}/images/up.png" width="18" height="18" class="on" onclick="text_onoff()" alt="Show text" title="Show text"
><img name="text_off" src="{$layout.layoutUrl}/images/down.png" width="18" height="18" class="off" onclick="text_onoff()" alt="Hide text" title="Hide text"
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
></div><div id="title"></div
><img name="textspace" width="0" height="0" src="" alt=""></div

><div id="text" style="visibility:hidden"></div

><iframe id="popup" frameborder="0" style="visibility:hidden"></iframe
><div id="popup_titlebar" style="visibility:hidden"
><div style="float:right;margin-left:2px"><img src="{$layout.layoutUrl}/images/down.png" width="18" height="18" onclick="popup_vis(0)" alt=""></div
>Item Details</div

><div id="popup_menu" onmouseover="clearTimeout(popup_timer)"
 onmouseout="popup_timer=setTimeout('ui_vis(\'popup_menu\',0)',1000)"
><div id="popup_links" onclick="ui_vis('popup_menu',0)"></div></div

><script type="text/javascript">app_init();</script>

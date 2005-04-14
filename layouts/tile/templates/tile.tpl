{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{include file="gallery:layouts/matrix/templates/pathbar.tpl" l10Domain="layouts_matrix"}

<table border="0" cellspacing="0" cellpadding="0">
<tr valign="top"><td id="gsSidebarCol">
  {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}
</td><td id="gsContent">

<noscript><p class="giError">
  {g->text text="Warning: This site requires javascript."}
</p></noscript>

<div style="display: none">
{foreach from=$layout.children key=i item=it}
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:ShowItem"
       arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:DownloadItem"
       arg2="itemId=`$it.image.id`" arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <span id="title_{$it.imageIndex}">{$it.title|markup}</span>
  {/if}
{/foreach}
</div>

<div id="image" class="gcBackground1" onclick="ui_vis('image',0)">
  <div class="gbBlock gcBackground2">
    <p id="title" class="giTitle"></p>
  </div>
  <div id="image_view"></div>
</div>

<div class="gbBlock gcBackground2">
  <p class="giTitle">{$layout.item.title|markup}</p>
</div>

<div class="gbBlock">
{if isset($layout.params.bgSerialNumber)}
  <table id="tile" style="background-image:url({g->url arg1="view=core:DownloadItem" arg2="itemId=`$layout.params.backgroundId`" arg3="serialNumber=`$layout.params.bgSerialNumber`"})" cellspacing="0">
  {section name=row loop=$layout.map}
   <tr>
   {section name=col loop=$layout.map[row]}
    <td>
    {assign var="id" value=$layout.map[row][col]}
    {if $id>0}
      {assign var="it" value=$layout.itemMap[$id]}
      <a href="#" onclick="image_show({$it.imageIndex});return false">
	{g->image item=$it image=$it.thumbnail class=thumb}
      </a>
    {else}
      <div class="emptyTile"></div>
    {/if}
    </td>
   {/section}
  </tr>
  {/section}
  </table>
{else}
  {g->text text="The layout has not been"}
  <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemEdit" arg3="editPlugin=ItemEditLayout" arg4="itemId=`$layout.item.id`"}">
    {g->text text="configured."}
  </a>
{/if}
</div>
</td></tr></table>

<script type="text/javascript">app_init();</script>

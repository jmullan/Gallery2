{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsContents">
{include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}

<div id="gsAlbumContents">
<noscript><p class="giError">
  {g->text text="Warning: This site requires javascript."}
</p></noscript>

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
    <span id="title_{$it.imageIndex}">{$it.title|markup}</span>
  {/if}
{/foreach}
</div>

<div id="image" style="visibility:hidden;overflow:hidden" onclick="ui_vis('image',0,1)">
  <div id="title" class="giTitle"></div>
  <span id="image_view"></span>
</div>

<div class="giTitle">{$layout.item.title|markup}</div>

{if isset($layout.params.bgSerialNumber)}
<table id="tile" style="background-image:url({g->url arg1="view=core:DownloadItem" arg2="itemId=`$layout.params.backgroundId`" arg3="serialNumber=`$layout.params.bgSerialNumber`"})" cellspacing="0">
{section name=row loop=$layout.map}
 <tr>
 {section name=col loop=$layout.map[row]}
  <td>
  {assign var="id" value=$layout.map[row][col]}
  {if $id>0}
    {assign var="it" value=$layout.itemMap[$id]}
    <a href="" onclick="image_show({$it.imageIndex});return false">
      {g->image item=$it image=$it.thumbnail class=thumb}
    </a>
  {else}
    <div class="empty"></div>
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
</div>

<script type="text/javascript">app_init();</script>

{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to hybrid.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{include file="gallery:layouts/tile/templates/sidebar.tpl"}

<noscript><p class="giError">
  {g->text text="Warning: This site requires javascript."}
</p></noscript>

<div style="position:absolute;visibility:hidden;left:0px">
{foreach from=$layout.itemList key=i item=it}
  {if isset($it.image)}
    {if isset($it.renderItem)}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:ShowItem"
          arg2="itemId=`$it.id`" arg3="renderId=`$it.image.id`"}"></a>
    {else}
      <a id="img_{$it.imageIndex}" href="{g->url arg1="view=core:DownloadItem"
          arg2="itemId=`$it.image.id`"
          arg3="serialNumber=`$it.image.serialNumber`"}"></a>
    {/if}
    <span id="title_{$it.imageIndex}">{$it.data.title|markup}</span>
  {/if}
{/foreach}
</div>

<div id="image" style="visibility:hidden;overflow:hidden" onclick="ui_vis('image',0,1)">
  <div id="title" class="giTitle"></div>
  <span id="image_view"></span>
</div>

<div class="giTitle">{$layout.title|markup}</div>

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
      {g->image item=$it.data image=$it.thumb class=thumb}
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
  {g->text text="The layout has not been configured."}
{/if}

<script type="text/javascript">app_init();</script>

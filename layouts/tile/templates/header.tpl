{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to header.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<title>
  {$layout.item.title|default:$layout.item.pathComponent|markup:stripBbcodeAndHtml}
</title>
<link rel="stylesheet" type="text/css" href="{$layout.layoutUrl}/templates/tile.css" />
{g->style}
<script type="text/javascript">
{if $layout.imageCount==1}
var image_width = new Array(1); image_width[0] = {$layout.imageWidths};
var image_height = new Array(1); image_height[0] = {$layout.imageHeights};
{else}
var image_width = new Array({$layout.imageWidths});
var image_height = new Array({$layout.imageHeights});
{/if}
var name = '{$layout.item.id}';
var view = {$layout.viewIndex|default:-1};
var path = '{$layout.cookiePath}';
</script>
<script type="text/javascript" src="{$layout.layoutUrl}/templates/tile.js"></script>
<style type="text/css">
div.empty {ldelim} width:{$layout.params.cellWidth}px; height:{$layout.params.cellHeight}px {rdelim}
td img {ldelim} display:block {rdelim}
</style>

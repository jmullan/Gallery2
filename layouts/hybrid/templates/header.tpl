<title>{$layout.title|markup}</title>
<link rel="stylesheet" type="text/css" href="{$layout.layoutUrl}/templates/hybrid.css" />
{g->style}
<script type="text/javascript">
{if $layout.imageCount==1}
var data_iw = new Array(1); data_iw[0] = {$layout.imageWidths};
var data_ih = new Array(1); data_ih[0] = {$layout.imageHeights};
{else}
var data_iw = new Array({$layout.imageWidths});
var data_ih = new Array({$layout.imageHeights});
{/if}
var data_count = data_iw.length, data_name = '{$layout.item.id}';
var data_view = {$layout.viewIndex|default:-1};
var app_path = '{$layout.cookiePath}';
</script>
<script type="text/javascript" src="{$layout.layoutUrl}/templates/hybrid.js"></script>

{if isset($ShowItem.layoutHeadFile)}
  {include file=$ShowItem.layoutHeadFile l10Domain=$ShowItem.layoutL10Domain}
{else}
<title>
  {$ShowItem.item.title|default:$ShowItem.item.pathComponent|markup}
</title>
{g->style}
{/if}

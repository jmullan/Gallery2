{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ShowItemHead.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if isset($ShowItem.layoutHeadFile)}
  {include file="gallery:`$ShowItem.layoutHeadFile`" l10Domain=$ShowItem.layoutL10Domain}
{else}
<title>
  {$ShowItem.item.title|default:$ShowItem.item.pathComponent|markup}
</title>
{g->style}
{/if}

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if isset($ShowItem.layoutHeadFile)}
  {include file="gallery:`$ShowItem.layoutHeadFile`" l10Domain=$ShowItem.layoutL10Domain}
{else}
<title>
  {$ShowItem.item.title|default:$ShowItem.item.pathComponent|markup}
</title>
{g->style}
{/if}

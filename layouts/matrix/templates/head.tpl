{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<title>
  {$layout.item.title|default:$layout.item.pathComponent|markup:stripBbcodeAndHtml}
</title>
<style type="text/css" media="all">@import url({$layout.layoutUrl}/layout.css.php);</style>
{g->style}
{if isset($layout.albumFrame) || isset($layout.itemFrame) || isset($layout.photoFrame)}
  {imageframe_style}
{/if}

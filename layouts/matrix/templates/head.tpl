{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to head.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<title>
  {$layout.title|markup:stripBbcodeAndHtml}
</title>
<style type="text/css" media="all">@import url({$layout.layoutUrl}/layout.css);</style>
{g->style}
{if isset($layout.frame)}
  {include file=$layout.frame.style ImageFrame_data=$layout.frame.data}
{/if}

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if isset($head.title)}<title>{$head.title}</title>{/if}
{foreach from=$head.tpl key=tpl item=l10Domain}
  {include file="gallery:`$tpl`" l10Domain=$l10Domain}
{/foreach}
{g->style}

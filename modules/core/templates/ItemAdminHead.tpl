{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<title>
  {g->text text="Gallery Item Administration"}
</title>
{if !empty($ItemAdmin.viewHeadFile)}
{include file="gallery:`$ItemAdmin.viewHeadFile`" l10Domain=$ItemAdmin.viewL10Domain}
{/if}
{g->style}

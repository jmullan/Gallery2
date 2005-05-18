{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gallery"{if $main.isRightToLeft} style="direction:rtl"{/if}>
  {* Content that G2 wants to display inside the <body> element *}
  {include file="gallery:`$main.viewBodyFile`" l10Domain=$main.viewL10Domain}

  <div id="gsFooter">
    <a href="http://validator.w3.org/check?uri={$main.validationUri}&amp;ss=1"><img
       src="{g->url href="images/xhtml10.png"}"
       alt="{g->text text="This page is valid XHTML 1.0"}"
       style="border: none" width="80" height="15"/></a>
    <a href="http://gallery.sourceforge.net"><img
       src="{g->url href="images/gallery.gif"}"
       alt="{g->text text="Gallery %s" arg1=$main.gallery.version}"
       style="border: none" width="80" height="15"/></a>
  </div>
</div>

{* If debugging or profiling is enabled, we'll display it here *}
{if isset($main.debug) || isset($main.profile)}
  {include file="gallery:templates/debug.tpl" fetchDebug=true}
{/if}

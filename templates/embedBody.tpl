{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to embedBody.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gallery"{if $main.isRightToLeft} style="direction:rtl"{/if}>
  {* Content that G2 wants to display inside the <body> element *}
  {include file="gallery:`$main.viewBodyFile`" l10Domain=$main.viewL10Domain}

  <div id="gsFooter">
    <a href="http://validator.w3.org/check?uri={$main.validationUri}&amp;ss=1"><img style="border: 0px"
       src="{g->url href="images/xhtml10.png"}"
       alt="{g->text text="This page is valid XHTML 1.0"}" 
       height="15" width="80"/></a>
    <a href="http://gallery.sourceforge.net"><img style="border: 0px"
       src="{g->url href="images/gallery.gif"}"
       alt="{g->text text="Gallery %s" arg1=$main.gallery.version}"
       height="15"  
       width="80"/></a>
  </div>
</div>

{* If debugging or profiling is enabled, we'll display it here *}
{if isset($main.debug) || isset($main.profile)}
  {include file="gallery:templates/debug.tpl"}
{/if}

{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{*
 * This is the master template for G2.  Every page will be rendered using
 * this file, so if you make changes here, they'll apply everywhere.
 *
 * Blocks inside {curly brackets} are callbacks to the Smarty
 * templating engine so you should handle those with care.  We've put
 * comments in below explaining what they are to help you figure out
 * how to safely make changes.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    {* This should help out users whose browsers are confused about the character set *}
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>

    {* Content that G2 wants to display inside the <head> element *}
    {if isset($head.title)}<title>{$head.title}</title>{/if}
    {foreach from=$head.tpl key=tpl item=l10Domain}
      {include file="gallery:`$tpl`" l10Domain=$l10Domain}
    {/foreach}
    {g->style}
  </head>
  <body>
    <div id="gallery"{if $main.isRightToLeft} style="direction:rtl"{/if}>
      <div id="gsHeader">
        <img src="{g->url href="images/galleryLogo_sm.gif"}" alt="" />
      </div>

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
	  title="{g->text text="Gallery %s" arg1=$main.gallery.version}"
	  style="border: none" width="80" height="15"/></a>

        <a href="http://www.google.com/search?q=&quot;Gallery+2+-+Beta+1&quot;"><img
                style="border: 0px"
                src="{g->url href="modules/core/data/g2b1-dark_fibre.png"}"
                alt="{g->text text="Gallery 2 - Beta 1: Dark Fibre"}"
                height="15"
                width="80"/></a>
      </div>
    </div>

    {* If debugging or profiling is enabled, we'll display it here *}
    {if isset($main.debug) || isset($main.profile)}
      {include file="gallery:templates/debug.tpl"}
    {/if}
  </body>
</html>

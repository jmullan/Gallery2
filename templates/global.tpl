{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to global.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *
 * This is the master template for G2.  Every page will be rendered in
 * this format.  If you want to change the look and feel of G2, you
 * can copy this file to global.tpl.local then customize it any way
 * that you choose.
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

    {* We're experimenting with Dean Edward's IE7 patch:  http://dean.edwards.name/IE7 *}
    <!-- compliance patch for microsoft browsers -->
    <!--[if lt IE 7]>
    <script src="{g->url href="lib/IE7/ie7-core.js"}" type="text/javascript"></script>
    <script src="{g->url href="lib/IE7/ie7-html4.js"}" type="text/javascript"></script>
    <script src="{g->url href="lib/IE7/ie7-css2.js"}" type="text/javascript"></script>
    <script src="{g->url href="lib/IE7/ie7-fixed.js"}" type="text/javascript"></script>
    <script src="{g->url href="lib/IE7/ie7-css3.js"}" type="text/javascript"></script>
    <![endif]-->

    {* Content that G2 wants to display inside the <head> element *}
    {include file="gallery:`$main.viewHeadFile`" l10Domain=$main.viewL10Domain}
  </head>
  <body>
    <div id="gallery">
      <div id="gsHeader">
        <img src="{g->url href="images/galleryLogo_sm.gif"}" alt="" />
      </div>

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
  </body>
</html>

{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to global.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if isset($main.viewMainFile)}
{include file="gallery:`$main.viewMainFile`" l10Domain=$main.viewL10Domain}
  {if isset($main.debug)}
    <div id="gpDebug">
      {include file="gallery:templates/debug.tpl"}
    </div>
  {/if}
{else}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
    <head>
      {include file="gallery:`$main.viewHeadFile`" l10Domain=$main.viewL10Domain}
    </head>
    <body
    {if isset($main.onLoad)}
    onload="{$main.onLoad}"
    {/if}
    {if isset($main.onUnload)}
    onunload="{$main.onUnload}"
    {/if}>

    <div id="gallery">
      {include file="gallery:`$main.viewBodyFile`" l10Domain=$main.viewL10Domain}

      <div id="gsFooter">
	<a href="http://validator.w3.org/check?uri={$main.validationUri}&amp;ss=1"><img style="border: 0px"
	    src="{g->url href="images/xhtml10.png"}"
	    alt="{g->text text="This page is valid XHTML 1.0"}" 
	    height="15" width="80"/></a>
	
	<a href="http://gallery.sourceforge.net"><img style="border: 0px"
	    src="{g->url href="images/gallery.gif"}"
	    alt="{g->text text="Powered by Gallery %s" arg1=$main.gallery.version}"
	    height="15"  
	    width="80"/></a>
      </div>
    </div>

    {if isset($main.debug)}
    <div id="gpDebug">
      {include file="gallery:templates/debug.tpl"}
    </div>
    {/if}
  </body>
</html>
{/if}

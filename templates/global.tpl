<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  {if isset($main.viewMainFile)}
    {include file=$main.viewMainFile l10Domain=$main.viewL10Domain}
    {if isset($main.debug)}
      {include file="templates/debug.tpl"}
    {/if}
  {else}
    <head>
      {include file=$main.viewHeadFile l10Domain=$main.viewL10Domain}
    </head>
    <body
    {if isset($main.onLoad)}
    onload="{$main.onLoad}"
    {/if}
    {if isset($main.onUnload)}
    onunload="{$main.onUnload}"
    {/if}>

    <div id="gallery">
      {include file=$main.viewBodyFile l10Domain=$main.viewL10Domain}

      <div id="gsFooter">
	<a href="http://validator.w3.org/check/referer"><img style="border: 0px"

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
      {include file="templates/debug.tpl"}
    </div>
    {/if}
  </body>
  {/if}
</html>

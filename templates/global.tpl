<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
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
    <body{if isset($main.onLoad)} onload="{$main.onLoad}"{/if
         }{if isset($main.onUnload)} onunload="{$main.onUnload}"{/if}>
      {include file=$main.viewBodyFile l10Domain=$main.viewL10Domain}

      <br />

      <a href="http://validator.w3.org/check/referer"><img border="0" 
         src="{g->url href="images/html401.gif"}"
         alt="{g->text text="This page is valid HTML 4.01"}" 
         height="15" width="80"></a>

      <a href="http://gallery.sourceforge.net"><img border="0" 
	 src="{g->url href="images/gallery.gif"}"
         alt="{g->text text="Powered by Gallery %s" arg1=$main.gallery.version}"
         height="15"  
         width="80"></a>

      {if isset($main.debug)}
	{include file="templates/debug.tpl"}
      {/if}
    </body>
  {/if}
</html>

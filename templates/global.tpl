<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
      {include file=$main.viewHeadFile l10Domain=$main.viewL10Domain}
  </head>
  <body>
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

      {if isset($main.profile)}
	{include file="templates/profile.tpl"}
      {/if}
  </body>
</html>

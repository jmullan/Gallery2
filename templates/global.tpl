<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
      {include file=$main.viewHeadFile l10domain=$main.viewL10Domain}
  </head>
  <body>
      {gallery->globalheader}
	{gallery->text text="Gallery 2"}
      {/gallery->globalheader}

      {include file=$main.viewBodyFile l10domain=$main.viewL10Domain}

      {gallery->globalfooter}
	<a href="http://validator.w3.org/check/referer"><img border="0" 
	   src="{gallery->url href="images/html401.gif"}"
           alt="{gallery->text text="This page is valid HTML 4.01"}" 
           height="15" width="80"></a>

	<a href="http://gallery.sourceforge.net"><img border="0" 
	   src="{gallery->url href="images/gallery.gif"}"
           alt="{gallery->text text="Powered by Gallery %s" arg1=$main.gallery.version}"
           height="15"  
           width="80"></a>
      {/gallery->globalfooter}

      {if isset($main.debug)}
	{include file="templates/debug.tpl"}
      {/if}

      {if isset($main.profile)}
	{include file="templates/profile.tpl"}
      {/if}
  </body>
</html>

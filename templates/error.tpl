<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>
      {gallery->text text="Error"}
    </title>
  </head>
  <body>
      {$main.error}

      {if isset($main.debug)}
	{include file="debug.tpl"}
      {/if}

      {if isset($main.profile)}
	{include file="profile.tpl"}
      {/if}
  </body>
</html>

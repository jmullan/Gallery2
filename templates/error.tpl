<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>
      {g->text text="Error"}
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

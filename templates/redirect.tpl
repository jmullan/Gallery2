{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{*
 * This template is only used for debugging purposes.  When G2 redirects
 * you to a new page, sometimes the developers want to see the debug output 
 * from the code that generated the redirect, so we have this intermediate
 * page that shows the debug output and a link you can click to complete
 * the redirect.  
 *
 * You shouldn't have to modify this page unless you're a G2 developer.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>
      {g->text text="Redirect"}
    </title>
    {g->style}
  </head>
  <body>
    {g->text text="You are in debug mode so we are not automatically redirecting."}
    <br/>
      <a href="{$main.redirectUrl}">[continue]</a>
      <br/>
	<font size="-1"><i>{$main.redirectUrl}</i></font>

	{if isset($main.debug)}
	{include file="gallery:templates/debug.tpl"}
      {/if}
  </body>
</html>

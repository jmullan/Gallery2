{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to error.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *
 * This is a special template that we use to display G2 errors.  This
 * should show up rarely (and will never show up when we fix the final
 * bug :-) )
 *}
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
	{include file="gallery:templates/debug.tpl"}
      {/if}

      {if isset($main.profile)}
	{include file="gallery:templates/profile.tpl"}
      {/if}
  </body>
</html>

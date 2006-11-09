{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if empty($item)}
  {assign var=item value=$theme.item}
{/if}

<div class="{$class}">
  <h3> {g->text text="WebDAV URL"} </h3>

  <div class="giDescription">
    <p> {g->text text="Open this album's %s URL with a %s client: " arg1="<a href=\"http://webdav.org/\"> WebDAV </a>" arg2="<a href=\"http://webdav.org/\"> WebDAV </a>"} <a href="{g->url arg1="controller=webdav.WebDav" arg2="itemId=`$item.id`" forceFullUrl=true}"> {g->url arg1="controller=webdav.WebDav" arg2="itemId=`$item.id`" forceFullUrl=true} </a> </p>
  </div>
</div>

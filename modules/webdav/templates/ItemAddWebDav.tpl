{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <div class="giDescription">
    <p> {g->text text="You can drag & drop items into Gallery by mounting it with a %s client" arg1="<a href=\"http://webdav.org/\"> WebDAV </a>"} </p>

    <p> {g->text text="Open this album's WebDAV URL with a WebDAV client: "} <a href="{g->url arg1="controller=webdav.WebDav" arg2="itemId=`$ItemAdmin.item.id`"}"> {g->url arg1="controller=webdav.WebDav" arg2="itemId=`$ItemAdmin.item.id`" forceFullUrl=true} </a> </p>
  </div>
</div>

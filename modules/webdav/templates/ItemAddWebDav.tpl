{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <div class="giDescription">
    <p>
      {g->text text="You can mount Gallery on your desktop with a WebDAV client.  You can then add items to Gallery by drag and drop.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s." arg1="<a href=\"http://codex.gallery2.org/index.php/Gallery2:Modules:webdav:user\">" arg2="</a>"}
    </p>

    <p>
      {g->text text="This album's WebDAV URL is:"} <a href="{g->url arg1="controller=webdav.WebDav" arg2="itemId=`$ItemAdmin.item.id`" forceFullUrl=true forceSessionId=false useAuthToken=false}"> {g->url arg1="controller=webdav.WebDav" arg2="itemId=`$ItemAdmin.item.id`" forceFullUrl=true forceSessionId=false useAuthToken=false} </a>
    </p>
  </div>
</div>
